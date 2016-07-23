# IPv6NSTest
A PoC that causes Windows 7 OS to crash by sending an IPv6 neighbor solicitation packet using Windows raw socket.

IPv6NSTest needs to run under **Administrator** privilege because on Windows, using a socket of type ``SOCK_RAW`` requires administrative privileges based on [this MSDN link](https://msdn.microsoft.com/en-us/library/windows/desktop/ms740548.aspx).

## Analysis

This should be a Windows 7 OS bug. the BSoD only happens when the IPv6 header ``Hop Limit`` field of the IPv6 neighbor solicitation packet is set to 255. When setting it to other values like 128 or 254, the BSoD doesn't occur. So I believe the IPv6 header ``Hop Limit`` handling code on the loopback path has some kind of bug.

A detailed binary-level analysis is here: http://stackoverflow.com/questions/37983755/winsock-kernels-wsksendto-function-causes-driver-irql-not-less-or-equal-bso.

## Build

Build ``IPv6NSTest.sln`` with ``Visual Studio 2013``.

## Releases
https://github.com/hsluoyz/IPv6NSTest/releases

## Usage
1. Prepare a Windows 7 OS.
2. Download and unzip the release package ``IPv6NSTest-0.2.zip``.
3. Launch ``x86\IPv6NSTest.exe`` or ``x64\IPv6NSTest.exe`` with **Administrator** privilege based on your OS.
4. You will see the BSoD immediately.