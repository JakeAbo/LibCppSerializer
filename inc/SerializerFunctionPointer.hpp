#pragma once
#include <memory>
#include "BaseObject.hpp"

namespace objserialization
{
	typedef BaseObject* BaseObjectPtr;
	template<typename T>
	using templateObjectPtr = T*;

	class SerializerFunctionPointerBase
	{
	public:
		virtual BaseObjectPtr deserialize(const std::string& serializedObj) = 0;
		virtual std::string serialize(BaseObjectPtr obj) = 0;
	};

	template<typename T>
	class SerializerFunctionPointer : public SerializerFunctionPointerBase
	{
	public:
		std::function<templateObjectPtr<T>(const std::string&)> _ptr;

		explicit SerializerFunctionPointer(std::function<templateObjectPtr<T>(const std::string&)> ptr = nullptr)
			: SerializerFunctionPointerBase(), _ptr(ptr)
		{}

		BaseObjectPtr deserialize(const std::string& serializedObj) override
		{
			if(_ptr != nullptr)
				return _ptr(serializedObj);
			return nullptr;
		}

		std::string serialize(BaseObjectPtr obj) override
		{
			std::ostringstream os;
			boost::archive::binary_oarchive ia(os);
			auto temp = static_cast<T*>(obj);
			ia << temp;
			return os.str() += temp->getType().value();
		}
	};
}

