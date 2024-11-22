#pragma once

#include <utility>
#include <cstdint>

namespace VMT
{
	static inline void** GetVTable(void* pObject)
	{
		return *reinterpret_cast<void***>(pObject);
	}

	/*
	*	These are exactly the same except one has TArguments&& and one is TArguments
	*	The && is needed for methods such as IVEngineClient::GetScreenSize because it uses int&
	*	But the && will break methods that need regular ints such as INetChannelInfo::GetLatency
	*	So, shitty compromise with 2 nearly identical methods and 2 macros!
	*/
	template <typename TReturn, typename... TArguments>
	static inline TReturn CallReference(void* pObject, std::uintptr_t lIndex, TArguments&&... Arguments)
	{
		void* pFunction = GetVTable(pObject)[lIndex];
		auto rFunction = reinterpret_cast<TReturn(__thiscall*)(void*, TArguments...)>(pFunction);

		return rFunction(pObject, std::forward<TArguments>(Arguments)...);
	}

	template <typename TReturn, typename... TArguments>
	static inline TReturn Call(void* pObject, std::uintptr_t lIndex, TArguments... Arguments)
	{
		void* pFunction = GetVTable(pObject)[lIndex];
		auto rFunction = reinterpret_cast<TReturn(__thiscall*)(void*, TArguments...)>(pFunction);

		return rFunction(pObject, std::forward<TArguments>(Arguments)...);
	}
}

#define VPROXY_REF(MethodName, Index, ReturnType, Arguments, ...)					\
	ReturnType MethodName Arguments													\
	{																				\
		return VMT::CallReference<ReturnType>((void*)this, Index, ## __VA_ARGS__);	\
	}

#define VPROXY(MethodName, Index, ReturnType, Arguments, ...)				\
	ReturnType MethodName Arguments											\
	{																		\
		return VMT::Call<ReturnType>((void*)this, Index, ## __VA_ARGS__);	\
	}
