
#include <winsock2.h>
#include <ws2ipdef.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
	char *s = NULL;
	int iErrorCode;

	int nRet;

	SOCKET sRaw = ::socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sRaw == INVALID_SOCKET)
	{
		iErrorCode = ::WSAGetLastError();
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, iErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &s, 0, NULL);
		printf("socket() failed: %d\n%s", iErrorCode, s);
		return -1;
	}

	SOCKADDR_IN dest = { 0 };
	dest.sin_family = AF_INET;
	struct in_addr inAnyAddr = in4addr_loopback;
	dest.sin_addr = inAnyAddr;

	int iHopLimit = 64;
	nRet = setsockopt(sRaw, IPPROTO_IP, IPV6_UNICAST_HOPS, (char *) &iHopLimit, sizeof(iHopLimit));
	if (nRet != 0)
	{
		closesocket(sRaw);
		iErrorCode = ::WSAGetLastError();
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, iErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&s, 0, NULL);
		printf("setsockopt() failed: %d\n%s", iErrorCode, s);
		return -1;
	}

	char packet[] = {
		//0x08, 0x00, 0x06, 0x0b, 0xf1, 0xf3, 0x00, 0x01
		0x00, 0x00, 0xc6, 0x8a, 0x39, 0x74, 0x00, 0x01
	};
	UINT packet_len = sizeof(packet);

	nRet = ::sendto(sRaw, packet, packet_len, 0, (SOCKADDR *)&dest, sizeof(dest));
	if (nRet == SOCKET_ERROR)
	{
		closesocket(sRaw);
		iErrorCode = ::WSAGetLastError();
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, iErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&s, 0, NULL);
		printf("sendto() failed: %d\n%s", iErrorCode, s);
		return -1;
	}

	closesocket(sRaw);
	printf("Success!\n");

	return 0;
}