#pragma once
#include <map>
#include "SerializerFunctionPointer.hpp"
#include "MessageHandler.hpp"

namespace mlcp
{
	class MessageSerializer
	{
	public:
		static MessageSerializer& instance()
		{
			static MessageSerializer instance;
			return instance;
		}

		template<class T>
		static const std::string serializeMsg(const T msg)
		{
			return mlcp::runSerializeHandler(msg->getType(), msg);
		}
				
		template<class T>
		static templateMessagePtr<T> deserializeMsg(const std::string& str)
		{
			templateMessagePtr<T> result = new T();
			std::istringstream iss(str);
			boost::archive::binary_iarchive ia(iss);
			ia >> result;
			return result;
		}

		static GeneralMessagePtr deserializeMsg(const std::string& str)
		{
			std::string substr;
			msgType type;
			size_t index;

			index = str.length() - 1;
			type = (msgType)(str[index]);
			substr = str.substr(0, index);
			
			return mlcp::runDesrializeHandler(type, substr);
		}
	
	private:
		MessageSerializer() = default;
	};

}
