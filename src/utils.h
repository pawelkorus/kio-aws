#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <aws/core/Aws.h>

static Aws::String toAwsString(const QString& qStr) {
    return Aws::String(qStr.toStdString().c_str(), qStr.toStdString().size());
}

#endif // UTILS_H
