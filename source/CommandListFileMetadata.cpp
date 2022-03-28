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

void CommandListFileMetadata::listBasicProperties(const std::filesystem::path& filename) const
{
    FileMetadata file{ filename };
    const auto properties{ file.basicProperties() };
    *output << L"DateModified = " <<  properties.dateModified.value() << std::endl
        << L"ItemDate = " << properties.itemDate.value() << std::endl
        << L"Size = " << properties.size.value() << std::endl;
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
    listBasicProperties(normaliseFilename());
}

void CommandListFileMetadata::onMusicPropertyGroup()
{
}

void CommandListFileMetadata::onVideoPropertyGroup()
{
}

void CommandListFileMetadata::onDocumentPropertyGroup()
{
}
