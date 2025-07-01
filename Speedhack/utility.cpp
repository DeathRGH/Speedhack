#include "utility.h"
#include "imports.h"

void Sleep(unsigned int milliseconds) {
	sceKernelUsleep(milliseconds * 1000);
}

void WriteJump(uint64_t address, uint64_t destination) {
	*(uint8_t *)(address) = 0xFF;
	*(uint8_t *)(address + 1) = 0x25;
	*(uint8_t *)(address + 2) = 0x00;
	*(uint8_t *)(address + 3) = 0x00;
	*(uint8_t *)(address + 4) = 0x00;
	*(uint8_t *)(address + 5) = 0x00;
	*(uint64_t *)(address + 6) = destination;
}

void Notify(const char *fmt, ...) {
	char buffer[512];

	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	sceSysUtilSendSystemNotificationWithText(222, buffer);
}
