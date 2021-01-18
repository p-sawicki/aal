Projekt z przedmiotu Analiza Algorytmów na Politechnice Warszawskiej

1. Autorzy
Rozwiązanie zostało opracowane przez duet:
	- Piotr Sawicki,	300265
	- Paweł Wieczorek, 	300283

2. Budowa projektu
Opis struktury katalogów:
.
├── bf			- implementacja rozwiązania brute-force
│   ├── bf.cpp		- kod funkcji rozwiązującej problem
│   └── bf_main.cpp	- wrapper potrzebny do zbudowania algorytmu jako osobnej aplikacji
├── bin			- katalog z gotowymi programami
├── docs		- elementy składowe dokumentacji (wykresy, dane, itd.)
├── dp			- implementacja rozwiązania metodą programowania dynamicznego
│   ├── dp.cpp		- kod funkcji rozwiązującej problem metodą programowania dynamicznego
│   └── dp_main.cpp
├── gen			- kod generatora przypadków testowych
│   ├── gen.cpp		- kod funkcji generującej przypadki testowe
│   └── gen_main.cpp
├── graph		- implementacja rozwiązania metodą grafową
│   ├── graph.cpp	- kod funkcji rozwiązującej problem metodą grafową
│   └── graph_main.cpp
├── inc			- pliki nagłówkowe
│   ├── bf.h
│   ├── brick.h		- definicja kostki używanej przez wszystkie algorytmy
│   ├── dp.h
│   ├── gen.h
│   ├── graph.h
│   └── utils.h
├── Makefile
├── README.md
├── tests.cpp		- implementacja testów jednostkowych 
├── timer.cpp		- aplikacja do benchmarkowania algorytmów
└── utils		- kody pomocnicze
    └── utils.cpp

3. Budowanie
W głównym katalogu wywołać komendę:
	make -j 16
po krótkiej chwili zbudowane aplikacje powinny znajdować się w podkatalogu bin/

4. Obsługa
W katalogu bin/ dostępne są następujące programy:
	a) ./dp < input > output - aplikacja rozwiązująca problem z użyciem metody programowania dynamicznego
	b) ./graph < input > output - aplikacja rozwiązująca problem z użyciem podejścia grafowego
	c) ./bf < input > output - aplikacja rozwiązująca problem z użyciem algorytmu brute-force
	d) ./gen [--amount N] [--min R] [--max R] > output - generator przypadków testowych; na wyjściu wypisanych zostanie "amount" klocków o wymiarach w przedziale <min; max>
	e) ./tests - aplikacja sprawdzająca kilka testowych przypadków
	f) ./timer [--algorithm [dp|graph|bf]] [--repeat N] [--min N] [--max N] [--step N] - narzędzie do benchmarkowania wybranego algorytmu; każdy test jest wykonywane "repeat" razy, począwszy od "min" klocków, co "step", aż do "max" klocków

W powyższych opcjach N oznacza liczby całkowite, a R rzeczywiste.

5. Format danych wejściowych i wyjściowych
Dane wejściowe do aplikacji mają format: "wysokość szerokość głębokość"; klocki są podawane w kolejnych liniach. Przykład:
	1 2 3
	3 4 5
	5 6 7

Na wyjściu algorytm zwraca wysokość najlepszej wieży oraz wymiary klocków wchodzących w jej skład:
	Tower depth: 287.284
	Bricks
	Width                   Height                  Depth
	10.7883                 31.3908                 55.9061
	21.2196                 53.049                  94.3735
	31.3908                 55.9061                 10.7883
	49.0737                 58.4328                 77.1428
	58.4328                 77.1428                 49.0737
	Time (seconds): 4.3214e-05

Ponadto, aplikacja "timer" zwraca informacje o czasie działania programu dla kolejnych testów:
	N,Average time (seconds)
	1000,0.0100203
	1010,0.00977529
	1020,0.00994956
	1030,0.0101443
	n,t(n),q(n)
	1000,0.0100203,1.0478
	1010,0.00977529,1.00204
	1020,0.00994956,1
	1030,0.0101443,0.999868