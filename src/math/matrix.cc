#if !defined(VULCAD_MATH_MATRIX)
#define VULCAD_MATH_MATRIX

#include "sigma.cc"
#include <vector>

/**
 * arbitrary dimension matrix
 *
 * **caution**
 * use A._(i, j) to access element of ith row and jth column instead of A[i][j]
 * becasue A[i][j] refers to ith columns vector's jth element,
 * which is different from common index notation
 */
class Mat {
  /**
   * consider matrix as array of column vectors
   */
  std::vector<std::vector<float>> elements;

public:
  u_int16_t countColumns;
  u_int16_t countRows;

  /**
   * initialise identity matrix
   */
  Mat(uint16_t countRows = 2, uint16_t countColumns = 2) {
    this->countRows = countRows;
    this->countColumns = countColumns;
    for (int i = 0; i < this->countColumns; i++) {
      this->elements.push_back(std::vector<float>(this->countRows, 0));
      if (i <= std::min(this->countRows, this->countColumns)) [[likely]]
        this->elements[i][i] = 1;
    }
  }

  /**
   * @param rowIndex 1 is the first index, not 0
   * @param columnIndex 1 is the first index, not 0
   */
  float &_(u_int16_t rowIndex, u_int16_t columnIndex) {
    if (rowIndex < 1 || this->countRows < rowIndex) [[unlikely]]
      throw "rowIndex must be between 1 ~ " + this->countRows;
    if (rowIndex < 1 || this->countRows < rowIndex) [[unlikely]]
      throw "columnIndex must be between 1 ~ " + this->countColumns;
    return this->elements[columnIndex - 1][rowIndex - 1];
  }

  Mat inverse() {
    if (this->countRows != this->countColumns) [[unlikely]]
      throw "the number of rows must be equal to the number of columns";

    // identity matrix
    auto inverseMat = Mat(this->countRows, this->countColumns);
    auto mat = this->copy();
    // use gaussian elimination to calculate inverse matrix
    for (int j = 1; j <= this->countColumns; j++) {
      for (int i = j; i <= this->countRows; i++) {
        auto element = mat._(i, j);
        if (element != 0) {
          if (i != j) {
            mat.swapRow(i, j);
            inverseMat.swapRow(i, j);
          }
          if (element != 1) {
            mat.multiplyRow(i, 1.f / element);
            inverseMat.multiplyRow(i, 1.f / element);
          }
          break;
        }
        if (i == this->countRows)
          throw "this matrix is not invertible";
      }
      for (int i = 1; i <= this->countRows; i++)
        [[likely]] if (i != j) {
          auto element = mat._(i, j);
          if (element != 0) {
            mat.subtractRow(i, j, element);
            inverseMat.subtractRow(i, j, element);
          }
        }
    }

    return inverseMat;
  }

  Mat operator+(Mat &mat) {
    auto newMat = this->copy();
    for (int i = 1; i <= this->countRows; i++)
      for (int j = 1; j <= this->countColumns; j++)
        newMat._(i, j) += mat._(i, j);
    return newMat;
  }

  Mat operator-(Mat &mat) {
    auto newMat = this->copy();
    for (int i = 1; i <= this->countRows; i++)
      for (int j = 1; j <= this->countColumns; j++)
        newMat._(i, j) -= mat._(i, j);
    return newMat;
  }

  Mat operator*(float scalar) {
    auto newMat = this->copy();
    for (int i = 1; i <= this->countRows; i++)
      for (int j = 1; j <= this->countColumns; j++)
        newMat._(i, j) *= scalar;
    return newMat;
  }

  friend Mat operator*(float scalar, Mat mat) {
    for (int i = 1; i <= mat.countRows; i++)
      for (int j = 1; j <= mat.countColumns; j++)
        mat._(i, j) *= scalar;
    return mat;
  }

  Mat operator*(Mat mat) {
    auto newMat = Mat(this->countRows, mat.countColumns);
    for (int i = 1; i <= newMat.countRows; i++)
      for (int j = 1; j <= newMat.countColumns; j++)
        newMat._(i, j) = sigma(
            [i, j, &mat, this](int k) { return this->_(i, k) * mat._(k, j); },
            1, this->countColumns);
    return newMat;
  }

  Mat operator/(float scalar) {
    auto newMat = this->copy();
    for (int i = 1; i <= this->countRows; i++)
      for (int j = 1; j <= this->countColumns; j++)
        newMat._(i, j) /= scalar;
    return newMat;
  }

private:
  Mat copy() {
    auto copy = Mat(this->countColumns, this->countRows);
    copy.elements = this->elements;
    return copy;
  }

  /**
   * @param i column index to multiply
   * @param scalar
   */
  void multiplyColumn(uint16_t i, float scalar) {
    for (int k = 1; k <= this->countRows; k++)
      this->_(k, i) *= scalar;
  }

  /**
   * @param i row index to multiply
   * @param scalar
   */
  void multiplyRow(uint16_t i, float scalar) {
    for (int k = 1; k <= this->countColumns; k++)
      this->_(i, k) *= scalar;
  }

  /**
   * subtract column i by column j multiplied by scalar
   * @param i column index to modify. the first index is 1
   * @param j column index to subtract by, the first index is 1
   * @param scalar multiply column j by scalar
   */
  void subtractColumn(uint16_t i, uint16_t j, float scalar = 1) {
    for (int k = 1; k <= this->countRows; k++)
      this->_(k, i) -= this->_(k, j) * scalar;
  }

  /**
   * subtract row i by row j multiplied by scalar
   * @param i row index to modify. the first index is 1
   * @param j row index to subtract by, the first index is 1
   * @param scalar multiply row j by scalar
   */
  void subtractRow(uint16_t i, uint16_t j, float scalar = 1) {
    for (int k = 1; k <= this->countColumns; k++)
      this->_(i, k) -= this->_(j, k) * scalar;
  }

  /**
   * swap row i and j
   * @param i row index to swap. the first row is 1
   * @param j row index to swap. the first row is 1
   */
  void swapRow(uint16_t i, uint16_t j) {
    for (int k = 1; k <= this->countColumns; k++) {
      auto tempI = this->_(i, k);
      this->_(i, k) = this->_(j, k);
      this->_(j, k) = tempI;
    }
  }

  /**
   * swap column i and j
   * @param i column index to swap. the first column is 1
   * @param j column index to swap. the first column is 1
   */
  void swapColumn(uint16_t i, uint16_t j) {
    for (int k = 1; k <= this->countRows; k++) {
      auto tempI = this->_(k, i);
      this->_(k, i) = this->_(k, j);
      this->_(k, j) = tempI;
    }
  }
};

#endif // VULCAD_MATH_MATRIX
