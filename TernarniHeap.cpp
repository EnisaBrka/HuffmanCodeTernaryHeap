#include "TernarniHeap.h"
#include <fstream>
#include <iterator>
#include <vector>
TernarniHeap::TernarniHeap(int size)
{
    kapacitet=size;
    velicina=0;
    //dodjeljujem velicinu heapu
    m=new HuffmanCvor*[kapacitet];
    for(int i=0;i<kapacitet;i++)
        {
            m[i]=NULL;
        }
}

TernarniHeap::~TernarniHeap()
{
    if(m!=NULL){
		for(int i = 0; i < kapacitet; i++){
			if(m[i]!=NULL){
				delete m[i];
				velicina--;
			}
		}
		delete[] m;
		cout<<"velicina heapa je (trebala bi biti nula): "<<velicina<<endl;
}
}
void TernarniHeap::insert(HuffmanCvor* hc)
{
    //provjeravamo da li je trenutna velicina heapa jednaka njegovom kapacitetu
    if(velicina==kapacitet)
        {
            cerr<<"U heapu nema više mjesta!"<<endl; //standardni ispis za greške
            return;
        }
    //a ako ima mjesta ubacujemo na kraj
    velicina++;
    m[velicina-1]=hc;
    percUp(velicina-1);
}

void TernarniHeap::percUp(int trenutni_index)
{
    int r_index; //indeks roditelja
    HuffmanCvor* temp;
    if(trenutni_index!=0) //provjeravamo da li je korijen
        {
            r_index=(trenutni_index-1)/3;
            //pravimo min heap
            if (m[r_index]->dajFrekvenciju()>m[trenutni_index]->dajFrekvenciju())
                {
                    temp=m[r_index];
                    m[r_index]=m[trenutni_index];
                    m[trenutni_index]=temp;
                    percUp(r_index);
                }
        }

}
int TernarniHeap::brojDjece(int index){
	int djeca = 0, lijevi = 3*index+1, srednji=3*index+2, desni = 3*index+3;
	if(lijevi >= velicina) return 0;
	if(m[lijevi] != NULL) djeca++;
	if(m[srednji] != NULL) djeca++;
	if (m[desni] != NULL) djeca++;
	return djeca;
}

void TernarniHeap::percDown(int trenutni_index){
	int djeca=0;
	if(djeca = brojDjece(trenutni_index)){ //provjeravamo da li smo na dnu
		HuffmanCvor* temp;
		int lijevi = 3*trenutni_index+1, srednji=3*trenutni_index+2, desni = 3*trenutni_index+3;
		switch(djeca){ //jedno, dvoje ili troje djece
			case 1:
			    //cout<<"----------------------------------------------------------1.slucaj"<<endl;
                //ako je dijete veće gurni dolje trenutni cvor
				if(m[trenutni_index]->dajFrekvenciju()>m[lijevi]->dajFrekvenciju()){
					temp = m[trenutni_index];
					m[trenutni_index] = m[lijevi];
					m[lijevi] = temp;
					percDown(lijevi);
				}
				break;
			case 2:

				if((m[trenutni_index]->dajFrekvenciju()>m[lijevi]->dajFrekvenciju()) && (m[lijevi]->dajFrekvenciju()<m[srednji]->dajFrekvenciju())){
                        cout<<"lijevo dijete"<<endl;
						temp = m[trenutni_index];
						m[trenutni_index] = m[lijevi];
						m[lijevi] = temp;
						percDown(lijevi);
					}
                if((m[trenutni_index]->dajFrekvenciju()>m[srednji]->dajFrekvenciju()) && (m[srednji]->dajFrekvenciju()<m[lijevi]->dajFrekvenciju())){
                        cout<<"srednje dijete"<<endl;
						temp = m[trenutni_index];
						m[trenutni_index] = m[srednji];
						m[srednji] = temp;
						percDown(srednji);
					}
				break;
            case 3:
				if((m[trenutni_index]->dajFrekvenciju()>m[lijevi]->dajFrekvenciju()) ||
							(m[trenutni_index]->dajFrekvenciju()>m[srednji]->dajFrekvenciju()) ||
                            (m[trenutni_index]->dajFrekvenciju()>m[desni]->dajFrekvenciju())){
					//lijevo dijete veće
					if((m[lijevi]->dajFrekvenciju()<m[desni]->dajFrekvenciju()) && (m[lijevi]->dajFrekvenciju()<m[srednji]->dajFrekvenciju())){
						temp = m[trenutni_index];
						m[trenutni_index] = m[lijevi];
						m[lijevi] = temp;
						percDown(lijevi);
					}
					//desno dijete veće
					else if((m[desni]->dajFrekvenciju()<m[lijevi]->dajFrekvenciju()) && (m[desni]->dajFrekvenciju()<m[srednji]->dajFrekvenciju())){
						temp = m[trenutni_index];
						m[trenutni_index] = m[desni];
						m[desni] = temp;
						percDown(desni);
					}
					else{ //srednje dijete veće
						temp = m[trenutni_index];
						m[trenutni_index] = m[srednji];
						m[srednji] = temp;
						percDown(srednji);
					}
				}

				//cout<<"djeca: "<<djeca<<endl;
				break;
			default:
				//cout << "greška" << endl;
				break;
		}
	}
	return;
}

HuffmanCvor* TernarniHeap::ukloniMax(){
	HuffmanCvor* vrijednost = new HuffmanCvor();
	*vrijednost = *m[0];
	//zamijeni max sa zadnjim popunjenim cvorom
	//perc down
	HuffmanCvor* temp = m[0];
	m[0] = m[velicina-1];
	m[velicina-1] = temp;
	delete m[velicina-1];
	m[velicina-1] = NULL;
	velicina--;
	percDown(0);
	return vrijednost;
}

HuffmanCvor TernarniHeap::peekMax(){
	return *m[0];
}

bool TernarniHeap::prazno(){
	return (velicina == 0);
}

void TernarniHeap::isprazniHeap(){
	while(!prazno()){
		HuffmanCvor* temp = ukloniMax();
		cout << *temp << endl;
	}
}
/*
void TernarniHeap::inOrderTraversal(){
	if(prazno()){
		cout << "Heap je prazan!" << endl;
		return;
	}
	inOrder(0);
	cout << endl;
}

void TernarniHeap::inOrder(int trenutni_index){
	//lijevi
	//trenutni
	//srednji
	//trenutni
	//desni
	if(((3*trenutni_index+1) < kapacitet) && (m[3*trenutni_index+1] != NULL)) inOrder(3*trenutni_index+1);
    cout << *m[trenutni_index] << " ";
	if(((3*trenutni_index+2) < kapacitet) && (m[3*trenutni_index+2] != NULL)) inOrder(3*trenutni_index+2);
    cout << *m[trenutni_index] << " ";
	if(((3*trenutni_index+3) < kapacitet) && (m[3*trenutni_index+3] != NULL)) inOrder(3*trenutni_index+3);
}

void TernarniHeap::postOrderTraversal(){
	if(prazno()){
		cout << "Heap je prazan!" << endl;
		return;
	}
	postOrder(0);
	cout << endl;
}

void TernarniHeap::postOrder(int trenutni_index){
	//lijevi
	//srednji
	//desni
	//trenutni
    if(((3*trenutni_index+1) < kapacitet) && (m[3*trenutni_index+1] != NULL)) inOrder(3*trenutni_index+1);
	if(((3*trenutni_index+2) < kapacitet) && (m[3*trenutni_index+2] != NULL)) inOrder(3*trenutni_index+2);
	if(((3*trenutni_index+3) < kapacitet) && (m[3*trenutni_index+3] != NULL)) inOrder(3*trenutni_index+3);
	cout << *m[trenutni_index] << " ";
}


void TernarniHeap::preOrderTraversal(){
	if(prazno()){
		cout << "Heap je prazan!" << endl;
		return;
	}
	preOrder(0);
	cout << endl;
}

void TernarniHeap::preOrder(int trenutni_index){
	//trenutni
	//lijevi
	//srednji
	//desni
    cout << *m[trenutni_index] << " ";
    if(((3*trenutni_index+1) < kapacitet) && (m[3*trenutni_index+1] != NULL)) inOrder(3*trenutni_index+1);
	if(((3*trenutni_index+2) < kapacitet) && (m[3*trenutni_index+2] != NULL)) inOrder(3*trenutni_index+2);
	if(((3*trenutni_index+3) < kapacitet) && (m[3*trenutni_index+3] != NULL)) inOrder(3*trenutni_index+3);
}


void TernarniHeap::linearDisplay(){
	for(int i = 0; i < velicina; i++){
		cout << *m[i] << " ";
	}
	cout << endl;
}
*/
