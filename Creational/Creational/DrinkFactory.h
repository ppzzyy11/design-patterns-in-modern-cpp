#pragma once
#include <string>
#include "HotDrink.h"
#include "TeaFactory.h"
#include "CoffeeFactory.h"
#include <map>
#include <functional>

struct HotDrink;

class DrinkFactory
{
  map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
  DrinkFactory()
  {
    hot_factories["coffee"] = make_unique<CoffeeFactory>();
    hot_factories["tea"] = make_unique<TeaFactory>();
  }

  unique_ptr<HotDrink> make_drink(const string& name)
  {
    auto drink = hot_factories[name]->make();
    drink->prepare(200); // oops!
    return drink;
  }
};

class DrinkWithVolumeFactory
{
  map<string, function<unique_ptr<HotDrink>(int)>> factories;//function method
public:

  DrinkWithVolumeFactory()
  {
    factories["tea"] = [](int volume) {
      auto tea = make_unique<Tea>();
      tea->prepare(volume);
      return tea;
    };
  }

  unique_ptr<HotDrink> make_drink(const string& name, int volume);
};

inline unique_ptr<HotDrink> DrinkWithVolumeFactory::make_drink(const string& name, int volume = 200)
{
  return factories[name](volume);
}
