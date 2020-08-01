#include "MessageHandler.hpp"
#include "MessageSerializer.hpp"

namespace mlcp
{
	MessageHandler::MessageHandler()
	{
		_deserializeHandlers.emplace_back(std::make_shared<SerializerFunctionPointer<GeneralMessage>>(std::function<templateMessagePtr<GeneralMessage>(const std::string&)>(MessageSerializer::deserializeMsg<GeneralMessage>)));
		_deserializeHandlers.emplace_back(std::make_shared<SerializerFunctionPointer<ConnectMessage>>(std::function<templateMessagePtr<ConnectMessage>(const std::string&)>(MessageSerializer::deserializeMsg<ConnectMessage>)));
		
		_serializeHandlers.emplace_back(std::make_shared<SerializerFunctionPointer<GeneralMessage>>());
		_serializeHandlers.emplace_back(std::make_shared<SerializerFunctionPointer<ConnectMessage>>());
	}
}