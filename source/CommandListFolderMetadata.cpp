#include "CommandListFolderMetadata.h"
#include "CommandListFileMetadata.h"
#include <winrt/base.h>

CommandListFolderMetadata::CommandListFolderMetadata(std::wostream* output, const Commandline& commandline)
	: Command{ output, commandline }
{
	if (!commandline.hasKey(L"filter") || commandline.getAtKey(L"action").second != L"list" || !commandline.hasKey(L"path"))
	{
		throw std::invalid_argument{ "you need a filter, action=list and a path" };
	}
}

void CommandListFolderMetadata::execute()
{
	handlePropertyGroupCase();
}

void CommandListFolderMetadata::onEmptyPropertyGroup()
{
	deferProcessing();
}

void CommandListFolderMetadata::onAllPropertyGroup()
{
	deferProcessing();
}

void CommandListFolderMetadata::onBasicPropertyGroup()
{
	deferProcessing();
}

void CommandListFolderMetadata::onDocumentPropertyGroup()
{
	deferProcessing();
}

void CommandListFolderMetadata::onMusicPropertyGroup()
{
	deferProcessing();
}

void CommandListFolderMetadata::onVideoPropertyGroup()
{
	deferProcessing();
}

void CommandListFolderMetadata::onAttriburePropertyGroup()
{
	deferProcessing();
}

void CommandListFolderMetadata::onImagePropertyGroup()
{
	deferProcessing();
}

void CommandListFolderMetadata::deferProcessing()
{
	const auto files{
		filterByRegex(
			commandline.getAtKey(L"path").second,
			commandline.getAtKey(L"filter").second,
			commandline.hasKey(L"recursive"))
	};
	Commandline cmd;
	for (const auto& file : files)
	{
		try
		{
			*output << L"---------------------------------------------------\n";
			cmd.setKey(L"filename", file.filename().c_str());
			cmd.setKey(L"path", file.parent_path().c_str());
			CommandListFileMetadata fileMeta{ output, cmd };
			fileMeta.execute();
		}
		catch (std::exception& e)
		{
			*output << e.what() << " Exception during getting info for " << file << std::endl;
			break;
		}
		catch (winrt::hresult_error& e)
		{
			*output << L"(" << e.code() << L") " << e.message().c_str() << " Exception during getting info for " << file << std::endl;
			break;
		}
	}
}
