#pragma once

#include <cstdint>

namespace VMT
{
	static inline void** GetVTable(void* pObject)
	{
		return *reinterpret_cast<void***>(pObject);
	}

	template <typename TReturn, typename ...TArguments>
	static inline TReturn Call(void* pObject, std::uintptr_t lIndex, TArguments ...Arguments)
	{
		return reinterpret_cast<TReturn(__thiscall*)(const void*, decltype(Arguments)...)>(GetVTable(pObject))(pObject, Arguments...);
	}
}

#define VPROXY(MethodName, Index, ReturnType, Arguments, ...)				\
	ReturnType MethodName Arguments											\
	{																		\
		return VMT::Call<ReturnType>((void*)this, Index, ## __VA_ARGS__);	\
	}
