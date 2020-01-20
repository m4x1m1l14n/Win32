#include <win32/DataProtection.hpp>

#include <assert.h>
#include <system_error>

namespace Win32 
{
	std::string DataProtection::ProtectData(const std::string & unprotectedData, const std::string & optionalEntropy, ProtectDataFlags flags)
	{
		DATA_BLOB dataInBlob;

		dataInBlob.pbData = reinterpret_cast<BYTE*>(const_cast<char*>(unprotectedData.c_str()));
		dataInBlob.cbData = static_cast<DWORD>(unprotectedData.length());

		DATA_BLOB optionalEntropyBlob;
		PDATA_BLOB pOptionalEntropyBlob = nullptr;
		
		if (!optionalEntropy.empty())
		{
			optionalEntropyBlob.pbData = reinterpret_cast<BYTE*>(const_cast<char*>(optionalEntropy.c_str()));
			optionalEntropyBlob.cbData = static_cast<DWORD>(optionalEntropy.length());

			pOptionalEntropyBlob = &optionalEntropyBlob;
		}

		DATA_BLOB dataOutBlob;

		dataOutBlob.pbData = nullptr;
		dataOutBlob.cbData = 0;

		BOOL fSuccess = ::CryptProtectData(&dataInBlob, nullptr, pOptionalEntropyBlob, nullptr, nullptr, static_cast<DWORD>(flags), &dataOutBlob);
		if (!fSuccess)
		{
			auto ec = std::error_code(::GetLastError(), std::system_category());

			throw std::system_error(ec, "CryptProtectData() returned FALSE.");
		}

		assert(dataOutBlob.pbData != nullptr);
		assert(dataOutBlob.cbData != 0);

		auto protectedData = std::string(reinterpret_cast<char*>(dataOutBlob.pbData), static_cast<size_t>(dataOutBlob.cbData));

		::LocalFree(dataOutBlob.pbData);
	
		return protectedData;
	}

	std::string DataProtection::UnprotectData(const std::string & protectedData, const std::string & optionalEntropy, ProtectDataFlags flags)
	{
		DATA_BLOB dataInBlob;

		dataInBlob.pbData = reinterpret_cast<BYTE*>(const_cast<char*>(protectedData.c_str()));
		dataInBlob.cbData = static_cast<DWORD>(protectedData.length());

		DATA_BLOB optionalEntropyBlob;
		PDATA_BLOB pOptionalEntropyBlob = nullptr;

		if (!optionalEntropy.empty())
		{
			optionalEntropyBlob.pbData = reinterpret_cast<BYTE*>(const_cast<char*>(optionalEntropy.c_str()));
			optionalEntropyBlob.cbData = static_cast<DWORD>(optionalEntropy.length());

			pOptionalEntropyBlob = &optionalEntropyBlob;
		}

		DATA_BLOB dataOutBlob;

		dataOutBlob.pbData = nullptr;
		dataOutBlob.cbData = 0;

		BOOL fSuccess = ::CryptUnprotectData(&dataInBlob, nullptr, pOptionalEntropyBlob, nullptr, nullptr, static_cast<DWORD>(flags), &dataOutBlob);
		if (!fSuccess)
		{
			auto ec = std::error_code(::GetLastError(), std::system_category());

			throw std::system_error(ec, "CryptUnprotectData() returned FALSE.");
		}

		assert(dataOutBlob.pbData != nullptr);
		assert(dataOutBlob.cbData != 0);

		auto unprotectedData = std::string(reinterpret_cast<char*>(dataOutBlob.pbData), static_cast<size_t>(dataOutBlob.cbData));

		::LocalFree(dataOutBlob.pbData);

		return unprotectedData;
	}
}
