#include "CommandListFolderMetadata.h"

CommandListFolderMetadata::CommandListFolderMetadata(std::wostream* output, const Commandline& commandline)
	: Command{ output }
	, commandline{ commandline }
{}

void CommandListFolderMetadata::execute()
{

}
