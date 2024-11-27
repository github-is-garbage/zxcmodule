#pragma once

#include "api.hpp"
#include "../globals.h"
#include <algorithm>
#include <vector>
#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/Lua/LuaInterface.h>

void CopyTable(int iStackPos, GarrysMod::Lua::ILuaInterface* pLuaFrom, GarrysMod::Lua::ILuaInterface* pLuaTo, std::vector<void*> pCopiedItems); // Bad language
void CopyStackItem(int iStackPos, GarrysMod::Lua::ILuaInterface* pLuaFrom, GarrysMod::Lua::ILuaInterface* pLuaTo, std::vector<void*> pCopiedItems)
{
	int iType = pLuaFrom->GetType(iStackPos);

	switch (iType)
	{
		default:
		case GarrysMod::Lua::Type::Nil:
			pLuaTo->PushNil();
			break;
		case GarrysMod::Lua::Type::String:
			pLuaTo->PushString(pLuaFrom->GetString(iStackPos));
			break;
		case GarrysMod::Lua::Type::Bool:
			pLuaTo->PushBool(pLuaFrom->GetBool(iStackPos));
			break;
		case GarrysMod::Lua::Type::Number:
			pLuaTo->PushNumber(pLuaFrom->GetNumber(iStackPos));
			break;
		case GarrysMod::Lua::Type::Table:
			CopyTable(iStackPos, pLuaFrom, pLuaTo, pCopiedItems);

			break;
		case GarrysMod::Lua::Type::Angle:
			pLuaTo->PushAngle(pLuaFrom->GetAngle(iStackPos));
			break;
		case GarrysMod::Lua::Type::Vector:
			pLuaTo->PushVector(pLuaFrom->GetVector(iStackPos));
			break;
	}
}

void CopyTable(int iStackPos, GarrysMod::Lua::ILuaInterface* pLuaFrom, GarrysMod::Lua::ILuaInterface* pLuaTo, std::vector<void*> pCopiedItems)
{
	pLuaTo->CreateTable();
	{
		pLuaFrom->Push(iStackPos);
		pLuaFrom->PushNil();

		while (pLuaFrom->Next(-2))
		{
			if (pLuaFrom->GetType(-1) == GarrysMod::Lua::Type::Table) // Avoid infinite loop with tables referencing themselves
			{
				void* pHorseshit = pLuaFrom->GetUserdata(-1);

				if (std::find(pCopiedItems.begin(), pCopiedItems.end(), pHorseshit) != pCopiedItems.end())
				{
					// TODO: Push table refrence somehow (ie. NOT a deep copy)

					goto fuckoff;
				}

				pCopiedItems.push_back(pHorseshit);
			}

			CopyStackItem(-2, pLuaFrom, pLuaTo, pCopiedItems);
			CopyStackItem(-1, pLuaFrom, pLuaTo, pCopiedItems);

			pLuaTo->RawSet(-3);

		fuckoff:
			pLuaFrom->Pop();
		}

		pLuaFrom->Pop();
	}
}

LUA_FUNCTION(RunClientString)
{
	GarrysMod::Lua::ILuaInterface* pLuaInterface = (GarrysMod::Lua::ILuaInterface*)LUA;

	const char* pszCode = LUA->CheckString(1);
	const char* pszIdentifier = LUA->IsType(2, GarrysMod::Lua::Type::String) ? LUA->GetString(2) : "[C]";
	bool bHandleErrors = LUA->IsType(3, GarrysMod::Lua::Type::Bool) ? LUA->GetBool(3) : true;

	LUA->Pop(LUA->Top());

	bool bSuccess = pLuaInterface->RunStringEx(pszIdentifier, "", pszCode, true, bHandleErrors, true, false);
	LUA->PushBool(bSuccess);
	LUA->Insert(1); // Move bSuccess to be the first return

	return LUA->Top();
}

LUA_FUNCTION(RunMenuString)
{
	GarrysMod::Lua::ILuaInterface* pLuaInterface = *pGlobals->pPointers->pLuaShared->GetMenuLuaInterface();

	if (!pLuaInterface)
	{
		LUA->ThrowError("Can't find menu Lua interface!");
		return 0;
	}

	GarrysMod::Lua::ILuaInterface* pLuaCurrent = (GarrysMod::Lua::ILuaInterface*)LUA;

	const char* pszCode = LUA->CheckString(1);
	const char* pszIdentifier = LUA->IsType(2, GarrysMod::Lua::Type::String) ? LUA->GetString(2) : "[C]";
	bool bHandleErrors = LUA->IsType(3, GarrysMod::Lua::Type::Bool) ? LUA->GetBool(3) : true;

	LUA->Pop(LUA->Top());

	bool bSuccess = pLuaInterface->RunStringEx(pszIdentifier, "", pszCode, true, bHandleErrors, true, false);
	LUA->PushBool(bSuccess);

	// Copy everything over
	for (int i = 1; i <= pLuaInterface->Top(); ++i)
		CopyStackItem(i, pLuaInterface, pLuaCurrent, std::vector<void*>());

	pLuaInterface->Pop(pLuaInterface->Top());

	return LUA->Top();
}

class LuaAPI : public API
{
public:
	void Init()
	{
		pGlobals->pLuaInterface->PushString("lua");
		pGlobals->pLuaInterface->CreateTable();
		{
			this->PushCFunction(pGlobals->pLuaInterface, RunClientString, "RunClientString");
			this->PushCFunction(pGlobals->pLuaInterface, RunMenuString, "RunMenuString");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
