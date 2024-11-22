#pragma once

#include "api.hpp"
#include <vector>

class APIController
{
public:
	std::vector<API*> apiList;

public:
	APIController();

	void AddAPI(API* pAPI);
	void AddAPIs();

	void Init();
	void UnInit();
};
