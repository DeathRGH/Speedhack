#pragma once

#include "types.h"
#include "syscall.h"

// kernel
extern int(*sceKernelMprotect)(const void *addr, size_t len, int prot);
extern int(*sceKernelUsleep)(unsigned int microseconds);
extern int(*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

// notifications
extern int(*sceSysUtilSendSystemNotificationWithText)(int messageType, const char *message);

// libc
extern int(*vsprintf)(char *s, const char *format, va_list arg);

int sys_dynlib_dlsym(int loadedModuleID, const char *name, void *destination);
int sys_dynlib_load_prx(const char *name, int *idDestination);

void initImports();
