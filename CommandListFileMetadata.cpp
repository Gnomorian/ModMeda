#include "CommandListFileMetadata.h"
#include <variant>
#include <Windows.h>
#include <Wmsdk.h>
#include <mfidl.h>
#pragma comment(lib, "Wmvcore.lib")

CommandListFileMetadata::CommandListFileMetadata(std::wostream* output, const Commandline& commandline)
	: Command{output}
	, commandline{commandline}
{}

void CommandListFileMetadata::execute()
{
	IWMMetadataEditor* editor{ nullptr };
	auto result{ WMCreateEditor(&editor) };
	if (result != S_OK)
	{
		*output << "WMCreateEditor error, " << result;
		return;
	}
	const auto filename{ normaliseFilename() };
	result = editor->Open(filename.c_str());
	if (result != S_OK)
	{
		*output << "IWMMetadataEditor::Open error, " << result << std::endl;
		return;
	}
	*output << "Listing metadata for " << filename << std::endl;

	IWMHeaderInfo3* headerinfo{ nullptr };
	result = editor->QueryInterface(&headerinfo);
	if (result != S_OK)
	{
		*output << "IWMMetadataEditor::QueryInterface<IWMHeaderInfo3**> error, " << result << std::endl;
		return;
	}
	WORD numAttributes{};
	result = headerinfo->GetAttributeCount(0xFFFF, &numAttributes);
	if (result != S_OK)
	{
		*output << "IWMHeaderInfo3::GetAttributeCount error, " << result << std::endl;
		return;
	}
	std::vector<wchar_t> nameBuffer;
	std::vector<BYTE> dataBuffer;
	using Metadata = std::variant<std::monostate, std::wstring, DWORD, WORD, QWORD, bool, std::vector<char>>;
	std::vector<std::pair<std::wstring, Metadata>> metadataForFile;
	for (WORD i{ 0 }; i < numAttributes; i++)
	{
		WORD streamNum{ 0xFFFF };
		WORD nameLen{};
		WMT_ATTR_DATATYPE dataType{};
		WORD dataLen{};
		result = headerinfo->GetAttributeByIndex(i, &streamNum, nullptr, &nameLen, &dataType, nullptr, &dataLen);
		if (result != S_OK)
		{
			*output << "IWMHeaderInfo3::GetAttributeByIndex error, " << result << std::endl;
			return;
		}
		nameBuffer.resize(nameLen);
		dataBuffer.resize(dataLen);
		result = headerinfo->GetAttributeByIndex(i, &streamNum, nameBuffer.data(), &nameLen, &dataType, dataBuffer.data(), &dataLen);
		if (result != S_OK)
		{
			*output << "IWMHeaderInfo3::GetAttributeByIndex error, " << result << std::endl;
			return;
		}
		std::wstring name{ nameBuffer.data(), nameLen };
		switch (dataType)
		{
		case WMT_TYPE_STRING:
			metadataForFile.emplace_back(std::move(name), Metadata{ std::in_place_index<1>, std::wstring(reinterpret_cast<wchar_t*>(dataBuffer.data()), static_cast<size_t>(dataLen)) });
			break;
		case WMT_TYPE_DWORD:
			metadataForFile.emplace_back(std::move(name), Metadata{std::in_place_index<2>, static_cast<DWORD>(*dataBuffer.data()) });
			break;
		case WMT_TYPE_WORD:
			metadataForFile.emplace_back(std::move(name), Metadata{ std::in_place_index<3>, static_cast<WORD>(*dataBuffer.data()) });
			break;
		case WMT_TYPE_QWORD:
			metadataForFile.emplace_back(std::move(name), Metadata{ std::in_place_index<4>, static_cast<QWORD>(*dataBuffer.data()) });
			break;
		case WMT_TYPE_BOOL:
			metadataForFile.emplace_back(std::move(name), Metadata{ std::in_place_index<5>, static_cast<bool>(*dataBuffer.data()) });
			break;
		case WMT_TYPE_BINARY:
			metadataForFile.emplace_back(std::move(name), Metadata{ std::in_place_index<6>, std::vector<char>{dataBuffer.begin(), dataBuffer.begin() + dataLen}});
			break;
		default:
			metadataForFile.emplace_back(std::move(name), Metadata{std::in_place_index<0>});
		}
	}
	*output << L"There where " << numAttributes << L" metadata attributes in the file.\n";
	for (int i{ 0 }; const auto & metadata : metadataForFile)
	{
		*output << ++i << L") " << metadata.first << L" = ";
		std::visit([&](const auto& variant) 
			{
				using Type = std::decay<decltype(variant)>::type;
				if constexpr (std::is_integral<Type>::value || std::is_same<std::wstring, Type>{})
				{
					*output << variant << std::endl;
				}
				else
				{
					*output << "not a value im handling yet" << std::endl;
				}
			}, 
			metadata.second
		);
	}

	headerinfo->Release();
	editor->Release();
}

std::filesystem::path CommandListFileMetadata::normaliseFilename() const
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
