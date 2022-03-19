#include "CommandListFileMetadata.h"
#include <variant>
#include <Windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <iomanip>
#include <chrono>
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;

CommandListFileMetadata::CommandListFileMetadata(std::wostream* output, const Commandline& commandline)
	: Command{output}
	, commandline{commandline}
{}

void CommandListFileMetadata::execute()
{
	const auto filename{ normaliseFilename() };
    init_apartment();
    auto file{ StorageFile::GetFileFromPathAsync(hstring{ filename.c_str() }).get()};
    if (file)
    {

        //auto basicProperties{ file.Properties().RetrievePropertiesAsync({}).get() };
        auto basicProperties{ file.GetBasicPropertiesAsync().get().RetrievePropertiesAsync({}).get() };
        for (int i{}; const auto & p : basicProperties)
        {
            const auto key{ p.Key().c_str() };
            std::wcout << ++i << L") " << key;
            if (p.Value())
            {
                std::wcout << " = ";
                auto value{ p.Value().as<IPropertyValue>() };
                const auto propertyType{ value.Type() };
                switch (propertyType)
                {
                case PropertyType::DateTime:
                {
                    const auto timepoint{ value.GetDateTime() };
                    using Type = decltype(timepoint);
                    const auto t_c{ Type::clock::to_time_t(timepoint) };
                    tm time{};
                    const auto result{ localtime_s(&time, &t_c) };
                    std::wcout << std::put_time(&time, L"%F %T.\n");
                    break;
                }
                case PropertyType::String:
                {
                    const auto string{ value.GetString() };
                    std::wcout << string.c_str();
                    break;
                }
                case PropertyType::Boolean:
                {
                    const auto boolean{ value.GetBoolean() };
                    std::wcout << std::boolalpha << boolean;
                    break;
                }
                case PropertyType::Double:
                    std::wcout << value.GetDouble();
                    break;
                case PropertyType::Char16:
                    std::wcout << static_cast<wchar_t>(value.GetChar16());
                    break;
                case PropertyType::Int16:
                    std::wcout << static_cast<int16_t>(value.GetInt16());
                    break;
                case PropertyType::UInt32:
                    std::wcout << static_cast<uint32_t>(value.GetUInt32());
                    break;
                case PropertyType::Int32:
                    std::wcout << static_cast<int32_t>(value.GetInt32());
                    break;
                case PropertyType::Int64:
                    std::wcout << static_cast<int64_t>(value.GetInt64());
                    break;
                case PropertyType::UInt64:
                    std::wcout << static_cast<uint64_t>(value.GetUInt64());
                    break;
                case PropertyType::StringArray:
                {
                    com_array<hstring> strArray;
                    value.GetStringArray(strArray);
                    for (bool first{ true }; const auto & str : strArray)
                    {
                        if (first)
                            first = false;
                        else
                            std::wcout << L';';
                        std::wcout << L'"' << str.c_str() << L'"';

                    }
                    break;
                }
                default:
                    std::wcout << L"? type = " << static_cast<int>(propertyType);
                }
            }
            std::wcout << std::endl;
        }
    }
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
