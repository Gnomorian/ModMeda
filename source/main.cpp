#include <iostream>
#include "Commandline.h"
#include "Command.h"

int wmain(int argc, wchar_t* args[])
{
	auto cmd{ Commandline::setupCommandlineWithArgs(argc, args) };
	makeCommandFromArgs(cmd)->execute();
}