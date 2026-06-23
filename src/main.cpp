#include <iostream>
#include <cstdlib>

#include "lfw-core/core.hpp"

// 示例声明
void run_signal_demos();
void run_expression_demos();
void run_fsm_demo();
void run_fps_demo();
void run_graves_demo();
void run_instfactory_demo();
void run_fields_demo();
void run_json_reflection_demo();
void run_math_demo();

auto main() -> int
{
  std::cout << lfw::description() << "\n";
  std::cout << "Version: " << lfw::version() << "\n\n";

  run_math_demo();
  run_json_reflection_demo();
  run_fields_demo();
  run_instfactory_demo();
  run_graves_demo();
  run_fps_demo();
  run_fsm_demo();
  run_expression_demos();
  run_signal_demos();

  return EXIT_SUCCESS;
}
