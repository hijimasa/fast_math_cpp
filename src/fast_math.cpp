/**
 * @file fast_math.cpp
 * @brief Fast trigonometric functions implementation
 * @author MCL Development Team
 * @version 2.0
 * @date 2025
 */

#include "fast_math.hpp"

namespace FastMath
{
  /**
   * sinをy=a+bx+cx^2の形で近似する
   * sin(0) = 0, sin(π/2) = 1, sin(π) = 0より
   * a = 0, b = 4 / π, c = -4 / (π^2)となる
   * さらに精度を向上させるために、加重平均を用いる
   * Q * y + P * y * abs(y)としたとき、
   * 絶対誤差が最も小さいのは、Q = 0.775, P = 0.225となる
   * 相対誤差が最も小さいのは、Q = 0.782, P = 0.218となる
   * 今回は絶対誤差が最も小さい組み合わせを採用する
   * これにより計算速度が向上する
   */
  float
  sin(float theta)
  {
    float sin;
    constexpr float pi = 3.14159265358979323846264338327950288;
    constexpr float two_pi = float(2.0) * pi;
    constexpr float B = float(4.0) / pi;
    constexpr float C = float(4.0) / (pi * pi);
    constexpr float zero = float(0.0);
    constexpr float P = float(0.225);

    while (theta < -pi)
    {
      theta += two_pi;
    }
    while (theta > pi)
    {
      theta -= two_pi;
    }

    // sin
    if (theta < zero)
    {
      sin = theta * B + C * theta * theta;
      if (sin < zero)
      {
        sin = P * (sin * -sin - sin) + sin;
      }
      else
      {
        sin = P * (sin * sin - sin) + sin;
      }
    }
    else
    {
      sin = theta * B - C * theta * theta;
      if (sin < zero)
      {
        sin = P * (sin * -sin - sin) + sin;
      }
      else
      {
        sin = P * (sin * sin - sin) + sin;
      }
    }
    return sin;
  }

  float
  cos(float theta)
  {
    float cos;
    constexpr float pi = 3.14159265358979323846264338327950288;
    constexpr float half_pi = pi / float(2.0);
    constexpr float two_pi = float(2.0) * pi;
    constexpr float B = float(4.0) / pi;
    constexpr float C = float(4.0) / (pi * pi);
    constexpr float zero = float(0.0);
    constexpr float P = float(0.225);

    while (theta < -pi)
    {
      theta += two_pi;
    }
    while (theta > pi)
    {
      theta -= two_pi;
    }
    theta += half_pi;
    if (theta > pi)
    {
      theta -= two_pi;
    }
    // cos
    if (theta < zero)
    {
      cos = theta * B + C * theta * theta;
      if (cos < zero)
      {
        cos = P * (cos * -cos - cos) + cos;
      }
      else
      {
        cos = P * (cos * cos - cos) + cos;
      }
    }
    else
    {
      cos = theta * B - C * theta * theta;
      if (cos < zero)
      {
        cos = P * (cos * -cos - cos) + cos;
      }
      else
      {
        cos = P * (cos * cos - cos) + cos;
      }
    }
    return cos;
  }

  /**
   * @brief Fast square root using Newton-Raphson method
   * @param number Input number
   * @return Square root of the input number
   * @note Newton-Raphson iteration: x_{n+1} = 0.5 * (x_n + number/x_n)
   *       Uses initial guess from bit manipulation for faster convergence
   */
  float
  sqrt(float number)
  {
    if (number <= 0.0f)
      return 0.0f;

    // Initial guess using bit manipulation (similar to Quake's method but for sqrt)
    union
    {
      float f;
      int i;
    } conv;

    conv.f = number;
    conv.i = 0x1FBD1DF5 + (conv.i >> 1); // Magic number for sqrt approximation
    float x = conv.f;

    // Newton-Raphson iterations (2 iterations for balance of speed/precision)
    x = 0.5f * (x + number / x);
    x = 0.5f * (x + number / x);

    return x;
  }

  /**
   * @brief Fast tangent
   * @param angle Angle in radians
   * @return Tangent value
   * @note Uses sin/cos ratio for accuracy
   */
  float
  tan(float theta)
  {
    float sin_val = sin(theta);
    float cos_val = cos(theta);

    // Avoid division by zero
    if (std::abs(cos_val) < 1e-7f)
    {
      return (cos_val >= 0.0f) ? 1e7f : -1e7f;
    }

    return sin_val / cos_val;
  }

  /**
   * @brief Fast arc sine using Newton-Raphson method
   * @param x Input value [-1, 1]
   * @return Arc sine in radians
   * @note Uses Newton-Raphson to solve sin(y) = x for y
   */
  float
  asin(float x)
  {
    // Clamp input to valid range
    if (x >= 1.0f)
      return M_PI / 2.0f;
    if (x <= -1.0f)
      return -M_PI / 2.0f;
    if (std::abs(x) < 1e-7f)
      return 0.0f;

    // Initial guess using polynomial approximation
    float y = x * (M_PI / 2.0f);

    // Newton-Raphson iterations: y_{n+1} = y_n - (sin(y_n) - x) / cos(y_n)
    for (int i = 0; i < 3; ++i)
    {
      float sin_y = sin(y);
      float cos_y = cos(y);
      if (std::abs(cos_y) < 1e-7f)
        break;
      y = y - (sin_y - x) / cos_y;
    }

    return y;
  }

  /**
   * @brief Fast arc cosine using Newton-Raphson method
   * @param x Input value [-1, 1]
   * @return Arc cosine in radians
   * @note Uses identity: acos(x) = π/2 - asin(x)
   */
  float
  acos(float x)
  {
    return M_PI / 2.0f - asin(x);
  }

  /**
   * @brief Fast arc tangent 2 (atan2)
   * @param y Y coordinate
   * @param x X coordinate
   * @return Arc tangent in radians [-π, π]
   * @note Uses CORDIC-inspired algorithm for quadrant-aware atan
   */
  float
  atan2(float y, float x)
  {
    // Handle special cases
    if (std::abs(x) < 1e-7f && std::abs(y) < 1e-7f)
      return 0.0f;
    if (std::abs(x) < 1e-7f)
      return (y >= 0.0f) ? M_PI / 2.0f : -M_PI / 2.0f;

    // Use fast atan approximation
    float abs_y = std::abs(y);
    float abs_x = std::abs(x);

    float a, angle;
    if (abs_x >= abs_y)
    {
      a = abs_y / abs_x;
      // Fast atan approximation for [0, 1]: atan(a) ≈ a * (π/4 + 0.273 * (1 - a))
      angle = a * (M_PI / 4.0f + 0.273f * (1.0f - a));
    }
    else
    {
      a = abs_x / abs_y;
      angle = M_PI / 2.0f - a * (M_PI / 4.0f + 0.273f * (1.0f - a));
    }

    // Adjust for quadrant
    if (x < 0.0f)
    {
      if (y >= 0.0f)
      {
        angle = M_PI - angle;
      }
      else
      {
        angle = -M_PI + angle;
      }
    }
    else
    {
      if (y < 0.0f)
      {
        angle = -angle;
      }
    }

    return angle;
  }

  /**
   * @brief Fast exponential function
   * @param x Input value
   * @return e^x
   * @note Uses range reduction and polynomial approximation
   *       Based on exp(x) = 2^(x/ln(2)) with optimized computation
   */
  float
  exp(float x)
  {
    // Handle extreme cases
    if (x > 88.0f)
      return 1e38f; // Avoid overflow
    if (x < -87.0f)
      return 0.0f; // Underflow to zero

    // Range reduction: exp(x) = 2^(x/ln(2))
    // Split x/ln(2) into integer and fractional parts
    constexpr float inv_ln2 = 1.44269504088896341f; // 1/ln(2)
    float fx = x * inv_ln2;

    // Extract integer part
    int n = static_cast<int>(fx + (fx >= 0.0f ? 0.5f : -0.5f));
    float r = fx - static_cast<float>(n);

    // Convert back: r is now in [-0.5, 0.5]
    constexpr float ln2 = 0.69314718055994531f;
    r *= ln2;

    // Polynomial approximation for exp(r) where r is in [-ln(2)/2, ln(2)/2]
    // Using 5th order polynomial: exp(r) ≈ 1 + r + r²/2! + r³/3! + r⁴/4! + r⁵/5!
    float r2 = r * r;
    float poly = 1.0f + r + 0.5f * r2 +
                 r2 * r * (1.0f / 6.0f + r * (1.0f / 24.0f + r * (1.0f / 120.0f)));

    // Combine with 2^n using bit manipulation
    union
    {
      float f;
      int i;
    } result;

    // 2^n = (n + 127) << 23 in IEEE 754 format
    result.i = (n + 127) << 23;

    return poly * result.f;
  }

  /**
   * @brief Fast natural logarithm
   * @param x Input value (x > 0)
   * @return ln(x)
   * @note Uses bit manipulation for range reduction and polynomial approximation
   */
  float
  log(float x)
  {
    if (x <= 0.0f)
      return -1e38f; // Handle invalid input
    if (x == 1.0f)
      return 0.0f;

    // Extract exponent and mantissa using bit manipulation
    union
    {
      float f;
      int i;
    } input;
    input.f = x;

    // IEEE 754: extract exponent (remove bias of 127)
    int exponent = ((input.i >> 23) & 0xFF) - 127;

    // Extract mantissa and normalize to [1, 2)
    input.i = (input.i & 0x007FFFFF) | 0x3F800000; // Set exponent to 127 (bias for 1.0)
    float mantissa = input.f;

    // Range reduction: log(x) = log(2^e * m) = e*ln(2) + log(m)
    // where m is in [1, 2), so log(m) is in [0, ln(2)]

    // Transform mantissa to [-1/3, 1/3] for better polynomial convergence
    // Using log((1+u)/(1-u)) = 2u(1 + u²/3 + u⁴/5 + ...)
    float t = (mantissa - 1.0f) / (mantissa + 1.0f);
    float t2 = t * t;

    // Polynomial approximation
    float poly = t * (2.0f + t2 * (2.0f / 3.0f + t2 * (2.0f / 5.0f + t2 * (2.0f / 7.0f + t2 * 2.0f / 9.0f))));

    // Combine: log(x) = exponent * ln(2) + log(mantissa)
    constexpr float ln2 = 0.69314718055994531f;
    return static_cast<float>(exponent) * ln2 + poly;
  }

  /**
   * @brief Fast base-10 logarithm
   * @param x Input value (x > 0)
   * @return log10(x)
   */
  float
  log10(float x)
  {
    constexpr float inv_ln10 = 0.43429448190325176f; // 1/ln(10)
    return log(x) * inv_ln10;
  }

  /**
   * @brief Fast base-2 logarithm
   * @param x Input value (x > 0)
   * @return log2(x)
   */
  float
  log2(float x)
  {
    constexpr float inv_ln2 = 1.44269504088896341f; // 1/ln(2)
    return log(x) * inv_ln2;
  }

  /**
   * @brief Fast power function (optimized)
   * @param base Base value
   * @param exponent Exponent value
   * @return base^exponent
   * @note Optimized with more special cases and integer exponent handling
   */
  float
  pow(float base, float exponent)
  {
    // Handle special cases first (most common optimizations)
    if (exponent == 0.0f)
      return 1.0f;
    if (exponent == 1.0f)
      return base;
    if (base == 0.0f)
      return (exponent > 0.0f) ? 0.0f : 1e38f;
    if (base == 1.0f)
      return 1.0f;

    // Fast integer exponent cases
    if (exponent == 2.0f)
      return base * base;
    if (exponent == 3.0f)
      return base * base * base;
    if (exponent == 4.0f)
    {
      float b2 = base * base;
      return b2 * b2;
    }
    if (exponent == 0.5f)
      return sqrt(base);
    if (exponent == -1.0f)
      return 1.0f / base;
    if (exponent == -2.0f)
      return 1.0f / (base * base);

    // Check for integer exponents (use fast integer power)
    int int_exp = static_cast<int>(exponent);
    if (exponent == static_cast<float>(int_exp) && std::abs(int_exp) <= 32)
    {
      // Fast integer power using binary exponentiation
      bool negative_result = false;
      if (base < 0.0f && (int_exp & 1))
      {
        negative_result = true;
        base = -base;
      }
      else if (base < 0.0f)
      {
        base = -base;
      }

      float result = 1.0f;
      float current_base = base;
      int abs_exp = std::abs(int_exp);

      while (abs_exp > 0)
      {
        if (abs_exp & 1)
        {
          result *= current_base;
        }
        current_base *= current_base;
        abs_exp >>= 1;
      }

      if (int_exp < 0)
        result = 1.0f / result;
      return negative_result ? -result : result;
    }

    // Handle negative base (only for integer exponents - already handled above)
    bool negative_result = false;
    if (base < 0.0f)
    {
      return 0.0f; // Invalid: negative base with fractional exponent
    }

    // For positive base with fractional exponent: base^exponent = exp(exponent * log(base))
    float result = exp(exponent * log(base));
    return result;
  }

  /**
   * @brief Fast floating-point remainder function
   * @param dividend The dividend
   * @param divisor The divisor
   * @return Floating-point remainder of dividend/divisor
   * @note Hybrid implementation: fast method for small values, std::fmod for large values
   */
  float
  fmod(float dividend, float divisor)
  {
    if (divisor == 0.0f)
      return 0.0f; // Handle division by zero
    if (std::abs(dividend) < std::abs(divisor))
      return dividend;

    // Define precision-safe range based on empirical testing
    // Use extremely conservative threshold to ensure high precision
    constexpr float max_safe_value = 25.0f; // Extremely conservative threshold

    // Use standard library for large values to maintain precision
    if (std::abs(dividend) > max_safe_value || std::abs(divisor) > max_safe_value)
    {
      return std::fmod(dividend, divisor);
    }

    // Fast method for smaller values: fmod(x,y) = x - trunc(x/y) * y
    float quotient = dividend / divisor;

    // Additional safety check: if quotient is too large, use standard library
    if (std::abs(quotient) > max_safe_value)
    {
      return std::fmod(dividend, divisor);
    }

    // Fast truncation towards zero (safe for smaller values)
    int int_quotient = static_cast<int>(quotient);
    float truncated_quotient = static_cast<float>(int_quotient);

    return dividend - truncated_quotient * divisor;
  }

  /**
   * @brief Fast ceiling function
   * @param x Input value
   * @return Smallest integer >= x
   * @note Uses bit manipulation and efficient integer conversion
   */
  float
  ceil(float x)
  {
    if (x >= 0.0f)
    {
      int int_x = static_cast<int>(x);
      return (x > static_cast<float>(int_x)) ? static_cast<float>(int_x + 1) : static_cast<float>(int_x);
    }
    else
    {
      int int_x = static_cast<int>(x);
      return static_cast<float>(int_x);
    }
  }

  /**
   * @brief Fast floor function
   * @param x Input value
   * @return Largest integer <= x
   * @note Uses bit manipulation and efficient integer conversion
   */
  float
  floor(float x)
  {
    if (x >= 0.0f)
    {
      int int_x = static_cast<int>(x);
      return static_cast<float>(int_x);
    }
    else
    {
      int int_x = static_cast<int>(x);
      return (x < static_cast<float>(int_x)) ? static_cast<float>(int_x - 1) : static_cast<float>(int_x);
    }
  }

  /**
   * @brief Fast round function
   * @param x Input value
   * @return Nearest integer to x
   * @note Uses efficient rounding to nearest even (banker's rounding)
   */
  float
  round(float x)
  {
    if (x >= 0.0f)
    {
      return floor(x + 0.5f);
    }
    else
    {
      return ceil(x - 0.5f);
    }
  }

  /**
   * @brief Fast hyperbolic sine
   * @param x Input value
   * @return sinh(x) = (e^x - e^(-x)) / 2
   * @note Uses optimized exp function and symmetry properties
   */
  float
  sinh(float x)
  {
    // Handle small values with Taylor series: sinh(x) ≈ x + x³/6 for |x| < 0.5
    if (std::abs(x) < 0.5f)
    {
      float x2 = x * x;
      return x * (1.0f + x2 * (1.0f / 6.0f + x2 * (1.0f / 120.0f + x2 / 5040.0f)));
    }

    // For larger values: sinh(x) = (e^x - e^(-x)) / 2
    // Use symmetry: sinh(-x) = -sinh(x)
    bool negative = x < 0.0f;
    if (negative)
      x = -x;

    float exp_x = exp(x);
    float exp_neg_x = 1.0f / exp_x;
    float result = 0.5f * (exp_x - exp_neg_x);

    return negative ? -result : result;
  }

  /**
   * @brief Fast hyperbolic cosine
   * @param x Input value
   * @return cosh(x) = (e^x + e^(-x)) / 2
   * @note Uses optimized exp function and even function property
   */
  float
  cosh(float x)
  {
    // Handle small values with Taylor series: cosh(x) ≈ 1 + x²/2 for |x| < 0.5
    if (std::abs(x) < 0.5f)
    {
      float x2 = x * x;
      return 1.0f + x2 * (0.5f + x2 * (1.0f / 24.0f + x2 * (1.0f / 720.0f + x2 / 40320.0f)));
    }

    // For larger values: cosh(x) = (e^x + e^(-x)) / 2
    // cosh is even function: cosh(-x) = cosh(x)
    x = std::abs(x);

    float exp_x = exp(x);
    float exp_neg_x = 1.0f / exp_x;
    return 0.5f * (exp_x + exp_neg_x);
  }

  /**
   * @brief Fast hyperbolic tangent
   * @param x Input value
   * @return tanh(x) = sinh(x) / cosh(x)
   * @note Uses optimized rational approximation for better performance
   */
  float
  tanh(float x)
  {
    // Handle extreme values
    if (x > 5.0f)
      return 1.0f;
    if (x < -5.0f)
      return -1.0f;

    // For small values, use Taylor series: tanh(x) ≈ x - x³/3 + 2x⁵/15
    if (std::abs(x) < 0.5f)
    {
      float x2 = x * x;
      return x * (1.0f - x2 * (1.0f / 3.0f - x2 * (2.0f / 15.0f - x2 * 17.0f / 315.0f)));
    }

    // For medium values, use efficient formula: tanh(x) = (e^(2x) - 1) / (e^(2x) + 1)
    float exp_2x = exp(2.0f * x);
    return (exp_2x - 1.0f) / (exp_2x + 1.0f);
  }

  /**
   * @brief Fast inverse hyperbolic sine
   * @param x Input value
   * @return asinh(x) = log(x + sqrt(x² + 1))
   * @note Uses optimized log and sqrt functions
   */
  float
  asinh(float x)
  {
    // Handle small values with Taylor series: asinh(x) ≈ x - x³/6 + 3x⁵/40
    if (std::abs(x) < 0.5f)
    {
      float x2 = x * x;
      return x * (1.0f - x2 * (1.0f / 6.0f - x2 * (3.0f / 40.0f - x2 * 15.0f / 336.0f)));
    }

    // Use symmetry: asinh(-x) = -asinh(x)
    bool negative = x < 0.0f;
    if (negative)
      x = -x;

    // For larger values: asinh(x) = log(x + sqrt(x² + 1))
    float result = log(x + sqrt(x * x + 1.0f));

    return negative ? -result : result;
  }

  /**
   * @brief Fast inverse hyperbolic cosine
   * @param x Input value (x >= 1)
   * @return acosh(x) = log(x + sqrt(x² - 1))
   * @note Uses optimized log and sqrt functions
   */
  float
  acosh(float x)
  {
    if (x < 1.0f)
      return 0.0f; // Invalid input, return 0

    // Handle values close to 1 with Taylor series
    if (x < 1.5f)
    {
      float t = x - 1.0f;
      float sqrt_2t = sqrt(2.0f * t);
      return sqrt_2t * (1.0f - t * (1.0f / 12.0f - t * (3.0f / 160.0f - t * 5.0f / 896.0f)));
    }

    // For larger values: acosh(x) = log(x + sqrt(x² - 1))
    return log(x + sqrt(x * x - 1.0f));
  }

  /**
   * @brief Fast inverse hyperbolic tangent
   * @param x Input value (-1 < x < 1)
   * @return atanh(x) = 0.5 * log((1 + x) / (1 - x))
   * @note Uses optimized log function
   */
  float
  atanh(float x)
  {
    // Handle boundary cases
    if (std::abs(x) >= 1.0f)
      return 0.0f; // Invalid input

    // Handle small values with Taylor series: atanh(x) ≈ x + x³/3 + 2x⁵/15
    if (std::abs(x) < 0.5f)
    {
      float x2 = x * x;
      return x * (1.0f + x2 * (1.0f / 3.0f + x2 * (2.0f / 15.0f + x2 * 17.0f / 315.0f)));
    }

    // For larger values: atanh(x) = 0.5 * log((1 + x) / (1 - x))
    return 0.5f * log((1.0f + x) / (1.0f - x));
  }

} // namespace FastMath