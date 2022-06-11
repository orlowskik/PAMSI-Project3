#include "AMatrixGraph.h"

// Konstruktor klasy. Nalezy zaalokowac pamiec na tablice i wypelnic ja zerami
AMatrixGraph::AMatrixGraph():
    AdjMatrix(new MEdge**[SIZE]),
    gSize(){
        for(unsigned i = 0; i != SIZE; ++i){
            AdjMatrix[i] = new MEdge*[SIZE];
            for(unsigned j = 0; j != SIZE; ++j){
                AdjMatrix[i][j] = nullptr;
            }
            _size = 0;
        }
}

// Destruktor klasy. Zwalnia wszystkie komorki macierzy i ja usuwa
AMatrixGraph::~AMatrixGraph(){
    for(unsigned i = 0; i != SIZE; ++i)
        delete AdjMatrix[i];
    delete AdjMatrix;
}


MVertex* AMatrixGraph::insertVertex(Type o){
    if(gSize == SIZE)       //Nie mozna przekroczyc rozmiaru macierzy 
        exit(-1);
    
    auto newNode = VList.addFront(MVertex(o,gSize));        // Alokacja pamieci na wezel listy
    ++gSize;                                                // Zwiekszenie rozmiaru (dla pozycji wierzcholkow)
    auto newVertex = newNode->elem;                         // Ustawienie nowego wierzcholka
    newVertex->position = newNode;                          // Referencja do pozycji na liscie
    newVertex->number = _size;                              // Numer wierzcholka
    ++_size;

    return newVertex;
}

//Dodanie krawedzi
MEdge* AMatrixGraph::insertEdge(MVertex* v, MVertex* w, Type o){
    auto newNode = EList.addFront(MEdge(v,w,o));                //Alokacja pamieci na wezel
    auto newEdge = newNode->elem;                               //Stworzenie nowego wierzcholka

    newEdge->position = newNode;                                //Referencja do pozycji na liscie
    
    AdjMatrix[v->matrixPos()][w->matrixPos()] = newEdge;        //Ustawienie odpowiednich rekordow w macierzy sasiedztwa
    AdjMatrix[w->matrixPos()][v->matrixPos()] = newEdge;

    return newEdge;

}

//Usuniecie krawedzi
void AMatrixGraph::removeEdge(MEdge* e){
    unsigned v1Pos = e->V1->matrixPos();
    unsigned v2Pos = e->V2->matrixPos();
    AdjMatrix[v1Pos][v2Pos] = nullptr;      //Usuniecie odpowiednich rekordow w macierzy sasiedztwa
    AdjMatrix[v2Pos][v1Pos] = nullptr;
    EList.removeElem(e->position);         // Usuniecie krawedzi

}

// Usuniecie wierzcholka i wszystkich przyleglych krawedzi
void AMatrixGraph::removeVertex(MVertex* v){
    unsigned tmp = v->matrixPos();

    for(unsigned i = 0; i!=gSize; ++i){
        MEdge** matrixPos = &(AdjMatrix[tmp][i]);       // Przeszukiwanie macierzy sasiedztwa
        if(*matrixPos){
            EList.removeElem((*matrixPos)->position);   // Jezeli znaleziono polaczenie
            *matrixPos = nullptr;
            AdjMatrix[i][tmp] = nullptr;
        }
    }
    VList.removeElem(v->position);      // Usuniecie samego wierzcholka
}

// Przeciwlegly wierzcholek wzgledem wybranej krawedzi
MVertex* AMatrixGraph::opposite(MVertex* v, MEdge* e){
    if(e->V1 == v)
        return e->V2;
    else
        return e->V1;
}

//Koncowe wierzcholki wybranej krawedzi
MVPairPtr AMatrixGraph::endVertices(MEdge* e){
    return MVPairPtr(e->V1,e->V2);
}

//Sprawdzenie sasiedztwa wybranych wierzcholkow
bool AMatrixGraph::areAdjacent(MVertex* v1, MVertex* v2){
    return AdjMatrix[v1->matrixPos()][v2->matrixPos()];   // Odczytanie odpowiedniego rekordu macierzy
}

void AMatrixGraph::replace(MVertex* v,Type x){
    v->value = x;
}

void AMatrixGraph::replace(MEdge* e,Type x){
    e->value = x;
}

List<MEdge> AMatrixGraph::incidentEdges(MVertex* v){
    List<MEdge> result;
    unsigned pos = v->matrixPos();

    for( unsigned i = 0; i!= gSize; ++i){
        auto tmp = AdjMatrix[pos][i];
        if(tmp)
            result.addFront(*tmp);
    }
    return result;
}


List<MEdge> AMatrixGraph::edges(){
    return EList;
}

List<MVertex> AMatrixGraph::verticies(){
    return VList;
};

