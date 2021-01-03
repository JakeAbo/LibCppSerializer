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
	Person(const std::string name = "", unsigned int age = 0, objserialization::objType type = objserialization::getObjectType<Person>())
		: BaseObject(type), _name(name), _age(age)
	{}
};

OBJECT_REGISTER(Person);

class Student : public Person
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int /*version*/)
	{
		ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Person);
		ar& BOOST_SERIALIZATION_NVP(_mathAvg);
	}

protected:
	unsigned int _mathAvg;

public:
	Student(const std::string name = "", unsigned int age = 0, unsigned int mathAvg = 0, objserialization::objType type = objserialization::getObjectType<Student>())
		: Person(name, age, type), _mathAvg(mathAvg)
	{}
};

OBJECT_REGISTER(Student);

void main()
{
	Person* p = new Person("jack", 23);
	Student* s = new Student("jack", 23, 69);

	//Text
	
	std::string serializedPerson = objserialization::ObjectSerializer::serialize(p, objserialization::ArchiveType::TEXT);
	Person* backToPerson = objserialization::ObjectSerializer::deserialize<Person>(serializedPerson, objserialization::ArchiveType::TEXT);

	std::string serializedStudent = objserialization::ObjectSerializer::serialize(s, objserialization::ArchiveType::TEXT);
	Student* backToStudent = objserialization::ObjectSerializer::deserialize<Student>(serializedStudent, objserialization::ArchiveType::TEXT);


	//Binary
	
	std::string serializedPerson2 = objserialization::ObjectSerializer::serialize(p, objserialization::ArchiveType::BINARY);
	Person* backToPerson2 = objserialization::ObjectSerializer::deserialize<Person>(serializedPerson2, objserialization::ArchiveType::BINARY);
	

	delete p; 
	delete backToPerson;
	delete backToPerson2;

	delete s;
	delete backToStudent;
}
