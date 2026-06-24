cmake_minimum_required(VERSION 3.20)

# ============================================================
# Project
# ============================================================
project(lfw-core
    VERSION 0.1.0
    DESCRIPTION "lfw-core - A C++23 core library"
    LANGUAGES CXX
)

# ============================================================
# C++ Standard
# ============================================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# Build Type
# ============================================================
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================
# Compiler Options
# ============================================================
if(MSVC)
    add_compile_options(
        /W4
        /permissive-
        /utf-8
        /Zc:preprocessor
    )

    # Debug flags
    add_compile_options("$<$<CONFIG:Debug>:/Od>")
    add_compile_options("$<$<CONFIG:Debug>:/Zi>")
    add_compile_options("$<$<CONFIG:Debug>:/Ob0>")

    # Release flags
    add_compile_options("$<$<CONFIG:Release>:/O2>")
    add_compile_options("$<$<CONFIG:Release>:/Oi>")
    add_compile_options("$<$<CONFIG:Release>:/GL>")
    add_compile_options("$<$<CONFIG:Release>:/Gw>")

    # Linker flags
    add_link_options("$<$<CONFIG:Debug>:/DEBUG>")
    add_link_options("$<$<CONFIG:Release>:/LTCG>")
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wdouble-promotion
        -Wformat=2
        $<$<CONFIG:Debug>:-g;-O0;-fsanitize=address;-fsanitize=undefined>
        $<$<CONFIG:Release>:-O3;-DNDEBUG>
    )
    add_link_options(
        $<$<CONFIG:Debug>:-fsanitize=address;-fsanitize=undefined>
    )
endif()

# ============================================================
# Options
# ============================================================
option(LFW_CORE_BUILD_TESTS "Build unit tests" ON)
option(LFW_CORE_BUILD_EXAMPLES "Build examples" OFF)

# ============================================================
# Source Files (auto-discovered recursively in src/)
# ============================================================
file(GLOB_RECURSE LFW_CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Exclude main.cpp from library sources (it goes to the executable)
set(LFW_CORE_LIB_SOURCES ${LFW_CORE_SOURCES})
list(REMOVE_ITEM LFW_CORE_LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

# ============================================================
# Main Library
# ============================================================
add_library(lfw-core
    ${LFW_CORE_LIB_SOURCES}
)

target_include_directories(lfw-core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(lfw-core
    PUBLIC
        cxx_std_23
)

# ============================================================
# JSON (nlohmann)
# ============================================================
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(lfw-core
    PUBLIC
        nlohmann_json::nlohmann_json
)

# ============================================================
# Executable
# ============================================================
add_executable(lfw-core-app
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

target_link_libraries(lfw-core-app
    PRIVATE
        lfw-core
)

# ============================================================
# Testing
# ============================================================
if(LFW_CORE_BUILD_TESTS)
    enable_testing()

    add_subdirectory(tests)
endif()

# ============================================================
# Install
# ============================================================
include(GNUInstallDirs)

install(TARGETS lfw-core
    EXPORT lfw-core-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT lfw-core-targets
    FILE lfw-core-config.cmake
    NAMESPACE lfw-core::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lfw-core
)
