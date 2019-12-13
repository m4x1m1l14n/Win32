# Win32 library

[![Build status](https://ci.appveyor.com/api/projects/status/3hqlxj5uyc4dfgac/branch/master?svg=true)](https://ci.appveyor.com/project/m4x1m1l14n/win32/branch/master)

C++ wrappers to simplify native Windows API calls

## Table of contents
* [Table of contents](#table-of-contents)
* [Basic usage](#basic-usage)
* [Win32 namespace](#win32-namespace)
  * [User namespace](#user-namespace)
  * [SysInfoAPI namespace](#sysinfoapi-namespace)
  * [DataProtection namespace](#dataprotection-namespace)
* [License](#license)

## Basic usage

> TODO

## Win32 namespace

All implemented wrappers in this library are scoped under Win32 namespace.

### User namespace
* Win32::User::GetWindowText

  [GetWindowText](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta) API wrapper
  > Function definition
  ```C++
  std::wstring Win32::User::GetWindowText(HWND hWnd)
  ```
  > Usage
  ```C++
  #include <Win32/User.hpp>
  
  using namespace Win32;
  
  const auto& windowText = User::GetWindowText(hWindow);
  ```
### SysInfoAPI namespace

* Win32::SysInfoAPI::GetComputerNameEx

  [GetComputerNameEx](https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getcomputernameexw) API wrapper
  > Function definition
  ```C++
  std::wstring Win32::SysInfoAPI::GetComputerNameEx(COMPUTER_NAME_FORMAT format)
  ```
  > Usage
  ```C++
  #include <Win32/SysInfoAPI.hpp>
  
  using namespace Win32;
  
  const auto& computerName = SysInfoAPI::GetComputerNameEx(ComputerNameNetBIOS);
  ```
### DataProtection namespace

* Win32::DataProtection::ProtectData

  [CryptProtectData](https://docs.microsoft.com/en-us/windows/win32/api/dpapi/nf-dpapi-cryptprotectdata) API wrapper
  > Function definition
  ```C++
  std::string
  Win32::DataProtection::ProtectData(
    const std::string& unprotectedData,
    const std::string& optionalEntropy = std::string(),
    ProtectDataFlags flags = ProtectDataFlags::LocalMachine
  )
  ```
  > Usage
  ```C++
  #include <Win32/DataProtection.hpp>

  using namespace Win32;

  const auto& protectedData = DataProtection::ProtectData("Some secret data to protect");
  ```
* Win32::DataProtection::UnprotectData

  [CryptUnprotectData](https://docs.microsoft.com/en-us/windows/win32/api/dpapi/nf-dpapi-cryptunprotectdata) API wrapper
  > Function definition
  ```C++
  std::string
  Win32::DataProtection::UnprotectData(
    const std::string& protectedData, 
    const std::string& optionalEntropy = std::string(), 
    ProtectDataFlags flags = ProtectDataFlags::LocalMachine
  )
  ```
  > Usage
  ```C++
  #include <Win32/DataProtection.hpp>

  using namespace Win32;

  const auto& unprotectedData = DataProtection::UnprotectData(previouslyProtectedData);
  ```
## License
