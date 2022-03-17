#pragma once
#include "Command.h"
#include "Commandline.h"
class CommandListFileMetadata : public Command
{
	Commandline commandline;
public:
	CommandListFileMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
};

