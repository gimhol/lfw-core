# ============================================================
# Test executable
# ============================================================
add_executable(lfw-core-tests
    test_core.cpp
    test_enum_strings.cpp
)

target_link_libraries(lfw-core-tests
    PRIVATE
        lfw-core
)

target_compile_features(lfw-core-tests
    PRIVATE
        cxx_std_23
)

# Register tests with CTest
add_test(
    NAME lfw-core-tests
    COMMAND lfw-core-tests
)
