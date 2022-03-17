#include <iostream>
#include "Commandline.h"
#include "strings.h"

int wmain(int argc, wchar_t* args[])
{
	Commandline cmd{ argc, args };
	std::wcout << HelpText << std::endl;
}