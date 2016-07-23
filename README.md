# IPv6NSTest
A PoC that causes Windows 7 OS to crash by sending an IPv6 neighbor solicitation packet

## Analysis

This should be a Windows 7 OS bug. A description is here: http://stackoverflow.com/questions/37983755/winsock-kernels-wsksendto-function-causes-driver-irql-not-less-or-equal-bso

## Build

This PoC is built by ``Visual Studio 2013``.

1. Build ``IPv6NSTest.sln`` with ``Visual Studio 2013``.

## Releases
https://github.com/hsluoyz/IPv6NSTest/releases

## Usage
1. Prepare a Windows 7 OS.
2. Download and unzip the release package ``IPv6NSTest-0.2.zip``.
3. Launch ``x86\IPv6NSTest.exe`` or ``x64\IPv6NSTest.exe`` based on your OS.
4. You will see the BSoD immediately.