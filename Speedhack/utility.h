#pragma once

#include "types.h"

#define	VM_PROT_NONE	0x00
#define	VM_PROT_READ	0x01
#define	VM_PROT_WRITE	0x02
#define	VM_PROT_EXECUTE	0x04
#define	VM_PROT_COPY	0x08

#define	VM_PROT_ALL	(VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE)
#define VM_PROT_RW	(VM_PROT_READ | VM_PROT_WRITE)

void Sleep(unsigned int milliseconds);
void WriteJump(uint64_t address, uint64_t destination);
void Notify(const char *fmt, ...);
