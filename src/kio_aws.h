#ifndef KIO_AWS_H
#define KIO_AWS_H

#include <KIO/SlaveBase>

namespace KIO {
    class UDSEntry;
}

class KIO_AWS : public QObject, public KIO::SlaveBase
{
public:
    KIO_AWS(const QByteArray &protocol,
            const QByteArray &pool_socket,
            const QByteArray &app_socket);
    virtual ~KIO_AWS() override;

    void listDir(const QUrl &url) override;
    void setHost(const QString &host, quint16 port, const QString &user, const QString &pass) override;

private:
    void defaultUdsEntry(KIO::UDSEntry& target);

};

#endif // KIO_AWS_H
