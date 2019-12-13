#include <Win32/User.hpp>

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
}
