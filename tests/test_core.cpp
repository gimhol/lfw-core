#include <cassert>
#include <iostream>

#include "lfw-core/core.hpp"

void run_enum_string_tests();

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

  std::cout << "All tests passed!\n";
  return 0;
}
