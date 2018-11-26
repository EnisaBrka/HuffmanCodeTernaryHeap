#include "HuffmanKod.h"
#include "HuffmanCvor.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <cstdlib>
using namespace std;

HuffmanKod::HuffmanKod(string src){
	podatak = src;
	kodirano = " ";
	heap = new TernarniHeap(podatak.length()); //proslijeðuje dužinu unesenog stringa koji treba kodirati
	cout<<"velicina heapa: "<<podatak.length()<<endl;
	napraviTabelu();
	napraviHeap();
}

HuffmanKod::~HuffmanKod(){
	if(heap != NULL) delete heap;
}

void HuffmanKod::napraviTabelu(){
    int brojac=0;
	for(int i = 0; i < podatak.length(); i++){
		char c = podatak.at(i);
		if (tabelaFrekvencije.find(podatak.at(i)) == tabelaFrekvencije.end()){
			tabelaFrekvencije.insert(pair<char, int>(c, 1));
			brojac++;
		}
		else{
			tabelaFrekvencije[c]++;
		}
	}
	if(brojac%2==0) tabelaFrekvencije.insert(pair<char, int>(' ', 0));
	//prikaziTabelu();
}





void HuffmanKod::napraviHeap(){
	for(map<char,int>::iterator it = tabelaFrekvencije.begin();
		it != tabelaFrekvencije.end(); ++it){
			heap->insert(new HuffmanCvor(it->first, it->second));
          //  cout << it->first << "\t" << it->second << endl;
	}
	//izbacujemo sve dok u heapu ne ostane samo 1 elemenat
	while(!heap->prazno()){
		if(heap->dajVelicinuHeapa() == 1) break;
		else if(heap->dajVelicinuHeapa() == 2){
		HuffmanCvor* lijevi = heap->ukloniMax();
        }
        else{
		HuffmanCvor* lijevi = heap->ukloniMax();
        HuffmanCvor* srednji = heap->ukloniMax();
        HuffmanCvor* desni = heap->ukloniMax();
        heap->insert(new HuffmanCvor(lijevi, srednji, desni));
        }
	}
	//zadnji elemenat je korijen
	string kod = "";
	dajHkod(heap->dajKorijen(), kod); //vršimo kodiranje cvorova
	kodiraj();
}

void HuffmanKod::dajHkod(HuffmanCvor* korijen, string kod){
	if(korijen->dajLijevi() == NULL){ //ako korijen nema djece, kodiramo samo njega
		korijen->postaviHuffmanovKod(kod); //pozivamo funkciju iz H. cvora da bismo cvoru dodijelili kod
		HTabela.insert(pair<char, string>(korijen->dajSlovo(), kod));
		return;
	}
    else if(korijen->dajSrednji() == NULL){ //ima samo 1 dijete
		dajHkod(korijen->dajLijevi(), kod+"0");
		}
    else if(korijen->dajDesni() == NULL){ //ima dvoje dijece
		dajHkod(korijen->dajLijevi(), kod+"0");
		dajHkod(korijen->dajSrednji(), kod+"1");
		}
	else{
		dajHkod(korijen->dajLijevi(), kod+"0");
		dajHkod(korijen->dajSrednji(), kod+"1");
		dajHkod(korijen->dajDesni(), kod+"2");
	}
}

void HuffmanKod::prikaziTabelu(){
	cout << "Tabela frekvencija:" << endl;
    ofstream tabela;
	tabela.open("tabela_frekvencija.txt", ios::trunc);
	for(map<char,int>::iterator it = tabelaFrekvencije.begin(); it != tabelaFrekvencije.end(); ++it){//slovo i frekvenciju
			cout << it->first << "\t" << it->second << endl;
			tabela << it->first << "\t" << it->second << endl;
	}
	tabela.close();
}

void HuffmanKod::prikaziHTabelu(){
	cout << "Huffmanova tabela:" << endl;
	ofstream H_tabela;
	H_tabela.open("Huffmanova_tabela.txt",ios::trunc);
	for(map<char,string>::iterator it = HTabela.begin();it != HTabela.end(); ++it){ //slovo i kod
			cout << it->first << "\t" << it->second << endl;
			H_tabela << it->first << "\t" << it->second << endl;
	}
	H_tabela.close();
}

void HuffmanKod::kodiraj(){
	ofstream k;
	k.open("kodirano.txt",ios::trunc);
	for(int i = 0; i < podatak.length(); i++){
		kodirano.append(HTabela[podatak.at(i)]); //nađi u H.T. podatak na poziciji i npr.slovo a, i daj njegov kod=>kodiran string
        k<<HTabela[podatak.at(i)];
		//kodirano.append(" ");
	}
	k.close();
}

string HuffmanKod::dekodiraj(string str){ //uzimamo kodiran string i vršimo dekodiranje na sonovu Huffmanove tabele
    string dekodiran;
    string temp=str;
    bool izlaz=true;
    string prvi;
    //int i=0;
    int j=1;
    while(str.length()!=1){
   // i++;
    prvi=str.substr(1,j);
   // cout<<"i je "<<i<<endl;
   // cout<<"j je "<<j<<endl;
   // cout<<"prvi simbol je "<<prvi<<endl;
    for(map<char,string>::iterator it = HTabela.begin(); it != HTabela.end(); ++it){
                if (it->second==prvi){
                 //   cout<<"first "<<it->first<<endl;
                //    cout<<"second "<<it->second<<endl;
                    dekodiran+=(it->first);
                   // cout<<"dekodiran je "<<dekodiran<<endl;
                    str.erase(1,it->second.length());
                 //   cout<<"string je "<<str<<endl;
                    izlaz=true;
                 //   cout<<"zzzzzzzzzzzzzzzzzzzzzzzzz "<<i<<endl;
                   // i++;
                    j--;
                    break;
                    }
                    else izlaz=false;
    }
    if(izlaz==false) j++;
    }
    ofstream pod;
    pod.open("dekodirano.txt", ios::trunc);
    pod<<dekodiran<<endl;
    pod.close();
    return dekodiran;
}
/*
void HuffmanKod::prikaziHeap(){
	heap->inOrderTraversal();
	cout<<"oooooooooooooooooooooooooooooooooooooo"<<endl;
}
*/
