#ifndef SEKWENCJA_HH
#define SEKWENCJA_HH
#include <iostream>
#include "kolejka.hh"

/*Plik zawiera klase modelujaca sekwencje, rozszerzajaca definicje kolejki priorytetowej.
  Struktura umozliwia pobranie wskaznika na element wykorzystujac jego indeks (pozycje)
  oraz pobranie indeksu elementu, wykorzystujac wskaznik.
*/
template<typename Typ_Danych>
class Sekwencja : public Kolejka_Na_Liscie<Typ_Danych> //Sekwencja dziedziczy z klasy kolejki priorytetowej na liscie dwukierunkowej
{
    public:
    //Definicje metod publicznych
    Wezel<Typ_Danych>* Wsk_Na_Element_O_Indeksie(unsigned int i) const;
    unsigned int Indeks_Elementu(const Wezel<Typ_Danych>* const wsk) const; 
};



/*!
 * Pobranie wskaznika na element o zadanym indeksie
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie sekwencja musi miec rozmiar 
 *      o wiekszej wartosci niz wskazany indeks.
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Sekwencja
 * Argument:
 *      i - wybrany indeks elementu
 * Zwraca:
 *      pom - wskaznik na element o zadanym indeksie
 */
template<typename Typ_Danych>
Wezel<Typ_Danych>* Sekwencja<Typ_Danych>::Wsk_Na_Element_O_Indeksie(unsigned int i) const
{   
    if (i >= (this->Podaj_Rozmiar())) // Jezeli podano niepoprawny indeks
    {
        throw -1;
    }

    if (i > (this->Podaj_Rozmiar())/2 ) //Jezeli podano poprawny indeks wiekszy niz polowa rozmiaru sekwencji
    {
        Wezel<Typ_Danych>* pom = this->Podaj_Wsk_Ostatni();
        unsigned int j = this->Podaj_Rozmiar() - i;
        for (unsigned int k = 1; k < j; ++k) //Przechodzenie po liscie wstecz wedlug zadanej wartosci indeksu
        {
            pom = pom->Podaj_Poprzedni();
        }
        return pom;
    }
    else //Jezeli podano poprawny indeks mniejszy niz polowa rozmiaru sekwencji
    {   
        Wezel<Typ_Danych>* pom = this->Podaj_Wsk_Pierwszy();
        for (unsigned int k = 0; k < i; ++k) //Przechodzenie po liscie do przodu wedlug zadanej wartosci indeksu
        {
            pom = pom->Podaj_Nastepny();
        }
        return pom;
    }
}

/*!
 * Odczytanie indeksu wskazywanego elementu
 *
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Sekwencja
 * Argument:
 *      wsk - wskaznik na istniejacy element nalezacy do sekwencji
 * Zwraca:
 *      i - indeks wskazanego elementu
 */
template<typename Typ_Danych>
unsigned int Sekwencja<Typ_Danych>::Indeks_Elementu(const Wezel<Typ_Danych>* const wsk) const
{   
    
    Wezel<Typ_Danych> *pom = this->Podaj_Wsk_Pierwszy();
    unsigned int i = 0;
    while(pom != wsk) //Przechodzenie po liscie tak dlugo az uzyska sie wskazany element
    {
        pom = pom->Podaj_Nastepny();
        ++i;
    }
    return i;
}  


#endif