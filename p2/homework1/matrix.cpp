#include <iostream>

struct UpperMatrix {
  int **rows;    // Tablica wskaźników na wiersze
  int *rowSizes; // Tablica przechowująca długość każdego wiersza
  int rowCount;  // Liczba wierszy
} rix;

void PrintMatrix(UpperMatrix *m) {
  for (int i = 0; i < m->rowCount; i++) {
    for (int j = 0; j < m->rowSizes[i]; j++) {
      printf("%3d ", m->rows[i][j]);
    }
    printf("\n");
  }
}

// 1. AddRow - dodaje nowy, najdłuższy wiersz na górę
void AddRow(UpperMatrix *m, int *newElements, int size) {
  m->rowCount++;
  m->rows = realloc(m->rows, m->rowCount * sizeof(int *));
  m->rowSizes = realloc(m->rowSizes, m->rowCount * sizeof(int));

  // Przesuwamy wiersze w dół, by zrobić miejsce na indeksie 0
  for (int i = m->rowCount - 1; i > 0; i--) {
    m->rows[i] = m->rows[i - 1];
    m->rowSizes[i] = m->rowSizes[i - 1];
  }

  // Wstawiamy nowy wiersz na początek
  m->rows[0] = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++)
    m->rows[0][i] = newElements[i];
  m->rowSizes[0] = size;
}

// 2. RemoveRow - usuwa pierwszy wiersz
void RemoveRow(UpperMatrix *m) {
  if (m->rowCount == 0)
    return;

  free(m->rows[0]); // zwalniamy pamięć pierwszego wiersza

  for (int i = 0; i < m->rowCount - 1; i++) {
    m->rows[i] = m->rows[i + 1];
    m->rowSizes[i] = m->rowSizes[i + 1];
  }

  m->rowCount--;
  m->rows = realloc(m->rows, m->rowCount * sizeof(int *));
  m->rowSizes = realloc(m->rowSizes, m->rowCount * sizeof(int));
}

// 3. RemoveColumn - usuwa pierwszą kolumnę (pierwszy element każdego wiersza)
void RemoveColumn(UpperMatrix *m) {
  for (int i = 0; i < m->rowCount; i++) {
    if (m->rowSizes[i] > 0) {
      // Przesuwamy elementy wewnątrz wiersza w lewo
      for (int j = 0; j < m->rowSizes[i] - 1; j++) {
        m->rows[i][j] = m->rows[i][j + 1];
      }
      m->rowSizes[i]--;
      // Opcjonalnie zmniejszamy pamięć wiersza
      m->rows[i] = realloc(m->rows[i], m->rowSizes[i] * sizeof(int));
    }
  }
  // Jeśli ostatni wiersz stał się pusty - usuwamy go całkowicie
  if (m->rowCount > 0 && m->rowSizes[m->rowCount - 1] == 0) {
    m->rowCount--;
  }
}

int main() {
  UpperMatrix m = {NULL, NULL, 0};

  int r1[] = {10};
  AddRow(&m, r1, 1);

  int r2[] = {20, 21};
  AddRow(&m, r2, 2);

  int r3[] = {30, 31, 32};
  AddRow(&m, r3, 3);

  printf("Macierz po dodaniu 3 wierszy:\n");
  PrintMatrix(&m);

  printf("Usuwam pierwsza kolumne:\n");
  RemoveColumn(&m);
  PrintMatrix(&m);

  printf("Usuwam pierwszy wiersz:\n");
  RemoveRow(&m);
  PrintMatrix(&m);

  return 0;
}
