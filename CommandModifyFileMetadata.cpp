#include "CommandModifyFileMetadata.h"

CommandModifyFileMetadata::CommandModifyFileMetadata(std::wostream* output, const Commandline& commandline)
	: Command{output}
	, commandline{commandline}
{}

void CommandModifyFileMetadata::execute()
{
}
