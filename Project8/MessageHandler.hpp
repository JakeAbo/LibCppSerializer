#pragma once
#include <memory>
#include "SerializerFunctionPointer.hpp"

namespace mlcp
{
	typedef std::shared_ptr<SerializerFunctionPointerBase> SerializeCallBack;
	typedef std::vector<SerializeCallBack> SerializeHandlersPool;
	typedef std::vector<SerializeCallBack> DeserializeHandlersPool;

	inline SerializeHandlersPool& getSerializers()
	{
		static SerializeHandlersPool serializeHandlers;
		return serializeHandlers;
	}

	inline DeserializeHandlersPool& getDeserializers()
	{
		static DeserializeHandlersPool deserializeHandlers;
		return deserializeHandlers;
	}

	template<typename T>
	static std::string runSerializeHandler(const msgType& type, const T msg)
	{
		return getSerializers()[type]->serialize(msg);
	}

	template<typename T>
	static std::string runSerializeHandler(const msgType& type, std::shared_ptr<T> msg)
	{
		return runSerializeHandler(type, msg.get());
	}

	template<typename T>
	static std::string runSerializeHandler(const msgType& type, std::unique_ptr<T> msg)
	{
		return runSerializeHandler(type, msg.get());
	}

	static GeneralMessagePtr runDesrializeHandler(const msgType& type, const std::string str)
	{
		return getDeserializers()[type]->deserialize(str);
	}

	template<typename T>
	static const msgType getMessageType()
	{
		size_t i;
		
		for (i = 0; i < getSerializers().size(); i++)
		{
			std::shared_ptr<SerializerFunctionPointerBase> temp = getSerializers()[i];
			auto check = std::dynamic_pointer_cast<SerializerFunctionPointer<T>>(temp);
			if (check != nullptr) return static_cast<msgType>(i);
		}
		
		std::cout << "unregistered type" << std::endl;
		return TYPE_GENERAL_MSG;
	}

	template<typename Class>
	class MessageHandler
	{
	private:
		MessageHandler()
		{
			getDeserializers().emplace_back(std::make_shared<SerializerFunctionPointer<Class>>(std::function<templateMessagePtr<Class>(const std::string&)>(MessageSerializer::deserializeMsg<Class>)));
			getSerializers().emplace_back(std::make_shared<SerializerFunctionPointer<Class>>());
		}

	public:
		static MessageHandler<Class>& instance()
		{
			static MessageHandler<Class> instance;
			return instance;
		}
	};
}

#define MESSAGE_REGISTER(TYPE)												  \
    namespace mlcpreg {	                                                      \
    namespace                                                                 \
    {                                                                         \
        template<class T>                                                     \
        class MessageRegistration;											  \
                                                                              \
        template<>                                                            \
        class MessageRegistration<TYPE>										  \
        {                                                                     \
            static const ::mlcp::MessageHandler<TYPE>& reg;					  \
        };                                                                    \
                                                                              \
        const ::mlcp::MessageHandler<TYPE>&									  \
			MessageRegistration<TYPE>::reg =                                  \
                ::mlcp::MessageHandler<TYPE>::instance();					  \
    }}

MESSAGE_REGISTER(mlcp::GeneralMessage);
