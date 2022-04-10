#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
/// <summary>
/// Allows you to view the arguments used to to start the application.
/// the Commandline(int,wchar_t*[]) constructor must be called first, subsiquent Commandline objects can be constructed
/// with the default constructor to view them.
/// </summary>
class Commandline
{
public:
	using ArgumentsMap = std::map<std::wstring, std::wstring>;
	Commandline();
	bool hasKey(std::wstring_view key) const noexcept;
	std::pair<const std::wstring, std::wstring> getAtKey(std::wstring_view key) const;
	static const Commandline& setupCommandlineWithArgs(int argc, wchar_t* args[]);
protected:
	Commandline(int argc, wchar_t* args[]);
	void initializeArguments(int argc, wchar_t* args[]);
	std::pair<std::wstring, std::wstring> splitByEquals(std::wstring_view argument) const noexcept;
	void assertArgumentsWereInitialized() const;
private:
	ArgumentsMap arguments;
	static std::unique_ptr<const Commandline> realCommandline;
};

