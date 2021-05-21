#if !defined(VULCAD_MATH_SIGMA)
#define VULCAD_MATH_SIGMA

#include <functional>

float sigma(std::function<float(int)> a, int from = 0, int to = 1) {
  float sum = 0;
  for (int k = from; k <= to; k++) {
    sum += a(k);
  }
  return sum;
}

#endif // VULCAD_MATH_SIGMA
