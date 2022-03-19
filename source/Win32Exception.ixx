module;
#include <stdexcept>
#include <Windows.h>
export module Win32Exception;

export class Win32Exception : public std::exception
{
	uint32_t errorCode{ GetLastError() };
	void* msgBuffer{ nullptr };
public:
	Win32Exception()
	{
		getMessageForCode();
	}
	explicit Win32Exception(uint32_t errorCode)
		: errorCode{ errorCode }
	{
		getMessageForCode();
	}
	~Win32Exception()
	{
		LocalFree(msgBuffer);
	}
	char const* what() const override
	{
		return static_cast<char const*>(msgBuffer);
	}
protected:
	void getMessageForCode()
	{
		constexpr auto Flags{
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS };
		constexpr void* NoSource{ nullptr };
		constexpr auto MsgLanguage{ MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) };
		constexpr auto NoSize{ 0 };
		constexpr va_list* VaList{ nullptr };

		FormatMessageA(Flags, NoSource, errorCode, MsgLanguage, (LPSTR)&msgBuffer, NoSize, VaList);
	}
};