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
/*Program umozliwia reczne przetestowanie mechanizmow opisanych
 w tresci zadania projektowego na ocene bardzo dobra.*/

using namespace std;

int main()
{   
    Sekwencja<string>* Moja_Kolejka = new Sekwencja<string>;
    Rand_Inicjalizuj(); //Niezbedna inicjalizacja generatora liczb losowych
    float klucz;
    string wartosc;
    cout << "Wylosowane dane: " << endl;
    for (unsigned int i = 0; i < 15; i++)
    {   
        wartosc = to_string(Rand_Losuj_Liczbe_Z_Przedzialu(MAX_KLUCZ));
        klucz = stof(wartosc);
        Moja_Kolejka->Dodaj_Na_Koniec(wartosc,klucz);
        cout << klucz << " ";
    }
    char wybor = '0';
    while (wybor != '1' && wybor != '2' && wybor != '3') //Proste menu uzytkownika
    {
        cout << endl << "Wybierz sortowanie do przetestowania:" << endl;
        cout << "1 - sortowanie szybkie:" << endl;
        cout << "2 - sortowanie przez scalanie" << endl;
        cout << "3 - sortowanie kubelkowe" << endl;
        cout << "Twoj wybor: "; 
        cin >> wybor;
        switch (wybor)
        {
		    case '1': 
                cout << "Wybrano sortowanie szybkie" << endl;
                Moja_Kolejka = Quick_Sort(Moja_Kolejka);
            break;

            case '2': 
                cout << "Wybrano sortowanie przez scalanie" << endl;
                Moja_Kolejka = Merge_Sort(Moja_Kolejka);
            break;

            case '3':
                cout << "Wybrano sortowanie kubelkowe" << endl;
                Bucket_Sort(Moja_Kolejka);
            break;  

		    default:
                cout << "Nie rozpoznano znaku, sprobuj ponownie" << endl;
            break;
        }
    }
    cout << "Posortowane dane: " << endl;
    while (!Moja_Kolejka->Czy_Pusta())
    {
        cout << Moja_Kolejka->Podaj_Klucz_Pierwszy() << " ";
        Moja_Kolejka->Usun_Pierwszy();
    }    
    cout << endl;
    delete Moja_Kolejka;
    Moja_Kolejka = nullptr;
    return 0;
}
