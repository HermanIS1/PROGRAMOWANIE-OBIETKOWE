# Laboratorium C++

## Zad 1: Klasa Wielomian
 - [x] analiza składni (napis -> wielomian)
 - [ ] klasa Wielomian
   - [ ] analiza składni jako konstruktor
   - [ ] pozostałe konstruktory
   - [ ] metoda Pokaz() 
 - [ ] operatory += (metoda klasy) i +
 - [ ] pozostałe operatory arytmetyczne: -= - *= * /= / %= % (różne konteksty: wielomiany i liczby)
 - [ ] dodatkowe operatory: () [] << >> 
 - [ ] podział na pliki Wielomian.h, Wielomian.cpp, testy.cpp

## Zad 2: Dziedziczenie wielomianów
- [ ] A. Klasa Jednomian jako potomna klasy Wielomian
  - konstruktor
  - wykorzystanie Jednomianu w dzieleniu 

- [ ] B. Klasa abstrakcyjna BazaWielomianu i klasy potomne Jednomian i Wielomian
  - optymalne wykorzystanie pamięci - Jednomian ma jeden współczynnik, Wielomian, jak wcześniej, cała tablicę
  - co wspólne do klasy BazaWielomianu (stopień, operatory, którym wystarczy operator [] i stopień)
  - czysto wirtualny operator [] w Bazie, nadpisany w Jednomianie i Wielomianie
  - operatory arytmetyczne: 
    - parametry wejściowe - BazaWielomianu wszędzie tam, gdzie może wystąpić Jednomian lub Wielomian
    - na wyjściu 
      - Jednomian tylko tam, gdzie jest pewność, że wynikiem jest jednomian,
      - Wielomian w przeciwnym przypadku.
    - Przykłady:
      - `Wielomian operator+(const BazaWielomianu &, const BazaWielomianu &);`
      - `Wielomian Wielomian::operator+=(const BazaWielomianu &);`

## Zad 3: [A Vexing Problem (problem I z konkursu ACM z 2001 roku)](https://is.umk.pl/~kg/zajecia/ACM/2001.pdf#page=17)

Klasy
 - Plansza,
 - Ruch, 
 - Bloczek/Klocek?, Sekwencja ruchów?, Stan w procesie szukania? (to samo co Plansza?)

Algorytmy rozwiązujące zadanie - zaimplementowane ogólnie + zastosowanie do tego problemu
 - [ ] szukanie **w głąb** do odpowiedniej głębokości (11); zapamiętane najlepsze rozwiązanie i podmiana, gdy znalezione lepsze
 - [ ] szukanie **wszerz** - pierwsze znalezione rozwiązanie jest minimalne; problem złożoności pamięci 

Programy
 - [ ] rozwiązujący zadanie (w konsoli)
 - [ ] gra z wizualizacją

## Zad 4: Szablony

Funkcji
- `Suma()` - suma n wartości z tablicy
    - jako zwykła funkcja
    - jako szablon dla tablic
    - jako szablon dla tablic i vectorów 
- `IleSpelnia()` - ile podzielnych przez 3, ile mniejszych od 0, ...
    - szablon dla tablic
    - dla tablic i wektorów
    - dla funkcji i funktorów 
- [ ] klasa Ulamek, wyposażona we wszystko co potrzebne dla ww szablonów, tzn. z możliwością liczenia sum i spełnionych warunków
- [ ] Projekcja/Obrazy (map) - funkcja generująca tablicę obrazów obiektów z innej tablicy uzyskanych danym przekształceniem
    - [ ] przykłady wykorzystania: kwadraty liczb, odwrotności ułamków, ... 

Klas
- Kopiec
   - [ ] dodawanie do kopca
   - [ ] usuwanie elementu maksymalnego (z korzenia)
   - [ ] wgląd w element maksymalny
   - [ ] pobranie wszystkich elementów np. do zewnętrznej tablicy 
- kMin - funkcjonalność wyboru k minimalnych elementów
   - [ ] wykorzystanie kopca - trzymamy w kopcu k elementów - kolejne dodajemy i usuwamy maksymalny, jeśli za dużo)
   - [ ] analiza kolejnego elementu - dodanie do kopca i usunięcie maksymalnego gdy za dużo
   - [ ] pobranie minimalnych elementów na koniec (te pozostałe w kopcu) 


