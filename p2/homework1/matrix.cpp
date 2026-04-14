#include <iostream>

struct UpperMatrix {
  int **rows = nullptr;    // Tablica wskaźników na wiersze
  int *rowSizes = nullptr; // Tablica przechowująca długości wierszy
  int rowCount = 0;        // Liczba wierszy

  void AddRow(int *newData, int size) {
    int **newRows = new int *[rowCount + 1];
    int *newRowSizes = new int[rowCount + 1];

    newRows[0] = new int[size];
    for (int i = 0; i < size; i++)
      newRows[0][i] = newData[i];
    newRowSizes[0] = size;

    for (int i = 0; i < rowCount; i++) {
      newRows[i + 1] = rows[i];
      newRowSizes[i + 1] = rowSizes[i];
    }

    delete[] rows;
    delete[] rowSizes;

    rows = newRows;
    rowSizes = newRowSizes;
    rowCount++;
  }

  void AddColumn(int *colData) {
    for (int i = 0; i < rowCount; i++) {
      int oldSize = rowSizes[i];
      int *newRow = new int[oldSize + 1];

      newRow[0] = colData[i];
      for (int j = 0; j < oldSize; j++) {
        newRow[j + 1] = rows[i][j];
      }

      delete[] rows[i];
      rows[i] = newRow;
      rowSizes[i] = oldSize + 1;
    }
  }

  // 3. RemoveRow - Usuń pierwszy wiersz
  void RemoveRow() {
    if (rowCount == 0)
      return;

    delete[] rows[0]; // Kasujemy dane pierwszego wiersza

    int **newRows = new int *[rowCount - 1];
    int *newRowSizes = new int[rowCount - 1];

    for (int i = 1; i < rowCount; i++) {
      newRows[i - 1] = rows[i];
      newRowSizes[i - 1] = rowSizes[i];
    }

    delete[] rows;
    delete[] rowSizes;

    rows = newRows;
    rowSizes = newRowSizes;
    rowCount--;
  }

  // 4. RemoveColumn - Usuń pierwszy element z każdego wiersza
  void RemoveColumn() {
    for (int i = 0; i < rowCount; i++) {
      if (rowSizes[i] <= 1)
        continue; // Zabezpieczenie przed pustym wierszem

      int *newRow = new int[rowSizes[i] - 1];
      for (int j = 1; j < rowSizes[i]; j++) {
        newRow[j - 1] = rows[i][j];
      }

      delete[] rows[i];
      rows[i] = newRow;
      rowSizes[i]--;
    }
  }

  void PrintMatrix() {
    for (int i = 0; i < rowCount; i++) {
      for (int s = 0; s < i; s++)
        std::cout << "  "; // Wcięcie
      for (int j = 0; j < rowSizes[i]; j++) {
        std::cout << rows[i][j] << " ";
      }
      std::cout << "\n";
    }
    std::cout << "---\n";
  }
};

int main() {
  UpperMatrix m;

  int r1[] = {1};
  m.AddRow(r1, 1);

  int r2[] = {2, 3};
  m.AddRow(r2, 2);

  std::cout << "Start:\n";
  m.PrintMatrix();

  int col[] = {9, 8};
  std::cout << "Dodaj kolumne [9, 8]:\n";
  m.AddColumn(col);
  m.PrintMatrix();

  return 0;
}
