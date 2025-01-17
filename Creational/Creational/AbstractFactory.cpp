#include <iostream>
#include "HotDrink.h"
#include "DrinkFactory.h"

using namespace std;

unique_ptr< HotDrink> make_drink( string type)//not a factory method
{
    unique_ptr<HotDrink> drink;
    if (type == "tea") {
        drink = make_unique< Tea>();
        drink->prepare(200);
    } else {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}

int main()
{
    auto d = make_drink("tea");
    DrinkFactory df;
    df.make_drink("coffee");
   
    DrinkWithVolumeFactory dvf;
    dvf.make_drink("tea");

    return 0;
}