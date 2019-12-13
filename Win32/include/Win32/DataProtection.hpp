#pragma once

#include <Windows.h>
#include <dpapi.h>

#include <string>

namespace Win32
{
	namespace DataProtection
	{
		enum class ProtectDataFlags : DWORD
		{
			LocalMachine = CRYPTPROTECT_LOCAL_MACHINE,
			UIForbidden = CRYPTPROTECT_UI_FORBIDDEN,
			Audit = CRYPTPROTECT_AUDIT
		};

		DEFINE_ENUM_FLAG_OPERATORS(ProtectDataFlags);

		std::string ProtectData(const std::string& unprotectedData, const std::string& optionalEntropy = std::string(), ProtectDataFlags flags = ProtectDataFlags::LocalMachine);
		std::string UnprotectData(const std::string& protectedData, const std::string& optionalEntropy = std::string(), ProtectDataFlags flags = ProtectDataFlags::LocalMachine);
	}
}
