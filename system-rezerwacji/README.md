# System rezerwacji miejsc

Program konsolowy w C++ do rezerwowania miejsc w autobusie, kinie i na stadionie.

> README bedzie rozbudowane na koncu projektu (architektura, przyklady dzialania).

## Aktualny stan
- na starcie wybor typu miejsca: autobus, kino albo stadion
- wyswietlanie planu miejsc: `[o]` wolne, `[x]` zajete
- rezerwowanie miejsca (imie klienta + rodzaj biletu)
- anulowanie rezerwacji, lista rezerwacji
- wyszukiwanie rezerwacji po numerze i zmiana jej danych

## Menu
```
1. Pokaz miejsca
2. Zarezerwuj miejsce
3. Anuluj rezerwacje
4. Pokaz rezerwacje
5. Szukaj rezerwacji po numerze
6. Zmien dane rezerwacji
0. Wyjscie
```

## Struktura
- `include/` - pliki naglowkowe (.h)
- `src/` - pliki implementacji (.cpp) oraz `main.cpp`

## Kompilacja i uruchomienie
```
g++ -Iinclude src/*.cpp -o rezerwacje
./rezerwacje        (Windows: rezerwacje.exe)
```
