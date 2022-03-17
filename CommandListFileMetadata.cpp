#include "CommandListFileMetadata.h"

CommandListFileMetadata::CommandListFileMetadata(std::wostream* output, const Commandline& commandline)
	: Command{output}
	, commandline{commandline}
{}

void CommandListFileMetadata::execute()
{

}
