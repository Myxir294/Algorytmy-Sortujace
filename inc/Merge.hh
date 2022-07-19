#ifndef MERGE_HH
#define MERGE_HH
#include <cstdlib>
#include <iostream>
#include "sekwencja.hh"


/*Plik zawiera funkcje umozliwiajace realizacje algorytmu Merge Sort,
  tj. sortowania przez scalanie. W ponizszej implementacji dzialania
  wykonywane sa dla sekwencji powstalej z kolejki priorytetowej.
*/





/*!
 * Funkcja umozliwiajaca podzielenie sekwencji na pol
 * Argumenty:
 *      S1 - wskaznik na sekwencje do ktorej zostanie zapisana pierwsza polowa
 *      S2 - wskaznik dla drugiej polowy
 *      S  - wskaznik na sekwencje ktora zostanie podzielona 
 * Zwraca:
 *      Nic - efekt dzialania funkcji widoczny jest poprzez zapelnienie sekwencji S1 i S2   
 */
template<typename Typ_Danych>
void Podziel_Na_Pol(Sekwencja<Typ_Danych> *S1, Sekwencja<Typ_Danych> *S2, Sekwencja<Typ_Danych> *S)
{   
    if(S->Podaj_Rozmiar() < 2) //Przypadek braku fizycznej mozliwosci podzielenia na pol
    {   
        std::cerr << "Blad dzielenia sekwencji" << std::endl; //Zwrocenie wyjatku
        throw -1;
    }
    unsigned int rozmiar = S->Podaj_Rozmiar();
    Wezel<Typ_Danych>* pom;
    for(unsigned int i = 0; i<rozmiar; ++i)
    {   
        pom = S->Podaj_Wsk_Pierwszy();
        if (i < rozmiar/2) //Pierwsza polowa
        {
            S1->Dodaj_Na_Koniec(pom->Podaj_Wartosc(),pom->Podaj_Klucz());
        }
        else //Druga polowa
        {
            S2->Dodaj_Na_Koniec(pom->Podaj_Wartosc(),pom->Podaj_Klucz());

        }
        S->Usun_Pierwszy(); 
    }
    delete S; //Zwolnienie pamieci
    S = nullptr; 
}




/*!
 * Funkcja umozliwiajaca polaczenie dwoch sekwencji w sposob uporzadkowany
 * Argumenty:
 *      S1 - wskaznik na sekwencje pierwsza
 *      S2 - wskaznik na druga 
 * Zwraca:
 *      S - wskaznik na nowa sekwencje, powstala z S1 i S2 
 */
template<typename Typ_Danych>
Sekwencja<Typ_Danych>* Polacz(Sekwencja<Typ_Danych> *S1, Sekwencja<Typ_Danych> *S2)
{   
    Sekwencja<Typ_Danych>* S = new Sekwencja<Typ_Danych>; //Zapis do nowej sekwencji
    Komparator_Kolejka_Priorytetowa_Klucz<Typ_Danych> Porownaj;

    //Zapisywanie az kazda z sekwencji skladowych stanie sie pusta
    while(!S1->Czy_Pusta() && !S2->Czy_Pusta())
    {   
        //Zapisanie mniejszego z elementow
        if (Porownaj(S1->Podaj_Wsk_Pierwszy(),S2->Podaj_Wsk_Pierwszy()) <= 0)
        {
            S->Dodaj_Na_Koniec(S1->Podaj_Wartosc_Pierwszego(),S1->Podaj_Klucz_Pierwszy());
            S1->Usun_Pierwszy();
        }
        else 
        {
            S->Dodaj_Na_Koniec(S2->Podaj_Wartosc_Pierwszego(),S2->Podaj_Klucz_Pierwszy());
            S2->Usun_Pierwszy();
        }            
    }
    while (!S1->Czy_Pusta())
    {
        S->Dodaj_Na_Koniec(S1->Podaj_Wartosc_Pierwszego(),S1->Podaj_Klucz_Pierwszy());
        S1->Usun_Pierwszy();  
    }
    while (!S2->Czy_Pusta())
    { 
        S->Dodaj_Na_Koniec(S2->Podaj_Wartosc_Pierwszego(),S2->Podaj_Klucz_Pierwszy());
        S2->Usun_Pierwszy();
    }

    delete S1; //Zwolnienie pamieci - sekwencje skladowe sa juz puste
    delete S2;    
    S1 = nullptr;
    S2 = nullptr;
    return S; //Zwrocenie nowej, posortowanej sekwencji
}



/*!
 * Funkcja realizuje zasadnicza czesc algorytmu sortowania przez scalanie w sposob rekurencyjny
 * Argumenty:
 *      S - wskaznik na sortowana sekwencje
 * Zwraca:
 *      Przypadek a) S  - wskaznik na ta sama sekwencje dla struktur o rozmiarze 1
 *      Przypadek b) S3 - wskaznik na nowa sekwencje, stanowiaca posortowana wersje struktury
 *                        wejsciowej, jezeli zawierala ona wiecej niz 1 element 
 */
template<typename Typ_Danych>
Sekwencja<Typ_Danych>* Merge_Sort(Sekwencja<Typ_Danych> *S)
{
    if (S->Podaj_Rozmiar() > 1) //Przypadek wiecej niz jednego elementu
    {
        Sekwencja<Typ_Danych>* S1 = new Sekwencja<Typ_Danych>; 
        Sekwencja<Typ_Danych>* S2 = new Sekwencja<Typ_Danych>;
        Podziel_Na_Pol(S1,S2,S); //Podzial na podproblemy
        S1 = Merge_Sort(S1); //Wywolanie rekurencyjne dla lewego podproblemu
        S2 = Merge_Sort(S2); //Wywolanie rekurencyjne dla prawego podproblemu
        Sekwencja<Typ_Danych>* S3 = Polacz(S1,S2); //Laczenie sekwencji w sposob uporzadkowany
        return S3;        
    }
    return S;
}
#endif
