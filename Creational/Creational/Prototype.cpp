/*
 * prototype的copy部分可以用
 * 1. 序列化和反序列化
 * 2. deep copy
 * 来做，这个文件列了一些错误写法
*/
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <sstream>
#include "Person.h"
using namespace std;
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

struct Address
{
    string street;
    string city;
    int suite;


    friend ostream& operator<<(ostream& os, const Address& obj)
    {
        return os
                << "street: " << obj.street
                << " city: " << obj.city
                << " suite: " << obj.suite;
    }

private:
    friend class boost::serialization::access;

    template<class Ar> void serialize(Ar& ar, const unsigned int version)
    {
        ar & street;
        ar & city;
        ar & suite;
    }
};

struct Contact
{
    string name;
    Address* address = nullptr;

    friend ostream& operator<<(ostream& os, const Contact& obj)
    {
        return os
                << "name: " << obj.name
                << " address: " << *obj.address;
    }


private:
    friend class boost::serialization::access;

    template<class Ar> void serialize(Ar& ar, const unsigned int version)
    {
        ar & name;
        ar & address; // no *
    }
};

struct EmployeeFactory
{
  static Contact main;
  static Contact aux;

  static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite)
  {
    //static Contact p{ "", new Address{ "123 East Dr", "London", 0 } };
    return NewEmployee(name, suite, main);
  }

  static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite)
  {
    return NewEmployee(name, suite, aux);
  }

private:
  static unique_ptr<Contact> NewEmployee(string name, int suite, Contact& proto)
  {
    auto result = make_unique<Contact>(proto);
    result->name = name;
    result->address->suite = suite;
    return result;
  }
};

//Contact EmployeeFactory::main{ "", new Address{ "123 East Dr", "London", 0 } };
//Contact EmployeeFactory::aux{ "", new Address{ "123B East Dr", "London", 0 } };

int main()
{
  // this is tedious
  // Contact john{ "John Doe", new Address{"123 East Dr", "London"} };
  // Contact jane{ "Jane Doe", new Address{"123 East Dr", "London"} };

  auto addr = new Address{ "123 East Dr", "London", 0 /* ? */ };

  //Contact john{ "John Doe", addr };
  //john.address->suite = 123;
  //Contact jane{ "Jane Doe", addr };
  //jane.address->suite = 124;

  //Contact jane2{ jane }; // shallow copy
  //jane2.address->suite = 555;

  

  //
  //std::cout << jane2 << std::endl;

  // whenever an address is needed, make a copy
  /*Contact john{ "John Doe", new Address{*addr} };
  john.address->suite = 123;

  Contact jane{ "Jane Doe", new Address{*addr} };
  jane.address->suite = 125;

  cout << john << "\n" << jane << endl;*/

  // much better. let's list employees
  //Contact employee{ "Unknown", new Address{"628 Happy St", "Joy", 0} };

  //// we can use this prototype to create john and jane
  //Contact john{ employee };
  //john.name = "John Doe";
  //john.address->suite = 123;

  //Contact jane{ employee };
  //jane.name = "Jane Doe";
  //jane.address->suite = 125;

  //cout << john << "\n" << jane << "\n";

  //delete addr;

  // 4. Boost Serialization

  auto clone = [](const Contact& c)
  {
    // 1. Serialize the contact
    ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << c;
    string s = oss.str();

    // 2. Deserialize the contact
    istringstream iss(oss.str());
    boost::archive::text_iarchive ia(iss);
    Contact result;
    ia >> result;
    return result;
  };
  
 Contact john{ "John Doe", addr };
  john.address->suite = 123;
  Contact jane = clone(john);
  jane.name = "Jane Doe";
  jane.address->street = "123B West Dr";
  jane.address->suite = 300;

  //auto john = EmployeeFactory::NewAuxOfficeEmployee("John Doe", 123);
  //auto jane = EmployeeFactory::NewMainOfficeEmployee("Jane Doe", 125);

  cout << john << "\n" << jane << "\n"; // note the stars here

  delete addr;

  getchar();
  return 0;
}