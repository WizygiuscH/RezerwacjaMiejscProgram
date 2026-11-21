# System rezerwacji miejsc

Program konsolowy w C++ do rezerwowania miejsc w autobusie, kinie i na stadionie.

> README bedzie rozbudowane na koncu projektu (architektura, przyklady dzialania).

## Aktualny stan
- na starcie wybor typu miejsca: autobus, kino albo stadion (0 w menu obiektu wraca do wyboru, 0 w wyborze konczy program)
- na stadionie najpierw wybor sektora, potem miejsca w sektorze
- zle miejsce od razu daje blad i prosi o poprawke; "4a" i "a4" to to samo miejsce
- wyswietlanie planu miejsc: `[o]` wolne, `[x]` zajete
- rezerwowanie miejsca (imie klienta + rodzaj biletu)
- anulowanie rezerwacji, lista rezerwacji
- wyszukiwanie rezerwacji po numerze i zmiana jej danych
- ceny biletow (kazdy obiekt liczy je po swojemu, na stadionie zaleza od sektora)
- obsluga bledow przez wyjatki (np. miejsce zajete, brak rezerwacji o takim numerze)
- przeciazone operatory: `<<` (miejsce, rezerwacja) i `==` (miejsce)

## Menu
```
1. Pokaz miejsca
2. Zarezerwuj miejsce
3. Anuluj rezerwacje
4. Pokaz rezerwacje
5. Szukaj rezerwacji po numerze
6. Zmien dane rezerwacji
0. Wroc do wyboru miejsca
```

## Struktura
- `include/` - pliki naglowkowe (.h)
- `src/` - pliki implementacji (.cpp) oraz `main.cpp`

## Kompilacja i uruchomienie
```
g++ -Iinclude src/*.cpp -o rezerwacje
./rezerwacje        (Windows: rezerwacje.exe)
```
