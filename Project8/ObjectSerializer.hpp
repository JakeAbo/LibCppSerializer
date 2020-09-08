#pragma once
#include <map>
#include "SerializerFunctionPointer.hpp"
#include "ObjectRegistry.hpp"

namespace objserialization
{
	class ObjectSerializer
	{
	public:
		static ObjectSerializer& instance()
		{
			static ObjectSerializer instance;
			return instance;
		}

		template<class T>
		static const std::string serializeObj(const T obj)
		{
			return objserialization::runSerializeHandler(obj->getType(), obj);
		}
				
		template<class T>
		static templateObjectPtr<T> deserializeObj(const std::string& str)
		{
			templateObjectPtr<T> result = new T();
			std::istringstream iss(str);
			boost::archive::binary_iarchive ia(iss);
			ia >> result;
			return result;
		}

		static BaseObjectPtr deserializeObj(const std::string& str)
		{
			std::string substr;
			objType type;
			size_t index;

			index = str.length() - 1;
			type = (objType)(str[index]);
			substr = str.substr(0, index);
			
			return objserialization::runDesrializeHandler(type, substr);
		}
	
	private:
		ObjectSerializer() = default;
	};

}
