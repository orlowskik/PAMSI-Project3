#include "AListGraph.h"


Node<Edge*>* Vertex::addAdjacency(Edge* newIncidentEdge){
    return AdjacencyList.addFront(newIncidentEdge);
}

void Vertex::removeAdjacency(Node<Edge*>* AdjEdge){
    AdjacencyList.removeElem(AdjEdge);
}


Vertex* AdjacencyListGraph::insertVertex(Type o){
    auto newNode = VList.addFront(Vertex(o));       // Alokacja pamieci na wezel listy i wierzcholek
    auto newVertex = newNode->elem;                 // Stworzenie nowego wierzcholka - nadanie wartosci
    newVertex->position = newNode;                  // Ustawienie referencji do listy
    newVertex->number = _size;                      // Ustawienie numeru wierzcholka
    ++_size;                                        // Zwiekszenie rozmiaru grafu

    return newVertex;
}


Edge* AdjacencyListGraph::insertEdge(Vertex* v, Vertex* w, Type o){
    auto newNode = EList.addFront(Edge(v,w,o));     //Alokacja pamieci na wezel listy krawedzi i krawedz
    auto newEdge = newNode->elem;                   //Nadanie wartosci krawedzi
    auto newV1   = v->addAdjacency(newEdge);        //Ustawienie listy incydencji
    auto newV2   = w->addAdjacency(newEdge);        

    newEdge->AdjNode1 = newV1;                      //Dodanie referencji do listy incydencji
    newEdge->AdjNode2 = newV2;
    newEdge->position = newNode;                    //Dodanie referencji do listy wierzcholkow

    return newEdge;

}

//Usuwanie krawedzi i wpisow w listach incydencji
void AdjacencyListGraph::removeEdge(Edge* e){
    e->V1->removeAdjacency(e->AdjNode1);
    e->V2->removeAdjacency(e->AdjNode2);
    EList.removeElem(e->position);

}

//Usuwanie wierzcholka i incydentnych krawedzi
void AdjacencyListGraph::removeVertex(Vertex* v){
    auto vertexAdj = v->incidentEdges();

    for(auto tmp = vertexAdj.front(); tmp; tmp = tmp->next()){  //usuwanie wszystkich krawedzi polaczonych z wierzcholkiem
        auto incidentEdge = *(tmp->elem);
        removeEdge(incidentEdge);
    }
    VList.removeElem(v->position);  //usuwanie samego wierzcholka
}

//przeciwstawne wierzcholki
Vertex* AdjacencyListGraph::opposite(Vertex* v, Edge* e){
    if(e->V1 == v)
        return e->V2;
    else
        return e->V1;
}

VPairPtr AdjacencyListGraph::endVertices(Edge* e){
    return VPairPtr(e->V1,e->V2);
}

// Sprawdzenie polaczenia miedzy wierzcholkami
bool AdjacencyListGraph::areAdjacent(Vertex* v1, Vertex* v2){
    if(v1->AdjacencyList.empty() || v2->AdjacencyList.empty())      // Jezeli dowolna lista incydencji jest pusta nie ma sensu sprawdzac
        return false;
    auto tmp = v1->AdjacencyList.front();       //sprawdzanie polaczen z listy incydencji pierwszego wierzcholka
    while(tmp != v1->AdjacencyList.end()){
        auto t1 = *tmp->elem;
        if(t1->V1 == v2 || t1->V2 == v2)
            return true;
        tmp = tmp->next();
    }
    auto t1 = *tmp->elem;
    if(t1->V1 == v2 || t1->V2 == v2)
        return true;

    return false;       // Jezeli nie znaleziono polaczenia zwraca falsz
}


void AdjacencyListGraph::replace(Vertex* v,Type x){
    v->value = x;
}


void AdjacencyListGraph::replace(Edge* e,Type x){
    e->value = x;
}




List<Edge> AdjacencyListGraph::incidentEdges(Vertex* v){
    List<Edge> result;
    for(auto tmp = v->AdjacencyList.front();tmp;tmp = tmp->next()){
        auto edgePtr = *(tmp->elem);
        result.addFront(*edgePtr);
    }
    return result;
}


List<Edge> AdjacencyListGraph::edges(){
    return EList;
}

List<Vertex> AdjacencyListGraph::verticies(){
    return VList;
}