#include <iostream>
#include <fstream>
#include <string>
#include "HuffmanKod.h"
using namespace std;

void UnosElemenata()
{
    int n;
    cout<<"Unijeti broj elemenata: ";
    cin>>n;
    char simbol[n];
    int frekvencija[n];
    ofstream input;
    input.open("uneseni_elementi.txt", ios::trunc);
    if(input.is_open())
    {
    for(int i=0;i<n;i++)
        {
            cout<<"Unijeti simbol: "<<'\t';
            cin>>simbol[i];
            cout<<"Unijeti njegovu frekvenciju: "<<'\t';
            cin>>frekvencija[i];
            input<<simbol[i]<<'\t'<<frekvencija[i]<<endl;
        }
    }
    input.close();
}

void UcitavanjeIzFajla(){
    ifstream ucitaj;
    ucitaj.open("uneseni_elementi.txt");
    char slovo;
    int frekvencija;
    string podatak;
    while(true){
        ucitaj>>slovo>>frekvencija;
        if(ucitaj.eof()) break;
        for(int i=0; i<frekvencija; ++i){
            podatak=podatak+slovo;
            cout<<"<<<<<<<"<<podatak<<endl;
        }
      //  cerr<<slovo<<'\t'<<frekvencija<<endl;
    }

    ucitaj.close();
    cerr<<"podatak je: "<<podatak<<endl;
    HuffmanKod* test = new HuffmanKod(podatak);
    test->prikaziTabelu();
	test->prikaziHTabelu();
	string kod = test->dajKodiranString();
	cout<<"Kodiran string: "<<kod<<endl;
	cout<<"Dekodiran string: "<<test->dekodiraj(kod)<<endl;
	delete test;
}

void Ucitavanje(){
    HuffmanKod* test = new HuffmanKod("neki string"); //sprema u podatak
	test->prikaziTabelu();
	test->prikaziHTabelu();
	string kod = test->dajKodiranString();
	cout<<"Kodiran string: "<<kod<<endl;
	cout<<"Dekodiran string: "<<test->dekodiraj(kod)<<endl;
	delete test;
}

int main(){
    cout<<"Odabrati željenu opciju:"<<endl;
    cout<<"1: Unos elemenata"<<endl;
    cout<<"2: Učitavanje elemenata iz datoteke"<<endl;
    cout<<"3: Uneseni tekst iz kojeg se uzimaju simboli i njihove frekvencije"<<endl;
    char x;
    cin>>x;
    switch(x)
    {
        case '1':
            UnosElemenata();
            UcitavanjeIzFajla();
            break;
        case '2':
            UcitavanjeIzFajla();
            break;
        case '3':
            //unijeti tekst iz kojeg se uzimaju simboli i njihove frekvencije
            Ucitavanje();
            break;
        default:
            Ucitavanje();
            break;
    }

	cin.get();
	return 0;
}


