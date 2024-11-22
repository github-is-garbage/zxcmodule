#pragma once

#include <utility>
#include <cstdint>

namespace VMT
{
	static inline void** GetVTable(void* pObject)
	{
		return *reinterpret_cast<void***>(pObject);
	}

	template <typename TReturn, typename... TArguments>
	static inline TReturn Call(void* pObject, std::uintptr_t lIndex, TArguments&&... Arguments)
	{
		void* pFunction = GetVTable(pObject)[lIndex];
		auto rFunction = reinterpret_cast<TReturn(__thiscall*)(void*, TArguments...)>(pFunction);

		return rFunction(pObject, std::forward<TArguments>(Arguments)...);
	}
}

#define VPROXY(MethodName, Index, ReturnType, Arguments, ...)				\
	ReturnType MethodName Arguments											\
	{																		\
		return VMT::Call<ReturnType>((void*)this, Index, ## __VA_ARGS__);	\
	}
