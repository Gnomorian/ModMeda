#pragma once
#include "Command.h"
class CommandListFolderMetadata : public Command
{
public:
	CommandListFolderMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
};

