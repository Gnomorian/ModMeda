#pragma once
#include <chrono>
#include <vector>
#include <optional>
#include <chrono>

/*
	basic structures for the different types of properties a file can have.
	this exists as a marchaling structure to seperate WinRT and application code.
	all the properties are std::optional so they can be used to show a null value or tell WinRT to modify that property.
*/

// https://docs.microsoft.com/en-us/uwp/api/windows.storage.fileproperties.basicproperties?view=winrt-22000
struct BasicProperties
{
	/// <summary>
	/// timestamp of the last time the file was modified.
	/// </summary>
	std::optional<std::chrono::sys_time<std::chrono::nanoseconds>> dateModified;
	/// <summary>
	/// the most relevant date for the item.
	/// The system determines the most relevant date based on the type of the item. For example, if the item is a photo the date in System.Photo.DateTaken is returned. Or if the item is a song the date in System.Media.DateReleased is returned.
	/// </summary>
	std::optional<std::chrono::sys_time<std::chrono::nanoseconds>> itemDate;
	/// <summary>
	/// the size of the file in bytes.
	/// </summary>
	std::optional<uint64_t> size;

	friend std::wostream& operator<<(std::wostream& stream, const BasicProperties& properties);
};

// https://docs.microsoft.com/en-us/uwp/api/windows.storage.fileproperties.documentproperties?view=winrt-22000
struct DocumentProperties
{
	/// <summary>
	/// collection of the document's authors
	/// </summary>
	std::optional<std::vector<std::wstring>> author;
	/// <summary>
	/// comments associated with the document
	/// </summary>
	std::optional<std::wstring> comment;
	/// <summary>
	/// collection of keywords associated with the document
	/// </summary>
	std::optional<std::vector<std::wstring>> keywords;
	/// <summary>
	/// title of the document
	/// </summary>
	std::optional<std::wstring> title;

	friend std::wostream& operator<<(std::wostream& stream, const DocumentProperties& properties);
};

// https://docs.microsoft.com/en-us/uwp/api/windows.storage.fileproperties.imageproperties?view=winrt-22000
struct ImageProperties
{
	enum class PhotoOrientation
	{
		Unspecified = 0,
		Normal = 1,
		FlipHorizontal = 2,
		Rotate180 = 3,
		FlipVertical = 4,
		Transpose = 5,
		Rotate270 = 6,
		Transverse = 7,
		Rotate90 = 8,
	};
	/// <summary>
	/// manufacturer of the camera that took the photo
	/// </summary>
	std::optional<std::wstring> cameraManufacturer;
	/// <summary>
	/// model of the camera that took the photo
	/// </summary>
	std::optional<std::wstring> cameraModel;
	/// <summary>
	/// date when the image was taken
	/// </summary>
	std::optional<tm> dateTaken;
	/// <summary>
	/// height of the image
	/// </summary>
	std::optional<uint32_t> height;
	/// <summary>
	/// collection of keywords associated with the image
	/// </summary>
	std::optional<std::vector<std::wstring>> keywords;
	/// <summary>
	/// latitude coordinate where the photo was taken
	/// </summary>
	std::optional<double> lattitude;
	/// <summary>
	/// longitude coordinate where the photo was taken
	/// </summary>
	std::optional<double> longitude;
	/// <summary>
	/// Exchangeable Image File (EXIF) orientation flag of the photo
	/// </summary>
	std::optional<PhotoOrientation> orientation;
	/// <summary>
	/// names of people who are tagged in the photo
	/// </summary>
	std::vector<std::wstring> peopleNames;
	/// <summary>
	/// the rating associated with an image file.
	/// The media file rating, as a value between 0 and 99.
	/// A value of 0 indicates that the file has not been rated.
	/// </summary>
	std::optional<uint32_t> rating;
	/// <summary>
	/// the title of the image
	/// </summary>
	std::optional<std::wstring> title;
	/// <summary>
	/// width of the image
	/// </summary>
	std::optional<uint32_t> width;

	friend std::wostream& operator<<(std::wostream& stream, const ImageProperties& properties);
};

//https://docs.microsoft.com/en-us/uwp/api/windows.storage.fileproperties.musicproperties?view=winrt-22000
struct MusicProperties
{
	/// <summary>
	/// name of the album that contains the song
	/// </summary>
	std::optional<std::wstring> album;
	/// <summary>
	/// name of the album artist of the song
	/// </summary>
	std::optional<std::wstring> albumArtist;
	/// <summary>
	/// artists that contributed to the song
	/// </summary>
	std::optional<std::wstring> artist;
	/// <summary>
	/// bit rate of the song file
	/// </summary>
	std::optional<uint32_t> bitrate;
	/// <summary>
	/// composers of the song
	/// </summary>
	std::optional<std::vector<std::wstring>> composers;
	/// <summary>
	/// conductors of the song
	/// </summary>
	std::optional<std::vector<std::wstring>> conductors;
	/// <summary>
	/// duration of the song in milliseconds
	/// </summary>
	std::optional<std::chrono::duration<int64_t, std::ratio_multiply<std::ratio<100>, std::nano>>> duration;
	/// <summary>
	/// names of music genres that the song belongs to
	/// </summary>
	std::optional<std::vector<std::wstring>> genre;
	/// <summary>
	/// producers of the song
	/// </summary>
	std::optional<std::vector<std::wstring>> producers;
	/// <summary>
	/// publisher of the song
	/// </summary>
	std::optional<std::wstring> publisher;
	/// <summary>
	/// rating associated with a music file
	/// The media file rating, as a value between 0 and 99.
	/// A value of 0 indicates that the file has not been rated.
	/// </summary>
	std::optional<uint32_t> rating;
	/// <summary>
	/// the subtitle of the song
	/// </summary>
	std::optional<std::wstring> subtitle;
	/// <summary>
	/// the title of the song
	/// </summary>
	std::optional<std::wstring> title;
	/// <summary>
	/// track number of the song on the song's album
	/// </summary>
	std::optional<uint32_t> trackNumber;
	/// <summary>
	/// the songwriters
	/// </summary>
	std::optional<std::vector<std::wstring>> writers;
	/// <summary>
	/// year that the song was released
	/// </summary>
	std::optional<uint32_t> year;

	friend std::wostream& operator<<(std::wostream& stream, const MusicProperties& properties);
};

// https://docs.microsoft.com/en-us/uwp/api/windows.storage.fileproperties.videoproperties?view=winrt-22000
struct VideoProperties
{
	enum class VideoOrientation
	{
		Normal = 0,
		Rotate180 = 180,
		Rotate270 = 270,
		Rotate90 = 90
	};
	/// <summary>
	/// sum audio and video bitrate of the video
	/// </summary>
	std::optional<uint32_t> bitrate;
	/// <summary>
	/// directors of the video
	/// </summary>
	std::optional<std::vector<std::wstring>> directors;
	/// <summary>
	/// duration of the video
	/// </summary>
	std::optional<std::chrono::duration<int64_t, std::ratio_multiply<std::ratio<100>, std::nano>>> duration;
	/// <summary>
	/// height of the video
	/// </summary>
	std::optional<uint32_t> height;
	/// <summary>
	/// collection of keywords associated with the video
	/// </summary>
	std::optional<std::vector<std::wstring>> keywords;
	/// <summary>
	/// latitude coordinate where the video was shot
	/// </summary>
	std::optional<double> lattitude;
	/// <summary>
	/// longitude coordinate where the video was shot
	/// </summary>
	std::optional<double> longitude;
	/// <summary>
	/// indicates how the video should be rotated to display it correctly
	/// </summary>
	std::optional<VideoOrientation> orientation;
	/// <summary>
	/// producers of the video
	/// </summary>
	std::optional<std::vector<std::wstring>> producers;
	/// <summary>
	/// publisher of the video
	/// </summary>
	std::optional<std::wstring> publisher;
	/// <summary>
	/// rating associated with a music file
	/// The media file rating, as a value between 0 and 99.
	/// A value of 0 indicates that the file has not been rated.
	/// </summary>
	std::optional<uint32_t> rating;
	/// <summary>
	/// the subtitle of the song
	/// </summary>
	std::optional<std::wstring> subtitle;
	/// <summary>
	/// the title of the song
	/// </summary>
	std::optional<std::wstring> title;
	/// <summary>
	/// width of the video
	/// </summary>
	std::optional<uint32_t> width;
	/// <summary>
	/// the songwriters
	/// </summary>
	std::optional<std::vector<std::wstring>> writers;
	/// <summary>
	/// year that the song was released
	/// </summary>
	std::optional<uint32_t> year;

	friend std::wostream& operator<<(std::wostream& stream, const VideoProperties& properties);
};