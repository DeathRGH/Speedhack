#include "imports.h"
#include "utility.h"

uint64_t savedTickCount;
uint64_t savedModdedTickCount;

float speedHackSpeed = 1.0f;
float writeableSetupValue = 1.0f;
float lastSetupValue = 0.0f;

void *sceKernelReadTsc_ptr;
void *sceKernelGetProcessTimeCounter_ptr;

uint64_t GetRealTick() {
	asm("rdtsc");
	asm("mov eax, eax");
	asm("shl rdx, 0x20");
	asm("or rax, rdx");

	register uint64_t rax asm("rax");
	return rax;
}

uint64_t GetModdedTick() {
	uint64_t rax = GetRealTick();

	return savedModdedTickCount + ((rax - savedTickCount) * speedHackSpeed);
}

void SetupSpeed(float speed) {
	uint64_t rax = GetRealTick();

	savedModdedTickCount = savedTickCount = rax;

	lastSetupValue = speedHackSpeed = speed;
}

void ChangeSpeed(float speed) {
	uint64_t rax = GetRealTick();

	savedModdedTickCount = GetModdedTick();
	savedTickCount = rax;

	lastSetupValue = speedHackSpeed = speed;
}

uint64_t sceKernelReadTsc_Hook() {
	return GetModdedTick();
}

uint64_t sceKernelGetProcessTimeCounter_Hook() {
	return GetModdedTick();
}

void Loop() {
	while (*(uint64_t *)((uint64_t)sceKernelReadTsc_ptr + 0x06) == (uint64_t)sceKernelReadTsc_Hook) {
		if (writeableSetupValue != lastSetupValue) {
			ChangeSpeed(writeableSetupValue);
			Notify("Speedhack: x%.2f\nCreated by DeathRGH & TLH", speedHackSpeed);
		}
		Sleep(10);
	}
}

extern "C" void _main(void) {
	initImports();

	SetupSpeed(speedHackSpeed);

	int handle = 0;
	sys_dynlib_load_prx("libkernel.sprx", &handle);

	sys_dynlib_dlsym(handle, "sceKernelReadTsc", &sceKernelReadTsc_ptr);

	if (sceKernelReadTsc_ptr) {
		sceKernelMprotect(sceKernelReadTsc_ptr, 16, VM_PROT_ALL);
		WriteJump((uint64_t)sceKernelReadTsc_ptr, (uint64_t)sceKernelReadTsc_Hook);
	}
	
	sys_dynlib_dlsym(handle, "sceKernelGetProcessTimeCounter", &sceKernelGetProcessTimeCounter_ptr);

	if (sceKernelGetProcessTimeCounter_ptr) {
		sceKernelMprotect(sceKernelGetProcessTimeCounter_ptr, 16, VM_PROT_ALL);
		WriteJump((uint64_t)sceKernelGetProcessTimeCounter_ptr, (uint64_t)sceKernelGetProcessTimeCounter_Hook);
	}

	Loop();
}
