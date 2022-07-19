#ifndef KOLEJKA_HH
#define KOLEJKA_HH
#include <iostream>
/*Plik zawiera klasy modelujace kolejke priorytetowa na liscie dwukierunkowej*/


/*
 * Klasa Wezel modeluje pojęcie wezla listy dwukierunkowej 
 * przechowujacej elementy o zadanym typie.
 * Zawiera metody umożliwiające odczyt i modyfikacje wartosci, 
 * klucza oraz wskaznika na sasiadujace wezly listy.
 */
template<typename Typ_Danych>
class Wezel
{
    private:
    Typ_Danych Wartosc;
    float Klucz;
    Wezel<Typ_Danych> *Nastepny; //Wskaznik na nastepny wezel
    Wezel<Typ_Danych> *Poprzedni; //Wskaznik na poprzedni wezel

    // Definicje metod publicznych
    public:
    //Konstruktor domyslny
    Wezel(){Nastepny = nullptr; Poprzedni = nullptr; /*std::cout << "wezel - utworzonie" << std::endl;*/}
    ~Wezel(){/*std::cout << "wezel - usuniecie" << std::endl;*/} //Destruktor domyslny 
    const Typ_Danych& Podaj_Wartosc() const {return Wartosc;}
    const float& Podaj_Klucz() const {return Klucz;}

    Wezel<Typ_Danych>* Podaj_Nastepny() const {return Nastepny;}
    Wezel<Typ_Danych>* Podaj_Poprzedni() const {return Poprzedni;}

    void Ustaw_Wartosc(const Typ_Danych& Nowa_Wartosc) {Wartosc = Nowa_Wartosc;}
    void Ustaw_Klucz(const float& Wartosc_Klucza) {Klucz = Wartosc_Klucza;}

    void Ustaw_Nastepny(Wezel<Typ_Danych> *Nowy_Nastepny) {Nastepny = Nowy_Nastepny;}
    void Ustaw_Poprzedni(Wezel<Typ_Danych> *Nowy_Poprzedni) {Poprzedni = Nowy_Poprzedni;}

};




/*
 * Klasa Komparator_Kolejka_Priorytetowa_Klucz modeluje komparator 
 * wezlow listy dwukierunkowej, przechowujacej elementy o zadanym typie.
 * Zawarte przeciazenie operatora umozliwia okreslenie wzajemnej
 * relacji kluczy przypisanych do porownywanych wezlow.
 */
template<typename Typ_Danych>
class Komparator_Kolejka_Priorytetowa_Klucz
{   
    public:
    int operator()(Wezel<Typ_Danych>* skl1, Wezel<Typ_Danych> *skl2) const //Przeciazienie operatora i porownanie
    {
        if (skl1->Podaj_Klucz() > skl2->Podaj_Klucz()){return 1;} // skl1 > skl2
        else if (skl1->Podaj_Klucz() < skl2->Podaj_Klucz()){return -1;} // skl1 < skl2
        else {return 0;} //skl1 == skl2
    }
};







/*
 * Klasa Kolejka_Na_Liscie modeluje pojecie kolejki priorytetowej wykorzystujac dynamiczna
 * dwukierunkowa liste elementow o zadanym typie.
 * Zawiera metody umozliwiajace wykonywanie roznych operacji na elementach,
 * takich jak dodawanie i usuwanie wezlow lub pobranie elementu o najmniejszym kluczu.
 */

template<typename Typ_Danych>
class Kolejka_Na_Liscie
{
    private:
    unsigned int rozmiar;            // rozmiar jako ilosc elementow
    Wezel<Typ_Danych> *Pierwszy_Pom; //Wskaznik na pierwszy wezel
    Wezel<Typ_Danych> *Ostatni_Pom;  //Wskaznik na ostatni wezel

    //Deklaraja prywatnej metody pomocniczej sluzacej do znalezienia elementu o najmniejszym kluczu
    Wezel<Typ_Danych>* Znajdz_Element_Min_Klucz() const; 

    public:
    Komparator_Kolejka_Priorytetowa_Klucz<Typ_Danych> Porownaj; //Zawarcie komparatora

    // Zapowiedzi definicji lub definicje metod publicznych
    Kolejka_Na_Liscie() //Konstruktor domyslny - inicjalizacja
    {   
        rozmiar = 0;
        Pierwszy_Pom = nullptr;
        Ostatni_Pom = nullptr;
    }
    ~Kolejka_Na_Liscie(); //Destruktor domyslny    
    unsigned int Podaj_Rozmiar() const {return rozmiar;}
    bool Czy_Pusta() const; //Sprawdzenie czy kolejka jest pusta

    /*Dostanie sie do wartosci elementu pierwszego wykorzystujac wskaznik Pierwszy_Pom.
    Aby metoda zadzialala poprawnie kolejka nie moze byc pusta*/
    const Typ_Danych& Podaj_Wartosc_Pierwszego() const; 

    /*Dostanie sie do wartosci elementu ostatniego wykorzystujac wskaznik Ostatni_Pom.
    Aby metoda zadzialala poprawnie kolejka nie moze byc pusta*/    
    const Typ_Danych& Podaj_Wartosc_Ostatniego() const;

    const float& Podaj_Klucz_Pierwszy() const; //Podanie klucza pierwszego elementu (o ile istnieje)

    const float& Podaj_Klucz_Ostatni() const;  //Podanie klucza ostatniego elementu (o ile istnieje)
    
    //Metoda pomocnicza umozliwiajaca pobranie wskaznika na pierwszy element
    Wezel<Typ_Danych>* Podaj_Wsk_Pierwszy() const{return Pierwszy_Pom;}

    //Metoda pomocnicza umozliwiajaca pobranie wskaznika na ostatni element
    Wezel<Typ_Danych>* Podaj_Wsk_Ostatni() const {return Ostatni_Pom;}

    //Metoda umozliwiajaca podanie wartosci elementu o najmniejszym kluczu
    const Typ_Danych& Podaj_Wartosc_Elementu_Min_Klucz() const;

    //Metoda umozliwiajaca zdjecie z kolejki elementu o najmniejszym kluczu
    const Typ_Danych Podaj_I_Usun_Element_Min_Klucz();

    //Metody umozliwiajace usuwanie elementow
    void Usun_Element(Wezel<Typ_Danych> *Element); //Poprzez wskaznik na wybrany element
    void Usun_Pierwszy(); //Usuniecie pierwszego
    void Usun_Ostatni();  //Usuniecie ostatniego

    //Metody umozliwiajace pobranie wartosci elementu jednoczesnie usuwajac go z kolejki 
    const Typ_Danych Podaj_I_Usun_Element(Wezel<Typ_Danych> *Element);    
    const Typ_Danych Podaj_I_Usun_Pierwszy(); 
    const Typ_Danych Podaj_I_Usun_Ostatni(); 
    
    //Metody umozliwiajace dodanie do kolejki elementu o wskazanej wartosci i kluczu
    void Dodaj_Za(const Typ_Danych& Wartosc,const float& Klucz, Wezel<Typ_Danych> *Element); //Dodanie za istniejacy element    
    void Dodaj_Na_Koniec (const Typ_Danych& Wartosc, const float& Klucz);
    void Dodaj_Na_Poczatek (const Typ_Danych& Wartosc, const float& Klucz);
   
};







/*!
 * Sprawdzenie, czy kolejka nie jest pusta (czy jej rozmiar wynosi 0)
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      true - kolejka jest pusta
 *      false - kolejka ma przynajmniej jeden element   
 */
template<typename Typ_Danych>
bool Kolejka_Na_Liscie<Typ_Danych>::Czy_Pusta() const
{
    if (this->rozmiar > 0)
    {
        return false;
    }
    else 
    {
        return true;
    }  
} 



/*!
 * Odczytanie wartosci elementu z poczatku kolejki
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      Wartosc pierwszego elementu z kolejki
 */
template<typename Typ_Danych>
const Typ_Danych& Kolejka_Na_Liscie<Typ_Danych>::Podaj_Wartosc_Pierwszego() const
{
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    else
    {
        return this->Pierwszy_Pom->Podaj_Wartosc();    
    }
}


/*!
 * Odczytanie wartosci elementu z konca kolejki
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      Wartosc ostatniego elementu z kolejki
 */
template<typename Typ_Danych>
const Typ_Danych& Kolejka_Na_Liscie<Typ_Danych>::Podaj_Wartosc_Ostatniego() const
{
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    else
    {
        return this->Ostatni_Pom->Podaj_Wartosc();    
    }
}

/*!
 * Odczytanie klucza elementu z poczatku kolejki
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      Klucz pierwszego elementu z kolejki
 */
template<typename Typ_Danych>
const float& Kolejka_Na_Liscie<Typ_Danych>::Podaj_Klucz_Pierwszy() const 
{    
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    return Pierwszy_Pom->Podaj_Klucz();
} 

/*!
 * Odczytanie klucza elementu z konca kolejki
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      Klucz ostatniego elementu z kolejki
 */
template<typename Typ_Danych>
const float& Kolejka_Na_Liscie<Typ_Danych>::Podaj_Klucz_Ostatni() const 
{    
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    return Ostatni_Pom->Podaj_Klucz();
}

/*!
 * Znalezienie elementu o minimalnym kluczu
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      tmp - Wskaznik na element o najmniejszym kluczu
 */
template<typename Typ_Danych>
Wezel<Typ_Danych>* Kolejka_Na_Liscie<Typ_Danych>::Znajdz_Element_Min_Klucz() const
{
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    else
    {   
        Wezel<Typ_Danych> *pom = this->Pierwszy_Pom;
        Wezel<Typ_Danych> *tmp = pom; //Domyslne zalozenie ze to element pierwszy ma minimalny klucz  
        for (unsigned int i = 1; i<(this->rozmiar); ++i) //Przejrzenie calej struktury
        {   
            pom = pom->Podaj_Nastepny();
            if(Porownaj(tmp,pom) > 0) //Porownywanie kluczy obecnego elementu o minimalnym kluczu i elementu badanego
            {   
                //Jezeli badany element ma mniejszy klucz od elementu o minimalnym kluczu, to zmien obecny element o minimalnym kluczu
                tmp = pom; 
            }
        }
        return tmp; 
    }
}


/*!
 * Podanie wartosci elementu o minimalnym kluczu
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Niemodyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      Wartosc elementu o minimalnym kluczu
 */
template<typename Typ_Danych>
const Typ_Danych& Kolejka_Na_Liscie<Typ_Danych>::Podaj_Wartosc_Elementu_Min_Klucz() const 
{
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    return this->Znajdz_Element_Min_Klucz()->Podaj_Wartosc();    
}


/*!
 * Metoda umozliwiajaca dynamiczne usuniecie wybranego elementu z kolejki
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Argument:
 *      Element - wskaznik na element do usuniecia  
 */
template<typename Typ_Danych>
void Kolejka_Na_Liscie<Typ_Danych>::Usun_Element(Wezel<Typ_Danych> *Element) 
{   
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    if(Ostatni_Pom == Pierwszy_Pom) //Jezeli lista ma jeden element
    {
        Ostatni_Pom = Pierwszy_Pom = nullptr;
    }
    else if(this->Pierwszy_Pom == Element) //Jezeli usuwany element jest pierwszym
    {   
        Element->Podaj_Nastepny()->Ustaw_Poprzedni(nullptr);
        Pierwszy_Pom = Element->Podaj_Nastepny();
    }
    else if(this->Ostatni_Pom == Element) //Jezeli usuwany element jest ostatnim
    {
        Element->Podaj_Poprzedni()->Ustaw_Nastepny(nullptr);
        Ostatni_Pom = Element->Podaj_Poprzedni();
    }
    else
    {
        Element->Podaj_Poprzedni()->Ustaw_Nastepny(Element->Podaj_Nastepny());
        Element->Podaj_Nastepny()->Ustaw_Poprzedni(Element->Podaj_Poprzedni());       
    }
    Element->Ustaw_Nastepny(nullptr); //Usuwanie wskaznikow elementu
    Element->Ustaw_Poprzedni(nullptr);
    delete Element;
    this->rozmiar = (this->rozmiar) - 1; //Zmniejszenie rozmiaru kolejki
}

/*!
 * Metoda umozliwiajaca zdjecie z kolejki elementu o minimalnym kluczu 
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      pom - wartosc elementu o minimalnym kluczu  
 */
template<typename Typ_Danych>
const Typ_Danych Kolejka_Na_Liscie<Typ_Danych>::Podaj_I_Usun_Element_Min_Klucz()
{
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    Typ_Danych pom = Podaj_Wartosc_Elementu_Min_Klucz();
    this->Usun_Element(this->Znajdz_Element_Min_Klucz());
    return pom;    
}


/*!
 * Metoda umozliwiajaca dynamiczne usuniecie elementu z poczatku kolejki
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie  
 */
template<typename Typ_Danych>
void Kolejka_Na_Liscie<Typ_Danych>::Usun_Pierwszy() 
{   
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    this->Usun_Element(this->Pierwszy_Pom);

}

/*!
 * Metoda umozliwiajaca dynamiczne usuniecie elementu z konca kolejki
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie  
 */
template<typename Typ_Danych>
void Kolejka_Na_Liscie<Typ_Danych>::Usun_Ostatni() 
{   
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    this->Usun_Element(this->Ostatni_Pom);

}


/*!
 * Metoda dajaca mozliwosc usuniecia wybranego elementu przy jednoczesnym zwroceniu jego wartosci.
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Argument:
 *      Element - wskaznik na element zdejmowany z kolejki
 * Zwraca:
 *      tmp - wartosc wybranego elementu z kolejki  
 */
template<typename Typ_Danych>
const Typ_Danych Kolejka_Na_Liscie<Typ_Danych>::Podaj_I_Usun_Element(Wezel<Typ_Danych> *Element)
{   
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    Typ_Danych tmp = Element->Podaj_Wartosc();
    this->Usun_Element(Element);
    return tmp;
}



/*!
 * Metoda dajaca mozliwosc usuniecia pierwszego elementu przy jednoczesnym zwroceniu jego wartosci.
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      tmp - wartosc pierwszego elementu z kolejki  
 */
template<typename Typ_Danych>
const Typ_Danych Kolejka_Na_Liscie<Typ_Danych>::Podaj_I_Usun_Pierwszy()
{   
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    Typ_Danych tmp = this->Pierwszy_Pom->Podaj_Wartosc();
    this->Usun_Pierwszy();
    return tmp;
}



/*!
 * Metoda dajaca mozliwosc usuniecia ostatniego elementu przy jednoczesnym zwroceniu jego wartosci.
 * Zalozenia:
 *      Zeby metoda zadzialala poprawnie kolejka nie moze byc pusta,
 *      w innym przypadku zwrocony jest wyjatek.
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Zwraca:
 *      tmp - wartosc ostatniego elementu z kolejki  
 */
template<typename Typ_Danych>
const Typ_Danych Kolejka_Na_Liscie<Typ_Danych>::Podaj_I_Usun_Ostatni()
{   
    if(this->rozmiar == 0)
    {
        throw -1;
    }
    Typ_Danych tmp = this->Ostatni_Pom->Podaj_Wartosc();
    this->Usun_Ostatni();
    return tmp;
}



/*!
 * Metoda umozliwiajaca dynamiczne dodanie elementu za wybrana pozycje
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Argumenty:
 *      Wartosc - Referencja do niemodyfikowalnej wartosci zadanego typu
 *      Klucz   - Referencja do niemodyfikowalnej wartosci klucza
 *      Element - wskaznik na istniejacy wezel, za ktory dodany zostanie nowy element    
 */
template<typename Typ_Danych>
void Kolejka_Na_Liscie<Typ_Danych>::Dodaj_Za(const Typ_Danych& Wartosc,const float& Klucz, Wezel<Typ_Danych> *Element)
{   
    if(this->rozmiar == 0)
    {
        throw -1;
    }    
    Wezel<Typ_Danych> *pom = new Wezel<Typ_Danych>; /* Dynamiczne utworzenie wezla z wartoscia
                                                    zadanego typu wykorzystujac wskaznik
                                                    pomocniczy.*/
    pom->Ustaw_Wartosc(Wartosc); // Przypisanie obiektowi pozadanej wartosci
    pom->Ustaw_Klucz(Klucz); // Przypisanie obiektowi pozadanego klucza   
    pom->Ustaw_Poprzedni(Element); // Odpowiednie zainicjowanie wskaznikow
    pom->Ustaw_Nastepny(Element->Podaj_Nastepny());
    if (Element->Podaj_Nastepny() != nullptr) // Jezeli nie dodajemy za ostatni element
    {
        Element->Podaj_Nastepny()->Ustaw_Poprzedni(pom);    
    }
    else //Jezeli dodajemy za ostatni element
    {
        this->Ostatni_Pom = pom;        
    }
    Element->Ustaw_Nastepny(pom);
    this->rozmiar++; // Zwiekszenie zapisywanego rozmiaru kolejki
}


/*!
 * Metoda umozliwiajaca dynamiczne dodanie elementu na koniec kolejki
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Argumenty:
 *      Wartosc - Referencja do niemodyfikowalnej wartosci zadanego typu
 *      Klucz   - Referencja do niemodyfikowalnej wartosci klucza   
 */
template<typename Typ_Danych>
void Kolejka_Na_Liscie<Typ_Danych>::Dodaj_Na_Koniec(const Typ_Danych& Wartosc,const float& Klucz)
{
    Wezel<Typ_Danych> *pom = new Wezel<Typ_Danych>; /* Dynamiczne utworzenie wezla z wartoscia
                                                    zadanego typu wykorzystujac wskaznik
                                                    pomocniczy.*/
    pom->Ustaw_Wartosc(Wartosc); // Przypisanie obiektowi pozadanej wartosci
    pom->Ustaw_Klucz(Klucz); // Przypisanie obiektowi pozadanego klucza
    pom->Ustaw_Nastepny(nullptr); // Odpowiednie zainicjowanie wskaznikow
    pom->Ustaw_Poprzedni(this->Ostatni_Pom);             
    if(this->Czy_Pusta()) //Przypadek pustej kolejki
    {
        this->Ostatni_Pom = pom; /* Obiekt zostaje dodany zamiast obecnie wskazywanej wartosci przez
                                    wskaznik Ostatni (czyli zamiast null)*/
        this->Pierwszy_Pom = this->Ostatni_Pom;   /* Obiekt jest jedynym elementem, wiec jest zarowno pierwszy
                                                    jak i ostatni.*/ 
    }
    else //Przypadek co najmniej jednego wezla
    {   
        this->Ostatni_Pom->Ustaw_Nastepny(pom); //Obecny ostatni element wskazuje na nowy ostatni element
        this->Ostatni_Pom = pom; //Wskaznik Ostatni wskazuje na nowy ostatni element    
    }
    this->rozmiar++; // Zwiekszenie zapisywanego rozmiaru kolejki
}


/*!
 * Metoda umozliwiajaca dynamiczne dodanie elementu na poczatek kolejki
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie
 * Argumenty:
 *      Wartosc - Referencja do niemodyfikowalnej wartosci zadanego typu
 *      Klucz   - Referencja do niemodyfikowalnej wartosci klucza   
 */
template<typename Typ_Danych>
void Kolejka_Na_Liscie<Typ_Danych>::Dodaj_Na_Poczatek(const Typ_Danych& Wartosc,const float& Klucz)
{
    Wezel<Typ_Danych> *pom = new Wezel<Typ_Danych>; /* Dynamiczne utworzenie wezla z wartoscia
                                                    zadanego typu wykorzystujac wskaznik
                                                    pomocniczy.*/
    pom->Ustaw_Wartosc(Wartosc); // Przypisanie obiektowi pozadanej wartosci
    pom->Ustaw_Klucz(Klucz); // Przypisanie obiektowi pozadanej wartosci
    pom->Ustaw_Nastepny(this->Pierwszy_Pom); // Przypisanie obiektowi pozadanej wartosci
    pom->Ustaw_Poprzedni(nullptr);            
    if(this->Czy_Pusta()) //Przypadek pustej kolejki
    {   
        this->Pierwszy_Pom = pom; /* Obiekt zostaje dodany zamiast obecnie wskazywanej wartosci przez
                            wskaznik Ostatni (czyli zamiast null)*/
        this->Ostatni_Pom = this->Pierwszy_Pom;   /* Obiekt jest jedynym elementem, wiec jest zarowno pierwszy
                                            jak i ostatni.*/ 
    }
    else //Przypadek co najmniej jednego wezla
    {   

        this->Pierwszy_Pom->Ustaw_Poprzedni(pom); //Obecny ostatni element wskazuje na nowy ostatni element
        this->Pierwszy_Pom = pom; //Wskaznik Ostatni wskazuje na nowy ostatni element    
    }
    this->rozmiar++; // Zwiekszenie zapisywanego rozmiaru kolejki
}



/*!
 * Bezparametryczny destruktor domyslny, umozliwiajacy poprawne zwolnienie pamieci
 * Argument domyslny:
 *      Modyfikowalny obiekt klasy Kolejka_Na_Liscie  
 */
template<typename Typ_Danych>
Kolejka_Na_Liscie<Typ_Danych>::~Kolejka_Na_Liscie() 
{
    while (rozmiar != 0) /*Petla powodujaca dynamiczne usuwanie elementow kolejki,
                         dopoki ta nie stanie sie pusta.*/
    {
        this->Usun_Pierwszy();
    }
    this->Ostatni_Pom = nullptr; //Usuniecie wskaznikow pomocniczych
    this->Pierwszy_Pom = nullptr;    
    delete this->Ostatni_Pom;
    delete this->Pierwszy_Pom;
}

#endif