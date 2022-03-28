#include "Command.h"
#include "HelpCommand.h"
#include "CommandListFileMetadata.h"
#include "CommandModifyFileMetadata.h"
#include "CommandListFolderMetadata.h"
#include "CommandModifyFolderMetadata.h"
#include <fstream>

auto ignoreCaseEquals(const std::wstring_view& str1, const std::wstring_view& str2) -> bool
{
	if (std::size(str2) != std::size(str1))
		return false;
	return std::is_permutation(
		std::begin(str1),
		std::end(str1),
		std::begin(str2),
		[](const auto& a, const auto& b)
		{
			return std::tolower(a) == std::tolower(b);
		}
	);
}

Command::Command()
	: nullOutput{ std::make_unique<std::wofstream>() }
	, commandline{}
	, output{ nullOutput.get() }
{}

Command::Command(std::wostream* output, const Commandline& commandline)
	: nullOutput{}
	, output{output}
	, commandline{commandline}
{
	if (output == nullptr)
		nullOutput = std::make_unique<std::wofstream>();
}

Command::~Command() = default;

std::filesystem::path Command::normaliseFilename() const
{
	const auto filename{ commandline.getAtKey(L"filename").second };
	std::filesystem::path filenamePath{ filename };
	if (filenamePath.has_parent_path())
	{
		return filenamePath;
	}
	else if (commandline.hasKey(L"path"))
	{
		const std::filesystem::path parentPath{ commandline.getAtKey(L"path").second };
		return parentPath / filenamePath;
	}
	else
	{
		return std::filesystem::current_path() /= filenamePath;
	}
}

void Command::onEmptyPropertyGroup() 
{}

void Command::onAllPropertyGroup()
{}

void Command::onBasicPropertyGroup()
{}

void Command::onDocumentPropertyGroup()
{}

void Command::onMusicPropertyGroup()
{}

void Command::onVideoPropertyGroup()
{}

void Command::onAttriburePropertyGroup()
{}

void Command::handlePropertyGroupCase()
{
	if (!commandline.hasKey(L"propertygroup"))
		onEmptyPropertyGroup();
	else
	{
		const auto propertyGroup{ commandline.getAtKey(L"propertygroup").second };
		if (ignoreCaseEquals(propertyGroup, L"all"))
		{
			onAllPropertyGroup();
		}
		else if (ignoreCaseEquals(propertyGroup, L"basic"))
		{
			onBasicPropertyGroup();
		}
		else if (ignoreCaseEquals(propertyGroup, L"document"))
		{
			onDocumentPropertyGroup();
		}
		else if (ignoreCaseEquals(propertyGroup, L"attribute"))
		{
			onAttriburePropertyGroup();
		}
		else if (ignoreCaseEquals(propertyGroup, L"music"))
		{
			onMusicPropertyGroup();
		}
		else if (ignoreCaseEquals(propertyGroup, L"video"))
		{
			onVideoPropertyGroup();
		}
		else
		{
			*output << L"Unknown property group '" << propertyGroup << L'\'' << std::endl;
			HelpCommand{ output }.execute();
		}
	}
}

std::unique_ptr<Command> makeCommandFromArgs(Commandline& commandline)
{
	// could be a file in the future or some other stream.
	auto output{ &std::wcout };
	try
	{
		const auto action{ commandline.getAtKey(L"action") };
		if (action.second == L"list")
		{
			if (commandline.hasKey(L"filename"))
				return std::make_unique<CommandListFileMetadata>(output, commandline);
			else if (commandline.hasKey(L"filter"))
				return std::make_unique<CommandListFolderMetadata>(output, commandline);
		}
		if (action.second == L"modify")
		{
			if (commandline.hasKey(L"filename"))
				return std::make_unique<CommandModifyFileMetadata>(output, commandline);
			else if (commandline.hasKey(L"filter"))
				return std::make_unique<CommandModifyFolderMetadata>(output, commandline);
		}
	}
	catch (std::out_of_range&)
	{
		*output << L"did not supply list or modify, nothing to do!\n\n";
	}
	return std::make_unique<HelpCommand>(&std::wcout);
}
