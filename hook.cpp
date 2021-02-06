#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "dllstub.hpp"

#pragma pack(push, 1)
struct jmp
{
	uint8_t opcode;
	size_t address;
};
#pragma pack(pop)

void InlineHook(void* func, void* hookFunc, size_t* origAddr)
{
	DWORD oldProtect;
	if (VirtualProtect(func, 5, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		jmp* hook = (jmp*)func;
		hook->opcode = 0xE9; // jmp
		hook->address = (size_t)hookFunc - (size_t)func - 5;
		*origAddr = (size_t)func + 5;
		VirtualProtect(func, 5, oldProtect, &oldProtect);
	}
}

LANGID WINAPI MyGetUserDefaultLangID(void) {
	return 0x0804;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		LoadDLL();

		auto pGetUserDefaultLangID = GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "GetUserDefaultLangID");
		size_t addrCreateFontIndirectW = 0;
		InlineHook(pGetUserDefaultLangID, MyGetUserDefaultLangID, &addrCreateFontIndirectW);
	}
	return TRUE;
}
