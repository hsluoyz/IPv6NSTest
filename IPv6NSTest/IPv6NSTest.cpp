
#include <stdio.h>
#include <stdlib.h>

#include "windivert.h"

int main()
{
	HANDLE handle;
	
	WINDIVERT_ADDRESS addr;
	addr.IfIdx = 1;
	addr.SubIfIdx = 1;
	addr.Direction = WINDIVERT_DIRECTION_OUTBOUND;

	// Divert traffic matching the filter:
	handle = WinDivertOpen("true", WINDIVERT_LAYER_NETWORK, 0, 0);
	if (handle == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_INVALID_PARAMETER)
		{
			printf("error: filter syntax error\n");
			//exit(EXIT_FAILURE);
			return -1;
		}
		printf("error: failed to open the WinDivert device (%d)\n",
			GetLastError());
		//exit(EXIT_FAILURE);
		return -1;
	}

	unsigned char packet[] = {
		0x60, 0x01,
		0x23, 0x45, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x87, 0x00, 0x78, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	};
	UINT packet_len = sizeof(packet);

	WinDivertHelperCalcChecksums(packet, packet_len, 0);

	if (!WinDivertSend(handle, packet, packet_len, &addr, NULL))
	{
		printf("warning: failed to inject packet (%d)\n", GetLastError());
	}

	WinDivertClose(handle);

	printf("Success!\n");
	//system("pause");

	return 0;
}