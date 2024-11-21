#pragma once

#include <Windows.h>
#include <Valve/Interfaces.h>
#include <Valve/IVEngineClient.h>

typedef void *(*CreateInterfaceFn)(const char*, int*);

class Pointers
{
public:
	IVEngineClient* pEngineClient;

public:
	template <typename T>
	T GetInterface(const char* pszModuleName, const char* pszInterfaceName)
	{
		HMODULE hModule = GetModuleHandleA(pszModuleName);
		if (!hModule) return nullptr;

		FARPROC pAddress = GetProcAddress(hModule, "CreateInterface");
		if (!pAddress) return nullptr;

		CreateInterfaceFn fnCreateInterface = reinterpret_cast<CreateInterfaceFn>(pAddress);

		return (T)fnCreateInterface(pszInterfaceName, nullptr);
	}

	void Init();
	void UnInit();
};
