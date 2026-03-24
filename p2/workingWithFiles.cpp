#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void zapisIOdczyt() {
  ofstream out("plik1.txt");
  if (!out.is_open()) {
    cout << "Blad" << endl;
    return;
  }

  out << "agffa" << endl;
  out << "Dji." << endl;
  out.close();

  ifstream in("plik1.txt");
  if (!in.is_open()) {
    cout << "blad" << endl;
    return;
  }

  string line;
  while (getline(in, line)) {
    cout << line << endl;
  }
  in.close();
  cout << endl;
}

void odwrotnaKolejnoscLiniiOdKonca() {

  ofstream source("plik_zrodlowy2.txt");
  source << "1" << endl;
  source << "gaga" << endl;
  source << "afa3" << endl;
  source << "4f" << endl;
  source << "5" << endl;
  source.close();

  ifstream in("plik_zrodlowy2.txt", ios::binary);
  ofstream out("plik_odwrotny2.txt", ios::binary);

  if (!in.is_open()) {
    cout << "Blad" << endl;
    return;
  }

  in.seekg(0, ios::end);
  streamoff fileSize = (streamoff)(in.tellg());

  string line;
  streamoff pos = fileSize;
  streamoff lineEnd = fileSize;

  while (pos > 0) {
    pos = pos - 1;
    in.seekg(pos);

    char c = in.get();

    if (c == '\n' || pos == 0) {
      streamoff lineStart = pos;
      if (c == '\n') {
        lineStart = pos + 1;
      }

      in.seekg(lineStart);
      streamoff lineLength = lineEnd - lineStart;

      if (c == '\n' && pos == 0) {
        lineLength = lineLength - 1;
      }

      if (lineLength > 0) {
        vector<char> buffer(static_cast<size_t>(lineLength));
        in.read(buffer.data(), lineLength);
        line.assign(buffer.data(), lineLength);

        if (pos == 0 && c == '\n' && line.empty()) {
        } else {
          out << line << endl;
        }
      }

      lineEnd = pos;
    }
  }

  in.close();
  out.close();

  ifstream result("plik_odwrotny2.txt");
  while (getline(result, line)) {
    cout << line << endl;
  }
  cout << endl;
}

void odwrocZnakiWLiniach() {

  ofstream source("plik_do_odwrocenia.txt");
  source << "ABC" << endl;
  source << "12345" << endl;
  source << "Hd" << endl;
  source << "Test" << endl;
  source.close();

  ifstream in("plik_do_odwrocenia.txt");
  ofstream out("plik_odwrocone_znaki.txt");

  string line;
  while (getline(in, line)) {
    reverse(line.begin(), line.end());
    out << line << endl;
  }

  in.close();
  out.close();

  ifstream result("plik_odwrocone_znaki.txt");
  while (getline(result, line)) {
    cout << line << endl;
  }
  cout << endl;
}

void polaczPosortowanePliki() {

  ofstream out1("posortowany1.txt");
  out1 << "1 3 5 7 9" << endl;
  out1.close();

  ofstream out2("posortowany2.txt");
  out2 << "2 4 6 8 10" << endl;
  out2.close();

  ifstream in1("posortowany1.txt");
  ifstream in2("posortowany2.txt");
  ofstream out("polaczone_posortowane.txt");

  int val1, val2;
  bool hasVal1 = (bool)(in1 >> val1);
  bool hasVal2 = (bool)(in2 >> val2);

  while (hasVal1 && hasVal2) {
    if (val1 <= val2) {
      out << val1 << " ";
      hasVal1 = static_cast<bool>(in1 >> val1);
    } else {
      out << val2 << " ";
      hasVal2 = static_cast<bool>(in2 >> val2);
    }
  }

  while (hasVal1) {
    out << val1 << " ";
    hasVal1 = static_cast<bool>(in1 >> val1);
  }

  while (hasVal2) {
    out << val2 << " ";
    hasVal2 = static_cast<bool>(in2 >> val2);
  }
  out << endl;

  in1.close();
  in2.close();
  out.close();

  ifstream result("polaczone_posortowane.txt");
  string line;
  getline(result, line);
  cout << line << endl;
  cout << endl;
}

void testFlagPliku() {

  ofstream out("test_flags.txt");
  out << "Pierwsza linia" << endl;
  out << "Druga linia" << endl;
  out << "Trzecia linia" << endl;
  out.close();

  cout << "\nTest 1: ios::in (plik istnieje)" << endl;
  {
    fstream f("test_flags.txt", ios::in);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    cout << "  good(): " << (f.good() ? "TAK" : "NIE") << endl;
    cout << "  eof(): " << (f.eof() ? "TAK" : "NIE") << endl;
    cout << "  fail(): " << (f.fail() ? "TAK" : "NIE") << endl;
    cout << "  bad(): " << (f.bad() ? "TAK" : "NIE") << endl;
    string line;
    getline(f, line);
    cout << "  Mozliwosc odczytu: " << (!line.empty() ? "TAK" : "NIE") << endl;
    cout << "  Pozycja po otwarciu: " << f.tellg() << endl;
    f.seekg(0);
    cout << "  Mozliwosc pozycjonowania: " << (!f.fail() ? "TAK" : "NIE")
         << endl;
  }
  cout << "\nTest 2: ios::in (plik NIE istnieje)" << endl;
  {
    fstream f("nie_istnieje.txt", ios::in);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    cout << "  good(): " << (f.good() ? "TAK" : "NIE") << endl;
    cout << "  fail(): " << (f.fail() ? "TAK" : "NIE") << endl;
  }

  cout << "\nTest 3: ios::out (plik istnieje)" << endl;
  {
    fstream f("test_flags.txt", ios::out);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    cout << "  good(): " << (f.good() ? "TAK" : "NIE") << endl;
    cout << "  Pozycja po otwarciu: " << f.tellp() << endl;
    f << "Nowa zawartosc";
    cout << "  Mozliwosc zapisu: " << (!f.fail() ? "TAK" : "NIE") << endl;
    f.seekp(0);
    cout << "  Mozliwosc pozycjonowania: " << (!f.fail() ? "TAK" : "NIE")
         << endl;
  }

  cout << "\nTest 4: ios::out (plik NIE istnieje - tworzy nowy)" << endl;
  {
    fstream f("nowy_plik.txt", ios::out);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    cout << "  good(): " << (f.good() ? "TAK" : "NIE") << endl;
    f << "Test";
    cout << "  Mozliwosc zapisu: " << (!f.fail() ? "TAK" : "NIE") << endl;
  }

  cout << "\nTest 5: ios::app (dopisywanie na koncu)" << endl;
  {
    ofstream tmp("test_app.txt");
    tmp << "Pierwsza" << endl;
    tmp.close();

    fstream f("test_app.txt", ios::app);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    cout << "  Pozycja po otwarciu: " << f.tellp() << endl;
    f << "Dopisana" << endl;
    cout << "  Mozliwosc zapisu: " << (!f.fail() ? "TAK" : "NIE") << endl;
    f.seekp(0);
    cout << "  Pozycja po seekp(0): " << f.tellp() << " (app ignoruje seek)"
         << endl;
  }

  cout << "\nTest 6: ios::ate (at end - pozycja na koncu po otwarciu)" << endl;
  {
    ofstream tmp("test_ate.txt");
    tmp << "Linia1" << endl;
    tmp << "Linia2" << endl;
    tmp.close();

    fstream f("test_ate.txt", ios::in | ios::ate);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    cout << "  Pozycja po otwarciu: " << f.tellg() << endl;
    f.seekg(0);
    cout << "  Pozycja po seekg(0): " << f.tellg() << endl;
  }

  cout << "\nTest 7: ios::in | ios::out (odczyt i zapis)" << endl;
  {
    ofstream tmp("test_inout.txt");
    tmp << "Dane testowe" << endl;
    tmp.close();

    fstream f("test_inout.txt", ios::in | ios::out);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    string line;
    getline(f, line);
    cout << "  Mozliwosc odczytu: " << (!line.empty() ? "TAK" : "NIE") << endl;
    f.seekp(0);
    f << "Zmienione";
    cout << "  Mozliwosc zapisu: " << (!f.fail() ? "TAK" : "NIE") << endl;
  }

  cout << "\nTest 8: ios::in | ios::out | ios::trunc (czyszczenie pliku)"
       << endl;
  {
    ofstream tmp("test_trunc.txt");
    tmp << "Do usuniecia" << endl;
    tmp.close();

    fstream f("test_trunc.txt", ios::in | ios::out | ios::trunc);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    cout << "  Pozycja po otwarciu: " << f.tellg() << endl;
    string line;
    getline(f, line);
    cout << "  Zawartosc po trunc: '" << line << "' (pusty)" << endl;
  }

  cout << "\nTest 9: Sam ios::out (domyślnie trunc)" << endl;
  {
    fstream f("test_out_only.txt", ios::out);
    cout << "  is_open(): " << (f.is_open() ? "TAK" : "NIE") << endl;
    cout << "  Tworzy plik jesli nie istnieje: TAK" << endl;
    cout << "  Czysci plik jesli istnieje: TAK" << endl;
  }

  cout << "\n========================================" << endl;
  cout << "Podsumowanie flag:" << endl;
  cout << "  ios::in      - otwarcie do odczytu" << endl;
  cout << "  ios::out     - otwarcie do zapisu (czyści plik)" << endl;
  cout << "  ios::app     - dopisywanie na końcu (nie można zmieniać pozycji)"
       << endl;
  cout << "  ios::ate     - otwarcie z pozycją na końcu (można zmieniać)"
       << endl;
  cout << "  ios::trunc   - czyści zawartość pliku" << endl;
  cout << "  ios::binary  - tryb binarny (nie testowane tutaj)" << endl;
  cout << endl;
}

int main() {

  zapisIOdczyt();
  odwrotnaKolejnoscLiniiOdKonca();
  odwrocZnakiWLiniach();
  polaczPosortowanePliki();
  testFlagPliku();

  return 0;
}
