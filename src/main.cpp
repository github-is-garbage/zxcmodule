#include <Windows.h>
#include <iostream>

int main()
{
	AllocConsole();

	FILE* pFile;
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	std::cout << "Hello!" << std::endl;

	return 0;
}
