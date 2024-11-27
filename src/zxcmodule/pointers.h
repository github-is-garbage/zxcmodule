#pragma once

#include <Windows.h>
#include <Interfaces.h>
#include <Valve/IVEngineClient.h>
#include <Valve/IClientState.h>
#include <GarrysMod/Lua/LuaShared.h>

typedef void *(*CreateInterfaceFn)(const char*, int*);

class Pointers
{
public:
	IVEngineClient* pEngineClient;
	CClientState* pClientState;
	GarrysMod::Lua::ILuaShared* pLuaShared;

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
