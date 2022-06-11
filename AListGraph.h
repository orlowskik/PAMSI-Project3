#pragma once
#include "List.h"
#include "PrioQueue.h"

using Type = int;  // Typ przechowywany w wierzcholkach
struct Vertex;
struct Edge;
struct VPairPtr;

// Klasa grafu
class AdjacencyListGraph{
        

    public:
        AdjacencyListGraph(){_size = 0;};   // Ochrona przed zrzutem pamieci

        //Interfejs klasy - podstawowe operacje na grafie
        Vertex* insertVertex(Type o);
        Edge* insertEdge(Vertex* v, Vertex* w, Type o);
        void removeVertex(Vertex* v);
        void removeEdge(Edge* e);

        Vertex* opposite(Vertex* v, Edge* e);
        VPairPtr endVertices(Edge* e);
        bool areAdjacent(Vertex* v1, Vertex* v2);
        void replace(Vertex* v,Type x);
        void replace(Edge* e,Type x);

        List<Edge> incidentEdges(Vertex* v);
        List<Vertex> verticies();
        List<Edge> edges();

        unsigned Size(){return _size;};

    private:
        List<Vertex> VList;
        List<Edge>   EList;
        unsigned     _size;
};

// Struktura wektora
struct Vertex{
    Type value;
    List<Edge*> AdjacencyList;  //Lista sasiedztwa
    Node<Vertex>* position;     // Referencja do pozycji na liscie
    unsigned   number;          //Numer wierzcholka

    Vertex(const Type& val):
        value(val){number = 0;};

    Node<Edge*>* addAdjacency(Edge* newIncidentEdge);
    void removeAdjacency(Node<Edge*>* AdjEdge);
    List<Edge*> incidentEdges(){
        return AdjacencyList;
    };
    
};

//Struktura krawedzi
struct Edge{
    Type value;
    Vertex* V1;             //Pierwszy wierzcholek
    Vertex* V2;             //Drugi wierzcholek
    Node<Edge>* position;   //Referencja do pozycji na liscie
    Node<Edge*>* AdjNode1;  //Wskazanie do listy sasiedztwa pierwszego wierzcholka
    Node<Edge*>* AdjNode2;  //Wskazanie do listy sasiedztwa drugiego wierzcholka

    Edge(Vertex* v1, Vertex* v2, const Type& val):
        value(val),V1(v1),V2(v2){};

    Edge(){
        position = nullptr;
        V1 = nullptr;
        V2 = nullptr;
        AdjNode1 = nullptr;
        AdjNode2 = nullptr;
    }

};

// Pomocnicza struktura dwoch wierzcholkow. Ulatwienie przy zwracaniu przeciwleglych wierzcholkow
struct VPairPtr{
    Vertex* v1Ptr;
    Vertex* v2Ptr;

    VPairPtr(){
        v1Ptr = nullptr;
        v2Ptr = nullptr;
    }

    VPairPtr(Vertex* v1, Vertex* v2):
        v1Ptr(v1), v2Ptr(v2){};

    bool exist(Vertex* verPtr){
        return v1Ptr == verPtr || v2Ptr == verPtr;
    }
};








