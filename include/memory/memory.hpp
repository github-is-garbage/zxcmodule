#pragma once

namespace Memory
{
	template <typename T>
	static T RelativeToReal(char* pAddress, int iOffset, int iInstructionSize)
	{
		if (!pAddress) return nullptr;

		char* pInstruction = pAddress + iOffset;
		int iRelativeAddress = *(int*)(pInstruction);

		char* pRealAddress = pAddress + iInstructionSize + iRelativeAddress;

		return (T)pRealAddress;
	}
}
