#pragma once
#include <memory>
#include <iostream>
#include "Commandline.h"
class Command
{
protected:
	std::wostream* output;
public:
	Command();
	Command(std::wostream* output);
	virtual void execute() = 0;
};

std::unique_ptr<Command> makeCommandFromArgs(Commandline& commandline);