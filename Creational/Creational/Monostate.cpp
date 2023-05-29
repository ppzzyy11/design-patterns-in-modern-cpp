//It is a class that behaves like a singleton while appearing as an ordinary class.
#include <string>

class Printer
{
  static int id;//Mono
public:
  int get_id() const { return id; }
  void set_id(int value) { id = value; }
};

int main()
{
  Printer p;

  return 0;
}