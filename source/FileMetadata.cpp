#include "FileMetadata.h"
#include <Windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;

FileMetadata::FileMetadata(std::filesystem::path file)
    : filename{file}
{
    winrt::init_apartment();
}

BasicProperties FileMetadata::basicProperties() const
{
    return BasicProperties();
}

std::map<std::wstring, PropertyVariant> FileMetadata::allProperties() const
{
    auto file{ StorageFile::GetFileFromPathAsync(hstring{ filename.c_str() }).get() };
    const auto winrtproperties{ file.Properties().RetrievePropertiesAsync({}).get() };
    std::map<std::wstring, PropertyVariant> stdproperties;
    for (const auto& prop : winrtproperties)
    {
        const auto key{ prop.Key() };
        const auto value{
            [&]
            {
                if (prop.Value())
                {
                    auto value{ prop.Value().as<IPropertyValue>() };
                    return propertyValueToVariant(value);
                }
                else
                {
                    return PropertyVariant{};
                }
            }()
        };
        stdproperties.emplace(key, value);
    }
    return stdproperties;
}

DocumentProperties FileMetadata::documentProperties() const
{
    return DocumentProperties();
}

MusicProperties FileMetadata::musicProperties() const
{
    return MusicProperties();
}

VideoProperties FileMetadata::videoProperties() const
{
    return VideoProperties();
}

PropertyVariant FileMetadata::propertyValueToVariant(const winrt::Windows::Foundation::IPropertyValue& property) const
{
    const auto propertyType{ property.Type() };
    switch (propertyType)
    {
    case PropertyType::DateTime:
    {
        const auto timepoint{ property.GetDateTime() };
        using Type = decltype(timepoint);
        const auto t_c{ Type::clock::to_time_t(timepoint) };
        tm time{};
        (void)localtime_s(&time, &t_c);
        return PropertyVariant{ time };
    }
    case PropertyType::String:
    {
        const auto string{ property.GetString() };
        return PropertyVariant{ std::wstring{string} };
    }
    case PropertyType::Boolean:
    {
        const auto boolean{ property.GetBoolean() };
        return PropertyVariant{ boolean };
    }
    case PropertyType::Single:
        return PropertyVariant{ property.GetSingle() };
    case PropertyType::Double:
        return PropertyVariant{ property.GetDouble() };
    case PropertyType::Char16:
        return PropertyVariant{ static_cast<wchar_t>(property.GetChar16()) };
    case PropertyType::Int16:
        return PropertyVariant{ property.GetInt16() };
    case PropertyType::UInt32:
        return PropertyVariant{ property.GetUInt32() };
    case PropertyType::Int32:
        return PropertyVariant{ property.GetInt32() };
    case PropertyType::Int64:
        return PropertyVariant{ property.GetInt64() };
    case PropertyType::UInt64:
        return PropertyVariant{ property.GetUInt64() };
    case PropertyType::StringArray:
    {
        using Vector_t = std::vector<std::wstring>;
        com_array<hstring> strArray;
        property.GetStringArray(strArray);
        PropertyVariant vector{ std::in_place_type_t<Vector_t>{} };
        for (const auto& str : strArray)
        {
            std::get<Vector_t>(vector).emplace_back(str);
        }
        return vector;
    }
    case PropertyType::Empty:
        return PropertyVariant{};
    default:
        return PropertyVariant{};
    }
}
