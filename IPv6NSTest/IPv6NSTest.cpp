
#include <winsock2.h>
#include <ws2ipdef.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);

	int nRet;

	SOCKET sRaw = ::socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6);

	SOCKADDR_IN6 dest = { 0 };
	dest.sin6_family = AF_INET6;
	dest.sin6_flowinfo = 0x12345;
	struct in6_addr in6AnyAddr = IN6ADDR_LOOPBACK_INIT;
	dest.sin6_addr = in6AnyAddr;

	int iHopLimit = 255;
	setsockopt(sRaw, IPPROTO_IPV6, IPV6_UNICAST_HOPS, (char *) &iHopLimit, sizeof(iHopLimit));

	char packet[] = {
		0x87, 0x00, 0x78, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	};
	UINT packet_len = sizeof(packet);

	nRet = ::sendto(sRaw, packet, packet_len, 0, (SOCKADDR *)&dest, sizeof(dest));
	if (nRet == SOCKET_ERROR)
	{
		printf("sendto() failed: %d /n", ::WSAGetLastError());
		return -1;
	}

	printf("Success!\n");

	return 0;
}