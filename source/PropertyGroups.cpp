#include "PropertyGroups.h"
#include <winrt/Windows.Storage.h>
#include <array>
#include <stdexcept>

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
	stream << L"DateModified = " << properties.dateModified.value() << L"\n"
		<< L"ItemDate = " << properties.itemDate.value() << L"\n"
		<< L"Size = " << properties.size.value();
	return stream;
}

std::wostream& operator<<(std::wostream& stream, const DocumentProperties& properties)
{
	stream << L"Author = " << properties.author.value() << L"\n"
		<< L"Comment = " << properties.comment.value() << L"\n"
		<< L"Keywords = " << properties.keywords.value() << L"\n"
		<< L"Title = " << properties.title.value();
	return stream;
}

std::wostream& operator<<(std::wostream& stream, const ImageProperties& properties)
{
	stream << L"CameraManufacturer = " << properties.cameraManufacturer.value() << L"\n"
		<< L"CameraModel = " << properties.cameraModel.value() << L"\n"
		<< L"DateTake = " << properties.dateTaken.value() << L"\n"
		<< L"Height = " << properties.height.value() << L"\n"
		<< L"Keywords = " << properties.keywords.value() << L"\n"
		<< L"Lattitude = " << properties.lattitude.value() << L"\n"
		<< L"Longitude = " << properties.longitude.value() << L"\n"
		<< L"Orientation = " << static_cast<std::wstring_view>(properties.orientation.value()) << L"\n"
		<< L"PeopleNames = " << properties.peopleNames.value() << L"\n"
		<< L"Rating = " << properties.rating.value() << L"\n"
		<< L"Title = " << properties.title.value() << L"\n"
		<< L"Width = " << properties.width.value();
	return stream;
}

std::wostream& operator<<(std::wostream& stream, const MusicProperties& properties)
{
	stream << L"Album = " << properties.album.value() << L"\n"
		<< L"AlbumArtist = " << properties.albumArtist.value() << L"\n"
		<< L"Artist = " << properties.artist.value() << L"\n"
		<< L"Bitrate = " << properties.bitrate.value() << L"\n"
		<< L"Composers = " << properties.composers.value() << L"\n"
		<< L"Conductors = " << properties.conductors.value() << L"\n"
		<< L"Duration = " << properties.duration.value() << L"\n"
		<< L"Genre = " << properties.genre.value() << L"\n"
		<< L"Producers = " << properties.producers.value() << L"\n"
		<< L"Publisher = " << properties.publisher.value() << L"\n"
		<< L"Rating = " << properties.rating.value() << L"\n"
		<< L"Subtitle = " << properties.subtitle.value() << L"\n"
		<< L"Title = " << properties.title.value() << L"\n"
		<< L"TrackNumber = " << properties.trackNumber.value() << L"\n"
		<< L"Writers = " << properties.writers.value() << L"\n"
		<< L"Year = " << properties.year.value();

	return stream;
}

std::wostream& operator<<(std::wostream& stream, const VideoProperties& properties)
{
	stream << L"Bitrate = " << properties.bitrate.value() << L"\n"
		<< L"Directors = " << properties.directors.value() << L"\n"
		<< L"Duration = " << properties.duration.value() << L"\n"
		<< L"Height = " << properties.height.value() << L"\n"
		<< L"Keywords = " << properties.keywords.value() << L"\n"
		<< L"Lattitude = " << properties.lattitude.value() << L"\n"
		<< L"Longitude = " << properties.longitude.value() << L"\n"
		<< L"Orientation = " << static_cast<std::wstring_view>(properties.orientation.value()) << L"\n"
		<< L"Producers = " << properties.producers.value() << L"\n"
		<< L"Publisher = " << properties.publisher.value() << L"\n"
		<< L"Rating = " << properties.rating.value() << L"\n"
		<< L"Subtitle = " << properties.subtitle.value() << L"\n"
		<< L"Title = " << properties.title.value() << L"\n"
		<< L"Width = " << properties.width.value() << L"\n"
		<< L"Writers = " << properties.writers.value() << L"\n"
		<< L"Year = " << properties.year.value();
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

DocumentProperties& DocumentProperties::operator<<(const std::pair < std::wstring_view, std::wstring_view>& newMemberVariable)
{
	auto& [key, value] {newMemberVariable};
	constexpr std::array<std::wstring_view, 4> memberNames{ {L"author", L"comment", L"keywords", L"title"} };
	if (key == L"author")
	{
		//TODO: parse string into std::vector<std::wstring>
		//author = value;
	}
	else if (key == L"comment")
	{
		comment = value;
	}
	else if (key == L"keywords")
	{
		//TODO: parse string into std::vector<std::wstring>
		//keywords = value;
	}
	else if (key == L"title")
	{
		title = value;
	}
	else
	{
		throw std::out_of_range{ "DocumentProperties doesn't have a property with that name." };
	}
	return *this;
}
