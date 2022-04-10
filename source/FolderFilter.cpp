#include "FolderFilter.h"
#include <regex>

FolderFilter::Results FolderFilter::filterByRegex(const std::filesystem::path& folder, const std::wstring_view filter, const bool recurrsive) const
{
    Results results;
    constexpr auto flags{ std::regex_constants::ECMAScript | std::regex_constants::icase };
    auto adder = [&results, re = std::wregex{filter.data(), flags }](const std::filesystem::path& path)
    {
        if (std::regex_search(path.wstring().data(), re))
        {
            results.emplace_back(path);
        }
    };
    if (recurrsive)
    {
        for (const auto& path : std::filesystem::recursive_directory_iterator{ folder })
        {
            adder(path);
        }
    }
    else
    {
        for (const auto& path : std::filesystem::directory_iterator{ folder })
        {
            adder(path);
        }
    }
    return results;
}
