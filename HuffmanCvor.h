#ifndef HUFFMANCVOR_H
#define HUFFMANCVOR_H

#include <iostream>
#include <string>
#include <ostream>
using namespace std;

class HuffmanCvor
{
    private:
        int frekvencija;
        char slovo;
        string kod;
        HuffmanCvor *lijevi,*srednji,*desni;
    public:
        HuffmanCvor();
        HuffmanCvor(char,int);
        HuffmanCvor(HuffmanCvor*,HuffmanCvor*,HuffmanCvor*);
        HuffmanCvor(const HuffmanCvor&);                            //konstruktor kopije
        virtual ~HuffmanCvor();

        int dajFrekvenciju(){return frekvencija;};
        char dajSlovo(){return slovo;};
        string dajKod(){return kod;};
        HuffmanCvor* dajLijevi(){return lijevi;};
        HuffmanCvor* dajSrednji(){return srednji;};
        HuffmanCvor* dajDesni(){return desni;};

        void postaviHuffmanovKod(string s){kod=s;};
        friend ostream& operator<<(ostream&,const HuffmanCvor&);
        HuffmanCvor& operator=(const HuffmanCvor&);                 //operator dodjele

};

#endif // HUFFMANCVOR_H
