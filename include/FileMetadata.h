#pragma once
#include <filesystem>
#include <variant>
#include "PropertyGroups.h"
#include <map>

using PropertyVariant = std::variant<std::monostate>;

class FileMetadata
{
public:
	BasicProperties basicProperties() const;
	std::map<std::wstring, PropertyVariant> allProperties() const;
	DocumentProperties documentProperties() const;
	MusicProperties musicProperties() const;
	VideoProperties videoProperties() const;
};

