#include "controller.h"

APIController::APIController()
{
	this->apiList = std::vector<API*>();
}

void APIController::AddAPI(API* pAPI)
{
	this->apiList.push_back(pAPI);
}

void APIController::Init()
{
	for (API* pAPI : this->apiList)
		pAPI->Init();
}

void APIController::UnInit()
{
	for (API* pAPI : this->apiList)
		pAPI->UnInit();
}
