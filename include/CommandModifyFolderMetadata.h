#pragma once
#include "Command.h"
class CommandModifyFolderMetadata : public Command
{
public:
	CommandModifyFolderMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
};

