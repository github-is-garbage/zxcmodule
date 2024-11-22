#include "pointers.h"

#include <Windows.h>
#include "globals.h"

void Pointers::Init()
{
	this->pEngineClient = this->GetInterface<IVEngineClient*>("engine.dll", VENGINE_CLIENT_INTERFACE_VERSION);
	this->pCBaseClientState_ConnectionStart = this->GetAddress("engine.dll", CBASECLIENTSTATE_CONNECTIONSTART);
}

void Pointers::UnInit()
{

}
