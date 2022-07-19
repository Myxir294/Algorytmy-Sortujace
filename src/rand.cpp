#include "..\inc\rand.hh"

void Rand_Inicjalizuj()
{
    std::srand(time(NULL));
}

int Rand_Losuj_Liczbe_Z_Przedzialu(const unsigned int max)
{   
    int liczba;
    liczba = rand() % (max+1); // zakres od 0 do max      
    return liczba;
}