#include <iostream>
#include <sstream>
#include <vector>
#include "ObjectSerializer.hpp"
#include "BaseObject.hpp"
#include "ConnectMessage.hpp"

void main()
{
	objserialization::ObjectSerializer a = objserialization::ObjectSerializer::instance();

	std::vector<objserialization::BaseObject*> msgs;
	msgs.push_back(new objserialization::ConnectMessage("jack", "123"));

	std::shared_ptr<objserialization::BaseObject> msg1 = std::make_shared<objserialization::ConnectMessage>("11", "22");

	std::string msgstr = a.serializeObj(msg1);

	objserialization::BaseObjectPtr n = a.deserializeObj(msgstr);
	objserialization::ConnectMessage* nn = static_cast<objserialization::ConnectMessage*>(n);

	std::cout << std::endl;
	int x;
	std::cin >> x;
}
