#pragma once
#include "MessageHandler.hpp"

namespace mlcp
{
	static const msgType TYPE_CONNECT_MSG = 1;

	class ConnectMessage : public GeneralMessage
	{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int /*version*/)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(GeneralMessage);
			ar & BOOST_SERIALIZATION_NVP(_username);
			ar & BOOST_SERIALIZATION_NVP(_password);
		}

	protected:
		std::string _username;
		std::string _password;

	public:
		ConnectMessage(const std::string username = "", const std::string password = "")
			: GeneralMessage(TYPE_CONNECT_MSG), _username(username), _password(password)
		{}
	};

	MESSAGE_REGISTER(ConnectMessage);
}