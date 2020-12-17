#include "ObjectSerializer.hpp"

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

void main()
{
	Person* p = new Person("jack", 23);
	
	//Text
	
	std::string serializedPerson = objserialization::ObjectSerializer::serialize(p, objserialization::ArchiveType::TEXT);
	Person* backToPerson = objserialization::ObjectSerializer::deserialize<Person>(serializedPerson, objserialization::ArchiveType::TEXT);
	

	//Binary
	
	std::string serializedPerson2 = objserialization::ObjectSerializer::serialize(p, objserialization::ArchiveType::BINARY);
	Person* backToPerson2 = objserialization::ObjectSerializer::deserialize<Person>(serializedPerson2, objserialization::ArchiveType::BINARY);
	delete backToPerson2;
	

	delete p; 
	delete backToPerson;
	delete backToPerson2;
}
