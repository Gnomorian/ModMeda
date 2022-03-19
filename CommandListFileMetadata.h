#pragma once
#include "Command.h"
#include "Commandline.h"
#include <filesystem>
class CommandListFileMetadata : public Command
{
	Commandline commandline;
public:
	CommandListFileMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
protected:
	std::filesystem::path normaliseFilename() const;
};

