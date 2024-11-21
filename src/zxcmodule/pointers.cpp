#include "pointers.h"

void Pointers::Init()
{
	this->pEngineClient = this->GetInterface<IVEngineClient*>("engine.dll", VENGINE_CLIENT_INTERFACE_VERSION);
}

void Pointers::UnInit()
{

}
