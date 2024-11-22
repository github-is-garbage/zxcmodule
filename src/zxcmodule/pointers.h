#pragma once

#include <Windows.h>
#include <Valve/Interfaces.h>
#include <Valve/IVEngineClient.h>

typedef void *(*CreateInterfaceFn)(const char*, int*);

class Pointers
{
public:
	IVEngineClient* pEngineClient;
	FARPROC pCBaseClientState_ConnectionStart;

public:
	FARPROC GetAddress(const char* pszModuleName, const char* pszAddressName)
	{
		HMODULE hModule = GetModuleHandleA(pszModuleName);
		if (!hModule) return nullptr;

		return GetProcAddress(hModule, pszAddressName);
	}

	template <typename T>
	T GetInterface(const char* pszModuleName, const char* pszInterfaceName)
	{
		FARPROC pAddress = GetAddress(pszModuleName, "CreateInterface");
		if (!pAddress) return nullptr;

		CreateInterfaceFn fnCreateInterface = reinterpret_cast<CreateInterfaceFn>(pAddress);

		return (T)fnCreateInterface(pszInterfaceName, nullptr);
	}

	void Init();
	void UnInit();
};
