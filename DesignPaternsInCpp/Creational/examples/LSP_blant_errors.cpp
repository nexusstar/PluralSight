// Liscov substitution principle
//
// Objects in a program should be replaceable with instances of their subtypes
// without altering the correctness of the program
#include <iostream>

class Rectangle
{
  protected:
    int width, height;

  public:
    Rectangle(const int width, const int height):
      width{width}, height{height}
    {}

    virtual int GetWidth() const
    {
      return width;
    }

    virtual void SetWidth(const int width)
    {
      this -> width = width;
    }
    virtual int GetHeight() const
    {
      return height;
    }
    virtual void SetHeight(const int height)
    {
      this -> height = height;
    }

    int Area() const {
      return width * height;
    }
};
// Violating LSP 
class Square : public Rectangle
{
  public:
    Square(int size) : Rectangle(size, size) {}

    // violates LSP when following are added
    void SetWidth(const int width) override
    {
      this -> width = height = width;
    }
    void SetHeight(const int height) override{
      this -> height = width = height;
    }

};

void process(Rectangle& r)
{
  int w = r.GetHeight();
  r.SetHeight(10);

  std::cout << "expect area = " << (w * 10) 
    << ", got " << r.Area() << std::endl;
}

int main()
{
  Rectangle r{5, 5};
  process(r);

  Square s{ 5 };
  process(s);

  return 0;
}
