#include "kio_aws.h"

#include <QCoreApplication>
#include <QDebug>

#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/core/Region.h>

#include "utils.h"

class KIOPluginForMetaData : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kio.slave.kioaws" FILE "kio_aws.json")
};

extern "C" Q_DECL_EXPORT int kdemain(int argc, char **argv)
{
    QCoreApplication app(argc, argv);   // needed for QSocketNotifier
    app.setApplicationName(QStringLiteral("kio_aws"));

    if (argc != 4) {
        fprintf(stderr, "Usage: kio_aws aws domain-socket1 domain-socket2\n");
        exit(-1);
    }

    KIO_AWS slave(argv[1], argv[2], argv[3]);
    slave.dispatchLoop();
    return 0;
}

KIO_AWS::KIO_AWS(const QByteArray &protocol, const QByteArray &pool_socket, const QByteArray &app_socket)
    : KIO::SlaveBase("s3aws", pool_socket, app_socket)
{
    Q_UNUSED(protocol);

    Aws::SDKOptions options;
    Aws::InitAPI(options);
}

KIO_AWS::~KIO_AWS()
{
    Aws::SDKOptions options;
    Aws::ShutdownAPI(options);
}

void KIO_AWS::setHost(const QString &host, quint16 port, const QString &user, const QString &pass)
{
    qDebug() << "Set host: " << host << port << user << pass;
}

void KIO_AWS::defaultUdsEntry(KIO::UDSEntry &target)
{
    target.clear();
    target.fastInsert(KIO::UDSEntry::UDS_NAME, QStringLiteral("."));
    target.fastInsert(KIO::UDSEntry::UDS_FILE_TYPE, S_IFDIR);
}

void KIO_AWS::listDir(const QUrl &url)
{
    qDebug() << "listDir" << url;
    KIO::UDSEntry udsEntry;
    QString bucketName = url.host();

    Aws::Client::ClientConfiguration clientConfiguration;
    clientConfiguration.region = Aws::Region::EU_CENTRAL_1;

    Aws::Auth::AWSCredentials simpleAwsCredential(toAwsString(url.userName()), toAwsString(url.password()));

    Aws::S3::S3Client s3_client(simpleAwsCredential, clientConfiguration);

    Aws::S3::Model::ListObjectsRequest objects_request;
    objects_request.WithBucket(toAwsString(bucketName));

    auto list_objects_outcome = s3_client.ListObjects(objects_request);
    if (list_objects_outcome.IsSuccess())
    {
        Aws::Vector<Aws::S3::Model::Object> object_list =
            list_objects_outcome.GetResult().GetContents();

        totalSize(object_list.size() + 1);

        for (auto const &s3_object : object_list)
        {
            udsEntry.clear();
            udsEntry.fastInsert(KIO::UDSEntry::UDS_NAME, s3_object.GetKey().c_str());
            udsEntry.fastInsert(KIO::UDSEntry::UDS_SIZE, s3_object.GetSize());
            listEntry(udsEntry);
        }

        defaultUdsEntry(udsEntry);
        listEntry(udsEntry);
    }
    else
    {
        error(KIO::ERR_INTERNAL_SERVER, QString::fromStdString(list_objects_outcome.GetError().GetMessage().c_str()));
    }

    finished();
}

#include "kio_aws.moc"
