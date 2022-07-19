#ifndef QUICK_HH
#define QUICK_HH

#include "sekwencja.hh"
#include "rand.hh"

/*Plik zawiera funkcje umozliwiajace realizacje algorytmu Quick Sort,
  tj. sortowania szybkiego. W ponizszej implementacji dzialania
  wykonywane sa dla sekwencji powstalej z kolejki priorytetowej.
*/



/*!
 * Funkcja umozliwiajaca podzielenie sekwencji wedlug losowo dobranej pozycji pivota
 * Argumenty:
 *      L - wskaznik na sekwencje do ktorej zapisane zostana elementy mniejsze od pivota
 *      E - wskaznik na sekwencje do ktorej zaisane zostana elementy rowne pivotowi
 *      G - wskaznik na sekwencje do ktorej zapisane zostana elementy wieksze od pivota
 *      S  - wskaznik na sekwencje ktora zostanie podzielona 
 * Zwraca:
 *      Nic - efekt dzialania funkcji widoczny jest poprzez zapelnienie sekwencji L,E,G
 *            oraz oproznienie i usuniecie sekwencji S   
 */
template<typename Typ_Danych>
void Podziel(Sekwencja<Typ_Danych> *L, Sekwencja<Typ_Danych> *E, Sekwencja<Typ_Danych> *G, Sekwencja<Typ_Danych> *S)
{   
    if(S->Podaj_Rozmiar() < 2) //Przypadek braku fizycznej mozliwosci podzialu
    {   
        std::cerr << "Blad dzielenia sekwencji" << std::endl;
        throw -1;
    }
    
    Komparator_Kolejka_Priorytetowa_Klucz<Typ_Danych> Porownaj;
    unsigned int rozmiar = S->Podaj_Rozmiar();
    unsigned int pozycja_pivota = (unsigned int)Rand_Losuj_Liczbe_Z_Przedzialu(rozmiar-1); //Losowe wybranie pivota
    Wezel<Typ_Danych>* pivot = S->Wsk_Na_Element_O_Indeksie(pozycja_pivota);
    Wezel<Typ_Danych>* pom1 = new Wezel<Typ_Danych>;
    Wezel<Typ_Danych>* pom2;
    pom1->Ustaw_Klucz(pivot->Podaj_Klucz());
    pom1->Ustaw_Wartosc(S->Podaj_I_Usun_Element(pivot));

    while (!S->Czy_Pusta())
    {
        pom2 = S->Podaj_Wsk_Pierwszy(); //Porownywanie elementow z pivotem
        if (Porownaj(pom2,pom1) < 0) //Dodanie do sekwencji elementow mniejszych od pivota
        {
            L->Dodaj_Na_Koniec(pom2->Podaj_Wartosc(),pom2->Podaj_Klucz());
        }
        else if (Porownaj(pom2,pom1) == 0) //Dodanie do sekwencji elementow rownych pivotowi
        {
            E->Dodaj_Na_Koniec(pom2->Podaj_Wartosc(),pom2->Podaj_Klucz());
        }
        else //Dodanie do sekwencji elementow wiekszych od pivota
        {
            G->Dodaj_Na_Koniec(pom2->Podaj_Wartosc(),pom2->Podaj_Klucz());
        }
        S->Usun_Pierwszy(); //Usuniecie dodanego elementu z oryginalnej sekwencji
    }
    E->Dodaj_Na_Koniec(pom1->Podaj_Wartosc(),pom1->Podaj_Klucz()); //Dodanie pivota do sekwencji elementow rownych pivotowi
    delete S; //Zwolnienie pamieci - struktura wejsciowa jest pusta
    S = nullptr;
    
}




/*!
 * Funkcja umozliwiajaca polaczenie elementow trzech sekwencji w sposob rosnacy
 * Argumenty:
 *      L - wskaznik na sekwencje pierwsza
 *      E - wskaznik na sekwencje druga
 *      G - wskaznik na sekwencje trzecia 
 * Zwraca:
 *      S - wskaznik na nowa sekwencje, powstala z L,E i G
 */
template<typename Typ_Danych>
Sekwencja<Typ_Danych>* Polacz(Sekwencja<Typ_Danych> *L, Sekwencja<Typ_Danych> *E, Sekwencja<Typ_Danych> *G)
{   
    Sekwencja<Typ_Danych>* S = new Sekwencja<Typ_Danych>;

    while (!L->Czy_Pusta()) 
    {
        S->Dodaj_Na_Koniec(L->Podaj_Wartosc_Pierwszego(),L->Podaj_Klucz_Pierwszy());
        L->Usun_Pierwszy();  
    }
    while (!E->Czy_Pusta())
    { 
        S->Dodaj_Na_Koniec(E->Podaj_Wartosc_Pierwszego(),E->Podaj_Klucz_Pierwszy());
        E->Usun_Pierwszy();
    }
    while (!G->Czy_Pusta())
    { 
        S->Dodaj_Na_Koniec(G->Podaj_Wartosc_Pierwszego(),G->Podaj_Klucz_Pierwszy());
        G->Usun_Pierwszy();
    }    

    delete L; //Zwolnienie pamieci - struktury skladowe sa teraz puste
    delete E;
    delete G;    
    L = nullptr;
    E = nullptr;
    G = nullptr;
    return S; //Zwrocenie sekwencji powstalej w wyniku polaczenia
}




/*!
 * Funkcja realizuje zasadnicza czesc algorytmu sortowania szybkiego w sposob rekurencyjny
 * Argumenty:
 *      S - wskaznik na sortowana sekwencje
 * Zwraca:
 *      Przypadek a) S  - wskaznik na ta sama sekwencje dla struktur o rozmiarze 1
 *      Przypadek b) S3 - wskaznik na nowa sekwencje, stanowiaca posortowana wersje struktury
 *                        wejsciowej, jezeli zawierala ona wiecej niz 1 element 
 */
template<typename Typ_Danych>
Sekwencja<Typ_Danych>* Quick_Sort(Sekwencja<Typ_Danych> *S)
{
    if (S->Podaj_Rozmiar() > 1) //Przypadek co najmniej dwoch elementow
    {
        Sekwencja<Typ_Danych>* L = new Sekwencja<Typ_Danych>; 
        Sekwencja<Typ_Danych>* E = new Sekwencja<Typ_Danych>;
        Sekwencja<Typ_Danych>* G = new Sekwencja<Typ_Danych>;

        Podziel(L,E,G,S); //Podzielenie sekwencji na sekwencje skladowe
        L = Quick_Sort(L); //Wywolanie rekurencyjne dla sekwencji elementow mniejszych od pivota
        G = Quick_Sort(G); //Wywolanie rekurencyjne dla sekwencji elementow wiekszych od pivota 
        Sekwencja<Typ_Danych>* S3 = Polacz(L,E,G); //Polaczenie sekwencji
        return S3;        
    }
    return S;
}

#endif