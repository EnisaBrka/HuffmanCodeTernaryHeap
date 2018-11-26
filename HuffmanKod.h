#ifndef HUFFMANKOD_H
#define HUFFMANKOD_H
#include <string>
#include <map>
#include "TernarniHeap.h"
#include "HuffmanCvor.h"
using namespace std;

class HuffmanKod{
private:
	string podatak;
	string kodirano;
	TernarniHeap* heap;
	map<char, int> tabelaFrekvencije;
	map<char, string> HTabela;
	void napraviTabelu();
	void napraviHeap();
	void dajHkod(HuffmanCvor*, string);
	void kodiraj();
public:
	HuffmanKod(string);
	~HuffmanKod();
	string dajIzvorniString()						{return podatak;};
	string dajKodiranString()						{return kodirano;};
	void prikaziTabelu();
	void prikaziHeap();
	void prikaziHTabelu();
	string dekodiraj(string);
	void isprazniHeap()								{heap->isprazniHeap();};
};
#endif // HUFFMANKOD_H
