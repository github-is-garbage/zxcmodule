#include "pointers.h"
#include "globals.h"
#include <memory/vmt.hpp>
#include <memory/memory.hpp>

void Pointers::Init()
{
	this->pEngineClient = this->GetInterface<IVEngineClient*>("engine.dll", VENGINE_CLIENT_INTERFACE_VERSION);
	this->pLuaShared = this->GetInterface<GarrysMod::Lua::ILuaShared*>("lua_shared.dll", GMOD_LUASHARED_INTERFACE);

	/*
		This nabs the CClientState instantiated within the engine by going down the instructions to find the push
		https://github.com/lua9520/source-engine-2018-hl2_src/blob/master/engine/cdll_engine_int.cpp#L1310
	*/
	char* pEngineIsPaused = VMT::GetMethodPointerAt((char***)this->pEngineClient, VENGINE_CLIENT_ISPAUSED_OFFSET);
	this->pClientState = Memory::RelativeToReal<CClientState*>(pEngineIsPaused, 3, 7);
}

void Pointers::UnInit()
{

}
