# FastMath C++ Library
English | [日本語](./README_jp.md)

[![CI](https://github.com/hijimasa/fast_math_cpp/actions/workflows/ci.yml/badge.svg)](https://github.com/hijimasa/fast_math_cpp/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard)
[![Platform](https://img.shields.io/badge/platform-linux%20%7C%20macos%20%7C%20windows-lightgrey.svg)](https://github.com/hijimasa/fast_math_cpp)
[![Performance](https://img.shields.io/badge/performance-optimized-brightgreen.svg)](https://github.com/hijimasa/fast_math_cpp)

A high-performance mathematical library providing faster alternatives to standard C++ math functions with maintained precision.

## Overview

FastMath is a comprehensive mathematical library designed for applications requiring optimized mathematical computations. It implements 25 mathematical functions using advanced optimization techniques including polynomial approximations, range reduction, bit manipulation, and hybrid implementations.

## Features

- **25 Optimized Functions**: Complete set of trigonometric, exponential, logarithmic, utility, and hyperbolic functions
- **High Precision**: Maintains excellent accuracy while providing performance improvements
- **Cross-Platform**: Optimized for both x86 and ARM architectures
- **Hybrid Implementation**: Automatically selects optimal method based on input range
- **Header-Only Design**: Simple integration with clean API

## Performance Results

### x86 Desktop Performance

| Function | Speedup | Status |
|----------|---------|--------|
| **atan2** | **3.76x** | ✅ FASTER |
| **sinh** | **2.97x** | ✅ FASTER |
| **atanh** | **2.86x** | ✅ FASTER |
| **tanh** | **2.69x** | ✅ FASTER |
| **tan** | **1.55x** | ✅ FASTER |
| **cos** | **1.07x** | ✅ FASTER |
| **fmod** | **1.08x** | ✅ FASTER |
| **sin** | **1.05x** | ✅ FASTER |

### Raspberry Pi 4 Performance

| Function | Speedup | Status |
|----------|---------|--------|
| **atan2** | **4.42x** | ✅ FASTER |
| **atanh** | **2.79x** | ✅ FASTER |
| **sinh** | **2.30x** | ✅ FASTER |
| **tanh** | **1.99x** | ✅ FASTER |
| **tan** | **1.51x** | ✅ FASTER |
| **sin** | **1.46x** | ✅ FASTER |
| **fmod** | **1.22x** | ✅ FASTER |
| **cos** | **1.16x** | ✅ FASTER |

## Supported Functions

### Trigonometric Functions
- `sin(x)` - Fast sine using polynomial approximation
- `cos(x)` - Fast cosine using polynomial approximation
- `tan(x)` - Fast tangent using sin/cos ratio
- `asin(x)` - Fast arc sine using Newton-Raphson method
- `acos(x)` - Fast arc cosine using Newton-Raphson method
- `atan2(y, x)` - Fast arc tangent 2 using CORDIC-inspired algorithm

### Exponential & Logarithmic Functions
- `exp(x)` - Fast exponential using range reduction and polynomial approximation
- `log(x)` - Fast natural logarithm using bit manipulation and polynomial approximation
- `log10(x)` - Fast base-10 logarithm
- `log2(x)` - Fast base-2 logarithm
- `pow(base, exp)` - Fast power function with optimized special cases

### Utility Functions
- `sqrt(x)` - Fast square root using Newton-Raphson with bit manipulation initial guess
- `fmod(x, y)` - Hybrid floating-point remainder (fast for small values, std::fmod for large)
- `ceil(x)` - Fast ceiling function using bit manipulation
- `floor(x)` - Fast floor function using bit manipulation
- `round(x)` - Fast rounding function

### Hyperbolic Functions
- `sinh(x)` - Fast hyperbolic sine using optimized exp function
- `cosh(x)` - Fast hyperbolic cosine using optimized exp function
- `tanh(x)` - Fast hyperbolic tangent using rational approximation
- `asinh(x)` - Fast inverse hyperbolic sine
- `acosh(x)` - Fast inverse hyperbolic cosine
- `atanh(x)` - Fast inverse hyperbolic tangent

## Usage

### Basic Usage

```cpp
#include "fast_math.hpp"

int main() {
    float angle = 1.5707963f; // π/2

    // Use FastMath functions
    float sin_val = FastMath::sin(angle);
    float cos_val = FastMath::cos(angle);
    float sqrt_val = FastMath::sqrt(16.0f);

    // Hyperbolic functions
    float sinh_val = FastMath::sinh(1.0f);
    float tanh_val = FastMath::tanh(0.5f);

    return 0;
}
```

### CMake Integration

```cmake
# Include FastMath in your project
add_subdirectory(path/to/fast_math_cpp)

# Link against your target
target_link_libraries(your_target fast_math_cpp)
```

## Building

### Requirements
- CMake 3.16 or higher
- C++17 compatible compiler
- Google Test (for testing)

### Build Instructions

```bash
mkdir build && cd build
cmake ..
make

# Run tests
./fast_math_test
```

### Build Options

```bash
# Build as shared library
cmake -DFAST_MATH_BUILD_SHARED_LIBS=ON ..

# Disable tests
cmake -DBUILD_TESTS=OFF ..
```

## Implementation Techniques

### Optimization Methods
- **Polynomial Approximations**: Taylor series and Padé approximations for high accuracy
- **Range Reduction**: Reduces input ranges for better polynomial convergence
- **Bit Manipulation**: IEEE 754 floating-point optimizations for exp/log functions
- **Newton-Raphson Method**: Iterative refinement for sqrt and inverse functions
- **Binary Exponentiation**: Fast integer power operations
- **Hybrid Strategies**: Automatic fallback to standard library for precision-critical ranges

### Precision Guarantees
- Trigonometric functions: < 0.01 absolute error
- Square root: < 1e-5 absolute error
- Exponential/logarithmic: < 0.01 relative error
- Hyperbolic functions: < 5e-5 absolute error
- Utility functions: Perfect precision for small values

## Architecture Support

The library is optimized for multiple architectures:

- **x86/x64**: Excellent performance on Intel/AMD processors
- **ARM**: Optimized for ARM Cortex processors (tested on Raspberry Pi 4)
- **Cross-platform**: Consistent API across all supported platforms

## Testing

Comprehensive test suite includes:
- **Precision Tests**: Verify accuracy against standard library
- **Performance Tests**: Benchmark speed improvements
- **Edge Case Tests**: Handle special values and boundary conditions

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.

## Contributing

Contributions are welcome! Please ensure:
- All tests pass
- Code follows existing style conventions
- Performance improvements are documented
- Cross-platform compatibility is maintained

## Benchmarking Results

The library shows consistent performance improvements across platforms, with particularly strong results on resource-constrained systems like Raspberry Pi 4. The hybrid implementation strategy ensures both speed and precision are maintained across all input ranges.

For detailed benchmark results, see the `sample_result/` directory containing platform-specific test outputs.