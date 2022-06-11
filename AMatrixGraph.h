#pragma once
#include "List.h"
#include "PrioQueue.h"

//Maksymalny rozmiar tablicy sasiedztwa (czyli na 1000 wierzcholkow)
const unsigned SIZE = 10000;

using Type = int;
struct MVertex;
struct MEdge;
struct MVPairPtr;

//Klasa grafu dla macierzy sasiedztwa
class AMatrixGraph{
    
    public:
        AMatrixGraph();
        ~AMatrixGraph();

        // Interfejs klasy
        MVertex* insertVertex(Type o);
        MEdge* insertEdge(MVertex* v, MVertex* w, Type o);
        void removeVertex(MVertex* v);
        void removeEdge(MEdge* e);

        MVertex* opposite(MVertex* v, MEdge* e);
        MVPairPtr endVertices(MEdge* e);
        bool areAdjacent(MVertex* v1, MVertex* v2);
        void replace(MVertex* v,Type x);
        void replace(MEdge* e,Type x);

        List<MEdge> incidentEdges(MVertex* v);
        List<MVertex> verticies();
        List<MEdge> edges();

        unsigned Size(){return _size;};
        
    private:
        List<MVertex> VList;
        List<MEdge>   EList;
        MEdge***      AdjMatrix;
        unsigned      gSize;
        unsigned      _size;
};

// Struktura wierzcholka 
struct MVertex{
    Type           value;
    Node<MVertex>* position;         //referencja do pozycji na liscie wierzcholkow
    unsigned       aMatrixPosition;  //pozycja w macierzy
    unsigned       number;           //numer wierzcholka

    MVertex(const Type& val, unsigned matrixPos):
        value(val),aMatrixPosition(matrixPos){number=0;};       //ochrona przed zrzutem pamieci

    unsigned matrixPos(){return aMatrixPosition;};
    void     matrixPos(unsigned newPos){aMatrixPosition = newPos;};
    
};


//Struktura krawedzi
struct MEdge{
    Type value;
    MVertex* V1;    //pierwszy wierzcholek
    MVertex* V2;    //drugi wierzcholek
    Node<MEdge>* position;   //referencja do listy krawedzi

    MEdge(){
        position = nullptr;
        V1 = nullptr;
        V2 = nullptr;
    }

    MEdge(MVertex* v1, MVertex* v2, const Type& val):
        value(val),V1(v1),V2(v2){};

};

// Pomocnicza struktura dwoch wierzcholkow. Ulatwienie przy zwracaniu przeciwleglych wierzcholkow
struct MVPairPtr{
    MVertex* v1Ptr;
    MVertex* v2Ptr;

    MVPairPtr(){
        v1Ptr = nullptr;
        v2Ptr = nullptr;
    }

    MVPairPtr(MVertex* v1, MVertex* v2):
        v1Ptr(v1), v2Ptr(v2){};

    bool exist(MVertex* verPtr){
        return v1Ptr == verPtr || v2Ptr == verPtr;
    }
};
