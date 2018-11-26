#include "HuffmanCvor.h"
#include <fstream>
using namespace std;

HuffmanCvor::HuffmanCvor()
{
    slovo=' ';
    frekvencija=0;
    lijevi=srednji=desni=NULL;
}

HuffmanCvor::HuffmanCvor(char s,int f)
{
    slovo=s;
    frekvencija=f;
    lijevi=srednji=desni=NULL;
}

HuffmanCvor::HuffmanCvor(HuffmanCvor* lijevi, HuffmanCvor* srednji, HuffmanCvor* desni)
{
    this->lijevi=lijevi;
    this->srednji=srednji;
    this->desni=desni;
    frekvencija=lijevi->dajFrekvenciju()+srednji->dajFrekvenciju()+desni->dajFrekvenciju();
    slovo=' ';
}

HuffmanCvor::HuffmanCvor(const HuffmanCvor& elemenat) //konstruktor kopije
{
    //provjeravamo da li su proslijeðeni dijelovi elementa prazni, ako nisu kopiramo ih
    if(elemenat.lijevi!=NULL)
        {
            lijevi=new HuffmanCvor();
            *lijevi=*(elemenat.lijevi);
        }
    if(elemenat.srednji!=NULL)
        {
            srednji=new HuffmanCvor();
            *srednji=*(elemenat.srednji);
        }
    if(elemenat.desni!=NULL)
        {
            desni=new HuffmanCvor();
            *desni=*(elemenat.desni);
        }

    kod=elemenat.kod;
    slovo=elemenat.slovo;
    frekvencija=elemenat.frekvencija;
}


HuffmanCvor::~HuffmanCvor()
{
    if(lijevi!=NULL) delete lijevi;
    if(srednji!=NULL) delete srednji;
    if(desni!=NULL) delete desni;
}

ostream& operator<<(ostream& ispis,const HuffmanCvor& elemenat)
{
    ispis<<elemenat.slovo<<'\t'<<elemenat.frekvencija<<endl;
    return ispis;
}
HuffmanCvor& HuffmanCvor::operator=(const HuffmanCvor& elemenat)
{
    ofstream stablo;
    stablo.open("stablo.txt", ios::app);
    //ako trenutni elemnat, nije proslijeðeni elemenat, dodijelimo mu vrijednosti proslijeðenog elementa
    if(!(this==&elemenat))
        {
            kod=elemenat.kod;
            slovo=elemenat.slovo;
            frekvencija=elemenat.frekvencija;
            stablo<<endl<<elemenat<<endl;
            //sko lijevi, srednji i desni nisu prazni obrišemo ih
            if(!(lijevi==NULL)) delete lijevi;
            if(!(srednji==NULL)) delete srednji;
            if(!(desni==NULL)) delete desni;
            //i dodijelimo im vrijednosti od proslijeðenog elementa, ako postoje, tj. nisu prazne
            if(elemenat.lijevi!=NULL)
                {
                    lijevi=new HuffmanCvor();
                    *lijevi=*(elemenat.lijevi);
                    if(elemenat.srednji!=NULL)
                        {
                            srednji=new HuffmanCvor();
                            *srednji=*(elemenat.srednji);
                            if(elemenat.desni!=NULL)
                            {
                                desni=new HuffmanCvor();
                                *desni=*(elemenat.desni);
                            }
                        }
                }
            else lijevi=srednji=desni=NULL;
        }
        stablo<<"-----------------------------"<<endl;
    stablo.close();
    return *this;
}
