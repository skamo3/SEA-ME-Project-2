cmake_minimum_required(VERSION 2.8)
project(CAN_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -latomic")
include_directories(
    src-gen
    libraries/capicxx-core-runtime/include
    libraries/capicxx-dbus-runtime/include
    libraries/dbus-1.10.10
)
link_directories(
    ~/workspace/Server/libraries/capicxx-core-runtime/build
    ~/workspace/Server/libraries/capicxx-dbus-runtime/build
    ~/workspace/Server/libraries/dbus-1.10.10/dbus/.libs
)
# Client execute file add
add_executable(IPCClient
	src-gen/v1/commonapi/IPCDBusProxy.cpp
	src-gen/v1/commonapi/IPCDBusDeployment.cpp
	srcs/IPCClient.cpp

	# libraries/src-gen/v1/commonapi/HelloWorldDBusProxy.cpp
	# libraries/src-gen/v1/commonapi/HelloWorldDBusDeployment
	# srcs/HelloWorldClient.cpp
)
target_link_libraries(IPCClient CommonAPI CommonAPI-DBus dbus-1)

# Server execute file add 
add_executable(IPCService
	src-gen/v1/commonapi/IPCDBusStubAdapter.cpp
	src-gen/v1/commonapi/IPCStubDefault.cpp
	src-gen/v1/commonapi/IPCDBusDeployment.cpp
	srcs/CANSocket.cpp
	srcs/utils.cpp
	srcs/IPCServer.cpp
	srcs/main.cpp

	# libraries/src-gen/v1/commonapi/HelloWorldDBusStubAdapter.cpp
	# libraries/src-gen/v1/commonapi/HelloWorldStubDefault
	# libraries/src-gen/v1/commonapi/HelloWorldDBusDeployment
	# srcs/HelloWorldService.cpp
	# srcs/HelloWorldStubImpl.cpp
)
target_link_libraries(IPCService CommonAPI CommonAPI-DBus dbus-1)