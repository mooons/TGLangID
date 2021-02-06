// This file contains code from https://github.com/ThirteenAG/Ultimate-ASI-Loader

#pragma once
#include <filesystem>
#define FuncAddr(name) FARPROC addr##name

extern "C"
{
	// version
	FuncAddr(GetFileVersionInfoA);
	FuncAddr(GetFileVersionInfoByHandle);
	FuncAddr(GetFileVersionInfoExA);
	FuncAddr(GetFileVersionInfoExW);
	FuncAddr(GetFileVersionInfoSizeA);
	FuncAddr(GetFileVersionInfoSizeExA);
	FuncAddr(GetFileVersionInfoSizeExW);
	FuncAddr(GetFileVersionInfoSizeW);
	FuncAddr(GetFileVersionInfoW);
	FuncAddr(VerFindFileA);
	FuncAddr(VerFindFileW);
	FuncAddr(VerInstallFileA);
	FuncAddr(VerInstallFileW);
	FuncAddr(VerLanguageNameA);
	FuncAddr(VerLanguageNameW);
	FuncAddr(VerQueryValueA);
	FuncAddr(VerQueryValueW);
}

inline auto GetSysDirFsPath()
{
	std::wstring path(MAX_PATH, L'\0');
	while (1)
	{
		const UINT pathSize = static_cast<UINT>(path.size());
		const UINT requiredSize = GetSystemDirectoryW(path.data(), pathSize);
		path.resize(requiredSize);
		if (requiredSize < pathSize)
			break;
	}
	return std::filesystem::path(path);
}

void LoadDLL()
{
	HMODULE hDll = LoadLibraryW((GetSysDirFsPath() / L"version.dll").c_str());
	if (!hDll)
		return;

#define GetAddr(name) addr##name = GetProcAddress(hDll, #name)
	GetAddr(GetFileVersionInfoA);
	GetAddr(GetFileVersionInfoByHandle);
	GetAddr(GetFileVersionInfoExA);
	GetAddr(GetFileVersionInfoExW);
	GetAddr(GetFileVersionInfoSizeA);
	GetAddr(GetFileVersionInfoSizeExA);
	GetAddr(GetFileVersionInfoSizeExW);
	GetAddr(GetFileVersionInfoSizeW);
	GetAddr(GetFileVersionInfoW);
	GetAddr(VerFindFileA);
	GetAddr(VerFindFileW);
	GetAddr(VerInstallFileA);
	GetAddr(VerInstallFileW);
	GetAddr(VerLanguageNameA);
	GetAddr(VerLanguageNameW);
	GetAddr(VerQueryValueA);
	GetAddr(VerQueryValueW);
}
