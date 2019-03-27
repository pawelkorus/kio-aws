include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

set(kio_aws_HEADER_FILES
    kio_aws.h
    utils.h
)

set(kio_aws_SRCS
    kio_aws.cpp
    ${kio_aws_HEADER_FILES}
)

kcoreaddons_add_plugin(kio_aws
    SOURCES ${kio_aws_SRCS}
    INSTALL_NAMESPACE kf5/kio)

target_link_libraries(kio_aws
    Qt5::Core
    KF5::KIOCore
    ${AWSSDK_LINK_LIBRARIES}
)

set_target_properties(kio_aws PROPERTIES OUTPUT_NAME "kioaws")
