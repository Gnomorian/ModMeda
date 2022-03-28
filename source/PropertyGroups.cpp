#include "PropertyGroups.h"
#include <winrt/Windows.Storage.h>

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
		<< L"" << properties.cameraModel.value() << std::endl
		<< L"" << properties.dateTaken.value() << std::endl
		<< L"" << properties.height.value() << std::endl
		<< L"" << properties.keywords.value() << std::endl
		<< L"" << properties.lattitude.value() << std::endl
		<< L"" << properties.longitude.value() << std::endl
		<< L"" << static_cast<std::wstring_view>(properties.orientation.value()) << std::endl
		<< L"" << properties.peopleNames.value() << std::endl
		<< L"" << properties.rating.value() << std::endl
		<< L"" << properties.title.value() << std::endl
		<< L"" << properties.title.value() << std::endl
		<< L"" << properties.width.value() << std::endl;
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
	throw std::runtime_error{ "unimplemented formatting function" };
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

ImageProperties::PhotoOrientation::operator std::wstring_view() const
{
	return orientationByName[index];
}

ImageProperties::PhotoOrientation::operator winrt::Windows::Storage::FileProperties::PhotoOrientation() const
{
	return static_cast<winrt::Windows::Storage::FileProperties::PhotoOrientation>(index);
}
