#pragma once
#include "Command.h"
class CommandModifyFileMetadata : public Command
{
	Commandline commandline;
public:
	CommandModifyFileMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
};

