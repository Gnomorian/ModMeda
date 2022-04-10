#pragma once
#include "Command.h"
class CommandListFolderMetadata : public Command
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
};

