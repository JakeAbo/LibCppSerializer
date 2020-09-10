#include "libcppserializer/ObjectSerializer.hpp"

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
	std::shared_ptr<objserialization::BaseObject> p1 = std::make_shared<Person>("jack", 23);

	std::string p1serialized = objserialization::ObjectSerializer::serialize(p1);

	auto baseP1Deserialized = objserialization::ObjectSerializer::deserialize(p1serialized);
	auto p1deserialized = objserialization::ObjectSerializer::deserialize<Person>(p1serialized);

	std::cout << std::endl;
	int x;
	std::cin >> x;
}
