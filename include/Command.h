#pragma once
#include <memory>
#include <iostream>
#include "Commandline.h"
class Command
{
protected:
	std::wostream* output;
	Commandline commandline;
public:
	Command();
	Command(std::wostream* output, const Commandline& commandline);
	virtual ~Command();
	virtual void execute() = 0;
};

std::unique_ptr<Command> makeCommandFromArgs(Commandline& commandline);