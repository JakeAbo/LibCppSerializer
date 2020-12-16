#pragma once
#include <stdexcept>
#include <map>

namespace objserialization
{
	enum class ExceptionMessageType
	{
		EXCEPTION_REGISTERY,
		EXCEPTION_TYPE,
		EXCEPTION_UNKNOWN_ARCHIVE_TYPE
	};

	class ExceptionMessages
	{
	public:
		static const std::string& getMessage(ExceptionMessageType msgType)
		{
			static std::map<ExceptionMessageType, const std::string> msgs;
			static std::string unknownExceptionMessage = "Unknown Exception";

			if (msgs.empty())
			{
				msgs.insert(std::make_pair<ExceptionMessageType, const std::string>(ExceptionMessageType::EXCEPTION_REGISTERY,	"Class registery failed"));
				msgs.insert(std::make_pair<ExceptionMessageType, const std::string>(ExceptionMessageType::EXCEPTION_TYPE, "Class type is undefined"));
				msgs.insert(std::make_pair<ExceptionMessageType, const std::string>(ExceptionMessageType::EXCEPTION_UNKNOWN_ARCHIVE_TYPE, "Archive type is unknown"));
			}

			auto it = msgs.find(msgType);
			if (it == msgs.end())
			{
				return unknownExceptionMessage;
			}

			return it->second;
		}
	};

	class ObjectSerializationException : public std::runtime_error
	{
	public:
		ObjectSerializationException(ExceptionMessageType msgType)
			: runtime_error(ExceptionMessages::getMessage(msgType))
		{}
	};
}