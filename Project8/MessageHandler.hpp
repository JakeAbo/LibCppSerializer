#pragma once
#include <memory>
#include "SerializerFunctionPointer.hpp"

namespace mlcp
{
	typedef std::shared_ptr<SerializerFunctionPointerBase> SerializeCallBack;
	typedef std::vector<SerializeCallBack> SerializeHandlersPool;
	typedef std::vector<SerializeCallBack> DeserializeHandlersPool;

	class MessageHandler
	{
	private:
		SerializeHandlersPool _serializeHandlers;
		DeserializeHandlersPool _deserializeHandlers;

		MessageHandler();

	public:
		static MessageHandler& instance()
		{
			static MessageHandler instance;
			return instance;
		}

		template<typename T>
		std::string runSerializeHandler(const msgType& type, const T msg)
		{
			return _serializeHandlers[type]->serialize(msg);
		}

		GeneralMessagePtr runDesrializeHandler(const msgType& type, const std::string str)
		{
			return _deserializeHandlers[type]->deserialize(str);
		}
	};
}