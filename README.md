# Systemy operacyjne 2 - Projekt

## Problem jedzących filozofów
Problem ucztujących filozofów (znany też jako problem pięciu filozofów) – przykład klasycznego dla informatyki zadania synchronizacji procesów.
Jest to teoretyczne wyjaśnienie zakleszczenia i uniemożliwienia innym jednostkom korzystania z zasobów poprzez założenie, że każdy z filozofów bierze po jednym widelcu, a dopiero potem próbuje zdobyć drugi.

Problem ucztujących filozofów jest prezentacją problemu synchronizacji pracujących współbieżnie procesów. Istnieje kilka możliwych rozwiązań tego problemu, między innymi wykorzystujące arbitrów lub grupy semaforów.

_Źródło: [wikipedia.org](https://pl.wikipedia.org/wiki/Problem_ucztuj%C4%85cych_filozof%C3%B3w)_
## Opis przyjętego rozwiązania

Proste rozwiązanie jest osiągalne poprzez częściowe uporządkowanie lub ustalenie hierarchii dla zasobów (w tym wypadku widelców) i wprowadzenie zasady, że kolejność dostępu do zasobów jest ustalona przez ów porządek, a ich zwalnianie następuje w odwrotnej kolejności, oraz że dwa zasoby niepowiązane relacją porządku nie mogą zostać użyte przez jedną jednostkę w tym samym czasie.

W tym przykładzie oznaczmy zasoby (widelce) numerami od 1 do 5 – w ustalonym porządku – oraz ustalmy, że jednostki (filozofowie) zawsze najpierw podnoszą widelec oznaczony niższym numerem, a dopiero potem ten oznaczony wyższym. Następnie, zwracając widelce, najpierw oddają widelec z wyższym numerem, a potem z niższym. W tym wypadku, jeśli czterech filozofów jednocześnie podniesie swoje widelce z niższymi numerami, na stole pozostanie widelec z najwyższym numerem, przez co piąty filozof nie będzie mógł podnieść żadnego. Ponadto tylko jeden filozof ma dostęp do widelca z najwyższym numerem, więc będzie on mógł jeść dwoma widelcami. Gdy skończy, najpierw odłoży widelec z najwyższym numerem, a następnie z niższym, umożliwiając kolejnemu filozofowi zabranie drugiego sztućca.

_Źródło: [wikipedia.org](https://pl.wikipedia.org/wiki/Problem_ucztuj%C4%85cych_filozof%C3%B3w)_

## Zrealizowane wymagania projektowe
* Program otrzymuje jako argument liczbę filozofów ✅
* Każdy z wątków raportuje o stanie w którym się znajduje ✅
* W programie nie dochodzi do trwałego zablokowania wątków ✅
* Repozytorium sprawdza kod przy każdym commicie (Github Actions) ✅
* Dodano automatyczną budowę projektu (Makefile) ✅
* Kod spełnia wymagania lintera (cpplint) ✅

## Opis programu
1. Wątki i ich reprezentacja

* W programie każdy filozof to osobny wątek. Wątki są tworzone w funkcji ```main()``` za pomocą ```pthread_create()```, gdzie każdy wątek wykonuje funkcję ```feast()```.
Każdy filozof ma swój unikalny identyfikator (id) oraz dwa widelce (lewy i prawy). Wątek cyklicznie przechodzi przez fazy rozmyślania i jedzenia.

* W funkcji ```main()``` jest nieskończona pętla, która co ```TIME_OF_AN_ACTION``` sekund wywołuje ```displayStatus()```, wypisując stan każdego filozofa.

* Po zakończeniu programu wątki są zamykane za pomocą ```pthread_join()```.

2. Sekcje krytyczne i ich rozwiązanie

* Sekcje krytyczne to fragmenty kodu, które dostępne są dla wielu wątków jednocześnie i mogą prowadzić do problemów z współbieżnym dostępem (widelce). W programie są one rozwiązane za pomocą mutexów (```pthread_mutex_t```).

* Każdy filozof musi podnieść dwa widelce przed jedzeniem. W funkcji ```pickUpTheForks()``` mutexy odpowiadające za widelce (```forks[leftForkId]``` i ```forks[rightForkId]```) są blokowane (```pthread_mutex_lock()```).
  Po skończeniu jedzenia, w funkcji ```putDownTheForks()```, mutexy są odblokowywane (```pthread_mutex_unlock()```).
* Jeśli każdy filozof podniesie jeden widelec i będzie czekał na drugi, system się zablokuje. Aby to rozwiązać zaimplementowano rozwiązanie przy użyciu hierarchii zasobów, co zapobiega takiej sytuacji. 




## Uruchamianie programu

```
$ ./SO2-Projekt [liczba filozofów przy stole]
```
Przykładowo:
```
$ ./SO2-Projekt 5
```
Z użyciem Makefile:
```
$ sudo apt install make
$ make
$ ./SO2-Projekt [liczba filozofów przy stole]
```
Usunięcie programu:
```
make clean
```

## Źródła:
* [Wikipedia.org](https://pl.wikipedia.org/wiki/Problem_ucztuj%C4%85cych_filozof%C3%B3w)
* [Short introduction to threads](https://www.youtube.com/watch?v=d9s_d28yJq0)
* [Biblioteka Pthreads](https://icis.pcz.pl/~olas/srr/wyklad2.4.pdf)
* [A Simple Makefile Tutorial](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)

