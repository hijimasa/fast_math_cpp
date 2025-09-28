/**
 * @file fast_math.hpp
 * @brief Fast trigonometric functions
 * @author MCL Development Team
 * @version 2.0
 * @date 2025
 */

#pragma once

#include <cmath>

namespace FastMath
{
  /**
   * @brief Fast sine
   * @param angle Angle in radians
   * @return Sine value
   * @note Reference: https://yuqlid.sakura.ne.jp/dokuwiki/fast_sin_cos
   */
  float sin(float theta);

  /**
   * @brief Fast cosine
   * @param angle Angle in radians
   * @return Cosine value
   * @note Reference: https://yuqlid.sakura.ne.jp/dokuwiki/fast_sin_cos
   */
  float cos(float theta);

  /**
   * @brief Fast square root using Newton-Raphson method
   * @param number Input number
   * @return Square root of the input number
   * @note This function uses Newton-Raphson iteration for high precision
   */
  float sqrt(float number);

  /**
   * @brief Fast tangent
   * @param angle Angle in radians
   * @return Tangent value
   * @note Uses sin/cos ratio for accuracy
   */
  float tan(float theta);

  /**
   * @brief Fast arc sine using Newton-Raphson method
   * @param x Input value [-1, 1]
   * @return Arc sine in radians
   */
  float asin(float x);

  /**
   * @brief Fast arc cosine using Newton-Raphson method
   * @param x Input value [-1, 1]
   * @return Arc cosine in radians
   */
  float acos(float x);

  /**
   * @brief Fast arc tangent 2 (atan2)
   * @param y Y coordinate
   * @param x X coordinate
   * @return Arc tangent in radians [-π, π]
   */
  float atan2(float y, float x);

  /**
   * @brief Fast exponential function
   * @param x Input value
   * @return e^x
   * @note Uses optimized polynomial approximation and bit manipulation
   */
  float exp(float x);

  /**
   * @brief Fast natural logarithm
   * @param x Input value (x > 0)
   * @return ln(x)
   * @note Uses bit manipulation and polynomial approximation
   */
  float log(float x);

  /**
   * @brief Fast base-10 logarithm
   * @param x Input value (x > 0)
   * @return log10(x)
   * @note Uses log(x) / log(10)
   */
  float log10(float x);

  /**
   * @brief Fast base-2 logarithm
   * @param x Input value (x > 0)
   * @return log2(x)
   * @note Uses log(x) / log(2)
   */
  float log2(float x);

  /**
   * @brief Fast power function
   * @param base Base value
   * @param exponent Exponent value
   * @return base^exponent
   * @note Optimized with special cases and fast exp/log
   */
  float pow(float base, float exponent);

  /**
   * @brief Fast floating-point remainder function
   * @param dividend The dividend
   * @param divisor The divisor
   * @return Floating-point remainder of dividend/divisor
   * @note Efficient modulo operation for floating-point numbers
   */
  float fmod(float dividend, float divisor);

  /**
   * @brief Fast ceiling function
   * @param x Input value
   * @return Smallest integer >= x
   * @note Uses bit manipulation for efficiency
   */
  float ceil(float x);

  /**
   * @brief Fast floor function
   * @param x Input value
   * @return Largest integer <= x
   * @note Uses bit manipulation for efficiency
   */
  float floor(float x);

  /**
   * @brief Fast round function
   * @param x Input value
   * @return Nearest integer to x
   * @note Uses efficient rounding to nearest even
   */
  float round(float x);

  /**
   * @brief Fast hyperbolic sine
   * @param x Input value
   * @return sinh(x) = (e^x - e^(-x)) / 2
   * @note Uses optimized exp function for efficiency
   */
  float sinh(float x);

  /**
   * @brief Fast hyperbolic cosine
   * @param x Input value
   * @return cosh(x) = (e^x + e^(-x)) / 2
   * @note Uses optimized exp function for efficiency
   */
  float cosh(float x);

  /**
   * @brief Fast hyperbolic tangent
   * @param x Input value
   * @return tanh(x) = sinh(x) / cosh(x)
   * @note Uses optimized rational approximation for better performance
   */
  float tanh(float x);

  /**
   * @brief Fast inverse hyperbolic sine
   * @param x Input value
   * @return asinh(x) = log(x + sqrt(x² + 1))
   * @note Uses optimized log and sqrt functions
   */
  float asinh(float x);

  /**
   * @brief Fast inverse hyperbolic cosine
   * @param x Input value (x >= 1)
   * @return acosh(x) = log(x + sqrt(x² - 1))
   * @note Uses optimized log and sqrt functions
   */
  float acosh(float x);

  /**
   * @brief Fast inverse hyperbolic tangent
   * @param x Input value (-1 < x < 1)
   * @return atanh(x) = 0.5 * log((1 + x) / (1 - x))
   * @note Uses optimized log function
   */
  float atanh(float x);

} // namespace FastMath