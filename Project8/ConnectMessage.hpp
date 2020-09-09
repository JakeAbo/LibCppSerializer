#pragma once
#include "ObjectRegistry.hpp"

namespace objserialization
{
	static const objType TYPE_CONNECT_MSG = 1;

	class ConnectMessage : public BaseObject
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int /*version*/)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseObject);
			ar & BOOST_SERIALIZATION_NVP(_username);
			ar & BOOST_SERIALIZATION_NVP(_password);
		}

	protected:
		std::string _username;
		std::string _password;

	public:
		ConnectMessage(const std::string username = "", const std::string password = "")
			: BaseObject(objserialization::getObjectType<ConnectMessage>()), _username(username), _password(password)
		{}
	};

	OBJECT_REGISTER(ConnectMessage);
}