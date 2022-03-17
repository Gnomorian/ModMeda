#pragma once
#include <map>
#include <string>
#include <vector>
/// <summary>
/// Allows you to view the arguments used to to start the application.
/// the Commandline(int,wchar_t*[]) constructor must be called first, subsiquent Commandline objects can be constructed
/// with the default constructor to view them.
/// </summary>
class Commandline
{
	static std::map<std::wstring, std::wstring> arguments;
public:
	Commandline();
	Commandline(int argc, wchar_t* args[]);
	bool hasKey(std::wstring_view key) const noexcept;
	std::pair<const std::wstring, std::wstring> getAtKey(std::wstring_view key);
protected:
	void initializeArguments(int argc, wchar_t* args[]);
	std::pair<std::wstring, std::wstring> splitByEquals(std::wstring_view argument) const noexcept;
	void assertArgumentsWereInitialized() const;
};

