#include "FileMetadata.h"

BasicProperties FileMetadata::basicProperties() const
{
    return BasicProperties();
}

std::map<std::wstring, PropertyVariant> FileMetadata::allProperties() const
{
    return std::map<std::wstring, PropertyVariant>();
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
