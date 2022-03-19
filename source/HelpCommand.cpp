#include "HelpCommand.h"
#include "strings.h"
#include <iostream>

HelpCommand::HelpCommand(std::wostream* output)
	: Command{ output, Commandline{} }
{}

void HelpCommand::execute()
{
	*output << HelpText << std::endl;
}
