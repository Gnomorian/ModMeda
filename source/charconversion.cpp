#include "charconversion.h"
#include <Windows.h>
#include <vector>
#include <system_error>

std::u8string wstring_to_utf8(std::wstring_view from)
{
	constexpr auto ConvertToFormat{ CP_UTF8 };
	constexpr auto Flags{ WC_ERR_INVALID_CHARS };
	constexpr auto DefaultCharacter{ nullptr };
	constexpr auto UsedDefaultCharacter{ nullptr };
	constexpr auto throwSystemException = []()
	{
		throw std::system_error(std::error_code{ static_cast<int>(GetLastError()), std::system_category() });
	};
	const auto utf8BufferSize{
		[&]() -> size_t
		{
			const auto size{ WideCharToMultiByte(ConvertToFormat, Flags, from.data(), from.size(), nullptr, 0, DefaultCharacter, UsedDefaultCharacter)};
			if (size == 0)
			{
				throwSystemException();
			}
			return static_cast<size_t>(size);
		}()
	};
	std::vector<char> buffer(utf8BufferSize);
	const auto size{ WideCharToMultiByte(ConvertToFormat, Flags, from.data(), from.size(), buffer.data(), utf8BufferSize, DefaultCharacter, UsedDefaultCharacter) };
	if (size == 0)
	{
		throwSystemException();
	}
	return std::u8string(buffer.begin(), buffer.end());
}
