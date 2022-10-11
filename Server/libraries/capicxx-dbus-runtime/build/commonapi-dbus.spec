Name:               libcommonapi-dbus
Version:            3.1.12
Release:            r0
Summary:            CommonAPI-DBus
Group:              libs
License:            MPLv2
Vendor:             BMW Group
URL:            	http://www.bmw.de
Source:             libcommonapi-dbus-3.1.12.tar.gz
BuildRoot:          %{_tmppath}/%{name}-%{version}-%{release}-root
#Requires:          libcommonapi

%description
CAPI-DBus for IPC

%package dev
Summary:           CommonAPI-DBus header files
Group:             Development/Libraries
Requires:          libcommonapi-dbus3

%package staticdev
Summary:           CommonAPI-DBus header files
Group:             Development/Libraries
Requires:          libcommonapi-dbus3


%description dev
CAPI-DBus headers for IPC development

%prep
mkdir -p %{_includedir}/CommonAPI-3.1/CommonAPI
%setup



%build
mkdir -p build
cd build
cmake ..
make

%install
rm -rf $RPM_BUILD_ROOT
cd build
cmake ..
make install DESTDIR=$RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{_bindir}
mkdir -p %{_includedir}/CommonAPI-3.1/CommonAPI


%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_libdir}/libCommonAPI-DBus.so.3
%{_libdir}/libCommonAPI-DBus.so.3.1.12
%{_libdir}/libCommonAPI-DBus.so

%files staticdev
#%{_libdir}/libCommonAPI-DBus.la

%files dev
%defattr(-,root,root,-)
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusAddress.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusAddressTranslator.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusAttribute.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusClientId.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusConfig.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusConnection.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusDaemonProxy.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusDeployment.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusError.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusEvent.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusFactory.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusFreedesktopAttribute.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusFreedesktopPropertiesStub.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusFreedesktopStubAdapterHelper.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusFreedesktopVariant.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusFunctionalHash.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusHelper.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusInputStream.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusInstanceAvailabilityStatusChangedEvent.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusInterfaceHandler.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusMainLoopContext.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusMessage.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusMultiEvent.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusObjectManager.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusObjectManagerStub.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusOutputStream.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusProxy.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusProxyAsyncCallbackHandler.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusProxyBase.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusProxyConnection.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusProxyHelper.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusProxyManager.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusSelectiveEvent.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusSerializableArguments.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusServiceRegistry.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusStubAdapter.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusStubAdapterHelper.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusTypeOutputStream.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusTypes.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/DBus/DBusUtils.hpp
%{_includedir}/CommonAPI-3.1/pugixml
%{_includedir}/CommonAPI-3.1/pugixml/pugiconfig.hpp
%{_includedir}/CommonAPI-3.1/pugixml/pugixml.hpp
%{_libdir}/cmake/CommonAPI-3.1.12/CommonAPI-DBusConfig.cmake
%{_libdir}/cmake/CommonAPI-3.1.12/CommonAPI-DBusConfigVersion.cmake
%{_libdir}/cmake/CommonAPI-3.1.12/CommonAPI-DBusTargets.cmake
%{_libdir}/cmake/CommonAPI-3.1.12/CommonAPI-DBusTargets-debug.cmake

%changelog dev
* Mon Mar 23 2015 Markus Freutsmiedl <Markus.Freutsmiedl@partner.bmw.de> 
- LIB_MAJOR_VERSION changed to LIBCOMMONAPI_MAJOR_VERSION
- LIB_MINOR_VERSION changed to LIBCOMMONAPI_MINOR_VERSION
- LIB_PATCH_VERSION changed to LIBCOMMONAPI_PATCH_VERSION
- files dev reworked

%changelog dev
* Wed Sep 3 2014 Markus Freutsmiedl <Markus.Freutsmiedl@partner.bmw.de> 
- files dev reworked

%changelog dev
* Tue Jun 03 2014 Markus Freutsmiedl <Markus.Freutsmiedl@partner.bmw.de> 
- Initial version
