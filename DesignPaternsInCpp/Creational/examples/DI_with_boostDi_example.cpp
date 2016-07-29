// DI example using Boost DI
// https://github.com/boost-experimental/di/blob/cpp14/include/boost/di.hpp
//
#include <iostream>
#include <memory>

#include "di.hpp"

struct Engine
{
  float volume = 5;
  int horse_power = 400;

  friend std::ostream& operator <<(std::ostream& os, const Engine& e)
  {
    return os
      << "volume: " << e.volume
      << " horse_power: " << e.horse_power;
  }
};

struct Car
{
  std::shared_ptr<Engine> engine;

  Car (const std::shared_ptr<Engine>& engine):
    engine{engine}
  {}

  friend std::ostream& operator <<(std::ostream& os, const Car& c)
  {
    return os << "Car engine: " << *c.engine; // as it's share_ptr we need to dereference it
  }
};

int main()
{
  // Manual setup is to init all dependencies
  // and then create the object
  auto e = std::make_shared<Engine>();
  auto c = std::make_shared<Car>(e);

  // Using Di framework that cares for all the
  // dependencies
  using namespace boost;
  auto injector = di::make_injector();
  auto c1 = injector.create<std::shared_ptr<Car>>();

  std::cout << *c << std::endl;
  std::cout << *c1 << std::endl;

  return 0;
}
