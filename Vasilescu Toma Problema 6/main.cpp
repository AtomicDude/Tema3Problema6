#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>

using namespace std;

class Farmacie  {
protected:
    string denumire;
    int nr_angajati, profituri_lunare;
public:
    Farmacie();
    ~Farmacie();
    Farmacie &operator = ( const Farmacie );
    friend istream& operator >> ( istream & , Farmacie & );
    friend ostream& operator << ( ostream & , Farmacie & );
    virtual void afisare () {
        cout << "Numele farmaciei: " << denumire;
        cout << "Numarul de angajati: " << nr_angajati;
        cout << "Profit lunar: " << profituri_lunare;
    }
    friend class FarmacieOffline;
    friend class FarmacieOnline;
};

class FarmacieOffline : public Farmacie {
protected:
    string adresa;
public:
    FarmacieOffline() : Farmacie () {
        adresa = '\0';
    }
    ~FarmacieOffline();
    void afisare () {
        cout << "Adresa farmaciei este: " << adresa;
        ( Farmacie & ) *this;
    }
    FarmacieOffline &operator = ( const FarmacieOffline & );
    friend istream& operator >> ( istream & , FarmacieOffline & );
    friend ostream& operator << ( ostream & , FarmacieOffline & );
    friend class Farmacie;
};

class FarmacieOnline : public Farmacie {
protected:
    string adresa_web;
    int nr_vizitatori;
    float discount;
public:
    FarmacieOnline() : Farmacie () {
    adresa_web = '\0';
    nr_vizitatori = 0;
    discount = 0;
    }
    ~FarmacieOnline();
    FarmacieOnline &operator = ( const FarmacieOnline & );
    friend istream& operator >> ( istream & , FarmacieOnline & );
    friend ostream& operator << ( ostream & , FarmacieOnline & );
    friend class Farmacie;
    int nrvizitatori () {
        return nr_vizitatori;
    }
};

void exceptie ( int a ) {
    try {
        if ( typeid ( a ) != typeid ( int ) )
            throw 1;
    }
    catch ( int i ) {
        cout << "Nu este un numar";
        terminate ();
    }
}

Farmacie :: Farmacie () {
    denumire = '\0';
    nr_angajati = 0;
    profituri_lunare = 0;
}

Farmacie :: ~Farmacie () {}

Farmacie& Farmacie :: operator = ( const Farmacie a ) {
    this -> denumire = a.denumire;
    this -> nr_angajati = a.nr_angajati;
    this -> profituri_lunare = a.profituri_lunare;
    return *this;
}

istream& operator >> ( istream& in , Farmacie &a ) {
    cout << "Introduceti numele farmaciei: ";
    in >> a.denumire;
    cout << "Introduceti numarul de angajati: ";
    in >> a.nr_angajati; exceptie ( a.nr_angajati );
    cout << "Introduceti profitul lunar: ";
    in >> a.profituri_lunare;
    return in;
}

ostream& operator << ( ostream& out , Farmacie &a ) {
    out << "Numele farmaciei este: " << a.denumire << ".";
        out << endl << "Farmacia are " << a.nr_angajati << " angajati.";
        out << endl << "Profiturile lunare sunt: " << a.profituri_lunare << " lei.";
        return out;
}

FarmacieOffline :: ~FarmacieOffline () {};

FarmacieOffline &FarmacieOffline :: operator = ( const FarmacieOffline &a ) {
    adresa = a.adresa;
    Farmacie :: operator = ( a );
    return *this;
}

istream& operator >> ( istream& in , FarmacieOffline &a ) {
    cout << "Introduceti adresa: ";
    in >>  a.adresa;
    in >> ( Farmacie & ) a;
    return in;
}

ostream& operator << ( ostream &out , FarmacieOffline &a ) {
    out << "Adresa Farmaciei este: " << a.adresa;
    out << endl << ( Farmacie & ) a;
    return out;
}

FarmacieOnline :: ~FarmacieOnline () {}

FarmacieOnline &FarmacieOnline :: operator = ( const FarmacieOnline &a ) {
    adresa_web = a.adresa_web;
    nr_vizitatori = a.nr_vizitatori;
    discount = a.discount;
    Farmacie :: operator = ( a );
    return *this;
}

istream& operator >> ( istream& in , FarmacieOnline &a ) {
    cout << "Introduceti adresa web a site-ului: ";
    in >> a.adresa_web;
    cout << endl << "Introduceti numarul de vizitatori: ";
    in >> a.nr_vizitatori;
    cout << endl << "Introduceti discount-ul:";
    in >> a.discount;
    in >> ( Farmacie& ) a;
    return in;
}

ostream& operator << ( ostream& out , FarmacieOnline &a ) {
    out << "Adresa web a site-ului este: " << a.adresa_web;
    out << endl << "Numarul de vizitatori este: " << a.nr_vizitatori;
    out << endl << "Discount-ul este: " << a.discount;
    out << endl << a;
    return out;
}

template < class Gestionare > class GestionareFarmacii;
template < class Gestionare > istream& operator >> ( istream& , GestionareFarmacii <Gestionare>& );
template < class Gestionare > ostream& operator << ( ostream& , GestionareFarmacii <Gestionare>& );


template < class Gestionare >
class GestionareFarmacii {
    int index_farmacie;
    const Gestionare id_lant_farmacie;
    list < FarmacieOnline > Fon;
    list < FarmacieOffline > Foff;
    static int lant;
public:
    GestionareFarmacii ();
    GestionareFarmacii ( Gestionare a ) : id_lant_farmacie( a ) {
        index_farmacie = 0;
    }
    ~GestionareFarmacii ();
    void operator = ( const GestionareFarmacii < Gestionare >& );
    void operator += ( Gestionare );
    friend istream& operator >> < Gestionare > ( istream& , GestionareFarmacii < Gestionare >& );
    friend ostream& operator << < Gestionare > ( ostream& , GestionareFarmacii < Gestionare >& );
    static void nr_lanturi ( int a ) {
    lant = a;
    }
    //get_fon () const {  }
};

template < class Gestionare > int GestionareFarmacii < Gestionare > :: lant = 0;

template <>
class GestionareFarmacii < FarmacieOnline > {
    //list < FarmacieOnline > Fon;
    int nr_total_vizitatori;
public:
    GestionareFarmacii ( list < FarmacieOnline> &a ) {
        nr_total_vizitatori = 0;
        list < FarmacieOnline > :: iterator it;
        for ( it = a.begin(); it != a.end(); it ++ )
            nr_total_vizitatori = nr_total_vizitatori + ( *it ).nrvizitatori();
    }
    ~GestionareFarmacii () {}
    void afisare_nr_total_vizitatori () {
        cout << "Numarul total de vizitatori este: " << nr_total_vizitatori << endl;
    }
};

template < class Gestionare >
GestionareFarmacii < Gestionare > :: GestionareFarmacii () {
    index_farmacie = 0;
}

template < class Gestionare >
GestionareFarmacii < Gestionare > :: ~GestionareFarmacii () {
}

template < class Gestionare >
void GestionareFarmacii < Gestionare > :: operator = ( const GestionareFarmacii < Gestionare > &a ) {
    index_farmacie = a.index_farmacie;
    Fon = a.Fon;
    Foff = a.Foff;
}

template < class Gestionare >
istream& operator >> ( istream& in , GestionareFarmacii < Gestionare > &a ) {
    int tip, contor = 1;
    FarmacieOnline temp_online;
    FarmacieOffline temp_offline;
    while ( contor == 1 ) {
        cout << "Ce tip de farmacie doriti sa introduceti?" << endl;
        cout << "1. Farmacie Online" << endl;
        cout << "2. Farmacie Offline" << endl;
        cout << "3. exit";
        cout << ">: "; cin >> tip;
        switch ( tip ) {
            case 1:
                a.index_farmacie ++;
                in >> temp_online;
                a.Fon.push_back ( temp_online );
                break;
            case 2:
                a.index_farmacie ++;
                in >> temp_offline;
                a.Foff.push_back ( temp_offline );
                break;
            case 3:
                contor = 0;
                break;
        }
    }
    return in;
}

template < class Gestionare >
ostream& operator << ( ostream& out , GestionareFarmacii < Gestionare > &a ) {
    list < FarmacieOnline > :: iterator it_online;
    list < FarmacieOffline > :: iterator it_offline;
    for ( it_online = a.Fon.begin(); it_online != a.Fon.end(); it_online++ )
        out << *it_online;
    for ( it_offline = a.Foff.begin(); it_offline != a.Foff.end(); it_offline ++ )
        out << *it_offline;
    return out;
}

template < class Gestionare >
void GestionareFarmacii < Gestionare > :: operator += ( Gestionare a ) {
    index_farmacie++;
    Fon.push_back( a );
}

template < class Gestionare >
void citire_lant ( vector < GestionareFarmacii < Gestionare > > &a , int nr_lanturi ) {
    int cit;
    for ( int i = 1; i <= nr_lanturi; i ++ ) {
        cout << "Introduceti un id pentru lantul " << i << endl;
        cin >> cit;
        a.push_back ( GestionareFarmacii < Gestionare > ( cit ) );
    }
    typename vector < GestionareFarmacii < Gestionare > > :: iterator it_lant;
    for ( it_lant = a.begin(); it_lant != a.end(); it_lant ++ )
        cin >> *it_lant;
    for ( it_lant = a.begin(); it_lant != a.end(); it_lant ++ )
        cout << *it_lant;
    list < GestionareFarmacii < FarmacieOnline > > b;
    list < GestionareFarmacii < FarmacieOnline > > :: iterator spec;
    for ( it_lant = a.begin(); it_lant != a.end(); it_lant ++ ) {
        //GestionareFarmacii < FarmacieOnline > c ( *it_lant -> Fon );
        //b.push_back ( GestionareFarmacii < FarmacieOnline > c );
    }
    for ( spec = b.begin(); spec != b.end(); spec ++ )
        spec -> afisare_nr_total_vizitatori ();
}

int main()
{
    int nr_lanturi;
    vector < GestionareFarmacii < int > > a;
    cout << "Introduceti numarul de lanturi de farmacii: ";
    cin >> nr_lanturi;
    GestionareFarmacii < int > :: nr_lanturi ( nr_lanturi );
    citire_lant ( a, nr_lanturi );
    return 0;
}
