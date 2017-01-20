Name:           libshelper
%global pname 	libslp
%global         VersionFile %{_topdir}/SPECS/%{name}.version
Version:        %(awk -F ':' '{if ($1 == "version") print $2}' %{VersionFile})
Release:        1%{?dist}
Summary:        library for sleeping 

License:        GPL         
URL:            NULL
#Source0:       

BuildRequires: gcc-c++ >= 4.8.3
Requires:      libevent 

#包的描述
%description
This library is builded to help myself

#预处理
%prep
    rm -fr %{?buildroot}
    mkdir -p %{?buildroot}

#构建
%build
    make -C %{_sourcedir}/%{pname}

#安装
%install
    cd %{_buildrootdir}
    ln %{name}-%{version}-%{release}.x86_64 %{name} -s
    cd -
    mkdir -p %{?buildroot}%{?_libdir}/%{name}
    mkdir -p %{?buildroot}%{?_includedir}/%{name}
    mkdir -p %{?buildroot}%{_mandir}/man3
    cp %{_sourcedir}/%{pname}/*.so* %{?buildroot}%{?_libdir}/%{name}
    cp %{_sourcedir}/%{pname}/doc/man/man3/* %{?buildroot}%{_mandir}/man3
	cd %{?buildroot}%{?_libdir}
	cd %{name}
	ln %{name}.%{version}.so %{name}.so -s
	cd -
	ln %{name}/%{name}.so %{name}.so -s
	cd -
    cp %{_sourcedir}/%{pname}/src/*.h %{?buildroot}%{?_includedir}/%{name}

#安装前执行的脚本程序
%pre

#安装后执行的脚本程序
#%post

#下载前执行的脚本程序
%preun

#卸载后执行的脚本程序
%postun
%files
    %defattr(-,root,root,-)
    %{?_libdir}/%{name}/%{name}.%{version}.so
%doc



%changelog

%clean

%package devel
Summary:        Development files for %{name} 
Group:          Development/Libraries
BuildRequires:  gcc-c++ >= 4.8.3
Requires:       %{name} = %{?version}

%description devel
The signs for libshelper

%post
	#cd %{?buildroot}%{?_libdir}/%{name}
    #ln %{name}.%{version}.so %{name}.so -s
    #ln %{name}.so ../%{name}.so -s
    #cd -

%files devel
    %defattr(-,root,root,-)
    %{?_includedir}/%{name}/*.h
    %{_mandir}/man3/*
    %{?_libdir}/%{name}.so
    %{?_libdir}/%{name}/%{name}.so

