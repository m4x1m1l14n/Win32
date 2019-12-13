#pragma once

#include <Windows.h>

#include <string>

namespace Win32
{
	namespace SysInfoAPI
	{
		std::wstring GetComputerNameEx(COMPUTER_NAME_FORMAT format);
	}
}
