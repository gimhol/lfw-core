#include <iostream>
#include <cstdlib>

#include "lfw-core/core.hpp"

auto main() -> int
{
  std::cout << lfw::description() << "\n";
  std::cout << "Version: " << lfw::version() << "\n";
  return EXIT_SUCCESS;
}
