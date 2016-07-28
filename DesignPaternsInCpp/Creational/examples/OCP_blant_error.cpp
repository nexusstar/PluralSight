//open for extension but close for modification
//
#include <string>
#include <vector>
#include <iostream>

enum class Color{Red, Green, Blue};
enum class Size{Small, Medium, Large};


struct Product
{
  std::string name;
  Color color;
  Size size;
};

struct ProductFilter
{
  typedef std::vector<Product*> Items;

  static Items by_color(Items items, Color color)
  {
    Items result;
    for (auto& i : items)
      if(i->color == color)
        result.push_back(i);

    return result;
  }
  //
  // if requirement change e.g we want filter by size
  // we need to jump in our class and add new filter
  // this directly violates OCP we modify our class
  //
  static Items by_size(Items items, Size size)
  {
    Items result;
    for(auto& i : items)
      if(i->size == size)
        result.push_back(i);

    return result;
  }
};

// One solution for this particular problem
// is to use Specification Pattern


// specification interface that check if one or
// other specification is satisfied
template <typename T> struct ISpecification
{
  virtual bool is_satisfied(T* item) = 0;
};

// generic definition of filter
template <typename T> struct IFilter
{
  virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T>& spec) = 0;
};

// Filter definition
struct BetterFilter : IFilter<Product>
{
  typedef std::vector<Product*> Items;
  std::vector<Product*> filter(std::vector<Product*> items, ISpecification<Product>& spec) override
  {
    Items result;
    for(auto& p : items)
      if(spec.is_satisfied(p))
        result.push_back(p);
    return result;
  }
};

// Colour Specification
struct ColorSpecification: ISpecification<Product>
{
  Color color;
  explicit ColorSpecification(const Color color)
    :color{color}
  {}
  bool is_satisfied(Product* item) override{
    return item->color == color;
  }
};

// Size Specification
struct SizeSpecification : ISpecification<Product>
{
  Size size;
  explicit SizeSpecification(const Size size)
    :size{size}
  {}
  bool is_satisfied(Product* item) override{
    return item->size == size;
  }
};

// Size and color specification
// following straight from previous but there is a better way
struct SizeAndColorSpecification : ISpecification<Product>
{
  Size size;
  Color color;
  explicit SizeAndColorSpecification(const Size size, const Color color)
  :size{size}, color{color}
  {}
  bool is_satisfied(Product* item) override{
    if (item->size == size && item->color == color)
      return true;

    return false;
  }
};

template <typename T> struct AndSpecification : ISpecification<T>
{
  ISpecification<T>& first;
  ISpecification<T>& second;
  AndSpecification(ISpecification<T>& first, ISpecification<T>& second)
    :first{first}, second{second}
  {}

  bool is_satisfied(T* item) override {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

int main()
{
  Product apple{ "Apple", Color::Green, Size::Small };
  Product tree{ "Tree", Color::Green, Size::Large };
  Product house{ "House", Color::Blue, Size::Large };
  Product shrek{ "Shrek", Color::Green, Size::Large };

  std::vector<Product*> all { &apple, &tree, &house , &shrek};
  BetterFilter bf;
  ColorSpecification green(Color::Green);
  SizeSpecification large(Size::Large);

  // naive approach
  SizeAndColorSpecification large_green(Size::Large, Color::Green);
  // and using template
  AndSpecification<Product> large_and_green{large, green};

  auto large_things = bf.filter(all, large);
  auto green_things = bf.filter(all, green);
  auto large_green_things = bf.filter(all, large_green);
  auto large_and_green_things = bf.filter(all, large_and_green);

  // Filter Color::Green items
  for(auto& i : green_things)
    std::cout << i->name << " is Green\n";

  // Filter Size::Large items
  for(auto& i : large_things)
    std::cout << i->name << " is Large\n";

  //Filter by Size::Large and Color::Green
  for(auto& i : large_green_things)
    std::cout << i->name << " is Large and Green\n";

  // Filter again by size and colour but with template
  for(auto& i : large_and_green_things)
    std::cout << i->name << " is Large and Green\n";

  return 0;
}
