cmake_minimum_required(VERSION 3.16)

project(fast_math_cpp CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set position independent code for shared library compatibility
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Option to build as shared library
option(FAST_MATH_BUILD_SHARED_LIBS "build fast_math as a shared library" OFF)

# Source files
set(fast_math_sources
    src/fast_math.cpp
)

# Header files
set(fast_math_headers
    include/fast_math.hpp
)

# Include directories
set(fast_math_include_dirs
    include
)

# Dependencies
set(fast_math_link_libraries
)

# Create library target
if(FAST_MATH_BUILD_SHARED_LIBS)
add_library(fast_math_cpp SHARED ${fast_math_sources})
else()
add_library(fast_math_cpp STATIC ${fast_math_sources})
endif()

# Set target properties
target_include_directories(fast_math_cpp PUBLIC
    ${fast_math_include_dirs}
)

target_link_libraries(fast_math_cpp ${fast_math_link_libraries})

# Compiler options
target_compile_options(fast_math_cpp PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wno-ignored-qualifiers  # Ignore const return type warnings from external libraries
    -O3                      # Maximum optimization
    -march=native            # Use native CPU instructions
    -ffast-math             # Fast math optimizations
    -funroll-loops          # Unroll loops for performance
)

# Install targets
install(TARGETS fast_math_cpp
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES ${fast_math_headers}
    DESTINATION include
)

# Export variables for parent scope
set(fast_math_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include
    CACHE INTERNAL "fast_math: Include Directories" FORCE)

set(fast_math_LIBRARIES fast_math_cpp
    CACHE INTERNAL "fast_math: Libraries" FORCE)

# Create alias for consistency
add_library(mcl::map ALIAS fast_math_cpp)

# Print configuration info
message(STATUS "fast_math_cpp configuration:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Shared libs: ${FAST_MATH_BUILD_SHARED_LIBS}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Include dirs: ${fast_math_include_dirs}")
message(STATUS "  Link libraries: ${fast_math_link_libraries}")

# Add test executable if testing is enabled
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    find_package(GTest REQUIRED)
    
    add_executable(fast_math_test
        test/fast_math_test.cpp
    )

    target_link_libraries(fast_math_test
        fast_math_cpp
        GTest::gtest
        GTest::gtest_main
        pthread
    )

    target_include_directories(fast_math_test PRIVATE
        ${fast_math_include_dirs}
    )

    # Apply same optimization flags to test executable
    target_compile_options(fast_math_test PRIVATE
        -O3
        -march=native
        -ffast-math
        -funroll-loops
    )
    
    # Register test with CTest
    enable_testing()
    add_test(NAME FastMathUnitTest COMMAND fast_math_test)

    message(STATUS "FastMath tests enabled")
endif()
