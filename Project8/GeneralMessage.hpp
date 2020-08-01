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

namespace mlcp
{
	typedef unsigned int msgType;
	static const msgType TYPE_GENERAL_MSG = 0;
		
	class GeneralMessage
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int /*version*/)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_HPP(_type);
		}

	protected:
		msgType _type;
		
	public:
		GeneralMessage(const msgType& type = TYPE_GENERAL_MSG) : _type(type) {}
		const msgType& getType()
		{
			return _type;
		}
	};
}


