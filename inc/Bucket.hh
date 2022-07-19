#ifndef BUCKET_HH
#define BUCKET_HH

#define MAX_KLUCZ 10
#include "sekwencja.hh"


/*!
 * Plik zawiera funkcje realizujaca algorytm sortowania kubelkowego
 * Argumenty:
 *      S - wskaznik na sortowana sekwencje
 * Zwraca:
 *      Nic - efektem dzialania funkcji jest posortowanie struktury
 *            wejsciowej 
 */
template<typename Typ_Danych>
void Bucket_Sort(Sekwencja<Typ_Danych> *S)
{
    Sekwencja<Typ_Danych> B[MAX_KLUCZ+1]; //Stworzenie tablicy kubelkow
    float klucz_pom;
    unsigned int indeks_pom;
    while (!S->Czy_Pusta()) //Dodawanie elementow sekwencji do odpowiedniego kubelka 
    {   
        klucz_pom = S->Podaj_Klucz_Pierwszy();
        indeks_pom = (unsigned int)klucz_pom; //Wybor wlasciwego kubelka
        B[indeks_pom].Dodaj_Na_Koniec(S->Podaj_I_Usun_Pierwszy(), klucz_pom);

    }
    for (unsigned int i = 0; i<MAX_KLUCZ+1; i++) //Oproznianie tablicy kubelkow
    {
        while (!B[i].Czy_Pusta()) //Ponowne dodawanie do sekwencji, w sposob uporzadkowany
        {
            klucz_pom = B[i].Podaj_Klucz_Pierwszy();
            S->Dodaj_Na_Koniec(B[i].Podaj_I_Usun_Pierwszy(), klucz_pom);
        }
    }
} 

#endif