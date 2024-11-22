#include "controller.h"
#include "../globals.h"

HookController::HookController()
{
	this->hookList = std::vector<Hook*>();
}

void HookController::AddHook(Hook* pHook)
{
	this->hookList.push_back(pHook);
}

void HookController::AddHooks()
{

}

void HookController::Init()
{
	this->AddHooks();

	for (Hook* pHook : this->hookList)
		pHook->Init();
}

void HookController::UnInit()
{
	for (Hook* pHook : this->hookList)
		pHook->UnInit();
}
