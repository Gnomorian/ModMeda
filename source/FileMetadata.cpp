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

auto getTm = [](const auto&& dateTime)
{
    using Type = DateTime;
    const auto t_c{ Type::clock::to_time_t(dateTime) };
    tm time{};
    (void)localtime_s(&time, &t_c);
    return time;
};

BasicProperties FileMetadata::basicProperties() const
{
    const auto file{ StorageFile::GetFileFromPathAsync(hstring{ filename.c_str() }).get() };
    const auto winrtprops{ file.GetBasicPropertiesAsync().get() };

    return BasicProperties{
        .dateModified{winrt::clock::to_sys(winrtprops.DateModified())},
        .itemDate{winrt::clock::to_sys(winrtprops.ItemDate())},
        .size{winrtprops.Size()}
    };
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

auto ivecstrToStd = [](const auto&& ivec)
{
    std::vector<std::wstring> stdvec;
    for (const auto& s : ivec)
        stdvec.emplace_back(s);
    return stdvec;
};

DocumentProperties FileMetadata::documentProperties() const
{
    const auto file{ StorageFile::GetFileFromPathAsync(hstring{ filename.c_str() }).get() };
    const auto docProperties{ file.Properties().GetDocumentPropertiesAsync().get() };
    return DocumentProperties{ 
        .author{ivecstrToStd(docProperties.Author())},
        .comment{static_cast<std::wstring>(docProperties.Comment())},
        .keywords{ivecstrToStd(docProperties.Keywords())},
        .title{static_cast<std::wstring>(docProperties.Title())}
    };
}

//using TimeSpan = std::chrono::duration<int64_t, impl::filetime_period>;
//using DateTime = std::chrono::time_point<clock, TimeSpan>;

MusicProperties FileMetadata::musicProperties() const
{
    const auto file{ StorageFile::GetFileFromPathAsync(hstring{ filename.c_str() }).get() };
    const auto musicProperties{ file.Properties().GetMusicPropertiesAsync().get() };

    return MusicProperties{
        .album{static_cast<std::wstring>(musicProperties.Album())},
        .albumArtist{static_cast<std::wstring>(musicProperties.AlbumArtist())},
        .artist{static_cast<std::wstring>(musicProperties.Artist())},
        .bitrate{musicProperties.Bitrate()},
        .composers{ivecstrToStd(musicProperties.Composers())},
        .conductors{ivecstrToStd(musicProperties.Conductors())},
        .duration{musicProperties.Duration()},
        .genre{ivecstrToStd(musicProperties.Genre())},
        .producers{ivecstrToStd(musicProperties.Producers())},
        .publisher{static_cast<std::wstring>(musicProperties.Publisher())},
        .rating{musicProperties.Rating()},
        .subtitle{static_cast<std::wstring>(musicProperties.Subtitle())},
        .title{static_cast<std::wstring>(musicProperties.Title())},
        .trackNumber{musicProperties.TrackNumber()},
        .writers{ivecstrToStd(musicProperties.Writers())},
        .year{musicProperties.Year()}
    };
}

VideoProperties FileMetadata::videoProperties() const
{
    const auto file{ StorageFile::GetFileFromPathAsync(hstring{ filename.c_str() }).get() };
    const auto videoProperties{ file.Properties().GetVideoPropertiesAsync().get() };

    return VideoProperties{
        .bitrate{videoProperties.Bitrate()},
        .directors{ivecstrToStd(videoProperties.Directors())},
        .duration{videoProperties.Duration()},
        .height{videoProperties.Height()},
        .keywords{ivecstrToStd(videoProperties.Keywords())},
        .lattitude{videoProperties.Latitude().GetDouble()},
        .longitude{videoProperties.Longitude().GetDouble()},
        .orientation{static_cast<VideoProperties::VideoOrientation>(videoProperties.Orientation())},
        .producers{ivecstrToStd(videoProperties.Producers())},
        .publisher{static_cast<std::wstring>(videoProperties.Publisher())},
        .rating{videoProperties.Rating()},
        .subtitle{static_cast<std::wstring>(videoProperties.Subtitle())},
        .title{static_cast<std::wstring>(videoProperties.Title())},
        .width{videoProperties.Width()},
        .writers{ivecstrToStd(videoProperties.Writers())},
        .year{videoProperties.Year()}
    };
}

ImageProperties FileMetadata::imageProperties() const
{
    const auto file{ StorageFile::GetFileFromPathAsync(hstring{ filename.c_str() }).get() };
    const auto imageProperties{ file.Properties().GetImagePropertiesAsync().get() };
    if (!imageProperties)
        throw std::runtime_error{ "imageProperties didnt exist" };
    return ImageProperties{
        .cameraManufacturer{static_cast<std::wstring>(imageProperties.CameraManufacturer())},
        .cameraModel{static_cast<std::wstring>(imageProperties.CameraModel())},
        .dateTaken{winrt::clock::to_sys(imageProperties.DateTaken())},
        .height{imageProperties.Height()},
        .keywords{ivecstrToStd(imageProperties.Keywords())},
        .lattitude{imageProperties.Latitude() ? imageProperties.Latitude().GetDouble() : 0.0},
        .longitude{imageProperties.Longitude() ? imageProperties.Longitude().GetDouble() : 0.0},
        .orientation{static_cast<ImageProperties::PhotoOrientation>(imageProperties.Orientation())},
        .peopleNames{ivecstrToStd(imageProperties.PeopleNames())},
        .rating{imageProperties.Rating()},
        .title{static_cast<std::wstring>(imageProperties.Title())},
        .width{imageProperties.Width()},
    };
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
