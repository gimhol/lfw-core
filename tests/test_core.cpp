#include <cassert>
#include <cstdio>
#include <iostream>

#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#else
#include <unistd.h>
#endif

#include "lfw-core/core.hpp"

void run_enum_string_tests();
void run_times_tests();
void run_math_tests();
void run_signal_tests();
void run_fps_tests();
void run_fields_tests();
void run_graves_tests();
void run_instfactory_tests();
void run_fsm_tests();
void run_expression_tests();
void run_condition_chain_tests();
void run_json_reflection_tests();
void run_string_parser_tests();

static void test_version()
{
  const auto ver = lfw::version();
  assert(!ver.empty());
  std::cout << "  PASS: version() = " << ver << "\n";
}

static void test_description()
{
  const auto desc = lfw::description();
  assert(!desc.empty());
  std::cout << "  PASS: description() = " << desc << "\n";
}

auto main() -> int
{
  std::cout << "Running lfw-core tests...\n";

  test_version();
  test_description();
  run_enum_string_tests();
  run_times_tests();
  run_math_tests();
  run_signal_tests();
  run_fps_tests();
  run_fields_tests();
  run_graves_tests();
  run_instfactory_tests();
  run_fsm_tests();
  run_expression_tests();
  run_condition_chain_tests();
  run_json_reflection_tests();
  run_string_parser_tests();

  std::cout << "All tests passed!\n";
  if (isatty(fileno(stdin)))
  {
    std::cout << "\nPress Enter to exit..." << std::flush;
    std::cin.get();
  }
  return 0;
}
