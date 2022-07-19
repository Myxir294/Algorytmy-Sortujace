#include <cstdlib>
#include <string>
#include <fstream>
#include <time.h>

#include "..\inc\sekwencja.hh"
#include "..\inc\rand.hh"
#include "..\inc\Bucket.hh"
#include "..\inc\Merge.hh"
#include "..\inc\Quick.hh"

using namespace std;
#define MAX_ROZMIAR_PLIKU 2000000


/*Program umozliwia reczne wykorzystanie mechanizmow opisanych
 w tresci zadania projektowego na ocene bardzo dobra.

 W tym celu uzytkownik musi podac dwa argumenty wywolania,
 gdzie pierwszy z nich stanowi identyfikator algorytmu (q,s,k),
 a drugi okresla maksymalna ilosc przetwarzanych danych.
 W przypadku podania wartosci niedodatniej program wykorzystuje
 zdefiniowana wartosc stalej MAX_ROZMIAR_PLIKU.*/







/*!
 * Funkcja umozliwiajaca weryfikacje posortowania rankingu
 * Argument:
 *      plik - nazwa badanego pliku
 * Zwraca:
 *      Nic - funkcja informuje o poprawnosci posortowania poprzez
 *      wyswietlenie odpowiedniego komunikatu   
 */
void Sprawdz_Posortowanie(string plik)
{
    string numer;
    string nazwa; //W przyjetym rozwiazaniu na nazwe przeznaczono dwie rozne zmienne
    string nazwa2; //Druga z nich znajduje zastosowanie dla przetwarzania zlozonych tytulow
    string ranking;
    float ranking_float;
    ifstream file3 (plik); //Otwarcie wskazanego pliku do odczytu
    bool posortowane = true; //Program domyslnie zaklada ze plik jest posortowany
    while ( file3.good())
    {   
        float min = 0;
        getline ( file3, numer, ',' ); //Pobranie numeru linijki
        getline ( file3, nazwa, ',' ); //Pobranie nazwy filmu
        if (nazwa.front() == '\"') //Przypadek dla nazwy zlozonej
        {    
            nazwa += ',';
            getline ( file3, nazwa2, '\"' );
            nazwa += (nazwa2 + '\"');
            file3.ignore(1);    
        }
        getline ( file3, ranking, '\n'); //Pobranie rankingu filmu
        try
        {
            ranking_float = stof(ranking);
            //Jezeli ranking jest mniejszy niz obecne minimum to sekwencja nie jest posortowana
            if (ranking_float < min){posortowane = false;}
            else //Przypadek poprawnej pozycji elementu
            {
                min = ranking_float; //Zmiana minimalnego rankingu
            }
        }
        catch(...)
        {
            cerr << "Blad odczytu - bledny ranking " << endl;    
        }
    }
    cout << "Weryfikacja posortowania: "; //Wyswietlenie komunikatu
    if (posortowane)
    {
        cout << "Sortowanie przebieglo pomyslnie." << endl;
    }   
    else
    {
        cout << "Sortowanie nie udalo sie." << endl;
    }
file3.close(); //Zamkniecie pliku    
}







/*!
 * Funkcja umozliwiajaca wczytanie wartosci z pliku do sekwencji.
 * Ponadto podaje srednia wartosc kluczy przetwarzanych elementow
 * oraz wyswietla odpowiednie komunikaty.
 * 
 * Argumenty:
 *      Moja_Kolejka - wskaznik na wykorzystywana sekwencje
 *      Plik_We - nazwa pliku wejsciowego
 *      limit - okreslona maksymalna liczba danych, ktore zostana
 *              dodane do sekwencji
 * Zwraca:
 *      Nic - efektem pracy funkcji jest odpowiednio zapelniona
 *            sekwencja wskazywana przez podany wskaznik   
 */
template <typename Typ_Danych>
void Wczytaj(Sekwencja<Typ_Danych>* Moja_Kolejka, string Plik_We, unsigned int limit)
{
    string komentarz; //W zmiennej przechowywana bedzie pierwsza linijka pliku, niezwiazana z sortowaniem
    string numer;
    string nazwa; //W przyjetym rozwiazaniu na nazwe przeznaczono dwie rozne zmienne
    string nazwa2; //Druga z nich znajduje zastosowanie dla przetwarzania zlozonych tytulow
    string ranking;
    float ranking_float;
    bool blad; //Zmienna uzywana w trakcie filtracji danych
    long double suma = 0; //Pomocnicza zmienna uzyta do wyznaczenia sredniej

    ifstream file (Plik_We); //Otwarcie wskazanego pliku do odczytu
    getline (file,komentarz); //Pobranie komentarza
    unsigned int i = 0;
    while ( file.good() && i < limit) //Obsluga zadanej ilosci danych
    {   
        blad = false;
        getline ( file, numer, ',' ); //Pobranie numeru linijki
        getline ( file, nazwa, ',' ); //Pobranie nazwy filmu
        if (nazwa.front() == '\"') //Przypadek dla nazwy zlozonej
        {    
            nazwa += ',';
            getline ( file, nazwa2, '\"' );
            nazwa += (nazwa2 + '\"');
            file.ignore(1);    
        }
        getline ( file, ranking, '\n'); //Pobranie rankingu filmu
        if (nazwa != " " && ranking != " " && ranking != "\n") //Weryfikacja poprawnosci rankingu
        {
            try
            {
                ranking_float = stof(ranking); //Zapisanie rankingu jako float
            }
            catch(...) //Przypadek blednego wykonania konwersji
            {
                blad = true;    
            }
        }
        else //Przypadek blednego rankingu
        {
            blad = true; 
        }
        if (!blad) //Jezeli ranking jest poprawny
        {
            i++;
            nazwa += (',' +  ranking); //Dodanie rankingu do nazwy
            Moja_Kolejka->Dodaj_Na_Poczatek(nazwa,ranking_float); //Dodanie elementu do sekwencji
            suma += (long double)ranking_float; //Pomocnicze obliczenia do wyznaczenia sredniej
        }
    }
unsigned int liczba_danych = Moja_Kolejka->Podaj_Rozmiar(); //Wyznaczenie sredniej
cout << "Wczytywanie skonczone" << endl;
cout << "Srednia kluczy: " << suma/(long double)liczba_danych << endl;
file.close();
}








/*!
 * Funkcja umozliwiajaca zapisanie wartosci z sekwencji do pliku.
 * Ponadto wyznacza mediane kluczy oraz podaje odpowiednie komunikaty.
 * 
 * Argumenty:
 *      Moja_Kolejka - wskaznik na wykorzystywana sekwencje
 *      Plik_Wy - nazwa pliku wyjsciowego
 * Zwraca:
 *      Nic - efektem pracy funkcji jest odpowiednio zapelniony
 *            plik o podanej nazwie   
 */
template <typename Typ_Danych>
void Zapisz(Sekwencja<Typ_Danych>* Moja_Kolejka, string Plik_Wy)
{   
    ofstream file2 (Plik_Wy); //Otwarcie pliku do zapisu
    unsigned int liczba_danych = Moja_Kolejka->Podaj_Rozmiar();
    //Wyswietlenie ilosci poprawnych danych zawartych w sekwencji wejsciowej
    cout << "Liczba wyjsciowych danych " << liczba_danych << endl;
    unsigned int indeks_srodkowego = liczba_danych/2; //Zmienna pomocnicza do wyznaczania mediany
    float mediana;
    if (liczba_danych % 2 == 0) //Wyznaczenie mediany dla parzystej liczby danych
    {   
        float klucz1 = Moja_Kolejka->Wsk_Na_Element_O_Indeksie(indeks_srodkowego)->Podaj_Klucz();
        float klucz2 = Moja_Kolejka->Wsk_Na_Element_O_Indeksie(indeks_srodkowego-1)->Podaj_Klucz();
        mediana = (klucz1+klucz2)/2; 
    }
    else //Wyznaczenie mediany dla nieparzystej liczby danych
    {
        mediana = Moja_Kolejka->Wsk_Na_Element_O_Indeksie(indeks_srodkowego)->Podaj_Klucz();
    }
    int k = 0;
    while (!Moja_Kolejka->Czy_Pusta()) //Zdejmowanie elementow z sekwencji i zapisywanie do pliku
    {   
        file2 << k << ',' << Moja_Kolejka->Podaj_I_Usun_Pierwszy() << '\n';
        if (file2.fail()){ cerr << "Blad zapisu" << endl;}
        ++k;
    }
    cout << "Zapisywanie skonczone" << endl;    
    cout << "Mediana kluczy: " << mediana << endl; //Podanie mediany    
    file2.close();
}






/*!
 * Program glowny
 * 
 * Obowiazkowe argumenty wywolania:
 *      nr 1 - identyfikator wykorzystywanego algorytmu
 *      nr 2 - maksymalna zadana liczba danych 
 *             (ignorowana, jesli niepoprawna badz niedodatnia) 
 * Zwraca:
 *      0 - program zadzialal poprawnie
 *     -1 - nie podano wlasciwej ilosci argumentow wywolania
 *     -2 - blednie wybrano algorytm sortowania   
 */
int main(int argc, char *argv[])
{
    int wybrany_rozmiar;
    char wybrany_algorytm;
    unsigned int limit; //Zadana maksymalna liczba danych wejsciowych
    if (argc != 3) {cerr << "Bledna ilosc argumentow wywolania" << endl; return -1;} //Rozmiar, jezeli poprawnie podano argument
    else
    {
        wybrany_algorytm = (*argv[1]);
        if (wybrany_algorytm != 'q' && wybrany_algorytm != 's' && wybrany_algorytm != 'k') //Wybranie algorytmu, jesli poprawnie podano argument
        {
            {cerr << "Bledny wybor algorytmu" << endl; return -2;}
        }
    wybrany_rozmiar = atoi(argv[2]); //Konwersja do typu int
    }

    clock_t start, end; // zmienne pomocnicze uzywane do mierzenia czasu pracy poszczegolnych sekcji programu
    double cpu_time_used;
    Rand_Inicjalizuj(); //Niezbedna inicjalizacja generatora liczb losowych

    Sekwencja<string>* Moja_Kolejka = new Sekwencja<string>;
    if (wybrany_rozmiar > 0) //Jezeli zadano dodatni rozmiar
    {
        limit = (unsigned int) wybrany_rozmiar; //Wykorzystanie zadanej wartosci
    }
    else //Jezeli podano wartosc ujemna
    {
        limit = MAX_ROZMIAR_PLIKU; //Wykorzystanie domyslnej wartosci maksymalnej
    }
    cout << "Maksymalna liczba danych: " << limit << endl;

    start = clock(); // Liczenie czasu wczytywania danych

    Wczytaj(Moja_Kolejka,"projekt2_dane.csv",limit); //Wczytanie zadanej ilosci danych z zadanego pliku

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Czas wczytywania: " << cpu_time_used << "s" << endl << endl; //Podanie czasu wczytywania danych (w sekundach)

    start = clock(); //Zmierzenie czasu sortowania

    switch (wybrany_algorytm) //Wybor uzywanego algorytmu
    {
        case 'q':
            cout << "Wybrano sortowanie szybkie" << endl;
            Moja_Kolejka = Quick_Sort(Moja_Kolejka);
            break;
        case 's':
            cout << "Wybrano sortowanie przez scalanie" << endl;
            Moja_Kolejka = Merge_Sort(Moja_Kolejka);
            break;
        case 'k':
            cout << "Wybrano sortowanie kubelkowe" << endl;
            Bucket_Sort(Moja_Kolejka);
            break;
        default: //Opcja default nigdy nie bedzie uzywana
            break;
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Czas sortowania: " << cpu_time_used << "s" << endl << endl; //Podanie czasu sortowania

    start = clock();
    Zapisz(Moja_Kolejka,"moje_dane.csv"); //Zapisanie danych do pliku
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Czas zapisywania: " << cpu_time_used << "s" << endl; //Podanie czasu zapisywania

    Sprawdz_Posortowanie("moje_dane.csv"); //Weryfikacja posortowania danych

    delete Moja_Kolejka; //Poprawne zwolnienie pamieci
    Moja_Kolejka = nullptr;
    return 0;
}