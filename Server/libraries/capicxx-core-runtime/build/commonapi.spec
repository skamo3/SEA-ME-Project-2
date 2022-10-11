Name:               libcommonapi
Version:            3.1.12
Release:            r0
Summary:            CommonAPI
Group:              libs
License:            MPLv2
Vendor:             BMW Group
URL:            	http://www.bmw.de
Source:             libcommonapi-3.1.12.tar.gz
BuildRoot:          %{_tmppath}/%{name}-%{version}-%{release}-root
#Requires:          libcommonapi

%description
CAPI middleware for IPC

%package dev
Summary:           CommonAPI header files
Group:             Development/Libraries
Requires:          libcommonapi3

%package staticdev
Summary:           CommonAPI header files
Group:             Development/Libraries
Requires:          libcommonapi3


%description dev
CAPI middleware headers for IPC development

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
%{_libdir}/libCommonAPI.so.3
%{_libdir}/libCommonAPI.so.3.1.12
%{_libdir}/libCommonAPI.so

%files staticdev
#%{_libdir}/libCommonAPI.la

%files dev
%defattr(-,root,root,-)
%{_includedir}/CommonAPI-3.1/CommonAPI
%{_includedir}/CommonAPI-3.1/CommonAPI/Address.hpp 
%{_includedir}/CommonAPI-3.1/CommonAPI/Attribute.hpp 
%{_includedir}/CommonAPI-3.1/CommonAPI/AttributeExtension.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/ByteBuffer.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/CommonAPI.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/ContainerUtils.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Deployable.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Deployment.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Enumeration.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Event.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Factory.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/IniFileReader.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/InputStream.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Logger.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/MainLoopContext.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/OutputStream.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Proxy.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/ProxyManager.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Runtime.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/SelectiveEvent.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/SerializableArguments.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Struct.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Stub.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/TypeOutputStream.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Types.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Utils.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Variant.hpp
%{_includedir}/CommonAPI-3.1/CommonAPI/Version.hpp
%{_libdir}/cmake/CommonAPI-3.1.12/CommonAPIConfig.cmake
%{_libdir}/cmake/CommonAPI-3.1.12/CommonAPIConfigVersion.cmake
%{_libdir}/cmake/CommonAPI-3.1.12/CommonAPITargets.cmake
%{_libdir}/cmake/CommonAPI-3.1.12/CommonAPITargets-relwithdebinfo.cmake

%changelog dev
* Fri Mar 20 2015 Markus Freutsmiedl <Markus.Freutsmiedl@partner.bmw.de> 
- LIB_MAJOR_VERSION changed to LIBCOMMONAPI_MAJOR_VERSION
- LIB_MINOR_VERSION changed to LIBCOMMONAPI_MINOR_VERSION
- LIB_PATCH_VERSION changed to LIBCOMMONAPI_PATCH_VERSION
- files dev reworked

%changelog dev
* Tue Sep 2 2014 Markus Freutsmiedl <Markus.Freutsmiedl@partner.bmw.de> 
- files dev reworked

%changelog dev
* Tue July 1 2014 Markus Freutsmiedl <Markus.Freutsmiedl@partner.bmw.de> 
- LIB_MAJOR_VERSION, LIB_MINOR_VERSION and LIB_PATCH_VERSION introduced

%changelog dev
* Wed Jan 29 2014 Gernot Wirschal <Gernot.Wirschal@bmw.de> 
- Add dev packet configuration
        
%changelog
* Wed Jan 29 2014 Gernot Wirschal <Gernot.Wirschal@bmw.de> 
- Add dev packet configuration
* Mon Jan 27 2014 Gernot Wirschal <Gernot.Wirschal@bmw.de> 
- Initial packaging for GPT

