#include <iostream>
#include <sstream>
#include <vector>
#include "MessageSerializer.hpp"

void main()
{
	mlcp::MessageSerializer a = mlcp::MessageSerializer::instance();

	std::vector<mlcp::GeneralMessage*> msgs;
	msgs.push_back(new mlcp::ConnectMessage("jack", "123"));

	std::shared_ptr<mlcp::GeneralMessage> msg1 = std::make_shared<mlcp::ConnectMessage>("11", "22");

	std::string msgstr = a.serializeMsg(msg1);

	mlcp::GeneralMessagePtr n = a.deserializeMsg(msgstr);
	std::shared_ptr<mlcp::ConnectMessage> nn = std::static_pointer_cast<mlcp::ConnectMessage>(n);

	std::cout << std::endl;
	int x;
	std::cin >> x;
}
