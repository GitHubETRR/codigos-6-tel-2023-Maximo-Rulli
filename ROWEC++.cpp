#include <iostream>
#include <vector>

class Matrix {
private:
  // The matrix takes as input the number of rows and columns
  int rows, cols;
  std::vector<std::vector<float>> data;

public:
  Matrix(int m, int n, std::vector<std::vector<float>> input)
      : rows(m), cols(n), data(input) {}
  // This function prints the matrix
  void printMatrix() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        std::cout << data[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  // In this function we get the rowechelon form of the matrix
  // we also return the matrix rank
  int rowEchelon() {
    // This variables will be used when performing vector operations
    std::vector<float> pivots;
    pivots.resize(rows);
    float factor = 0.0;
    bool iterated = false;

    int rank = 0;

    // Build copy of the matrix
    std::vector<std::vector<int>> rowEch(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        rowEch[i][j] = data[i][j]; // Copy data from original matrix
      }
    }

    // std::cout << "Matrix copied!" << std::endl;

    // Perform math to get row echelon form
    for (int i = 0; i < rows - 1; i++) {
      iterated = false;
      for (int j = 0; j < cols; j++) {
        if (rowEch[i][j] != 0 && iterated == false) {
          // Get the row pivot
          pivots[i] = rowEch[i][j];
          iterated = true;

          // Perform row operations
          for (int k = i + 1; k < rows; k++) {
            factor = rowEch[k][j] / pivots[i];
            for (int l = j; l < cols; l++) {
              // Get 0s under the pivot
              rowEch[k][l] -= rowEch[i][l] * factor;
            }
          }
        }
      }
    }

    // Print the row echelon form
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        std::cout << rowEch[i][j] << " ";
      }
      std::cout << std::endl;
    }

    for (int i = 0; i < rows; i++) {
      if (pivots[i] != 0) {
        rank++;
      }
    }

    // Check whether the last row has a pivot
    for (int j = 0; j < cols; j++) {
      if (rowEch[rows - 1][j] != 0.0) {
        rank++;
        break;
      }
    }
    return rank;
  }
};

int main() {
  std::vector<std::vector<float>> inputData = {{1.0, 2.0, 5.0, 6.0},
                                               {5.0, -7.0, 3.0, 2.0},
                                               {1.0, 2.0, 3.0, 6.0},
                                               {8.0, 2.0, 8.0, -6.0}};
  Matrix myMatrix(4, 4, inputData);
  myMatrix.printMatrix();
  int mat_rank = myMatrix.rowEchelon();
  std::cout << "The matrix is rank " << mat_rank << " " << std::endl;
}
