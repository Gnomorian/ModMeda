#include "charconversion.h"
#include <Windows.h>
#include <vector>
import Win32Exception;

std::u8string wstring_to_utf8(std::wstring_view from)
{
	constexpr auto ConvertToFormat{ CP_UTF8 };
	constexpr auto Flags{ WC_ERR_INVALID_CHARS };
	constexpr auto DefaultCharacter{ nullptr };
	constexpr auto UsedDefaultCharacter{ nullptr };
	const auto utf8BufferSize{
		[&]() -> size_t
		{
			const auto size{ WideCharToMultiByte(ConvertToFormat, Flags, from.data(), from.size(), nullptr, 0, DefaultCharacter, UsedDefaultCharacter)};
			if (size == 0)
			{
				throw Win32Exception{};
			}
			return static_cast<size_t>(size);
		}()
	};
	std::vector<char> buffer(utf8BufferSize);
	const auto size{ WideCharToMultiByte(ConvertToFormat, Flags, from.data(), from.size(), buffer.data(), utf8BufferSize, DefaultCharacter, UsedDefaultCharacter) };
	if (size == 0)
	{
		throw Win32Exception{};
	}
	return std::u8string(buffer.begin(), buffer.end());
}
