#include "CommandListFolderMetadata.h"

CommandListFolderMetadata::CommandListFolderMetadata(std::wostream* output, const Commandline& commandline)
	: Command{ output, commandline }
{
	if (!commandline.hasKey(L"filter") || commandline.getAtKey(L"action").second != L"list")
	{
		throw std::invalid_argument{ "" };
	}
}

void CommandListFolderMetadata::execute()
{
	handlePropertyGroupCase();
}

void CommandListFolderMetadata::onEmptyPropertyGroup()
{

}

void CommandListFolderMetadata::onAllPropertyGroup()
{
}

void CommandListFolderMetadata::onBasicPropertyGroup()
{
}

void CommandListFolderMetadata::onDocumentPropertyGroup()
{
}

void CommandListFolderMetadata::onMusicPropertyGroup()
{
}

void CommandListFolderMetadata::onVideoPropertyGroup()
{
}

void CommandListFolderMetadata::onAttriburePropertyGroup()
{
}

void CommandListFolderMetadata::onImagePropertyGroup()
{
}
