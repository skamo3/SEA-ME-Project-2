!host_build {
    QMAKE_CFLAGS    += --sysroot=$$[QT_SYSROOT]
    QMAKE_CXXFLAGS  += --sysroot=$$[QT_SYSROOT]
    QMAKE_LFLAGS    += --sysroot=$$[QT_SYSROOT]
}
host_build {
    QT_ARCH = x86_64
    QT_BUILDABI = x86_64-little_endian-lp64
    QT_TARGET_ARCH = arm
    QT_TARGET_BUILDABI = arm-little_endian-ilp32-eabi-hardfloat
} else {
    QT_ARCH = arm
    QT_BUILDABI = arm-little_endian-ilp32-eabi-hardfloat
}
QT.global.enabled_features = shared cross_compile shared rpath c++11 c++14 c++17 c++1z c99 c11 thread future concurrent pkg-config signaling_nan
QT.global.disabled_features = framework appstore-compliant debug_and_release simulator_and_device build_all c++2a force_asserts separate_debug_info static
PKG_CONFIG_SYSROOT_DIR = /home/seame-four/rpi/sysroot
PKG_CONFIG_LIBDIR = /home/seame-four/rpi/sysroot/usr/lib/pkgconfig:/home/seame-four/rpi/sysroot/usr/share/pkgconfig:/home/seame-four/rpi/sysroot/usr/lib/arm-linux-gnueabihf/pkgconfig
QT_CONFIG += shared shared rpath release c++11 c++14 c++17 c++1z concurrent dbus reduce_exports stl
CONFIG += shared cross_compile shared release
QT_VERSION = 5.15.0
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 15
QT_PATCH_VERSION = 0
QT_GCC_MAJOR_VERSION = 7
QT_GCC_MINOR_VERSION = 4
QT_GCC_PATCH_VERSION = 1
QT_EDITION = OpenSource
