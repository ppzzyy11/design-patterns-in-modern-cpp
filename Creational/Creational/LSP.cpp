//This is an example breaking Liskov Substitution Principle(LSP), the square can not replace its parent perfectly in the function process.
// Objects in a program should be replaceable with instances of their subtypes
// w/o altering the correctness of the program

#include <iostream>

class Rectangle
{
protected:
  int width, height;
public:
  Rectangle(const int width, const int height)
    : width{width}, height{height} { }

  int get_width() const { return width; }
  virtual void set_width(const int width) { this->width = width; }
  int get_height() const { return height; }
  virtual void set_height(const int height) { this->height = height; }

  int area() const { return width * height; }
};

class Square : public Rectangle
{
public:
  Square(int size): Rectangle(size,size) {}
  void set_width(const int width) override {
    this->width = height = width;
  }
  void set_height(const int height) override {
    this->height = width = height;
  }
};

struct RectangleFactory
{
  static Rectangle create_rectangle(int w, int h);
  static Square create_square(int size);
};

Rectangle RectangleFactory::create_rectangle(
        int w,
        int h)
{
    return Rectangle(w, h);
}

Square RectangleFactory::create_square(
        int size)
{
    return Square(size);
}

void process(Rectangle& r)
{
  int w = r.get_width();
  std::cout<<"area: "<<r.area()<<"\t";
  r.set_height(10);

  std::cout << "expected area = " << (w * 10) 
    << ", got " << r.area() << std::endl;
}

int main()
{
  Rectangle r{ 3, 3 };
  process(r);
  
  Rectangle r2 = RectangleFactory::create_rectangle(1, 2);
  process(r2);

  Square sq{ 5 };
  process(sq);
  
  Square sq2 = RectangleFactory::create_square(3);
  process(sq2);

  getchar();
  return 0;
}