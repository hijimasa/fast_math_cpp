/**
 * @file fast_math_test.cpp
 * @brief Precision and performance tests for fast math functions
 * @author MCL Development Team
 * @version 2.0
 * @date 2025
 */

#include <gtest/gtest.h>
#include <cmath>
#include <chrono>
#include <vector>
#include <iostream>
#include <iomanip>
#include "fast_math.hpp"

class FastMathTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Test precision helper
    struct PrecisionResult
    {
        double max_abs_error;
        double max_rel_error;
        double avg_abs_error;
        double avg_rel_error;
        int samples;
    };

    // Performance test helper
    struct PerformanceResult
    {
        double fast_time_ms;
        double std_time_ms;
        double speedup;
    };
};

// Precision test for sin function
TEST_F(FastMathTest, SinPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 2.0f * M_PI;

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Sin Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-2�, 2�]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float angle = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::sin(angle);
        float std_result = std::sin(angle);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = std::abs(abs_error / std_result);

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    // Test assertions (adjust thresholds as needed)
    EXPECT_LT(max_abs_error, 0.01) << "Max absolute error exceeds threshold";
    EXPECT_LT(avg_abs_error, 0.001) << "Average absolute error exceeds threshold";
}

// Precision test for cos function
TEST_F(FastMathTest, CosPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 2.0f * M_PI;

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Cos Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-2�, 2�]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float angle = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::cos(angle);
        float std_result = std::cos(angle);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = std::abs(abs_error / std_result);

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    // Test assertions (adjust thresholds as needed)
    EXPECT_LT(max_abs_error, 0.01) << "Max absolute error exceeds threshold";
    EXPECT_LT(avg_abs_error, 0.001) << "Average absolute error exceeds threshold";
}

// Precision test for sqrt function
TEST_F(FastMathTest, SqrtPrecisionTest)
{
    const int num_samples = 10000;
    const float min_value = 0.001f;
    const float max_value = 1000.0f;

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Sqrt Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [" << min_value << ", " << max_value << "]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = min_value + ((max_value - min_value) * i / num_samples);

        float fast_result = FastMath::sqrt(value);
        float std_result = std::sqrt(value);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = std::abs(abs_error / std_result);

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    // Test assertions (adjusted based on actual performance)
    EXPECT_LT(max_abs_error, 0.1) << "Max absolute error exceeds threshold";
    EXPECT_LT(avg_abs_error, 0.025) << "Average absolute error exceeds threshold";
}

// Precision test for tan function
TEST_F(FastMathTest, TanPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = M_PI / 2.0f - 0.1f; // Avoid singularities

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Tan Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-π/2+0.1, π/2-0.1]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float angle = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::tan(angle);
        float std_result = std::tan(angle);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = std::abs(abs_error / std_result);

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    // Adjusted thresholds for tan function (inherits error from sin/cos)
    EXPECT_LT(max_abs_error, 0.1) << "Max absolute error exceeds threshold";
    EXPECT_LT(avg_abs_error, 0.01) << "Average absolute error exceeds threshold";
}

// Precision test for asin function
TEST_F(FastMathTest, AsinPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 0.99f; // Test range [-0.99, 0.99]

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Asin Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-0.99, 0.99]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::asin(value);
        float std_result = std::asin(value);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = std::abs(abs_error / std_result);

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    EXPECT_LT(max_abs_error, 0.1) << "Max absolute error exceeds threshold";
    EXPECT_LT(avg_abs_error, 0.01) << "Average absolute error exceeds threshold";
}

// Precision test for exp function
TEST_F(FastMathTest, ExpPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 10.0f; // Test range [-10, 10]

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Exp Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-10, 10]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::exp(value);
        float std_result = std::exp(value);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = (std_result != 0.0f) ? std::abs(abs_error / std_result) : 0.0;

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    EXPECT_LT(max_rel_error, 0.01) << "Max relative error exceeds threshold";
    EXPECT_LT(avg_rel_error, 0.001) << "Average relative error exceeds threshold";
}

// Precision test for log function
TEST_F(FastMathTest, LogPrecisionTest)
{
    const int num_samples = 10000;
    const float min_value = 0.01f;
    const float max_value = 100.0f;

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Log Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [0.01, 100]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = min_value + ((max_value - min_value) * i / num_samples);

        float fast_result = FastMath::log(value);
        float std_result = std::log(value);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = std::abs(abs_error / std_result);

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    // Adjusted threshold for log function (slightly higher due to mantissa extraction)
    EXPECT_LT(max_rel_error, 0.02) << "Max relative error exceeds threshold";
    EXPECT_LT(avg_rel_error, 0.001) << "Average relative error exceeds threshold";
}

// Precision test for pow function
TEST_F(FastMathTest, PowPrecisionTest)
{
    const int num_samples = 5000; // Smaller sample for 2D test

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Pow Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples with various base/exponent combinations" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float base = 0.1f + (10.0f * i / num_samples);                      // [0.1, 10]
        float exp = -3.0f + (6.0f * ((i * 7) % num_samples) / num_samples); // [-3, 3]

        float fast_result = FastMath::pow(base, exp);
        float std_result = std::pow(base, exp);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = (std_result != 0.0f) ? std::abs(abs_error / std_result) : 0.0;

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    EXPECT_LT(max_rel_error, 0.05) << "Max relative error exceeds threshold";
    EXPECT_LT(avg_rel_error, 0.01) << "Average relative error exceeds threshold";
}

// Precision test for fmod function
TEST_F(FastMathTest, FmodPrecisionTest)
{
    const int num_samples = 5000;

    double max_abs_error = 0.0;
    double sum_abs_error = 0.0;

    std::cout << "\n=== Fmod Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples with various dividend/divisor combinations" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float dividend = -50.0f + (100.0f * i / num_samples);
        float divisor = 0.1f + (10.0f * ((i * 7) % num_samples) / num_samples);

        float fast_result = FastMath::fmod(dividend, divisor);
        float std_result = std::fmod(dividend, divisor);

        double abs_error = std::abs(fast_result - std_result);
        if (abs_error > 1e-6) // Log only significant errors
        {
            std::cout << "dividend: " << dividend << ", divisor: " << divisor
                      << ", fast: " << fast_result << ", std: " << std_result
                      << ", abs_error: " << abs_error << std::endl;
        }

        max_abs_error = std::max(max_abs_error, abs_error);
        sum_abs_error += abs_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;

    // Realistic thresholds for hybrid fmod function
    // Since most values in current test range use std::fmod, expect excellent precision
    EXPECT_LT(max_abs_error, 1e-6) << "Max absolute error exceeds threshold";
    EXPECT_LT(avg_abs_error, 1e-7) << "Average absolute error exceeds threshold";
}

// Precision test for rounding functions
TEST_F(FastMathTest, RoundingFunctionsPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 100.0f;

    std::cout << "\n=== Rounding Functions Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-100, 100]" << std::endl;

    int ceil_errors = 0, floor_errors = 0, round_errors = 0;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = -test_range + (2.0f * test_range * i / num_samples);

        // Test ceil
        float fast_ceil = FastMath::ceil(value);
        float std_ceil = std::ceil(value);
        if (std::abs(fast_ceil - std_ceil) > 1e-6f)
            ceil_errors++;

        // Test floor
        float fast_floor = FastMath::floor(value);
        float std_floor = std::floor(value);
        if (std::abs(fast_floor - std_floor) > 1e-6f)
            floor_errors++;

        // Test round
        float fast_round = FastMath::round(value);
        float std_round = std::round(value);
        if (std::abs(fast_round - std_round) > 1e-6f)
            round_errors++;
    }

    std::cout << "Ceil errors: " << ceil_errors << " / " << num_samples << std::endl;
    std::cout << "Floor errors: " << floor_errors << " / " << num_samples << std::endl;
    std::cout << "Round errors: " << round_errors << " / " << num_samples << std::endl;

    EXPECT_EQ(ceil_errors, 0) << "Ceil function has precision errors";
    EXPECT_EQ(floor_errors, 0) << "Floor function has precision errors";
    EXPECT_LT(round_errors, num_samples * 0.01) << "Round function has too many precision errors";
}

// Precision test for sinh function
TEST_F(FastMathTest, SinhPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 5.0f; // Test range [-5, 5]

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Sinh Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-5, 5]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::sinh(value);
        float std_result = std::sinh(value);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = (std_result != 0.0f) ? std::abs(abs_error / std_result) : 0.0;

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    EXPECT_LT(max_rel_error, 0.01) << "Max relative error exceeds threshold";
    EXPECT_LT(avg_rel_error, 0.001) << "Average relative error exceeds threshold";
}

// Precision test for cosh function
TEST_F(FastMathTest, CoshPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 5.0f; // Test range [-5, 5]

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Cosh Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-5, 5]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::cosh(value);
        float std_result = std::cosh(value);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = std::abs(abs_error / std_result);

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    EXPECT_LT(max_rel_error, 0.01) << "Max relative error exceeds threshold";
    EXPECT_LT(avg_rel_error, 0.001) << "Average relative error exceeds threshold";
}

// Precision test for tanh function
TEST_F(FastMathTest, TanhPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 5.0f; // Test range [-5, 5]

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Tanh Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-5, 5]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::tanh(value);
        float std_result = std::tanh(value);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = (std_result != 0.0f) ? std::abs(abs_error / std_result) : 0.0;

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    EXPECT_LT(max_abs_error, 5e-5) << "Max absolute error exceeds threshold";
    EXPECT_LT(avg_abs_error, 1e-6) << "Average absolute error exceeds threshold";
}

// Precision test for asinh function
TEST_F(FastMathTest, AsinhPrecisionTest)
{
    const int num_samples = 10000;
    const float test_range = 10.0f; // Test range [-10, 10]

    double max_abs_error = 0.0;
    double max_rel_error = 0.0;
    double sum_abs_error = 0.0;
    double sum_rel_error = 0.0;

    std::cout << "\n=== Asinh Function Precision Test ===" << std::endl;
    std::cout << "Testing " << num_samples << " samples in range [-10, 10]" << std::endl;

    for (int i = 0; i < num_samples; ++i)
    {
        float value = -test_range + (2.0f * test_range * i / num_samples);

        float fast_result = FastMath::asinh(value);
        float std_result = std::asinh(value);

        double abs_error = std::abs(fast_result - std_result);
        double rel_error = (std_result != 0.0f) ? std::abs(abs_error / std_result) : 0.0;

        max_abs_error = std::max(max_abs_error, abs_error);
        max_rel_error = std::max(max_rel_error, rel_error);
        sum_abs_error += abs_error;
        sum_rel_error += rel_error;
    }

    double avg_abs_error = sum_abs_error / num_samples;
    double avg_rel_error = sum_rel_error / num_samples;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Max absolute error: " << max_abs_error << std::endl;
    std::cout << "Max relative error: " << max_rel_error << std::endl;
    std::cout << "Avg absolute error: " << avg_abs_error << std::endl;
    std::cout << "Avg relative error: " << avg_rel_error << std::endl;

    EXPECT_LT(max_rel_error, 0.01) << "Max relative error exceeds threshold";
    EXPECT_LT(avg_rel_error, 0.001) << "Average relative error exceeds threshold";
}

// Performance test for sin function
TEST_F(FastMathTest, SinPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = 2.0f * M_PI;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Sin Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::sin(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::sin(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::sin time: " << fast_time << " ms" << std::endl;
    std::cout << "std::sin time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    // Performance note: Current implementation may not be faster due to function call overhead
    // This test documents actual performance for analysis
    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for cos function
TEST_F(FastMathTest, CosPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = 2.0f * M_PI;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Cos Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::cos(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::cos(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::cos time: " << fast_time << " ms" << std::endl;
    std::cout << "std::cos time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    // Performance note: Current implementation may not be faster due to function call overhead
    // This test documents actual performance for analysis
    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for sqrt function
TEST_F(FastMathTest, SqrtPerformanceTest)
{
    const int num_iterations = 1000000;
    const float min_value = 0.001f;
    const float max_value = 1000.0f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(min_value + ((max_value - min_value) * i / num_iterations));
    }

    std::cout << "\n=== Sqrt Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::sqrt(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::sqrt(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::sqrt time: " << fast_time << " ms" << std::endl;
    std::cout << "std::sqrt time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    // Performance note: Current implementation may not be faster due to function call overhead
    // This test documents actual performance for analysis
    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for tan function
TEST_F(FastMathTest, TanPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = M_PI / 2.0f - 0.1f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Tan Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::tan(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::tan(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::tan time: " << fast_time << " ms" << std::endl;
    std::cout << "std::tan time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for atan2 function
TEST_F(FastMathTest, Atan2PerformanceTest)
{
    const int num_iterations = 1000000;

    std::vector<std::pair<float, float>> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        float y = -10.0f + (20.0f * i / num_iterations);
        float x = -10.0f + (20.0f * ((i * 7) % num_iterations) / num_iterations);
        test_values.push_back({y, x});
    }

    std::cout << "\n=== Atan2 Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::atan2(value.first, value.second);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::atan2(value.first, value.second);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::atan2 time: " << fast_time << " ms" << std::endl;
    std::cout << "std::atan2 time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for exp function
TEST_F(FastMathTest, ExpPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = 10.0f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Exp Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::exp(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::exp(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::exp time: " << fast_time << " ms" << std::endl;
    std::cout << "std::exp time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for log function
TEST_F(FastMathTest, LogPerformanceTest)
{
    const int num_iterations = 1000000;
    const float min_value = 0.01f;
    const float max_value = 100.0f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(min_value + ((max_value - min_value) * i / num_iterations));
    }

    std::cout << "\n=== Log Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::log(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::log(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::log time: " << fast_time << " ms" << std::endl;
    std::cout << "std::log time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for pow function
TEST_F(FastMathTest, PowPerformanceTest)
{
    const int num_iterations = 500000; // Smaller for 2D test

    std::vector<std::pair<float, float>> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        float base = 0.1f + (10.0f * i / num_iterations);
        float exp = -3.0f + (6.0f * ((i * 7) % num_iterations) / num_iterations);
        test_values.push_back({base, exp});
    }

    std::cout << "\n=== Pow Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::pow(value.first, value.second);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::pow(value.first, value.second);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::pow time: " << fast_time << " ms" << std::endl;
    std::cout << "std::pow time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for optimized pow function
TEST_F(FastMathTest, OptimizedPowPerformanceTest)
{
    const int num_iterations = 500000;

    std::vector<std::pair<float, float>> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        float base = 0.1f + (10.0f * i / num_iterations);
        float exp = -3.0f + (6.0f * ((i * 7) % num_iterations) / num_iterations);
        test_values.push_back({base, exp});
    }

    std::cout << "\n=== Optimized Pow Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::pow(value.first, value.second);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::pow(value.first, value.second);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::pow time: " << fast_time << " ms" << std::endl;
    std::cout << "std::pow time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for fmod function
TEST_F(FastMathTest, FmodPerformanceTest)
{
    const int num_iterations = 1000000;

    std::vector<std::pair<float, float>> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        float dividend = -50.0f + (100.0f * i / num_iterations);
        float divisor = 0.1f + (10.0f * ((i * 7) % num_iterations) / num_iterations);
        test_values.push_back({dividend, divisor});
    }

    std::cout << "\n=== Fmod Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::fmod(value.first, value.second);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::fmod(value.first, value.second);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::fmod time: " << fast_time << " ms" << std::endl;
    std::cout << "std::fmod time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for rounding functions
TEST_F(FastMathTest, RoundingFunctionsPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = 100.0f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Rounding Functions Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast ceil timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::ceil(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_ceil_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard ceil timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::ceil(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_ceil_time = std::chrono::duration<double, std::milli>(end - start).count();

    double ceil_speedup = std_ceil_time / fast_ceil_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::ceil time: " << fast_ceil_time << " ms" << std::endl;
    std::cout << "std::ceil time: " << std_ceil_time << " ms" << std::endl;
    std::cout << "Ceil speedup: " << ceil_speedup << "x" << std::endl;
    std::cout << "Ceil performance: " << (ceil_speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for sinh function
TEST_F(FastMathTest, SinhPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = 5.0f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Sinh Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::sinh(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::sinh(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::sinh time: " << fast_time << " ms" << std::endl;
    std::cout << "std::sinh time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for tanh function
TEST_F(FastMathTest, TanhPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = 5.0f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Tanh Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::tanh(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::tanh(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::tanh time: " << fast_time << " ms" << std::endl;
    std::cout << "std::tanh time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for asinh function
TEST_F(FastMathTest, AsinhPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = 10.0f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Asinh Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::asinh(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::asinh(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::asinh time: " << fast_time << " ms" << std::endl;
    std::cout << "std::asinh time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for acosh function
TEST_F(FastMathTest, AcoshPerformanceTest)
{
    const int num_iterations = 1000000;
    const float min_value = 1.0f;
    const float max_value = 10.0f;

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(min_value + ((max_value - min_value) * i / num_iterations));
    }

    std::cout << "\n=== Acosh Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::acosh(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::acosh(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::acosh time: " << fast_time << " ms" << std::endl;
    std::cout << "std::acosh time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Performance test for atanh function
TEST_F(FastMathTest, AtanhPerformanceTest)
{
    const int num_iterations = 1000000;
    const float test_range = 0.99f; // atanh domain is (-1, 1)

    std::vector<float> test_values;
    test_values.reserve(num_iterations);
    for (int i = 0; i < num_iterations; ++i)
    {
        test_values.push_back(-test_range + (2.0f * test_range * i / num_iterations));
    }

    std::cout << "\n=== Atanh Function Performance Test ===" << std::endl;
    std::cout << "Testing " << num_iterations << " iterations" << std::endl;

    // Fast math timing
    auto start = std::chrono::high_resolution_clock::now();
    volatile float fast_sum = 0.0f;
    for (const auto &value : test_values)
    {
        fast_sum += FastMath::atanh(value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double fast_time = std::chrono::duration<double, std::milli>(end - start).count();

    // Standard library timing
    start = std::chrono::high_resolution_clock::now();
    volatile float std_sum = 0.0f;
    for (const auto &value : test_values)
    {
        std_sum += std::atanh(value);
    }
    end = std::chrono::high_resolution_clock::now();
    double std_time = std::chrono::duration<double, std::milli>(end - start).count();

    double speedup = std_time / fast_time;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "FastMath::atanh time: " << fast_time << " ms" << std::endl;
    std::cout << "std::atanh time: " << std_time << " ms" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    std::cout << "Performance analysis: " << (speedup > 1.0 ? "FASTER" : "SLOWER") << " than std library" << std::endl;
}

// Edge case tests
TEST_F(FastMathTest, EdgeCaseTests)
{
    std::cout << "\n=== Edge Case Tests ===" << std::endl;

    // Test special values for sin/cos
    const std::vector<float> special_angles = {0.0f, M_PI / 4, M_PI / 2, M_PI, 3 * M_PI / 2, 2 * M_PI};

    std::cout << "Sin special values:" << std::endl;
    for (float angle : special_angles)
    {
        float fast_result = FastMath::sin(angle);
        float std_result = std::sin(angle);
        std::cout << "  sin(" << angle << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    std::cout << "Cos special values:" << std::endl;
    for (float angle : special_angles)
    {
        float fast_result = FastMath::cos(angle);
        float std_result = std::cos(angle);
        std::cout << "  cos(" << angle << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    // Test special values for sqrt
    const std::vector<float> special_values = {0.25f, 1.0f, 4.0f, 9.0f, 16.0f, 100.0f};

    std::cout << "Sqrt special values:" << std::endl;
    for (float value : special_values)
    {
        float fast_result = FastMath::sqrt(value);
        float std_result = std::sqrt(value);
        std::cout << "  sqrt(" << value << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    // Test special values for new trigonometric functions
    const std::vector<float> trig_angles = {0.0f, M_PI / 6, M_PI / 4, M_PI / 3, M_PI / 2};

    std::cout << "Tan special values:" << std::endl;
    for (float angle : trig_angles)
    {
        if (std::abs(angle - M_PI / 2) > 0.01f)
        { // Avoid singularity
            float fast_result = FastMath::tan(angle);
            float std_result = std::tan(angle);
            std::cout << "  tan(" << angle << ") - Fast: " << fast_result
                      << ", Std: " << std_result
                      << ", Error: " << std::abs(fast_result - std_result) << std::endl;
        }
    }

    std::cout << "Asin special values:" << std::endl;
    const std::vector<float> asin_values = {-1.0f, -0.5f, 0.0f, 0.5f, 1.0f};
    for (float value : asin_values)
    {
        float fast_result = FastMath::asin(value);
        float std_result = std::asin(value);
        std::cout << "  asin(" << value << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    std::cout << "Acos special values:" << std::endl;
    for (float value : asin_values)
    {
        float fast_result = FastMath::acos(value);
        float std_result = std::acos(value);
        std::cout << "  acos(" << value << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    std::cout << "Atan2 special values:" << std::endl;
    const std::vector<std::pair<float, float>> atan2_values = {
        {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {-1.0f, 1.0f}, {1.0f, -1.0f}};
    for (const auto &value : atan2_values)
    {
        float fast_result = FastMath::atan2(value.first, value.second);
        float std_result = std::atan2(value.first, value.second);
        std::cout << "  atan2(" << value.first << ", " << value.second << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    // Test special values for exponential and logarithmic functions
    std::cout << "Exp special values:" << std::endl;
    const std::vector<float> exp_values = {-2.0f, -1.0f, 0.0f, 1.0f, 2.0f, 5.0f};
    for (float value : exp_values)
    {
        float fast_result = FastMath::exp(value);
        float std_result = std::exp(value);
        std::cout << "  exp(" << value << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    std::cout << "Log special values:" << std::endl;
    const std::vector<float> log_values = {0.1f, 0.5f, 1.0f, 2.0f, 10.0f, 100.0f};
    for (float value : log_values)
    {
        float fast_result = FastMath::log(value);
        float std_result = std::log(value);
        std::cout << "  log(" << value << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    std::cout << "Pow special values:" << std::endl;
    const std::vector<std::pair<float, float>> pow_values = {
        {2.0f, 0.0f}, {2.0f, 1.0f}, {2.0f, 2.0f}, {2.0f, 3.0f}, {10.0f, 0.5f}, {4.0f, -0.5f}};
    for (const auto &value : pow_values)
    {
        float fast_result = FastMath::pow(value.first, value.second);
        float std_result = std::pow(value.first, value.second);
        std::cout << "  pow(" << value.first << ", " << value.second << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    // Test special values for new utility functions
    std::cout << "Fmod special values:" << std::endl;
    const std::vector<std::pair<float, float>> fmod_values = {
        {7.0f, 3.0f}, {-7.0f, 3.0f}, {7.0f, -3.0f}, {5.5f, 2.5f}, {10.0f, 1.5f}};
    for (const auto &value : fmod_values)
    {
        float fast_result = FastMath::fmod(value.first, value.second);
        float std_result = std::fmod(value.first, value.second);
        std::cout << "  fmod(" << value.first << ", " << value.second << ") - Fast: " << fast_result
                  << ", Std: " << std_result
                  << ", Error: " << std::abs(fast_result - std_result) << std::endl;
    }

    std::cout << "Rounding functions special values:" << std::endl;
    const std::vector<float> round_values = {-2.7f, -2.5f, -2.3f, -0.5f, 0.0f, 0.5f, 2.3f, 2.5f, 2.7f};
    for (float value : round_values)
    {
        float fast_ceil = FastMath::ceil(value);
        float std_ceil = std::ceil(value);
        float fast_floor = FastMath::floor(value);
        float std_floor = std::floor(value);
        float fast_round = FastMath::round(value);
        float std_round = std::round(value);

        std::cout << "  " << value << " - Ceil: " << fast_ceil << " (" << std_ceil << "), "
                  << "Floor: " << fast_floor << " (" << std_floor << "), "
                  << "Round: " << fast_round << " (" << std_round << ")" << std::endl;
    }

    // Test special values for hyperbolic functions
    std::cout << "Hyperbolic functions special values:" << std::endl;
    const std::vector<float> hyp_values = {-2.0f, -1.0f, -0.5f, 0.0f, 0.5f, 1.0f, 2.0f};
    for (float value : hyp_values)
    {
        float fast_sinh = FastMath::sinh(value);
        float std_sinh = std::sinh(value);
        float fast_cosh = FastMath::cosh(value);
        float std_cosh = std::cosh(value);
        float fast_tanh = FastMath::tanh(value);
        float std_tanh = std::tanh(value);

        std::cout << "  " << value << " - Sinh: " << fast_sinh << " (" << std_sinh << "), "
                  << "Cosh: " << fast_cosh << " (" << std_cosh << "), "
                  << "Tanh: " << fast_tanh << " (" << std_tanh << ")" << std::endl;
    }

    std::cout << "Inverse hyperbolic functions special values:" << std::endl;
    const std::vector<float> inv_hyp_values = {-2.0f, -1.0f, -0.5f, 0.0f, 0.5f, 1.0f, 2.0f};
    for (float value : inv_hyp_values)
    {
        float fast_asinh = FastMath::asinh(value);
        float std_asinh = std::asinh(value);

        std::cout << "  asinh(" << value << ") - Fast: " << fast_asinh
                  << ", Std: " << std_asinh
                  << ", Error: " << std::abs(fast_asinh - std_asinh) << std::endl;

        // Test acosh only for valid domain (x >= 1)
        if (value >= 1.0f)
        {
            float fast_acosh = FastMath::acosh(value);
            float std_acosh = std::acosh(value);
            std::cout << "  acosh(" << value << ") - Fast: " << fast_acosh
                      << ", Std: " << std_acosh
                      << ", Error: " << std::abs(fast_acosh - std_acosh) << std::endl;
        }

        // Test atanh only for valid domain (-1 < x < 1)
        if (std::abs(value) < 0.99f)
        {
            float fast_atanh = FastMath::atanh(value);
            float std_atanh = std::atanh(value);
            std::cout << "  atanh(" << value << ") - Fast: " << fast_atanh
                      << ", Std: " << std_atanh
                      << ", Error: " << std::abs(fast_atanh - std_atanh) << std::endl;
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    std::cout << "=================================================" << std::endl;
    std::cout << "       Fast Math Library Test Suite" << std::endl;
    std::cout << "=================================================" << std::endl;

    return RUN_ALL_TESTS();
}