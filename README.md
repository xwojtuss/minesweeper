# minesweeper

Gra polega na odkryciu wszystkich pól nieposiadających bomb, jednocześnie unikając odkrycia pola posiadającego bombe. Numery na polach oznaczają ile bomb znajduje się wokół danego pola.

## Kompilacja i uruchamianie

1. Sklonuj repozytorium:
```
git clone https://github.com/xwojtuss/minesweeper.git
```

2. Przejdź do katalogu projektu:
```
cd minesweeper
```

3. Uruchom make aby skompilować projekt:
```
make
```

Po skompilowaniu programu należy wywołać program wpisując w terminal:
```
./minesweeper
```
lub:
```
./minesweeper -f [ścieżka_do_pliku]
```
gdzie ścieżka_do_pliku to plik, z którego zamierzamy pobierać komendy używane w programie i/lub mapę, plik ma wyglądać tak samo jak w przypadku wczytywania z terminala, więc oto przykład:
```
4
2 2
01
10
r 0 0
f 0 1
f 1 0
r 1 1
Karolina
```
A tak wygląda format pliku:
```
poziom_trudności(1-4)
ilość_wierszy ilość_kolumn
mapa
instrukcje
imię(opcjonalnie)
```
Można także wykonać komendę: make test, aby przeprowadzić testy. Mamy także reguły: clean – usuwanie plików .o, fclean – usuwanie skompilowanego programu i plików .o, re – ponowna całkowita kompilacja, nazwa_pliku.o – kompilacja pojedynczego pliku z zakończeniem kompilacji na procesie asemblacji.

## Rozgrywka

Grę prowadzi się poprzez wybranie poziomu trudności za pomocą wpisania liczby od 1 do 4, zgodnie z wyświetlonymi opcjami. Jeżeli wybierzemy 4 – program poprosi nas o wpisanie własnej mapy, przykładowa prawidłowa mapa 3x5 wygląda następująco:
```
10001
10110
01010
```
Następnie zaczynamy grę, gdzie możemy odkrywać pola za pomocą komendy “r x y”, lub stawiać/usuwać flagi za pomocą komendy “f x y”, gdzie “x” to numer wiersza a “y” to numer kolumny, liczone od lewego, górnego rogu, indeksując od 0. Po zakończonej grze otrzymujemy informację, czy gra zakończyła się sukcesem, ile prawidłowych ruchów wykonaliśmy oraz ile zdobyliśmy punktów. Jeżeli wygraliśmy – program prosi nas o imię, które później zostanie zapisane w wynikach (a dokładniej w pliku .leaderboard).

## Nasze rozwiązanie

Mapa złożona jest z komórek typu char, gdzie zapisujemy wszystkie potrzebne nam informacje:
```
najmniej znaczący bit mówi o tym czy jest tam bomba (1-jest, 0-nie ma),
drugi najmniej znaczący bit mówi o tym czy jest tam flaga (1-jest, 0-nie ma),
trzeci najmniej znaczący bit mówi czy pole jest odkryte (1-tak, 0-nie),
czwarty, piąty i szósty bit najmniej znaczący to informacja o tym ile jest bomb dookoła.
```

## Autorzy

* **Wojtek Kornatowski** - [xwojtuss](https://github.com/xwojtuss)
* **Szymon Karbowiak** - [Szymon-Karbowiak](https://github.com/Szymon-Karbowiak)
