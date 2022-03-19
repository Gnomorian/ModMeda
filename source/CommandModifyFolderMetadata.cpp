#include "CommandModifyFolderMetadata.h"

CommandModifyFolderMetadata::CommandModifyFolderMetadata(std::wostream* output, const Commandline& commandline)
	: Command{ output }
	, commandline{ commandline }
{}

void CommandModifyFolderMetadata::execute()
{
}
