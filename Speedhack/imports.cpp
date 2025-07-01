#include "types.h"
#include "imports.h"

// kernel
int(*sceKernelMprotect)(const void *addr, size_t len, int prot);
int(*sceKernelUsleep)(unsigned int microseconds);
int(*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

// notifications
int(*sceSysUtilSendSystemNotificationWithText)(int messageType, const char *message);

// libc
int(*vsprintf)(char *s, const char *format, va_list arg);

int sys_dynlib_dlsym(int loadedModuleID, const char *name, void *destination) {
	return syscall(591, loadedModuleID, name, destination);
}

int sys_dynlib_load_prx(const char *name, int *idDestination) {
	return syscall(594, name, 0, idDestination, 0);
}


void initImports() {
	int h = 0;

	// kernel
	sys_dynlib_load_prx("libkernel.sprx", &h);
	sys_dynlib_dlsym(h, "sceKernelMprotect", &sceKernelMprotect);
	sys_dynlib_dlsym(h, "sceKernelUsleep", &sceKernelUsleep);
	sys_dynlib_dlsym(h, "sceKernelLoadStartModule", &sceKernelLoadStartModule);

	// libc
	sys_dynlib_load_prx("libSceLibcInternal.sprx", &h);
	sys_dynlib_dlsym(h, "vsprintf", &vsprintf);

	//notify
	int sysUtilHandle = sceKernelLoadStartModule("libSceSysUtil.sprx", 0, NULL, 0, 0, 0);
	sys_dynlib_dlsym(sysUtilHandle, "sceSysUtilSendSystemNotificationWithText", &sceSysUtilSendSystemNotificationWithText);
}
