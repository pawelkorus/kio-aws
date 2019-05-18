project(kio-aws)
cmake_minimum_required(VERSION 3.0)

set(QT5_MIN_VERSION "5.12.0")
set(KF5_MIN_VERSION "5.10.0")

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

# Locate the AWS SDK for C++ package.
# Requires that you build with:
#   -DCMAKE_PREFIX_PATH=/path/to/sdk_install
find_package(AWSSDK REQUIRED COMPONENTS
    s3
)

include(FeatureSummary)
include(ECMGenerateHeaders)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    KIO
)

add_custom_target(useful_files DEPENDS ALL
    SOURCES
        Dockerfile
        README.md)

add_subdirectory(src)
