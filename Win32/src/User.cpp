#include <Win32/User.hpp>

#include <memory>
#include <system_error>

namespace Win32 
{
	std::wstring User::GetWindowText(HWND hWnd)
	{
		std::wstring text;

		int length = ::GetWindowTextLength(hWnd);
		if (length)
		{
			++length;

			auto wszWindowText = new WCHAR[length];
			
			int ret = ::GetWindowText(hWnd, wszWindowText, length);
			if (ret)
			{
				text = std::wstring(wszWindowText, ret);
			}

			delete[] wszWindowText;
		}

		return text;
	}

	std::wstring User::GetClassName(HWND hWnd)
	{
		size_t bufferLength = 256;
		auto pBuffer = std::make_unique<wchar_t[]>(bufferLength);

		size_t length = 0;

		do
		{
			length = ::GetClassName(hWnd, pBuffer.get(), static_cast<int>(bufferLength));
			if (length == 0)
			{
				const auto lastError = ::GetLastError();

				throw std::system_error(
					std::error_code(lastError, std::system_category()),
					"GetClassName() returned 0"
				);
			}

			if ((length + 1) == bufferLength)
			{
				bufferLength *= 2;

				pBuffer = std::make_unique<wchar_t[]>(bufferLength);
			}
			else
			{
				break;
			}

		} while (true);

		const auto& ret = std::wstring(pBuffer.get(), length);

		return ret;
	}
}
