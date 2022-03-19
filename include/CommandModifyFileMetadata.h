#pragma once
#include "Command.h"
class CommandModifyFileMetadata : public Command
{
public:
	CommandModifyFileMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
};

