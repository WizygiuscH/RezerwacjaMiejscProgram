# System rezerwacji miejsc

Program konsolowy w C++ do rezerwowania miejsc w **autobusie**, **kinie** i na **stadionie**.
Wykorzystuje klasy, enkapsulację, dziedziczenie, polimorfizm, wyjątki i przeciążanie operatorów.

## Funkcjonalności

- wybór typu miejsca (autobus, kino, stadion) i powrót do tego wyboru (`0`)
- plan miejsc: `[o]` wolne, `[x]` zajęte
- rezerwacja (imię klienta + rodzaj biletu), anulowanie, lista rezerwacji z łączną wartością
- wyszukiwanie rezerwacji po numerze i zmiana jej danych
- `4a` i `a4` to to samo miejsce, a zły wpis od razu daje błąd i prosi o poprawkę
- na stadionie najpierw wybór sektora, potem miejsca
- rezerwacje każdego obiektu są pamiętane do końca działania programu

## Obiekty i ceny

| | Autobus | Kino | Stadion |
|---|---|---|---|
| Miejsca | 28 (7 rzędów po 4, A-D) | 150 (15 rzędów A-O po 10) | 400 (5 sektorów) |
| Oznaczenie | `4C` | `C8` | `N-C7` (sektor, rząd, miejsce) |
| Bilety | normalny, ulgowy | normalny, ulgowy, dla dzieci, dla seniorów | normalny, ulgowy, dla dzieci |
| Cena bazowa | 12 zł | 28 zł | N 70 zł, W i E 90 zł, S 60 zł, G 50 zł |
| Ulgi | ulgowy -50% | ulgowy -20%, dzieci -40%, seniorzy -30% | ulgowy -30%, dzieci -50% |

Sektory stadionu: `N` Północna (100 miejsc), `W` Zachodnia (100), `E` Wschodnia (100),
`S` Południowa (50), `G` Sektor Gości (50).

## Struktura projektu

```
include/   pliki nagłówkowe (.h)
src/       pliki implementacji (.cpp) i main.cpp
docs/      schemat UML (uml.png)
.vscode/   tasks.json (budowanie w VS Code)
```

## Architektura

![Schemat klas UML](docs/uml.png)

Wypełnione romby to **kompozycja** (`SystemRezerwacji` jest właścicielem obiektu i rezerwacji,
`Obiekt` właścicielem miejsc), puste trójkąty to **dziedziczenie**, a przerywana strzałka to
zależność (system rzuca wyjątek). Agregacji nie ma. Operatory `==` i `<<` to funkcje nieskładowe.

| Klasa | Zadanie |
|---|---|
| `Miejsce` | Oznaczenie miejsca i informacja, czy jest zajęte. |
| `Rezerwacja` | Numer, imię klienta, miejsce, rodzaj biletu i cena. |
| `Obiekt` | Klasa abstrakcyjna: wspólna baza autobusu, kina i stadionu. |
| `Autobus`, `Kino`, `Stadion` | Własny układ miejsc, wygląd planu, ceny i rodzaje biletów. |
| `SystemRezerwacji` | Rezerwowanie, anulowanie, wyszukiwanie i zmiana rezerwacji. |
| `BladRezerwacji` | Własny wyjątek (dziedziczy po `std::exception`). |

**Zastosowane mechanizmy**

- **Enkapsulacja:** pola `private` (w `Obiekt` `protected`), dostęp przez gettery i settery.
- **Polimorfizm:** `SystemRezerwacji` trzyma `Obiekt*` i wywołuje metody wirtualne
  (`wyswietlMiejsca`, `getCena`, `przygotujOznaczenie`, `getPrzykladMiejsca`), więc działa tak samo
  dla autobusu, kina i stadionu. Klasy pochodne przesłaniają je z `override`.
- **`const`:** gettery oraz metody wyświetlające i wyszukujące.
- **Operatory:** `<<` dla `Miejsce` (`[o]`/`[x]`) i `Rezerwacja` (rezerwacja w jednej linijce),
  `==` dla `Miejsce` (używany w wyszukiwaniu miejsca).
- **Wyjątki:** `SystemRezerwacji` rzuca `BladRezerwacji` (miejsce zajęte lub nieistniejące, zły
  format, brak rezerwacji, zły bilet), a `main.cpp` je łapie i pokazuje komunikat.

## Kompilacja i uruchomienie

Potrzebny jest `g++` z obsługą C++11 lub nowszego.

**VS Code:** otwórz folder projektu, naciśnij **Ctrl+Shift+B** i uruchom program w terminalu.

**Linux / macOS:**
```
g++ -Iinclude src/*.cpp -o rezerwacje
./rezerwacje
```

**Windows (PowerShell):**
```
g++ -Iinclude src/main.cpp src/Miejsce.cpp src/Rezerwacja.cpp src/Obiekt.cpp src/Autobus.cpp src/Kino.cpp src/Stadion.cpp src/SystemRezerwacji.cpp src/BladRezerwacji.cpp -o rezerwacje
.\rezerwacje.exe
```

## Obsługa

Na starcie wybierasz typ miejsca (`0` kończy program), a potem pojawia się menu (`0` wraca do wyboru):

```
 -+- SYSTEM REZERWACJI (Autobus) -+-
Wolnych miejsc: 28 z 28
1. Pokaz miejsca
2. Zarezerwuj miejsce
3. Anuluj rezerwacje
4. Pokaz rezerwacje
5. Szukaj rezerwacji po numerze
6. Zmien dane rezerwacji
0. Wroc do wyboru miejsca
```

Przy wpisywaniu miejsca `0` wraca do menu. Wielkość liter, spacje i kolejność nie mają znaczenia.

## Przykłady działania

**Autobus: zły wpis, `a4` jako `4A`, miejsce zajęte**
```
Twoj wybor: 2
[... plan miejsc ...]

Podaj miejsce, np. 4C (0 = wroc do menu): 9z
BLAD: takie miejsce nie istnieje, sprobuj jeszcze raz.

Podaj miejsce, np. 4C (0 = wroc do menu): a4
Podaj imie klienta: Jan Kowalski

Wybierz rodzaj biletu:
1. Bilet normalny - 12.00 zl
2. Bilet ulgowy - 6.00 zl
Twoj wybor: 2

Zarezerwowano!
Rezerwacja nr 1 | Klient: Jan Kowalski | Miejsce: 4A | Bilet ulgowy | 6.00 zl

Podaj miejsce, np. 4C (0 = wroc do menu): 4A
BLAD: miejsce 4A jest juz zajete, sprobuj jeszcze raz.
```

**Stadion: najpierw sektor, potem miejsce (cena zależy od sektora)**
```
Wybierz sektor:
1. TRYBUNA POLNOCNA (N) - 100 miejsc
2. TRYBUNA ZACHODNIA (W) - 100 miejsc
3. TRYBUNA WSCHODNIA (E) - 100 miejsc
4. TRYBUNA POLUDNIOWA (S) - 50 miejsc
5. SEKTOR GOSCI (G) - 50 miejsc
0. Wroc do menu
Twoj wybor: 4
[... plan sektora S ...]

Podaj miejsce, np. C7 (0 = wroc do menu): 3c
Podaj imie klienta: Ola
[... wybor biletu: ulgowy ...]

Zarezerwowano!
Rezerwacja nr 1 | Klient: Ola | Miejsce: S-C3 | Bilet ulgowy | 42.00 zl
```

**Kino: zmiana danych rezerwacji i błąd**
```
Obecne dane:
Rezerwacja nr 1 | Klient: Anna | Miejsce: C8 | Bilet dla seniorow | 19.60 zl
[... nowe imie i bilet ...]
Dane rezerwacji zostaly zmienione:
Rezerwacja nr 1 | Klient: Anna Nowak | Miejsce: C8 | Bilet ulgowy | 22.40 zl

Podaj numer rezerwacji.
Twoj wybor: 99
BLAD: nie ma rezerwacji o numerze 99
```