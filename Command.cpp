#include "Command.h"
#include "HelpCommand.h"

Command::Command()
	: output{nullptr}
{}

Command::Command(std::wostream* output)
	: output{output}
{}

bool argsAreValid()
{
	return false;
}

std::unique_ptr<Command> makeCommandFromArgs(Commandline& commandline)
{
	// could be a file in the future or some other stream.
	auto output{ &std::wcout };

	if (!argsAreValid())
	{
		return std::make_unique<HelpCommand>(&std::wcout);
	}
	throw std::runtime_error{ "not done this yet." };
}
