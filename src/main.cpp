#include <iostream>
#include <cstdlib>

#include "lfw-core/core.hpp"

// 示例声明
void run_signal_demos();
void run_expression_demos();

auto main() -> int
{
  std::cout << lfw::description() << "\n";
  std::cout << "Version: " << lfw::version() << "\n\n";

  run_expression_demos();
  run_signal_demos();

  return EXIT_SUCCESS;
}
