#pragma once
#include <map>
#include "SerializerFunctionPointer.hpp"
#include "ObjectRegistry.hpp"

namespace objserialization
{
	class ObjectSerializer
	{
		template<typename>
		friend class ObjectRegistry;

		template<class T>
		static const std::string serializeObj(const T obj, ArchiveType arType)
		{
			return objserialization::ObjectHandler::runSerializeHandler(obj->getType(), obj, arType);
		}
		
		template<class T>
		static templateObjectPtr<T> deserializeObj(const std::string& str, ArchiveType arType)
		{
			return objserialization::Archives::deserializeArchive<T>(str, arType);
		}

		static BaseObjectPtr deserializeObj(const std::string& str, ArchiveType arType)
		{
			std::string substr;
			objType type;
			size_t index;

			index = str.length() - 1;
			type = (objType)(str[index]);
			substr = str.substr(0, index);
			
			return objserialization::ObjectHandler::runDesrializeHandler(type, substr, arType);
		}
		
	public:
		template<class T>
		static const std::string serialize(const T obj, ArchiveType arType)
		{
			return objserialization::ObjectSerializer::serializeObj(obj, arType);
		}

		template<class T>
		static templateObjectPtr<T> deserialize(const std::string& str, ArchiveType arType)
		{
			return objserialization::ObjectSerializer::deserializeObj<T>(str, arType);
		}

		static BaseObjectPtr deserialize(const std::string& str, ArchiveType arType)
		{
			return objserialization::ObjectSerializer::deserializeObj(str, arType);
		}
	};
}
