#if !defined(VULCAD_MATH_BINOMIAL)
#define VULCAD_MATH_BINOMIAL

#include <vector>

/** get binomial coefficients nCk */
int binomial(int n, int k) {
  // calculate by Pascal's triangle
  std::vector<std::vector<float>> pascalTriangle(n + 1);
  for (int i = 0; i <= n; i++) {
    std::vector<float> pascalTriangleRowI(i + 1);
    for (int j = 0; j < i + 1; j++)
      pascalTriangleRowI[j] = j == 0 || j == i ? 1
                                               : pascalTriangle[i - 1][j - 1] +
                                                     pascalTriangle[i - 1][j];
    pascalTriangle[i] = pascalTriangleRowI;
  }
  return pascalTriangle[n][k];
}

#endif // VULCAD_MATH_BINOMIAL
