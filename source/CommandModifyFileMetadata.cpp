#include "CommandModifyFileMetadata.h"
#include "PropertyGroups.h"

CommandModifyFileMetadata::CommandModifyFileMetadata(std::wostream* output, const Commandline& commandline)
	: Command{output, commandline }
{}

void CommandModifyFileMetadata::execute()
{
	handlePropertyGroupCase();
}

void CommandModifyFileMetadata::onAllPropertyGroup()
{
}

void CommandModifyFileMetadata::onAttriburePropertyGroup()
{
}

void CommandModifyFileMetadata::onBasicPropertyGroup()
{
}

void CommandModifyFileMetadata::onDocumentPropertyGroup()
{
	const auto& propertyName{ commandline.getAtKey(L"key").second };
	const auto& rawValue{ commandline.getAtKey(L"value").second };
	DocumentProperties properties{};
	properties << std::make_pair<std::wstring_view, std::wstring_view>(propertyName, rawValue);
}

void CommandModifyFileMetadata::onEmptyPropertyGroup()
{
}

void CommandModifyFileMetadata::onImagePropertyGroup()
{
}

void CommandModifyFileMetadata::onMusicPropertyGroup()
{
}

void CommandModifyFileMetadata::onVideoPropertyGroup()
{
}
