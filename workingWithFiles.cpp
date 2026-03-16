#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// FUNKCJA 1: Zapis do pliku i odczyt z wyświetleniem
// ============================================================================
void zapisIOdczyt() {
    cout << "=== FUNKCJA 1: Zapis i odczyt pliku ===" << endl;
    
    ofstream out("plik1.txt");
    if (!out.is_open()) {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return;
    }
    
    out << "To jest pierwszy wiersz tekstu." << endl;
    out << "Drugi wiersz ma   wiele   spacji." << endl;
    out << "Trzeci wiersz z liczbami: 123 456 789" << endl;
    out << endl;
    out << "Pusty wiersz powyzej, a teraz koniec." << endl;
    out.close();
    
    cout << "Zapisano dane do pliku plik1.txt" << endl << endl;
    
    ifstream in("plik1.txt");
    if (!in.is_open()) {
        cout << "Blad otwarcia pliku do odczytu!" << endl;
        return;
    }
    
    cout << "Odczytana zawartosc pliku:" << endl;
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
    cout << endl;
}

// ============================================================================
// FUNKCJA 2: Odwrócenie kolejności linii w pliku (wersja z wektorem)
// ============================================================================
void odwrotnaKolejnoscLinii() {
    cout << "=== FUNKCJA 2: Odwrotna kolejnosc linii ===" << endl;
    
    ofstream source("plik_zrodlowy.txt");
    source << "Linia pierwsza" << endl;
    source << "Linia druga" << endl;
    source << "Linia trzecia" << endl;
    source << "Linia czwarta" << endl;
    source << "Linia piata" << endl;
    source.close();
    
    vector<string> lines;
    ifstream in("plik_zrodlowy.txt");
    string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();
    
    ofstream out("plik_odwrotny.txt");
    for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
        out << *it << endl;
    }
    out.close();
    
    cout << "Odwrocona kolejnosc linii zapisana do plik_odwrotny.txt" << endl;
    cout << "Zawartosc:" << endl;
    
    ifstream result("plik_odwrotny.txt");
    while (getline(result, line)) {
        cout << line << endl;
    }
    cout << endl;
}

// ============================================================================
// FUNKCJA 2B: Odwrócenie kolejności linii - odczyt od końca pliku
// ============================================================================
// Ta wersja nie ładuje całego pliku do pamięci.
// Przechodzi do końca pliku, a następnie czyta linia po linii od końca.
// Działa dla dużych plików (np. 100 GB) - przechowuje tylko jedną linię w pamięci.
void odwrotnaKolejnoscLiniiOdKonca() {
    cout << "=== FUNKCJA 2B: Odwrotna kolejnosc linii (od konca pliku) ===" << endl;

    ofstream source("plik_zrodlowy2.txt");
    source << "Linia pierwsza" << endl;
    source << "Linia druga" << endl;
    source << "Linia trzecia" << endl;
    source << "Linia czwarta" << endl;
    source << "Linia piata" << endl;
    source.close();

    ifstream in("plik_zrodlowy2.txt", ios::binary);
    ofstream out("plik_odwrotny2.txt", ios::binary);

    if (!in.is_open()) {
        cout << "Blad otwarcia pliku zrodlowego!" << endl;
        return;
    }

    in.seekg(0, ios::end);
    streamoff fileSize = static_cast<streamoff>(in.tellg());

    if (fileSize == 0) {
        cout << "Plik jest pusty." << endl;
        return;
    }

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

    cout << "Odwrocona kolejnosc linii zapisana do plik_odwrotny2.txt" << endl;
    cout << "Zawartosc:" << endl;

    ifstream result("plik_odwrotny2.txt");
    while (getline(result, line)) {
        cout << line << endl;
    }
    cout << endl;
}

// ============================================================================
// FUNKCJA 3: Odwrócenie kolejności znaków w każdej linii
// ============================================================================
// Ta wersja przetwarza linia po linii - działa dla dużych plików.
void odwrocZnakiWLiniach() {
    cout << "=== FUNKCJA 3: Odwrocenie znakow w kazdej linii ===" << endl;
    
    ofstream source("plik_do_odwrocenia.txt");
    source << "ABC" << endl;
    source << "12345" << endl;
    source << "Hello World" << endl;
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
    
    cout << "Odwocone znaki zapisane do plik_odwrocone_znaki.txt" << endl;
    cout << "Zawartosc:" << endl;
    
    ifstream result("plik_odwrocone_znaki.txt");
    while (getline(result, line)) {
        cout << line << endl;
    }
    cout << endl;
}

// ============================================================================
// FUNKCJA 4: Rozdzielenie pliku na dwa pliki seriami
// ============================================================================
// Seria to ciąg kolejnych liczb rosnących lub malejących.
// Wersja strumieniowa - działa dla dużych plików.
void rozdzielNaDwaPlikiSeriami() {
    cout << "=== FUNKCJA 4: Rozdzielenie pliku na dwa pliki seriami ===" << endl;
    
    ofstream source("liczby.txt");
    source << "1 2 3 5 4 3 2 6 7 8 7 6 5 9 10" << endl;
    source.close();
    
    ifstream in("liczby.txt");
    ofstream outRosnace("serie_rosnace.txt");
    ofstream outMalejace("serie_malejace.txt");
    
    int prev, curr;
    if (!(in >> prev)) {
        cout << "Brak liczb w pliku!" << endl;
        return;
    }
    
    vector<int> currentSeries;
    currentSeries.push_back(prev);
    bool isAscending = true;
    bool directionSet = false;
    
    while (in >> curr) {
        bool continueAscending = isAscending && curr >= prev;
        bool continueDescending = !isAscending && curr <= prev;
        
        if (!directionSet) {
            if (curr > prev) {
                isAscending = true;
                directionSet = true;
            } else if (curr < prev) {
                isAscending = false;
                directionSet = true;
            }
        }
        
        if (directionSet && (continueAscending || continueDescending)) {
            currentSeries.push_back(curr);
            if (curr > prev) isAscending = true;
            else if (curr < prev) isAscending = false;
        } else {
            if (isAscending) {
                for (int n : currentSeries) outRosnace << n << " ";
                outRosnace << endl;
            } else {
                for (int n : currentSeries) outMalejace << n << " ";
                outMalejace << endl;
            }
            currentSeries.clear();
            currentSeries.push_back(curr);
            directionSet = false;
        }
        prev = curr;
    }
    
    if (isAscending) {
        for (int n : currentSeries) outRosnace << n << " ";
        outRosnace << endl;
    } else {
        for (int n : currentSeries) outMalejace << n << " ";
        outMalejace << endl;
    }
    
    in.close();
    outRosnace.close();
    outMalejace.close();
    
    cout << "Serie rosnace w pliku: serie_rosnace.txt" << endl;
    cout << "Serie malejace w pliku: serie_malejace.txt" << endl;
    cout << endl;
}

// ============================================================================
// FUNKCJA 5: Połączenie dwóch posortowanych plików w jeden
// ============================================================================
// Wersja strumieniowa - nie ładuje całych plików do pamięci.
// Działa dla plików dowolnego rozmiaru.
void polaczPosortowanePliki() {
    cout << "=== FUNKCJA 5: Polaczenie dwoch posortowanych plikow ===" << endl;
    
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
    bool hasVal1 = static_cast<bool>(in1 >> val1);
    bool hasVal2 = static_cast<bool>(in2 >> val2);

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
    
    cout << "Polaczone pliki w pliku: polaczone_posortowane.txt" << endl;
    cout << "Zawartosc: ";
    
    ifstream result("polaczone_posortowane.txt");
    string line;
    getline(result, line);
    cout << line << endl;
    cout << endl;
}

// ============================================================================
// FUNKCJA 6: Połączenie dwóch plików - naprzemienne serie
// ============================================================================
// Wersja strumieniowa - przetwarza linia po linii.
void polaczPlikiNaprzemiennieSerie() {
    cout << "=== FUNKCJA 6: Polaczenie plikow naprzemiennymi seriami ===" << endl;
    
    ofstream out1("plik_a.txt");
    out1 << "AAA" << endl;
    out1 << "BBB" << endl;
    out1 << "CCC" << endl;
    out1.close();
    
    ofstream out2("plik_b.txt");
    out2 << "111" << endl;
    out2 << "222" << endl;
    out2 << "333" << endl;
    out2.close();
    
    ifstream in1("plik_a.txt");
    ifstream in2("plik_b.txt");
    ofstream out("polaczone_naprzemiennie.txt");
    
    string line1, line2;
    bool hasLine1 = (bool)getline(in1, line1);
    bool hasLine2 = (bool)getline(in2, line2);
    
    bool fromFirst = true;
    
    while (hasLine1 || hasLine2) {
        if (fromFirst && hasLine1) {
            out << line1 << endl;
            hasLine1 = (bool)getline(in1, line1);
        } else if (!fromFirst && hasLine2) {
            out << line2 << endl;
            hasLine2 = (bool)getline(in2, line2);
        } else if (hasLine1) {
            out << line1 << endl;
            hasLine1 = (bool)getline(in1, line1);
        } else if (hasLine2) {
            out << line2 << endl;
            hasLine2 = (bool)getline(in2, line2);
        }
        fromFirst = !fromFirst;
    }
    
    in1.close();
    in2.close();
    out.close();
    
    cout << "Polaczone naprzemiennie w pliku: polaczone_naprzemiennie.txt" << endl;
    cout << "Zawartosc:" << endl;
    
    ifstream result("polaczone_naprzemiennie.txt");
    while (getline(result, line1)) {
        cout << line1 << endl;
    }
    cout << endl;
}

// ============================================================================
// FUNKCJA 7: Testowanie flag otwarcia pliku
// ============================================================================
void testFlagPliku() {
    cout << "=== FUNKCJA 7: Testowanie flag otwarcia pliku ===" << endl;
    
    ofstream out("test_flags.txt");
    out << "Pierwsza linia" << endl;
    out << "Druga linia" << endl;
    out << "Trzecia linia" << endl;
    out.close();
    
    cout << "Utworzono plik testowy z 3 liniami." << endl;
    cout << "========================================" << endl;
    
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
        cout << "  Mozliwosc pozycjonowania: " << (!f.fail() ? "TAK" : "NIE") << endl;
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
        cout << "  Mozliwosc pozycjonowania: " << (!f.fail() ? "TAK" : "NIE") << endl;
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
        cout << "  Pozycja po seekp(0): " << f.tellp() << " (app ignoruje seek)" << endl;
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
    
    cout << "\nTest 8: ios::in | ios::out | ios::trunc (czyszczenie pliku)" << endl;
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
    cout << "  ios::app     - dopisywanie na końcu (nie można zmieniać pozycji)" << endl;
    cout << "  ios::ate     - otwarcie z pozycją na końcu (można zmieniać)" << endl;
    cout << "  ios::trunc   - czyści zawartość pliku" << endl;
    cout << "  ios::binary  - tryb binarny (nie testowane tutaj)" << endl;
    cout << endl;
}

// ============================================================================
// FUNKCJA GŁÓWNA
// ============================================================================
int main() {
    cout << "============================================" << endl;
    cout << "Program demonstracyjny operacji na plikach" << endl;
    cout << "============================================" << endl;
    cout << endl;
    
    zapisIOdczyt();
    odwrotnaKolejnoscLinii();
    odwrotnaKolejnoscLiniiOdKonca();
    odwrocZnakiWLiniach();
    rozdzielNaDwaPlikiSeriami();
    polaczPosortowanePliki();
    polaczPlikiNaprzemiennieSerie();
    testFlagPliku();
    
    cout << "Wszystkie operacje zakonczone!" << endl;
    
    return 0;
}
