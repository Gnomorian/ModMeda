#pragma once
#include "Command.h"
class CommandListFolderMetadata : public Command
{
	Commandline commandline;
public:
	CommandListFolderMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
};

