#pragma once
#include "ObjectRegistry.hpp"

class Person : public objserialization::BaseObject
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int /*version*/)
	{
		ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseObject);
		ar& BOOST_SERIALIZATION_NVP(_name);
		ar& BOOST_SERIALIZATION_NVP(_age);
	}

protected:
	std::string _name;
	unsigned int _age;

public:
	Person(const std::string name = "", unsigned int age = 0)
		: BaseObject(objserialization::getObjectType<Person>()), _name(name), _age(age)
	{}
};

OBJECT_REGISTER(Person);
