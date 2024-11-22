#pragma once

#include "hook.hpp"
#include <vector>

class HookController
{
public:
	std::vector<Hook*> hookList;

public:
	HookController();

	void AddHook(Hook* pHook);
	void AddHooks();

	void Init();
	void UnInit();
};
