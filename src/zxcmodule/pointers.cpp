#include "pointers.h"
#include "globals.h"
#include <memory/vmt.hpp>
#include <memory/memory.hpp>

void Pointers::Init()
{
	this->pEngineClient = this->GetInterface<IVEngineClient*>("engine.dll", VENGINE_CLIENT_INTERFACE_VERSION);
	this->pClientState = Memory::RelativeToReal<CClientState*>(VMT::GetMethodPointerAt((char***)this->pEngineClient, VENGINE_CLIENT_ISPAUSED_OFFSET), 3, 7);
}

void Pointers::UnInit()
{

}
