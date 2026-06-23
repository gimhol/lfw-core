#include <iostream>
#include <cstdlib>

#include "lfw-core/core.hpp"

auto main() -> int
{
  std::cout << lfw::description() << "\n";
  std::cout << "Version: " << lfw::version() << "\n\n";

  std::cout << "Run tests with: lfw-core-tests.exe\n";
  return EXIT_SUCCESS;
}
