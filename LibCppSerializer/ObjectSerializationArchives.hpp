#pragma once

#include "boost\archive\text_iarchive.hpp"
#include "boost\archive\text_oarchive.hpp"
#include "boost\archive\binary_iarchive.hpp"
#include "boost\archive\binary_oarchive.hpp"
#include <unordered_map>

namespace objserialization
{
	enum class ArchiveType
	{
		BINARY,
		TEXT
	};

	class Archives
	{
	public:
		template<typename T>
		static std::string serializeArchive(T& obj, ArchiveType ar)
		{
			static std::map<ArchiveType, std::function<std::string(T& obj)>> m;
			if (m.empty())
			{
				m[ArchiveType::BINARY] = [](T& obj) -> std::string {
					return generalSerializeArchive<boost::archive::binary_oarchive>(obj);
				};

				m[ArchiveType::TEXT] = [](T& obj) -> std::string {
					return generalSerializeArchive<boost::archive::text_oarchive>(obj);
				};
			}

			if (m.find(ar) == m.end())
				throw ObjectSerializationException(ExceptionMessageType::EXCEPTION_UNKNOWN_ARCHIVE_TYPE);

			return m[ar](obj);
		}

		template<typename T>
		static T* deserializeArchive(const std::string& str, ArchiveType ar)
		{
			static std::map<ArchiveType, std::function<T*(const std::string&)>> m;
			if (m.empty())
			{
				m[ArchiveType::BINARY] = [](const std::string& str) -> T* {
					return generalDeserializeArchive<boost::archive::binary_iarchive, T>(str);
				};

				m[ArchiveType::TEXT] = [](const std::string& str) -> T* {
					return generalDeserializeArchive<boost::archive::text_iarchive, T>(str);
				};
			}

			if (m.find(ar) == m.end())
				throw ObjectSerializationException(ExceptionMessageType::EXCEPTION_UNKNOWN_ARCHIVE_TYPE);

			return m[ar](str);
		}

	private:
		template<typename Ar, typename T>
		static std::string generalSerializeArchive(T& obj)
		{
			std::ostringstream os;
			Ar ia(os);
			ia << obj;
			return os.str();
		}

		template<typename Ar, typename T>
		static T* generalDeserializeArchive(const std::string& str)
		{
			T* result = new T();
			std::istringstream iss(str);
			Ar ia(iss);
			ia >> result;
			return result;
		}
	};
}


