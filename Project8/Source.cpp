#include <iostream>
#include <sstream>
#include <vector>
#include "ObjectSerializer.hpp"
#include "BaseObject.hpp"
#include "ConnectMessage.hpp"

void main()
{
	std::vector<objserialization::BaseObject*> msgs;
	msgs.push_back(new objserialization::ConnectMessage("jack", "123"));

	std::shared_ptr<objserialization::BaseObject> msg1 = std::make_shared<objserialization::ConnectMessage>("11", "22");
	
	std::string msgstr = objserialization::ObjectSerializer::serialize(msg1);

	auto n = objserialization::ObjectSerializer::deserialize(msgstr);
	auto n2 = objserialization::ObjectSerializer::deserialize<objserialization::ConnectMessage>(msgstr);

	std::cout << std::endl;
	int x;
	std::cin >> x;
}
