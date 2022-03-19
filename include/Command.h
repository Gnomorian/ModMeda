#pragma once
#include <memory>
#include <iostream>
#include <filesystem>
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
protected:
	virtual void handlePropertyGroupCase() final;
	virtual std::filesystem::path normaliseFilename() const;
	virtual void onEmptyPropertyGroup();
	virtual void onAllPropertyGroup();
	virtual void onBasicPropertyGroup();
};

std::unique_ptr<Command> makeCommandFromArgs(Commandline& commandline);