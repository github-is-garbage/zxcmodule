#pragma once

#include <utility>
#include <cstdint>

namespace VMT
{
	static inline void** GetVTable(void* pObject)
	{
		return *reinterpret_cast<void***>(pObject);
	}

	template <typename T>
	struct RefWrapper
	{
		T& ref;
		explicit RefWrapper(T& r) : ref(r) {}
	};

	template <typename T>
	inline T& UnWrap(RefWrapper<T> wrapper)
	{
		return wrapper.ref;
	}

	template <typename T>
	inline T&& UnWrap(T&& value)
	{
		return std::forward<T>(value);
	}

	template <typename ReturnType, typename... TArguments>
	static inline ReturnType Call(void* pObject, std::uintptr_t lIndex, TArguments&&... Arguments)
	{
		using MethodType = ReturnType(__thiscall*)(void*, std::decay_t<TArguments>...);

		void* pMethod = GetVTable(pObject)[lIndex];
		MethodType vMethod = reinterpret_cast<MethodType>(pMethod);

		return vMethod(pObject, std::forward<TArguments>(Arguments)...);
	}

}

#define VWRAP(Argument)			\
	VMT::RefWrapper(Argument)

#define VPROXY(MethodName, Index, ReturnType, Arguments, ...)				\
	ReturnType MethodName Arguments											\
	{																		\
		return VMT::Call<ReturnType>((void*)this, Index, ## __VA_ARGS__);	\
	}
