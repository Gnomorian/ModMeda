#pragma once
#include "Command.h"
class HelpCommand : public Command
{
public:
	HelpCommand(std::wostream* output);
	void execute() override;
};

