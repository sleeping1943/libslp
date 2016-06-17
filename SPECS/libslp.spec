Name:           libslp
%global         VersionFile %{_topdir}/SPECS/%{name}.version
Version:        %(awk -F ':' '{if ($1 == "version") print $2}' %{VersionFile})
Release:        1%{?dist}
Summary:        library for sleeping 

License:        GPL         
URL:            NULL
#Source0:       

BuildRequires: gcc-c++ >= 4.8.5 
Requires:      libevent 

%description
This library is builded to help myself

%prep
    rm -fr %{?buildroot}
    mkdir -p %{?buildroot}

%build
    make -C %{_sourcedir}/%{name}
%install
    cd %{_buildrootdir}
    ln %{name}-%{version}-%{release}.x86_64 %{name} -s
    cd -
    mkdir -p %{?buildroot}%{?_libdir}/%{name}
    mkdir -p %{?buildroot}%{?_includedir}/%{name}
    cp %{_sourcedir}/%{name}/*.so %{?buildroot}%{?_libdir}/%{name}
    cd %{?buildroot}%{?_libdir}
    ln %{name}/%{name}_utils.so %{name}_utils.so -s
    cd -
    cp %{_sourcedir}/%{name}/utils/*.h %{?buildroot}%{?_includedir}/%{name}

%files
    %defattr(-,root,root,-)
    %{?_libdir}/*
%doc



%changelog

%clean

%package devel
Summary:        Development files for %{name} 
Group:          Development/Libraries
BuildRequires:  gcc-c++ >= 4.8.5 
Requires:       %{name} = %{?version}
%description devel
The signs for libslp
%files devel
    %defattr(-,root,root,-)
    %{?_includedir}/%{name}/*.h

