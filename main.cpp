#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstring>
using namespace std;
///istream fin("date.in");
///ofstream fout("date.out");
const int nmax=1001;
struct abc
{
    int val,poz;
} a;
class Nod
{
    int info;
    Nod *next;
public:
    Nod(const int x=0,Nod *urmator=NULL)
    {
        info = x;
        next = urmator;
    }
    ~Nod()
    {
        next = NULL;
    }
    inline Nod* get_next() const
    {
        return next;
    }
    inline int get_info() const
    {
        return info;
    }
    void set_next(Nod* urmator)
    {
        next = urmator;
    }
    void set_info(const int x)
    {
        info = x;
    }
};
class Lista_circulara
{
private:
    Nod *first=NULL;
    Nod *last;
    Nod *copie_de_parcurs;
public:
    Lista_circulara()
    {
        first=NULL;
    }
    ~Lista_circulara()
    {
        copie_de_parcurs = first->get_next();
        Nod *x;
        while(copie_de_parcurs!=first)
        {
            x = copie_de_parcurs;
            copie_de_parcurs=copie_de_parcurs->get_next();
            delete x;
        }
        delete first;
    }
    Lista_circulara(const Lista_circulara &lista) ///constructor de copiere
    {
        Nod *listaPrim = lista.first;
        Nod *prim;
        prim = new Nod;
        prim->set_info(listaPrim->get_info());
        Nod *p = listaPrim->get_next();
        Nod *parcurgere, *precedent = prim;
        while (p != listaPrim)
        {
            parcurgere = new Nod;
            parcurgere->set_info(p->get_info());
            precedent->set_next(parcurgere);
            precedent = parcurgere;
            p = p->get_next();
        }
        precedent->set_next(prim);
    }
    void Adauga_element(int element,int pozitie)
    {
        if (first == NULL)
        {
            first = new Nod();
            first->set_info(element);
            first->set_next(first);
        }
        else
        {
            Nod *r, *q;
            r = first;
            for (int i=1; i<=pozitie-2; i++)
                r=r->get_next();
            q = new Nod;
            q->set_info(element);
            q->set_next(r->get_next());
            r->set_next(q);
        }
    }
    void Stergere_element(int pozitie)
    {
        Nod *r, *q;
        if (pozitie == 1)
        {
            r = first;
            while (r->get_next()!=first)
                r = r->get_next();
            q = first;
            first = first->get_next();
            r->set_next(first);
            delete q;
        }
        else
        {
            r = first;
            for (int i=1; i<=pozitie-2; i++)
                r = r->get_next();
            q = r->get_next();
            r->set_next(r->get_next()->get_next());
            delete q;
        }
    }
    void Inversare_legaturi()
    {
        Nod *list=last;
        Nod *temporara = list;
        Nod *inversa = NULL;
        while(temporara != NULL)
        {
            list = list->get_next();
            temporara->set_next(inversa);
            inversa = temporara;
            temporara = list;
        }
        first=inversa;
    }
    void afisare()
    {
        if(!first)
            cout<<"[]";
        else
        {
            copie_de_parcurs=first->get_next();
            cout<<first->get_info()<<" ";
            while(copie_de_parcurs!=first)
            {
                cout<<copie_de_parcurs->get_info()<<" ";
                copie_de_parcurs=copie_de_parcurs->get_next();
            }
        }
         cout<<endl;
    }
    /* Transforma_in_Circulara()
    {
        copie_de_parcurs=first;
        while(copie_de_parcurs->get_next())
            copie_de_parcurs=copie_de_parcurs->get_next();
        copie_de_parcurs->set_next(first);
        last=copie_de_parcurs;
        copie_de_parcurs=first;
    }*/
    void Elimina_elemente(int k)
    {
        Nod *q;
        copie_de_parcurs=first->get_next();
        int total=1,eliminate=0;
        while(copie_de_parcurs!=first)
        {
            ++total;
            copie_de_parcurs=copie_de_parcurs->get_next();
        }
        copie_de_parcurs=first;
        int contor=0;
        if(k>1)
        {
            while(total!=eliminate)
            {
                while(copie_de_parcurs)
                {
                    // if(!poz[i])
                    contor++;
                    if(contor+1==k)
                    {
                        cout<<copie_de_parcurs->get_next()->get_info()<<" ";
                        q=copie_de_parcurs->get_next();
                        contor=0;
                        ++eliminate;
                        //poz[i]=true;
                        if(q==first)
                            first=first->get_next();
                        copie_de_parcurs->set_next(copie_de_parcurs->get_next()->get_next());
                        delete q;
                    }
                    if(copie_de_parcurs->get_next()!=NULL)
                        copie_de_parcurs=copie_de_parcurs->get_next();
                    if(eliminate==total)
                        {
                            Stergere_element(1);
                            break;
                        }
                }
            }
        }
        else
        {
            Nod *p;
            p=first;
            while(p)
            {
                ++eliminate;
                cout<<p->get_info()<<' ';
                p=p->get_next();
                Stergere_element(1);
                if(eliminate==total)
                    break;
            }
        }

    }
    Lista_circulara operator + (const Lista_circulara &lista_de_adaugat)
    {
        Lista_circulara lista_finala;
        int cnt=1;
        copie_de_parcurs = first->get_next();
        lista_finala.Adauga_element(first->get_info(),cnt++);
        while(copie_de_parcurs!=first)
        {
            lista_finala.Adauga_element(copie_de_parcurs->get_info(),cnt++);
            copie_de_parcurs=copie_de_parcurs->get_next();
        }
        copie_de_parcurs = lista_de_adaugat.first->get_next();
        lista_finala.Adauga_element(lista_de_adaugat.first->get_info(),cnt++);
        while(copie_de_parcurs!=lista_de_adaugat.first)
        {
            lista_finala.Adauga_element(copie_de_parcurs->get_info(),cnt++);
            copie_de_parcurs=copie_de_parcurs->get_next();

        }
        return lista_finala;
    }
    friend istream &operator >> (istream& input,Lista_circulara &lista);
    friend ostream &operator << (ostream& output,const Lista_circulara &lista);
};
ostream& operator << (ostream& output,const Lista_circulara &lista)
{
    Nod* curent = lista.first->get_next();
    output<<lista.first<<' ';
    while(curent != lista.first)
    {
        output<<curent->get_info()<<' ';
        curent=curent ->get_next();
    }
    return output;
}
istream& operator >> (istream& input,  Lista_circulara &lista)
{
    int valoare,pozitie;
    input >> valoare >> pozitie;
    lista.Adauga_element(valoare,pozitie);
    return input;
}
Lista_circulara& operator >> (Lista_circulara &lista,  const abc b)
{
    lista.Adauga_element(b.val,b.poz);
    return lista;
}
int main()
{
    abc b;
    a.poz=1;
    a.val=5;
    b.poz=2;
    b.val=6;
    Lista_circulara lista2,lista3;
    lista2.Adauga_element(1,1);
    lista2.Adauga_element(2,2);
    lista2.Adauga_element(3,3);
    lista2.Adauga_element(4,4);
    lista2.afisare();
    lista3>>a>>b;
    lista3.afisare();
    Lista_circulara lista4=lista2+lista3;
    lista4.afisare();
    lista4.Inversare_legaturi();
    lista4.afisare();
    lista4.Elimina_elemente(2);
    lista4.afisare();
    return 0;
}
