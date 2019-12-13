#include <win32/SysInfoAPI.hpp>

#include <memory>

namespace Win32
{
	namespace SysInfoAPI
	{
		std::wstring GetComputerNameEx(COMPUTER_NAME_FORMAT format)
		{
			DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1;

			auto buffer = std::make_unique<wchar_t[]>(dwSize);

			BOOL fResult = ::GetComputerNameEx(format, buffer.get(), &dwSize);
			if (fResult == FALSE && (::GetLastError() == ERROR_MORE_DATA))
			{
				buffer = std::make_unique<wchar_t[]>(dwSize);

				fResult = ::GetComputerNameEx(format, buffer.get(), &dwSize);
			}

			if (fResult == FALSE)
			{
				throw std::system_error(
					std::error_code(::GetLastError(), std::system_category()),
					"GetComputerNameEx() returned FALSE"
				);
			}

			return std::wstring(buffer.get(), dwSize);
		}
	}
}
