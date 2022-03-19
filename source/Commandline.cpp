#include "Commandline.h"
#include <stdexcept>
#include <iterator>
#include <span>
#include <algorithm>

std::map<std::wstring, std::wstring> Commandline::arguments;

Commandline::Commandline()
{
    assertArgumentsWereInitialized();
}

Commandline::Commandline(int argc, wchar_t* args[])
{
    initializeArguments(argc, args);
}

bool Commandline::hasKey(std::wstring_view key) const noexcept
{
    return arguments.contains(std::wstring{ key });
}

std::pair<const std::wstring, std::wstring> Commandline::getAtKey(std::wstring_view key) const
{
    std::wstring keyString{ key };
    const auto& value{ arguments.at(keyString) };
    return std::make_pair(std::move(keyString), value);
}

void Commandline::initializeArguments(int argc, wchar_t* args[])
{
    arguments.clear();
    if (argc < 0) [[unlikely]]
        throw std::invalid_argument{ "argc cannot be negative" };
    std::span<wchar_t*, std::dynamic_extent> stdargs{ args, static_cast<size_t>(argc) };
    const auto generator = [this] (const auto& arg)
    {
        arguments.emplace(splitByEquals(arg));
    };
    std::for_each(stdargs.begin(), stdargs.end(), generator);
}

std::pair<std::wstring, std::wstring> Commandline::splitByEquals(std::wstring_view argument) const noexcept
{
    const auto offset{ argument.find(L"=", 0) };
    if (offset != std::string::npos)
    {
        const auto equalsItr{ argument.begin() + offset };
        std::wstring_view key{ argument.begin(), equalsItr };
        for (auto& c : key)
        {
            const_cast<wchar_t&>(c) = static_cast<wchar_t>(std::tolower(c));
        }
        std::wstring_view value(equalsItr + 1, argument.end());
        return std::make_pair(std::wstring{key}, std::wstring{value});
    }
    else
    {
        return std::make_pair(std::wstring{ argument.begin(), argument.end() }, std::wstring{});
    }
}

void Commandline::assertArgumentsWereInitialized() const
{
    if(arguments.size() == 0) [[unlikely]] // the first argument is always the exe path, so if there are no arguments then we are not initialized.
        throw std::runtime_error{ "Have not initialized arguments. call the (argc, args[]) constructor first" };
}
