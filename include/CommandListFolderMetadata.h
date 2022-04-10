#pragma once
#include "Command.h"
#include "FolderFilter.h"
class CommandListFolderMetadata : public Command, FolderFilter
{
public:
	CommandListFolderMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
	void onEmptyPropertyGroup() override;
	void onAllPropertyGroup() override;
	void onBasicPropertyGroup() override;
	void onDocumentPropertyGroup() override;
	void onMusicPropertyGroup() override;
	void onVideoPropertyGroup() override;
	void onAttriburePropertyGroup() override;
	void onImagePropertyGroup() override;
	void deferProcessing();
};

