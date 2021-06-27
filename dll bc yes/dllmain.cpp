//nom makes best anti paste? i think yes

#include <Windows.h>
#include <string>
#include "minhook/MinHook.h"
#include "kernel.h"
#include "Driver.h"
#pragma comment(lib,"MinHook.x64.lib")

DWORD64 base_address = 0;

typedef void* (*Connection)(void*, void*, std::string*, void*);
Connection original_connection = NULL;


typedef BOOL(*AC)(void);
AC original_allocconsole = NULL;

DWORD64 thread;

BOOL
allocconsole_hook()
{
	base_address = reinterpret_cast<DWORD64>(GetModuleHandleA("netsh-cleaner.exe"));

	MH_Initialize();

	//Connection real_connection = (Connection)reinterpret_cast<LPVOID>((base_address + 0x89c80)); old connection hook from old crack

	MH_DisableHook(&AllocConsole);

	return original_allocconsole();
}

BOOL
DllMain(HMODULE module, DWORD call_reason, LPVOID reserved) {
	if (call_reason == DLL_PROCESS_ATTACH)
	{
		if (!GetModuleHandleA("kernel32.dll")) LoadLibraryA("kernel32.dll");

		MH_Initialize();
		MH_CreateHook(&AllocConsole, &allocconsole_hook, (void**)&original_allocconsole);
		MH_EnableHook(&AllocConsole);
		o::kExecute("netsh-cleaner.exe", thread + base_address, openKDriverHandle(thread, "netsh-cleaner.exe", base_address + 0x89c80));
	}
	return TRUE;
}

void createKHook() {
	//cpp god? we have the power of minhook on our side!!
	thread = NULL;
}

void openKDriverHandle(DWORD64 thread, std::string processName, int modulebaseaddress) {
	//its on uc go find it
}

