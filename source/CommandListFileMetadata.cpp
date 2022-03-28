#include "CommandListFileMetadata.h"
#include <variant>
#include <Windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <iomanip>
#include <chrono>
#include "FileMetadata.h"
#include <algorithm>
#include <iterator>
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;

CommandListFileMetadata::CommandListFileMetadata(std::wostream* output, const Commandline& commandline)
	: Command{output, commandline }
{}
// v|attribute|music|video|document
void CommandListFileMetadata::execute()
{
    handlePropertyGroupCase();
}

void CommandListFileMetadata::listAllProperties(const std::filesystem::path& filename) const
{
    FileMetadata meta{ filename };
    const auto properties{ meta.allProperties() };
    *output << L"All properties for " << filename << std::endl;
    for (int i{ 0 }; const auto & [key, value] : properties)
    {
        *output << ++i << L") " << key << L" = ";
        std::visit(
            [this](const auto& value)
            {
                using Type = std::decay_t<decltype(value)>;
                constexpr auto IsStreamable{
                    std::is_arithmetic<Type>::value || std::is_same<std::wstring, Type>::value
                };
                if constexpr (IsStreamable)
                    *output << value << std::endl;
                else if constexpr (std::is_same<std::vector<std::wstring>, Type>{})
                {
                    for (const auto& str : value)
                        *output << str << L";";
                    *output << std::endl;
                }
                else if constexpr (std::is_same_v<std::monostate, Type>)
                {
                    *output << "***EMPTY***" << std::endl;
                }
                else
                {
                    *output << "***UNKNOWN***" << std::endl;
                }
            },
            value);
    }
}

void CommandListFileMetadata::onAllPropertyGroup()
{
    listAllProperties(normaliseFilename());
}

void CommandListFileMetadata::onEmptyPropertyGroup()
{
    listAllProperties(normaliseFilename());
}

void CommandListFileMetadata::onBasicPropertyGroup()
{
    FileMetadata file{ normaliseFilename() };
    const auto properties{ file.basicProperties() };
    *output << properties << std::endl;
}

void CommandListFileMetadata::onMusicPropertyGroup()
{
    FileMetadata file{ normaliseFilename() };
    const auto properties{ file.musicProperties() };
    *output << properties << std::endl;
}

void CommandListFileMetadata::onVideoPropertyGroup()
{
    FileMetadata file{ normaliseFilename() };
    const auto properties{ file.videoProperties() };
    *output << properties << std::endl;
}

void CommandListFileMetadata::onDocumentPropertyGroup()
{
    FileMetadata file{ normaliseFilename() };
    const auto properties{ file.documentProperties() };
    *output << properties << std::endl;
}

void CommandListFileMetadata::onImagePropertyGroup()
{
    FileMetadata file{ normaliseFilename() };
    const auto properties{ file.videoProperties() };
}
