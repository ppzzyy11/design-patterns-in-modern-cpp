//boost::optinal is a library solution for Maybe Monad; below is a implementation.
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>
#include <functional>
#include <boost/optional.hpp>

using namespace std;
//嵌套的optional 成员
struct Address {
  string* house_name = nullptr;
};

struct Person {
  Address* address = nullptr;
};

template <typename T> struct Maybe;
template <typename T> Maybe<T> maybe(T* context)
{
  return Maybe<T>(context);
}

template <typename T>
struct Maybe {
  T* context;

  Maybe(T *context) : context(context) { }

  //都要处理 nullptr和非nullptr两种场景，并且可能返回nullptr
  template <typename TFunc>
  auto With(TFunc evaluator)
  {
    /*if (context == nullptr)
      return Maybe<typename remove_pointer<decltype(evaluator(context))>::type>(nullptr);
    return maybe(evaluator(context));*/
    return context != nullptr ? maybe(evaluator(context)) : nullptr;
  };

  template <typename TFunc>
  auto Do(TFunc action)
  {
    if (context != nullptr) action(context);
    return *this;
  }
};

void print_house_name(Person* p)
{
  //    if (p != nullptr && p->address != nullptr && p->address->house_name != nullptr)
  //        cout << *p->address->house_name << endl;
  auto z = maybe(p)
    .With([](auto x) { return x->address; })
    .With([](auto x) { return x->house_name; })
    .Do([](auto x) { cout << *x << endl; });
}



int main()
{
  Person p;
  p.address = new Address;
  p.address->house_name = new string("name");
  print_house_name(&p);

  delete p.address->house_name;
  delete p.address;

    auto null0 = maybe((int*)nullptr);
    null0.Do([](auto x) {cout<<x;});
    auto ret = null0.With([](auto x) {return x;});

  return 0;
}