#pragma once
#include <filesystem>
#include <variant>
#include "PropertyGroups.h"
#include <map>
#include <vector>

using PropertyVariant = std::variant<
    std::monostate, uint8_t, int16_t, uint16_t, int32_t, 
    uint32_t, int64_t, uint64_t, float, double, wchar_t, 
    bool, std::wstring, tm, std::chrono::duration<int64_t, std::milli>, 
    std::vector<std::wstring>>;

namespace winrt::Windows::Foundation
{
	struct IPropertyValue;
}

class FileMetadata
{
	std::filesystem::path filename;
public:
	FileMetadata(std::filesystem::path file);
	BasicProperties basicProperties() const;
	std::map<std::wstring, PropertyVariant> allProperties() const;
	DocumentProperties documentProperties() const;
	MusicProperties musicProperties() const;
	VideoProperties videoProperties() const;
protected:
	PropertyVariant propertyValueToVariant(const winrt::Windows::Foundation::IPropertyValue& property) const;
};

