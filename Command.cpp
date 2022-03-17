#include "Command.h"
#include "HelpCommand.h"
#include "CommandListFileMetadata.h"
#include "CommandModifyFileMetadata.h"
#include "CommandListFolderMetadata.h"
#include "CommandModifyFolderMetadata.h"
#include <fstream>

Command::Command()
	: output{ new std::wofstream{} }
{}

Command::Command(std::wostream* output)
	: output{output}
{}

bool argsAreValid(Commandline& commandline)
{
	if(commandline.hasKey(L"filename") && commandline.hasKey(L"filter"))
		return false;
	return true;
}

std::unique_ptr<Command> makeCommandFromArgs(Commandline& commandline)
{
	// could be a file in the future or some other stream.
	auto output{ &std::wcout };

	if (!argsAreValid(commandline))
	{
		return std::make_unique<HelpCommand>(&std::wcout);
	}
	if (commandline.hasKey(L"list"))
	{
		if (commandline.hasKey(L"filename"))
			return std::make_unique<CommandListFileMetadata>(output, commandline);
		else if (commandline.hasKey(L"filter"))
			return std::make_unique<CommandListFolderMetadata>(output, commandline);
	}
	if (commandline.hasKey(L"modify"))
	{
		if (commandline.hasKey(L"filename"))
			return std::make_unique<CommandModifyFileMetadata>(output, commandline);
		else if (commandline.hasKey(L"filter"))
			return std::make_unique<CommandModifyFolderMetadata>(output, commandline);
	}
	throw std::runtime_error{ "not done this yet." };
}
