#pragma once
#include "Command.h"
#include "Commandline.h"
#include <filesystem>
class CommandListFileMetadata : public Command
{
public:
	CommandListFileMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
protected:
	void listAllProperties(const std::filesystem::path& filename) const;
	void listBasicProperties(const std::filesystem::path& filename) const;
	void onAllPropertyGroup() override;
	void onEmptyPropertyGroup() override;
	void onBasicPropertyGroup() override;
};

