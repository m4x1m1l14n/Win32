#pragma once

#include <Windows.h>

#include <string>

namespace Win32
{
	namespace User
	{
		std::wstring GetWindowText(HWND hWnd);
		std::wstring GetClassName(HWND hWnd);
	}
}
