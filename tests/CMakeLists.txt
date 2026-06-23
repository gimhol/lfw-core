# ============================================================
# Test executable
# ============================================================
add_executable(lfw-core-tests
    test_core.cpp
    test_enum_strings.cpp
    test_times.cpp
    test_math.cpp
    test_signal.cpp
    test_fps.cpp
    test_fields.cpp
    test_graves.cpp
    test_instfactory.cpp
    test_fsm.cpp
    test_expression.cpp
    test_condition_chain.cpp
    test_json_reflection.cpp
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
