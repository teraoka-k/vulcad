#if !defined(VULCAD_MATH_MATRIX)
#define VULCAD_MATH_MATRIX

#include "sigma.cc"
#include <vector>

template <u_int16_t CountRows, u_int16_t CountColumns = CountRows> class Mat {
  /**
   * consider matrix as array of column vectors
   */
  std::vector<std::vector<float>> elements;

public:
  /**
   * initialise identity matrix
   */
  Mat() {
    for (int i = 0; i < CountColumns; i++) {
      this->elements.push_back(std::vector<float>(CountRows, 0));
      if (i <= std::min(CountRows, CountColumns)) [[likely]]
        this->elements[i][i] = 1;
    }
  }

  /**
   * @param rowIndex 1 is the first index, not 0
   * @param columnIndex 1 is the first index, not 0
   */
  float &_(u_int16_t rowIndex, u_int16_t columnIndex) {
    if (rowIndex < 1 || CountRows < rowIndex) [[unlikely]]
      throw "rowIndex must be between 1 ~ " + CountRows;
    if (rowIndex < 1 || CountRows < rowIndex) [[unlikely]]
      throw "columnIndex must be between 1 ~ " + CountColumns;
    return this->elements[columnIndex - 1][rowIndex - 1];
  }

  Mat inverse() {
    if (CountRows != CountColumns) [[unlikely]]
      throw "the number of rows must be equal to the number of columns";

    // identity matrix
    Mat<CountRows, CountColumns> inverseMat;
    Mat mat = this->copy();
    // use gaussian elimination to calculate inverse matrix
    for (int j = 1; j <= CountColumns; j++) {
      for (int i = 1; i <= CountRows; i++) {
        auto element = mat._(i, j);
        if (element != 0) {
          if (i != j) {
            mat.swapRow(i, j);
            inverseMat.swapRow(i, j);
          }
          if (element != 1) {
            mat.multiplyRow(j, 1.f / element);
            inverseMat.multiplyRow(j, 1.f / element);
          }
          break;
        }
        if (i == CountRows)
          throw "this matrix is not invertible";
      }
      for (int i = 1; i <= CountRows; i++)
        if (i != j) [[unlikely]] {
          mat.subtractRow(i, j, mat._(i, j));
          inverseMat.subtractRow(i, j, mat._(i, j));
        }
    }

    return inverseMat;
  }

  Mat operator+(Mat<CountRows, CountColumns> &mat) {
    auto newMat = this->copy();
    for (int i = 1; i <= CountRows; i++)
      for (int j = 1; j <= CountColumns; j++)
        newMat._(i, j) += mat._(i, j);
    return newMat;
  }

  Mat operator-(Mat<CountRows, CountColumns> &mat) {
    auto newMat = this->copy();
    for (int i = 1; i <= CountRows; i++)
      for (int j = 1; j <= CountColumns; j++)
        newMat._(i, j) -= mat._(i, j);
    return newMat;
  }

  Mat operator*(float scalar) {
    auto newMat = this->copy();
    for (int i = 1; i <= CountRows; i++)
      for (int j = 1; j <= CountColumns; j++)
        newMat._(i, j) *= scalar;
    return newMat;
  }
  friend Mat operator*(float scalar, Mat<CountRows, CountColumns> mat) {
    for (int i = 1; i <= CountRows; i++)
      for (int j = 1; j <= CountColumns; j++)
        mat._(i, j) *= scalar;
    return mat;
  }
  template <u_int16_t C> Mat operator*(Mat<CountColumns, C> mat) {
    Mat<CountRows, CountColumns> newMat;
    for (int i = 1; i <= CountRows; i++)
      for (int j = 1; j <= CountColumns; j++)
        newMat._(i, j) = sigma(
            [i, j, &mat, this](int k) { return this->_(i, k) * mat._(k, j); },
            1, CountColumns);
    return newMat;
  }

  Mat operator/(float scalar) {
    auto newMat = this->copy();
    for (int i = 1; i <= CountRows; i++)
      for (int j = 1; j <= CountColumns; j++)
        newMat._(i, j) /= scalar;
    return newMat;
  }

private:
  Mat copy() {
    Mat<CountColumns, CountRows> copy;
    copy.elements = this->elements;
    return copy;
  }

  /**
   * @param i column index to multiply
   * @param scalar
   */
  void multiplyColumn(uint16_t i, float scalar) {
    for (int k = 1; k <= CountRows; k++)
      this->_(k, i) *= scalar;
  }

  /**
   * @param i row index to multiply
   * @param scalar
   */
  void multiplyRow(uint16_t i, float scalar) {
    for (int k = 1; k <= CountColumns; k++)
      this->_(i, k) *= scalar;
  }

  /**
   * subtract column i by column j multiplied by scalar
   * @param i column index to modify. the first index is 1
   * @param j column index to subtract by, the first index is 1
   * @param scalar multiply column j by scalar
   */
  void subtractColumn(uint16_t i, uint16_t j, float scalar = 1) {
    for (int k = 1; k <= CountRows; k++)
      this->_(k, i) -= this->_(k, j) * scalar;
  }

  /**
   * subtract row i by row j multiplied by scalar
   * @param i row index to modify. the first index is 1
   * @param j row index to subtract by, the first index is 1
   * @param scalar multiply row j by scalar
   */
  void subtractRow(uint16_t i, uint16_t j, float scalar = 1) {
    for (int k = 1; k <= CountColumns; k++)
      this->_(i, k) -= this->_(j, k) * scalar;
  }

  /**
   * swap row i and j
   * @param i row index to swap. the first row is 1
   * @param j row index to swap. the first row is 1
   */
  void swapRow(uint16_t i, uint16_t j) {
    for (int k = 1; k <= CountColumns; k++) {
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
    for (int k = 1; k <= CountRows; k++) {
      auto tempI = this->_(k, i);
      this->_(k, i) = this->_(k, j);
      this->_(k, j) = tempI;
    }
  }
};

#endif // VULCAD_MATH_MATRIX
