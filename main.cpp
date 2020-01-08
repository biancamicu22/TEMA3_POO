#include <iostream>
#include <cstring>
#include <string.h>
#include <vector>
#include <typeinfo>
#include <cstdlib>

using namespace std;

int nr_locuinte;

class Locuinta
{
protected:
    string numeClient;
    int suprafataUtila;
    float discount;

public:
    Locuinta();
    Locuinta(string numeC, int suprafataU, float disc);
    Locuinta(const Locuinta&);
    ~Locuinta();

    friend istream& operator >> (istream& in, Locuinta& L)
    {
        cout<<"Numele clientului este:"<<endl;
        in>>L.numeClient;
        if(in.fail())
        {
            in.clear();
            in.ignore();
            cout<<"Ai introdus tipul de data gresit!"<<endl;
            cout<<"Numele corect al clientului este = "<<endl;
            in>>L.numeClient;
        }
        cout<<"Suprafata utila a locuintei este:"<<endl;
        in>>L.suprafataUtila;
        if(in.fail())
        {
            in.clear();
            in.ignore();
            cout<<"Ai introdus tipul de data gresit!"<<endl;
            cout<<"Suprafata utila corecta a locuintei este = "<<endl;
            in>>L.suprafataUtila;
        }
        cout<<"Discountul aplicat este:"<<endl;
        in>>L.discount;
        if(in.fail())
        {
            in.clear();
            in.ignore();
            cout<<"Ai introdus tipul de data gresit!"<<endl;
            cout<<"Discount-ul corect aplicat locuintei este = "<<endl;
            in>>L.discount;
        }
        else
        {
            if(L.discount<0 || L.discount>10)
            {
                in.clear();
                in.ignore();
                cout<<"Discount-ul se afla numai in intervalul 0-10%"<<endl;
                cout<<"Discount-ul citit corect este = "<<endl;
                in>>L.discount;
            }
        }

        return in;
    }

    virtual void afisare()
    {
        cout<<"Nume client: "<<numeClient<<endl;
        cout<<"Suprafata utila: "<<suprafataUtila<<" m^2"<<endl;
        cout<<"Discountul aplicat: "<<discount<<"%"<<endl;
    }

    Locuinta& operator= (const Locuinta& L)
    {
        if(this != &L)
        {
            numeClient = L.numeClient;
            suprafataUtila = L.suprafataUtila;
            discount = L.discount;
        }

        return *this;
    }

    virtual float Chirie()=0;
};

Locuinta::Locuinta()
{
    numeClient = "---";
    suprafataUtila = 0;
    discount = 0;
}

Locuinta::Locuinta(string numeC, int suprafataU, float disc)
{
    numeClient = numeC;
    suprafataUtila = suprafataU;
    discount = disc;
}

Locuinta::Locuinta(const Locuinta& L)
{
    this->numeClient = L.numeClient;
    this->suprafataUtila = L.suprafataUtila;
    this->discount = L.discount;

    cout<<"CC Locuinta"<<endl;
}

Locuinta::~Locuinta()
{
    cout<<endl<<"Destructor Locuinta"<<endl;
}



class Apartament : public Locuinta
{
protected:
    int etaj;
    const string tip_locuinta = "Apartament";

public:
    Apartament():Locuinta()
    {
        etaj = 0;
    }

    Apartament(string numeC, int suprafataU, int et, float disc):Locuinta(numeC, suprafataU, disc)
    {
        etaj = et;
    }

    Apartament(const Apartament& A):Locuinta(A)
    {
        etaj = A.etaj;

        cout<<"CC Apartament"<<endl;
    }

    ~Apartament()
    {
        cout<<endl<<"Destructor Apartament"<<endl;
    }

    friend istream& operator >>(istream& in, Apartament& A)
    {
        in>>(Locuinta&) A;
        cout<<"La ce etaj se afla apartamentul?: ";
        in>>A.etaj;

        return in;

    }

    void afisare()
    {
        cout<<endl;
        cout<<"Tip locuinta: "<<tip_locuinta<<endl;
        Locuinta::afisare();
        cout<<"Etajul la care se afla apartamentul: "<<etaj<<endl;
    }

    Apartament& operator= (const Apartament& A)
    {
        if(this != &A)
        {
            this->etaj = A.etaj;
            this->Locuinta::operator=(A);
        }

        return *this;
    }

    float Chirie()
    {
        int pret_inchiriere;
        int ok;
        float chirie_apartament;
        cout<<"Care este pretul de inchiriere pe metru patrat?"<<endl;
        cin>>pret_inchiriere;
        cout<<"Se aplica discount?"<<endl;
        cin>>ok;
        chirie_apartament = pret_inchiriere * suprafataUtila * (1 - ok * discount/100.0);

        if(ok==0 || ok==1)
        {
            chirie_apartament = pret_inchiriere * suprafataUtila * (1 - ok * discount/100.0);
        }
        else
        {
            cout<<"Ai introdus valoarea gresita! Nu poti introduce decat 0 sau 1!"<<endl;
            cin.fail();
            cin.clear();
            cin.ignore();
            cin>>ok;
            chirie_apartament = pret_inchiriere * suprafataUtila * (1 - ok * discount/100.0);
        }
        cout<<"Chiria apartamentului este: "<<chirie_apartament<<endl;
    }
};


class Casa: public Locuinta
{
protected:
    int suprafataCurte;
    int nrEtaje;
    float* suprafataEtaj;
    const string tip_locuinta = "Casa";

public:
    Casa():Locuinta()
    {
        suprafataCurte = 0;
        nrEtaje = 0;
        suprafataEtaj = 0;
    }

    Casa(string numeC, int suprafataU, int suprafataC, int nrEt, float* suprafataE, float disc):Locuinta(numeC, suprafataU, disc)
    {
        suprafataCurte = suprafataC;
        nrEtaje = nrEt;
        suprafataEtaj = new float[nrEtaje+1];
        suprafataE = new float[nrEt+1];
        for(int i=0; i<nrEtaje; i++)
            suprafataEtaj[i] = suprafataE[i];
    }

    Casa(const Casa& C):Locuinta(C)
    {
        suprafataCurte = C.suprafataCurte;
        nrEtaje = C.nrEtaje;
        suprafataEtaj = new float[nrEtaje+1];
        for(int i=0; i<nrEtaje; i++)
            suprafataEtaj[i] = C.suprafataEtaj[i];

        cout<<"CC Casa"<<endl;
    }

    ~Casa()
    {
        cout<<endl<<"Destructor Casa"<<endl;
    }

    friend istream& operator >>(istream& in, Casa& C)
    {
        in>>(Locuinta&) C;
        cout<<"Suprafata curte: ";
        in>>C.suprafataCurte;
        cout<<"Numarul de etaje: ";
        in>>C.nrEtaje;
        C.suprafataEtaj = new float[C.nrEtaje+1];
        cout<<"Suprafata etajelor este:"<<endl;
        for(int i=0; i<C.nrEtaje; i++)
        {
            cout<<"Etaj "<<i+1<<": ";
            in>>C.suprafataEtaj[i];
        }

        return in;
    }

    void afisare()
    {
        cout<<endl;
        cout<<"Tip locuinta: "<<tip_locuinta<<endl;
        Locuinta::afisare();
        cout<<"Suprafata curte: "<<suprafataCurte<<" m^2"<<endl;
        cout<<"Numarul de etaje: "<<nrEtaje<<endl;
        for(int i=0; i<nrEtaje; i++)
            cout<<"Etaj "<<i+1<<": "<<suprafataEtaj[i]<<" m^2"<<endl;
    }

    Casa& operator= (const Casa& C)
    {
        if(this != &C)
        {
            this->suprafataCurte = C.suprafataCurte;
            this->nrEtaje = C.nrEtaje;
            suprafataEtaj = new float[nrEtaje+1];
            for(int i=0; i<nrEtaje; i++)
            {
                this->suprafataEtaj[i] = C. suprafataEtaj[i];
            }
            this->Locuinta::operator=(C);
        }

        return *this;
    }

    float Chirie()
    {
        int pret_inchiriere, pret_curte;
        int ok;
        float chirie_curte;
        cout<<"Care este pretul de inchiriere pe metru patrat?"<<endl;
        cin>>pret_inchiriere;
        cout<<"Care este pretul de inchiriere pe metru patrat al curtii?"<<endl;
        cin>>pret_curte;
        cout<<"Se aplica discount?"<<endl;
        cin>>ok;
        chirie_curte = pret_inchiriere * suprafataUtila * (1 - ok * discount/100.0);

        if(ok==0 || ok==1)
        {
            chirie_curte = (pret_inchiriere * suprafataUtila + pret_curte * suprafataCurte) * (1 - ok * discount/100.0);
        }
        else
        {
            cout<<"Ai introdus valoarea gresita! Nu poti introduce decat 0 sau 1!"<<endl;
            cin.fail();
            cin.clear();
            cin.ignore();
            cin>>ok;
            chirie_curte = (pret_inchiriere * suprafataUtila + pret_curte * suprafataCurte) * (1 - ok * discount/100.0);
        }
        cout<<"Chiria casei este: "<<endl;
        return chirie_curte;
    }
};

template <class T>
class Gestiune
{
    vector < pair<T, int> > vec;
    static int id;

public:
    Gestiune();
    void citire();
    void afisare();
    Gestiune& operator +=(T ob1)
    {
        ob1.id++;
    }
};

template <class T>
int Gestiune<T>::id=0;

template <class T>
Gestiune<T>::Gestiune()
{
    id++;
}

template <class T>
void Gestiune<T>::citire()
{
    //for(i = 0; i < nr_locuinte; i++)
    //{
    T ob;
    cin>>ob;
    id+=0;
    vec.push_back(make_pair(ob,id));
    //}
}

template <class T>
void Gestiune<T>::afisare()
{
    unsigned int i;
    for(i=0; i<vec.size(); i++)
    {
        cout<<vec[i].second<<" ";
        (vec[i].first).afisare();
        cout<<endl;
    }
}

template <>
class Gestiune<Casa>
{
    Casa c;
    vector < pair<Casa, float> > casa;
    int n;
    float aux;
    float s=0;
public:
    Gestiune()
    {
        n=0;
    }

    void citire();
    void afisare();
    float* total();
};

void Gestiune<Casa>::citire()
{
    cout<<"Cate case doriti sa cititi?"<<endl;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>c;
        aux = c.Chirie();
        s = s + aux;
        casa.push_back(make_pair(c,aux));
    }
}

void Gestiune<Casa>::afisare()
{
    unsigned int i;
    cout<<"Numarul total de case este: "<<n<<endl;
    for(i=0; i<casa.size(); i++)
    {
        (casa[i].first).afisare();
        cout<<"Chiria casei este:"<<endl;
        cout<<casa[i].second<<" ";
        cout<<endl;
    }

    cout<<endl<<"Totalul obtinut de agentia imobiliara este:"<<endl;
    cout<<s<<endl;
}



void meniu_apartament();
void meniu_casa();
void meniu_gestiune();
void meniu_specializare_casa();

void meniu_apartament()
{
    Apartament A;
    int alegere;
    while(1)
    {
        cout<<endl<<"Operatii posibile asupra apartamentului:"<<endl;

        cout<<"1. Creare apartament"<<endl;

        cout<<"2. Afisare apartament"<<endl;

        cout<<"3. Verificare operatia de atribuire"<<endl;

        cout<<"4. Calcul chirie"<<endl;

        cout<<"5. Casa"<<endl;

        cout<<"6. Implementare clasa Gestiune"<<endl;

        cout<<"7. Implementare specializare Casa"<<endl;

        cout<<"8. Iesire din program"<<endl;

        cout<<endl;

        cout<<"Ce operatie doriti sa efectuati?"<<endl;

        cin>>alegere;

        switch(alegere)
        {
        case 1:
            cin>>A;
            A.afisare();
            break;

        case 2:
            cout<<"Afisare:"<<endl;
            A.afisare();
            cout<<endl;
            break;

        case 3:
        {
            Apartament A1;
            cin>>A1;
            A = A1;
            A.afisare();
            A1.afisare();
            break;
        }

        case 4:
            A.Chirie();
            break;

        case 5:
            meniu_casa();
            break;

        case 6:
            meniu_gestiune();
            break;

        case 7:
            meniu_specializare_casa();
            break;

        case 8:
            cout<<endl;
            cout<<"Iesire din program..."<<endl;
            exit(1);
            break;

        default:

            cout<<"Nu s-a putut efectua operatia. Incercati din nou!"<<endl;
        }
    }
}


void meniu_casa()
{
    Casa C;
    int alegere;
    while(1)
    {
        cout<<endl<<"Operatii posibile asupra casei:"<<endl;

        cout<<"1. Creare casa"<<endl;

        cout<<"2. Afisare casa"<<endl;

        cout<<"3. Verificare operatia de atribuire"<<endl;

        cout<<"4. Calcul chirie"<<endl;

        cout<<"5. Apartament"<<endl;

        cout<<"6. Implementare clasa Gestiune"<<endl;

        cout<<"7. Implementare specializare Casa"<<endl;

        cout<<"8. Iesire din program"<<endl;

        cout<<endl;

        cout<<"Ce operatie doriti sa efectuati?"<<endl;

        cin>>alegere;

        switch(alegere)
        {
        case 1:
            cin>>C;
            C.afisare();
            break;

        case 2:
            cout<<"Afisare:"<<endl;
            C.afisare();
            cout<<endl;
            break;

        case 3:
        {
            Casa C1;
            cin>>C1;
            C = C1;
            C.afisare();
            C1.afisare();
            break;
        }

        case 4:
            cout<<C.Chirie();
            break;

        case 5:
            meniu_apartament();
            break;

        case 6:
            meniu_gestiune();
            break;

        case 7:
            meniu_specializare_casa();
            break;

        case 8:
            cout<<endl;
            cout<<"Iesire din program..."<<endl;
            exit(1);
            break;

        default:

            cout<<"Nu s-a putut efectua operatia. Incercati din nou!"<<endl;
        }
    }
}

void meniu_gestiune()
{
    int alegere;
    while(1)
    {
        cout<<endl<<"Operatii posibile asupra apartamentului:"<<endl;

        cout<<"1. Creare gestiune"<<endl;

        cout<<"2. Apartament"<<endl;

        cout<<"3. Casa"<<endl;

        cout<<"4. Implementare specializare Casa"<<endl;

        cout<<"5. Iesire din program"<<endl;

        cout<<endl;

        cout<<"Ce operatie doriti sa efectuati?"<<endl;

        cin>>alegere;

        switch(alegere)
        {
        case 1:
            int nr_locuinte, i;
            cout<<"Cate locuinte doriti sa cititi?"<<endl;
            cin>>nr_locuinte;
            int optiune;
            for(i=0; i<nr_locuinte; i++)
            {
                cout<<"Ce tip de locuinta doriti sa cititi?"<<endl;
                cout<<"1. Apartament"<<endl;
                cout<<"2. Casa"<<endl;
                cin>>optiune;

                switch(optiune)
                {
                case 1:
                {
                    Gestiune<Apartament> ap;
                    ap.citire();
                    ap.afisare();
                    cout<<endl;
                    break;
                }

                case 2:
                {
                    Gestiune<Casa> ca;
                    ca.citire();
                    ca.afisare();
                    cout<<endl;
                    break;
                }

                default:
                    cout<<"Ati introdus valoarea gresita! Incercati din nou!"<<endl;
                }
            }
            break;

        case 2:
            meniu_apartament();
            break;

        case 3:
            meniu_casa();
            break;

        case 4:
            meniu_specializare_casa();
            break;

        case 5:
            cout<<endl;
            cout<<"Iesire din program..."<<endl;
            exit(1);
            break;

        default:

            cout<<"Nu s-a putut efectua operatia. Incercati din nou!"<<endl;
        }
    }
}

void meniu_specializare_casa()
{
    Gestiune<Casa> c;
    int alegere;
    while(1)
    {
        cout<<endl<<"Operatii posibile asupra specializarii:"<<endl;

        cout<<"1. Creare specializare"<<endl;

        cout<<"2. Afisare specializare"<<endl;

        cout<<"3. Apartament"<<endl;

        cout<<"4. Casa"<<endl;

        cout<<"5. Implementare clasa Gestiune"<<endl;

        cout<<"6. Iesire din program"<<endl;

        cout<<endl;

        cout<<"Ce operatie doriti sa efectuati?"<<endl;

        cin>>alegere;

        switch(alegere)
        {
        case 1:
            c.citire();
            c.afisare();
            break;

        case 2:
            cout<<"Afisare:"<<endl;
            c.afisare();
            cout<<endl;
            break;

        case 3:
            meniu_apartament();
            break;

        case 4:
            meniu_casa();
            break;

        case 5:
            meniu_gestiune();
            break;

        case 6:
            cout<<endl;
            cout<<"Iesire din program..."<<endl;
            exit(1);
            break;

        default:

            cout<<"Nu s-a putut efectua operatia. Incercati din nou!"<<endl;
        }
    }
}

int main()
{
    ///Locuinta
    /*Locuinta L1, L2;
    cin>>L1;
    cin>>L2;
    L1 = L2;
    L1.afisare();
    L2.afisare();

    /*Locuinta L1;
    cin>>L1;
    L1.afisare();*/


    ///Apartament
    /*Apartament A;
    cin>>A;
    A.afisare();

    Apartament A1, A2;
    cin>>A1>>A2;
    A1 = A2;
    A1.afisare();
    A2.afisare();*/

    /*Apartament A;
    cin>>A;
    A.afisare();
    A.Chirie();*/

    ///Casa
    /*Casa C;
    cin>>C;
    C.afisare();*/

    /*Casa C1, C2;
    cin>>C1>>C2;
    C1 = C2;
    C1.afisare();
    C2.afisare();*/

    /*Casa C;
    cin>>C;
    C.afisare();
    C.Chirie();*/

    ///Gestiune
    /*int nr_locuinte, i;
    cout<<"Cate locuinte doriti sa cititi?"<<endl;
    cin>>nr_locuinte;
    int optiune;
    for(i=0; i<nr_locuinte; i++)
    {
        cout<<"Ce tip de locuinta doriti sa cititi?"<<endl;
        cout<<"1. Apartament"<<endl;
        cout<<"2. Casa"<<endl;
        cin>>optiune;

        switch(optiune)
        {
        case 1:
        {
            Gestiune<Apartament> ap;
            ap.citire();
            ap.afisare();
            cout<<endl;
            break;
        }

        case 2:
        {
            Gestiune<Casa> casa;
            casa.citire();
            casa.afisare();
            cout<<endl;
            break;
        }

        default:
            cout<<"Ati introdus valoarea gresita! Incercati din nou!"<<endl;
        }
    }*/

    ///Specializare Casa
    /*Gestiune<Casa> c;
    c.citire();
    c.afisare();*/

    int choice;

    while(1)
    {
        cout<<"Operatii posibile:"<<endl;

        cout<<"1. Apartament"<<endl;

        cout<<"2. Casa"<<endl;

        cout<<"3. Clasa Gestiune"<<endl;

        cout<<"4. Specializare Casa"<<endl;

        cout<<"5. Iesire"<<endl;

        cout<<endl;

        cout<<"Ce operatie doriti sa efectuati?"<<endl;

        cin>>choice;

        switch(choice)
        {
        case 1:
            meniu_apartament();
            break;

        case 2:
            meniu_casa();
            break;

        case 3:
            meniu_gestiune();
            break;

        case 4:
            meniu_specializare_casa();
            break;

        case 5:
            cout<<endl;
            cout<<"Iesire din program..."<<endl;
            exit(1);
            break;

        default:
            cout<<"Nu s-a putut efectua operatia! Incercati din nou!"<<endl;

        }
    }

    return 0;
}
