#ifndef TERNARNIHEAP_H
#define TERNARNIHEAP_H
#include "HuffmanCvor.h"
#include <vector>

class TernarniHeap
{
    private:
        HuffmanCvor** m;
        int velicina;
        int kapacitet;

        void percUp(int);
        void percDown(int);
        int brojDjece(int);

        void inOrder(int);
        void postOrder(int);
        void preOrder(int);
    public:
        TernarniHeap(int);
        void insert(HuffmanCvor*);
        HuffmanCvor* ukloniMax();
        HuffmanCvor peekMax();

        bool prazno();

        int dajVelicinuHeapa(){return velicina;};
        HuffmanCvor* dajKorijen(){return m[0];};

        virtual ~TernarniHeap();


        	//traversal
	//not really necessary for Huffman, left for debug purposes
	void inOrderTraversal();
	void postOrderTraversal();
	void preOrderTraversal();
	void linearDisplay();
        void isprazniHeap();

};

#endif // TERNARNIHEAP_H
