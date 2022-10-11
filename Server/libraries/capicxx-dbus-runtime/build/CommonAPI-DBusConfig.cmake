# - Config file for the CommonAPI-DBus package
# It defines the following variables
#  COMMONAPI_DBUS_INCLUDE_DIRS - include directories for CommonAPI-DBus

# Compute paths
get_filename_component(COMMONAPI_DBUS_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(COMMONAPI_DBUS_INCLUDE_DIRS "/home/pi-chan/commonapi/capicxx-dbus-runtime/include")

# Our library dependencies (contains definitions for IMPORTED targets)
include("${COMMONAPI_DBUS_CMAKE_DIR}/CommonAPI-DBusTargets.cmake")

set(COMMONAPI_DBUS_VERSION 3.1.12)
set(COMMONAPI_DBUS_VERSION_STRING "3.1.12")
