#include <iostream>
#include "Commandline.h"
#include "Command.h"
int wmain(int argc, wchar_t* args[])
{
	Commandline cmd{ argc, args };
	makeCommandFromArgs(cmd)->execute();
}