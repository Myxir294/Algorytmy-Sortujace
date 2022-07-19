#include <ctime>
#include <iostream>

/*Plik zawiera funkcje umozliwiajace realizacje generatora liczb losowych*/


/* Funkcja przekazujaca generatorowi czas systemowy, konieczna do poprawnych losowan */
void Rand_Inicjalizuj();

/*!
 * Funkcja losuje nieujemna liczbe calkowita z zadanego przedzialu.
 * Argumenty:
 *    max - maksymalna wartosc wylosowanej liczby
 * Zwraca:
 *     Nieujemna liczbe calkowita
 */
int Rand_Losuj_Liczbe_Z_Przedzialu(const unsigned int max);