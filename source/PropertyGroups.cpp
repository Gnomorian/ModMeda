#include "PropertyGroups.h"
#include <winrt/Windows.Storage.h>
#include <array>

template<typename Duration, typename Elem>
std::basic_ostream<Elem>& operator<<(std::basic_ostream<Elem>& stream, std::chrono::sys_time<Duration> time)
{
	constexpr auto formatStr{
		[&]() consteval
		{
			using CharType = std::remove_reference_t<decltype(stream)>::char_type;
			static_assert(std::is_same_v<CharType, wchar_t> || std::is_same_v<CharType, char>);
			if constexpr (std::is_same_v<CharType, char>)
			{
				return "{:%F %H:%M:%OS}";
			}
			else if constexpr (std::is_same_v<CharType, wchar_t>)
			{
				return L"{:%F %H:%M:%OS}";
			}
		}()
	};
	stream << std::format(formatStr, time);
	return stream;
}

std::wostream& operator<<(std::wostream& stream, const std::vector<std::wstring>& strings)
{
	stream << L"Size(" << strings.size() << L")";
	if (strings.size() == 0)
		return stream;

	for (const auto & s : strings)
	{
		stream << L"\t\"" << s << "\"\n";
	}
	return stream;
}

std::wostream& operator<<(std::wostream& stream, const BasicProperties& properties)
{
	stream << L"DateModified = " << properties.dateModified.value() << std::endl
		<< L"ItemDate = " << properties.itemDate.value() << std::endl
		<< L"Size = " << properties.size.value();
	return stream;
}

std::wostream& operator<<(std::wostream& stream, const DocumentProperties& properties)
{
	stream << L"Author = " << properties.author.value() << std::endl
		<< L"Comment = " << properties.comment.value() << std::endl
		<< L"Keywords = " << properties.keywords.value() << std::endl
		<< L"Title = " << properties.title.value();
	return stream;
}

std::wostream& operator<<(std::wostream& stream, const ImageProperties& properties)
{
	stream << L"CameraManufacturer = " << properties.cameraManufacturer.value() << std::endl
		<< L"CameraModel = " << properties.cameraModel.value() << std::endl
		<< L"DateTake = " << properties.dateTaken.value() << std::endl
		<< L"Height = " << properties.height.value() << std::endl
		<< L"Keywords = " << properties.keywords.value() << std::endl
		<< L"Lattitude = " << properties.lattitude.value() << std::endl
		<< L"Longitude = " << properties.longitude.value() << std::endl
		<< L"Orientation = " << static_cast<std::wstring_view>(properties.orientation.value()) << std::endl
		<< L"PeopleNames = " << properties.peopleNames.value() << std::endl
		<< L"Rating = " << properties.rating.value() << std::endl
		<< L"Title = " << properties.title.value() << std::endl
		<< L"Width = " << properties.width.value();
	return stream;
}

std::wostream& operator<<(std::wostream& stream, const MusicProperties& properties)
{
	stream << L"Album = " << properties.album.value() << std::endl
		<< L"AlbumArtist = " << properties.albumArtist.value() << std::endl
		<< L"Artist = " << properties.artist.value() << std::endl
		<< L"Bitrate = " << properties.bitrate.value() << std::endl
		<< L"Composers = " << properties.composers.value() << std::endl
		<< L"Conductors = " << properties.conductors.value() << std::endl
		<< L"Duration = " << properties.duration.value() << std::endl
		<< L"Genre = " << properties.genre.value() << std::endl
		<< L"Producers = " << properties.producers.value() << std::endl
		<< L"Publisher = " << properties.publisher.value() << std::endl
		<< L"Rating = " << properties.rating.value() << std::endl
		<< L"Subtitle = " << properties.subtitle.value() << std::endl
		<< L"Title = " << properties.title.value() << std::endl
		<< L"TrackNumber = " << properties.trackNumber.value() << std::endl
		<< L"Writers = " << properties.writers.value() << std::endl
		<< L"Year = " << properties.year.value();

	return stream;
}

std::wostream& operator<<(std::wostream& stream, const VideoProperties& properties)
{
	stream << L"Bitrate = " << properties.bitrate.value() << std::endl
		<< L"Directors = " << properties.directors.value() << std::endl
		<< L"Duration = " << properties.duration.value() << std::endl
		<< L"Height = " << properties.height.value() << std::endl
		<< L"Keywords = " << properties.keywords.value() << std::endl
		<< L"Lattitude = " << properties.lattitude.value() << std::endl
		<< L"Longitude = " << properties.longitude.value() << std::endl
		<< L"Orientation = " << static_cast<std::wstring_view>(properties.orientation.value()) << std::endl
		<< L"Producers = " << properties.producers.value() << std::endl
		<< L"Publisher = " << properties.publisher.value() << std::endl
		<< L"Rating = " << properties.rating.value() << std::endl
		<< L"Subtitle = " << properties.subtitle.value() << std::endl
		<< L"Title = " << properties.title.value() << std::endl
		<< L"Width = " << properties.width.value() << std::endl
		<< L"Writers = " << properties.writers.value() << std::endl
		<< L"Year = " << properties.year.value() << std::endl;
	return stream;
}

ImageProperties::PhotoOrientation::PhotoOrientation()
	: index{}
{}

ImageProperties::PhotoOrientation::PhotoOrientation(int32_t orientation)
	:index{static_cast<uint8_t>(orientation)}
{}

ImageProperties::PhotoOrientation::PhotoOrientation(winrt::Windows::Storage::FileProperties::PhotoOrientation orientation)
	: index{ static_cast<uint8_t>(static_cast<int32_t>(orientation)) }
{}

constexpr std::pair<winrt::Windows::Storage::FileProperties::VideoOrientation, std::wstring_view> VideoProperties::VideoOrientation::orientationByName[4]
{
	{ winrt::Windows::Storage::FileProperties::VideoOrientation::Normal, L"Normal" },
	{ winrt::Windows::Storage::FileProperties::VideoOrientation::Rotate180, L"Rotate180" },
	{ winrt::Windows::Storage::FileProperties::VideoOrientation::Rotate270, L"Rotate270" },
	{ winrt::Windows::Storage::FileProperties::VideoOrientation::Rotate90, L"Rotate90" }
};

VideoProperties::VideoOrientation::VideoOrientation()
	: index{}
{}

VideoProperties::VideoOrientation::VideoOrientation(int32_t orientation)
	: index{static_cast<uint8_t>(orientation)}
{}

VideoProperties::VideoOrientation::VideoOrientation(winrt::Windows::Storage::FileProperties::VideoOrientation orientation)
	: index{static_cast<uint8_t>(orientation)}
{}



VideoProperties::VideoOrientation::operator std::wstring_view() const
{
	return {};
}

VideoProperties::VideoOrientation::operator winrt::Windows::Storage::FileProperties::VideoOrientation() const
{
	return static_cast<winrt::Windows::Storage::FileProperties::VideoOrientation>(index);
}

ImageProperties::PhotoOrientation::operator std::wstring_view() const
{
	return orientationByName[index];
}

ImageProperties::PhotoOrientation::operator winrt::Windows::Storage::FileProperties::PhotoOrientation() const
{
	return static_cast<winrt::Windows::Storage::FileProperties::PhotoOrientation>(index);
}
