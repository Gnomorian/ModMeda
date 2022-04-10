#pragma once
#include <filesystem>
#include <vector>

struct FolderFilter
{
	using Results = std::vector<std::filesystem::path>;
	Results filterByRegex(const std::filesystem::path& folder, const std::wstring_view filter, const bool recurrsive) const;
};

