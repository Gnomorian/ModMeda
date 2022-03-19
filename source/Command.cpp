#include "Command.h"
#include "HelpCommand.h"
#include "CommandListFileMetadata.h"
#include "CommandModifyFileMetadata.h"
#include "CommandListFolderMetadata.h"
#include "CommandModifyFolderMetadata.h"
#include <fstream>

Command::Command()
	: output{ new std::wofstream{} }
	, commandline{}
{}

Command::Command(std::wostream* output, const Commandline& commandline)
	: output{output}
	, commandline{commandline}
{}

Command::~Command() = default;

std::unique_ptr<Command> makeCommandFromArgs(Commandline& commandline)
{
	// could be a file in the future or some other stream.
	auto output{ &std::wcout };
	try
	{
		const auto action{ commandline.getAtKey(L"action") };
		if (action.second == L"list")
		{
			if (commandline.hasKey(L"filename"))
				return std::make_unique<CommandListFileMetadata>(output, commandline);
			else if (commandline.hasKey(L"filter"))
				return std::make_unique<CommandListFolderMetadata>(output, commandline);
		}
		if (action.second == L"modify")
		{
			if (commandline.hasKey(L"filename"))
				return std::make_unique<CommandModifyFileMetadata>(output, commandline);
			else if (commandline.hasKey(L"filter"))
				return std::make_unique<CommandModifyFolderMetadata>(output, commandline);
		}
	}
	catch (std::out_of_range&)
	{
		*output << L"did not supply list or modify, nothing to do!\n\n";
	}
	return std::make_unique<HelpCommand>(&std::wcout);
}
