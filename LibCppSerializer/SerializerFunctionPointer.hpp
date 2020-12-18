#pragma once
#include <memory>
#include "BaseObject.hpp"
#include "ObjectSerializationArchives.hpp"

namespace objserialization
{
	typedef BaseObject* BaseObjectPtr;
	template<typename T>
	using templateObjectPtr = T*;

	class SerializerFunctionPointerBase
	{
	public:
		virtual BaseObjectPtr deserialize(const std::string& serializedObj, ArchiveType arType) = 0;
		virtual std::string serialize(BaseObjectPtr obj, ArchiveType arType) = 0;
	};

	template<typename T>
	class SerializerFunctionPointer : public SerializerFunctionPointerBase
	{
	public:
		std::function<templateObjectPtr<T>(const std::string&, ArchiveType arType)> _ptr;

		explicit SerializerFunctionPointer(std::function<templateObjectPtr<T>(const std::string&, ArchiveType)> ptr = nullptr)
			: SerializerFunctionPointerBase(), _ptr(ptr)
		{}

		BaseObjectPtr deserialize(const std::string& serializedObj, ArchiveType arType) override
		{
			if(_ptr != nullptr)
				return _ptr(serializedObj, arType);
			return nullptr;
		}

		std::string serialize(BaseObjectPtr obj, ArchiveType arType) override
		{
			std::ostringstream os;
			auto temp = static_cast<T*>(obj);

			return Archives::serializeArchive(temp, arType) += temp->getType().value();

		}
	};
}

