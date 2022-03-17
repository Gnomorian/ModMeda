#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Commandline.h"


auto getCommandline(auto argc, auto args)
{
	std::vector<std::wstring_view> cmdline;
	std::generate_n(std::back_inserter(cmdline), argc, [args, i = 0]()mutable {return args[i]; });
	return cmdline;
}

int wmain(int argc, wchar_t* args[])
{
	Commandline cmd{ argc, args };
}