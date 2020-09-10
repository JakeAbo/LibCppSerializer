# LibCppSerializer
LibCppSerializer implements a modern C++ API library which providing a generic wrapper to boost serialization library that enables to add
new classes which will easily be serialized and deserialized. 
The library provides fast runtime serialization using templates, lambdas and macros using C++ 17.

----
*Author*:      [Jack Abulafia](https://www.linkedin.com/in/jack-abulafia-463a23199/)

## Dependencies
This library requires use of boost/serialization which can be obtained from:
* <https://github.com/boostorg/serialization>

Tested on boost version 1.70.

## Building 
The library is header-only. 

## How to use
Project should include boost library and inc directory of the repository which include all necessary header files of LibCppSerializer.

## Getting Started
The additions to the standard boost/serialization library are:
1) Class must be inherit from objserialization::BaseObject which is general object with one member that symbolize object type.
2) In order to register class in serializers, OBJECT_REGISTER MACRO must be called. i.e. OBJECT_REGISTER([CLASS])
```cpp
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
```

Once class registered, class can be code and decode easily.
```cpp
void main()
{
	Person *p = new Person("jack", 23);
	std::string serializedPerson =  objserialization::ObjectSerializer::serialize(p);
	Person* backToPerson = objserialization::ObjectSerializer::deserialize<Person>(serializedPerson);

	delete p;
	delete backToPerson;
}
```
```cpp
void main()
{
	Person *p = new Person("jack", 23);
	std::string serializedPerson =  objserialization::ObjectSerializer::serialize(p);
	Person* backToPerson = static_cast<Person*>(objserialization::ObjectSerializer::deserialize(serializedPerson));

	delete p;
	delete backToPerson;
}
```
```cpp
void main()
{
	std::shared_ptr<Person> p = std::make_shared<Person>("jack", 23);
	std::string serializedPerson =  objserialization::ObjectSerializer::serialize(p);
	std::shared_ptr<Person> backToPerson(objserialization::ObjectSerializer::deserialize<Person>(serializedPerson));
}
```
```cpp
void main()
{
	std::unique_ptr<Person> p = std::make_unique<Person>("jack", 23);
	std::string serializedPerson =  objserialization::ObjectSerializer::serialize(p);
	std::unique_ptr<Person> backToPerson(objserialization::ObjectSerializer::deserialize<Person>(serializedPerson));
}
```
```cpp
void main()
{
	std::shared_ptr<Person> p = std::make_shared<Person>("jack", 23);
	std::string serializedPerson =  objserialization::ObjectSerializer::serialize(p);
	std::shared_ptr<objserialization::BaseObject> backToBase(objserialization::ObjectSerializer::deserialize(serializedPerson));
	std::shared_ptr<Person> backToPerson = std::static_pointer_cast<Person>(std::move(backToBase));
}
```


## License 
This project is open source and freely available.

  Copyright (c) 2020, Jack Abulafia 
  All rights reserved.


