# Algorytmy-Sortujace
Rezpozytorium zawiera implementacje algorytmów QuickSort, BucketSort i MergeSort z wykorzystaniem klasy modelującej sekwencję danych.

Główny program umożliwia wybór algorytmu poprzez argument wywołania (q - szybkie, s - sortowanie przez scalanie, k - sortowanie kubełkowe) oraz ilości danych do posortowania (podanie wartości innej niż liczba naturalna, np. -1 spowoduje posortowanie wszystkich danych). Algorytmy operują na bazie filmów zawierającej niecałe milion wpisów, sortując je rosnąco na podstawie oceny oraz filtrując niepoprawne wpisy.

Zrealizowano również program pomocniczy umożliwiający przetestowanie napisanych algorytmów na niewielkiej ilości losowo wygenerowanych danych.

Kompilacja programu głównego: g++ -pedantic -Wall main.cpp rand.cpp
Kompilacja programu pomocniczego: g++ -pedantic -Wall driver.cpp rand.cpp


