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

			if (arType == ArchiveType::BINARY)
			{
				boost::archive::binary_oarchive ia(os);
				ia << temp;
			}

			else if (arType == ArchiveType::TEXT)
			{
				boost::archive::text_oarchive ia(os);
				ia << temp;
			}

			else
			{
				throw ObjectSerializationException(ExceptionMessageType::EXCEPTION_UNKNOWN_ARCHIVE_TYPE);
			}

			return os.str() += temp->getType().value();
		}
	};
}

