#include <iostream>

using namespace std;

class Matrix {
  // hermetyzacja
private:
  int **matrix;
  unsigned short *rowSizes;
  unsigned short rowCount;

  void freeMemory() {
    if (matrix != nullptr) {
      unsigned short i;
      for (i = 0; i < rowCount; i++) {
        delete[] *(matrix + i);
      }
      delete[] matrix;
      matrix = nullptr;
    }
    if (rowSizes != nullptr) {
      delete[] rowSizes;
      rowSizes = nullptr;
    }
    rowCount = 0;
  }

public:
  // konstruktor
  Matrix() {
    matrix = nullptr;
    rowSizes = nullptr;
    rowCount = 0;
  }
  // konstruktor kopiujacy
  Matrix(const Matrix &other) {
    rowCount = other.rowCount;

    if (rowCount == 0) {
      matrix = nullptr;
      rowSizes = nullptr;
      return;
    }

    matrix = new int *[rowCount];
    rowSizes = new unsigned short[rowCount];

    unsigned short i, j, currentW;
    for (i = 0; i < rowCount; i++) {
      currentW = *(other.rowSizes + i);
      *(rowSizes + i) = currentW;

      *(matrix + i) = new int[currentW];

      for (j = 0; j < currentW; j++) {
        *(*(matrix + i) + j) = *(*(other.matrix + i) + j);
      }
    }
  }
  // destruktor
  ~Matrix() { freeMemory(); }

  // operator przypisania
  Matrix &operator=(const Matrix &other) {
    if (this == &other)
      return *this;

    freeMemory();

    rowCount = other.rowCount;
    if (rowCount == 0) {
      matrix = nullptr;
      rowSizes = nullptr;
      return *this;
    }

    matrix = new int *[rowCount];
    rowSizes = new unsigned short[rowCount];

    unsigned short i, j, currentW;
    for (i = 0; i < rowCount; i++) {
      currentW = *(other.rowSizes + i);
      *(rowSizes + i) = currentW;

      *(matrix + i) = new int[currentW];

      for (j = 0; j < currentW; j++) {
        *(*(matrix + i) + j) = *(*(other.matrix + i) + j);
      }
    }
    return *this;
  }

  void AFR() {
    unsigned short w, i;
    if (!(cin >> w))
      return;

    int *newRow = new int[w];
    for (i = 0; i < w; i++) {
      cin >> *(newRow + i);
    }

    int **tempMatrix = new int *[rowCount + 1];
    unsigned short *tempSizes = new unsigned short[rowCount + 1];

    *tempMatrix = newRow;
    *tempSizes = w;

    for (i = 0; i < rowCount; i++) {
      *(tempMatrix + i + 1) = *(matrix + i);
      *(tempSizes + i + 1) = *(rowSizes + i);
    }

    delete[] matrix;
    delete[] rowSizes;

    matrix = tempMatrix;
    rowSizes = tempSizes;
    rowCount++;
  }
  void Print() {
    cout << '\n';
    for (unsigned short i = 0; i < rowCount; i++) {
      unsigned short len = *(rowSizes + i);
      for (unsigned short j = 0; j < len; j++) {
        cout << *(*(matrix + i) + j) << " ";
      }
      cout << "\n";
    }
  }
};

int main() {
  Matrix m;
  m.AFR();
  m.AFR();
  m.Print();
  return 0;
}
