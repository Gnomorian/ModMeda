#pragma once
#include "Command.h"
class CommandModifyFileMetadata : public Command
{
public:
	CommandModifyFileMetadata(std::wostream* output, const Commandline& commandline);
	void execute() override;
	void onAllPropertyGroup() override;
	void onAttriburePropertyGroup() override;
	void onBasicPropertyGroup() override;
	void onDocumentPropertyGroup() override;
	void onEmptyPropertyGroup() override;
	void onImagePropertyGroup() override;
	void onMusicPropertyGroup() override;
	void onVideoPropertyGroup() override;
};

