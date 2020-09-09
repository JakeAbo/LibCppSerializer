#pragma once
#include <memory>
#include "SerializerFunctionPointer.hpp"

namespace objserialization
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
	static std::string runSerializeHandler(const objType& type, const T obj)
	{
		return getSerializers()[type.value()]->serialize(obj);
	}

	template<typename T>
	static std::string runSerializeHandler(const objType& type, std::shared_ptr<T> obj)
	{
		return runSerializeHandler(type, obj.get());
	}

	template<typename T>
	static std::string runSerializeHandler(const objType& type, std::unique_ptr<T> obj)
	{
		return runSerializeHandler(type, obj.get());
	}

	static BaseObjectPtr runDesrializeHandler(const objType& type, const std::string str)
	{
		return getDeserializers()[type.value()]->deserialize(str);
	}

	template<typename T>
	static const objType getObjectType()
	{	
		for (size_t i = 0; i < getSerializers().size(); i++)
		{
			auto check = std::dynamic_pointer_cast<SerializerFunctionPointer<T>>(getSerializers()[i]);
			if (check != nullptr) return objType(i);
		}
		
		return objType();
	}

	template<typename Class>
	class ObjectRegistry
	{
	private:
		ObjectRegistry()
		{
			getDeserializers().emplace_back(std::make_shared<SerializerFunctionPointer<Class>>(std::function<templateObjectPtr<Class>(const std::string&)>(ObjectSerializer::deserializeObj<Class>)));
			getSerializers().emplace_back(std::make_shared<SerializerFunctionPointer<Class>>());
		}

	public:
		static ObjectRegistry<Class>& instance()
		{
			static ObjectRegistry<Class> instance;
			return instance;
		}
	};
}

#define OBJECT_REGISTER(TYPE)												  \
    namespace mlcpreg {	                                                      \
    namespace                                                                 \
    {                                                                         \
        template<class T>                                                     \
        class ObjectRegistration;											  \
                                                                              \
        template<>                                                            \
        class ObjectRegistration<TYPE>										  \
        {                                                                     \
            static const ::objserialization::ObjectRegistry<TYPE>& reg;		  \
        };                                                                    \
                                                                              \
        const ::objserialization::ObjectRegistry<TYPE>&						  \
			ObjectRegistration<TYPE>::reg =                                   \
                ::objserialization::ObjectRegistry<TYPE>::instance();		  \
    }}

OBJECT_REGISTER(objserialization::BaseObject);