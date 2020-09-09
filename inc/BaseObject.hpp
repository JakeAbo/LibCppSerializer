#pragma once
#include <iostream>
#include <sstream>
#include "boost\serialization\access.hpp"
#include "boost\archive\text_oarchive.hpp"
#include "boost\archive\binary_oarchive.hpp"
#include "boost\archive\text_iarchive.hpp"
#include "boost\archive\binary_iarchive.hpp"
#include "boost\serialization\export.hpp"
#include "boost\serialization\nvp.hpp"
#include "boost\serialization\shared_ptr.hpp"
#include "boost\serialization\vector.hpp"
#include "boost\serialization\base_object.hpp"
#include "boost\optional\optional.hpp"
#include "boost\serialization\optional.hpp"
#include "ObjectSerializationException.hpp"

namespace objserialization
{
	typedef boost::optional<unsigned int> objType;
	static const objType TYPE_BASE_OBJ = 0;
		
	class BaseObject
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int /*version*/)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_HPP(_type);
		}

	protected:
		objType _type;
		
	public:
		BaseObject(const objType& type = TYPE_BASE_OBJ) : _type(type) {}
		const objType& getType()
		{
			if(_type.has_value())
				return _type;
			throw ObjectSerializationException(ExceptionMessageType::EXCEPTION_TYPE);
		}
	};
}


