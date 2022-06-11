#include<iostream>
#include<vector>
#include "AListGraph.h"
#include "AMatrixGraph.h"
#include "PrioQueue.h"

const unsigned nVertex = 5;

// Struktura dla klastrow przy algorytmie Kruskala
struct DSNode{
    int up;
    int rank;
};
// Klasa definiujaca zbiory klastrow dla algorytmu Kruskala
class DSStruct{
    private:
        DSNode* Z;
    public:
        DSStruct(unsigned n){
            Z = new DSNode[n];
        };
        
        ~DSStruct(){
            delete []Z;
        };
        
        void MakeSet(int v){        // Tworzenie klastra
            Z[v].up = v;
            Z[v].rank = 0;
        };
        int  FindSet(int v){        // Przeszukiwanie drzewa do korzenia
            if(Z[v].up != v) Z[v].up = FindSet(Z[v].up);
            return Z[v].up;
        };
        void Union(MEdge e){        // Laczenie klastrow dal Macierzy
            int ru,rv;

            ru = FindSet(e.V1->number);
            rv = FindSet(e.V2->number);

            if(ru != rv){
                if(Z[ru].rank > Z[rv].rank)
                    Z[rv].up = ru;
                else{
                    Z[ru].up = rv;
                    if(Z[ru].rank == Z[rv].rank)
                        Z[rv].rank++;
                } 
            }
        };

        void Union(Edge e){         // Laczenie klastrow dal listy
            int ru,rv;

            ru = FindSet(e.V1->number);
            rv = FindSet(e.V2->number);

            if(ru != rv){
                if(Z[ru].rank > Z[rv].rank)
                    Z[rv].up = ru;
                else{
                    Z[ru].up = rv;
                    if(Z[ru].rank == Z[rv].rank)
                        Z[rv].rank++;
                } 
            }
        };
};


/*
    Algorytm Kruskala tworzenia minimalnego drzewa rozpinajacego dla klasy AMAtrixGraph
*/
AMatrixGraph Kruskal(AMatrixGraph& original){
    PrioList<MEdge>   prio;
    AMatrixGraph      tree;
    List<MVertex>     vertexList(original.verticies());
    List<MEdge>       edgeList(original.edges());
    DSStruct          Z(nVertex);           // Struktura klastrow drzewa
    MEdge             tmp;
    MVertex*          test_list[nVertex];
    int j = 0;

    for(int i = 0; i < nVertex ;i++){   // Stworz osobne zbiory dla kazdego wierzholka
        Z.MakeSet(i);
    }
    
    while(!edgeList.empty()){
        prio.insert(edgeList.front()->elem->value,*edgeList.front()->elem);
        edgeList.removeElem(edgeList.front());
    }

    while(!vertexList.empty()){
        test_list[j] = tree.insertVertex(vertexList.front()->elem->value);
        vertexList.removeElem(vertexList.front());
        ++j;
    }
    
    for(int n = 1; n < nVertex; n++){   
        do{                             // Eliminacja zapetlen w drzewie 
           tmp = prio.removeMin();      // wybranie krawedzi o najmniejszym koszcie 
        } while (Z.FindSet(tmp.V1->number) == Z.FindSet(tmp.V2->number));       // Przeszukanie korzeni dla wierzcholkow
        tree.insertEdge(test_list[tmp.V1->number],test_list[tmp.V2->number],tmp.value);  
        Z.Union(tmp);   //Laczenie klastrow
    }

    return tree;
};





/*
    Algorytm Kruskala tworzenia minimalnego drzewa rozpinajacego dla klasy AdjacencyListGraph
*/
AdjacencyListGraph Kruskal(AdjacencyListGraph& original){
    PrioList<Edge>     prio;
    AdjacencyListGraph tree;
    List<Vertex>       vertexList(original.verticies());
    List<Edge>         edgeList(original.edges());
    DSStruct           Z(nVertex);
    Edge               tmp;
    Vertex*            test_list[nVertex];
    int j = 0;

    

    for(int i = 0; i < nVertex ;i++){
        Z.MakeSet(i);
    }
    
    while(!edgeList.empty()){
        prio.insert(edgeList.front()->elem->value,*edgeList.front()->elem);
        edgeList.removeElem(edgeList.front());
        
    }
    
    while(!vertexList.empty()){
        test_list[j] = tree.insertVertex(vertexList.front()->elem->value);
        vertexList.removeElem(vertexList.front());
        ++j;
    }
    
    for(int n = 1; n < nVertex; n++){
        do{
           tmp = prio.removeMin();
        } while (Z.FindSet(tmp.V1->number) == Z.FindSet(tmp.V2->number));
        tree.insertEdge(test_list[tmp.V1->number],test_list[tmp.V2->number],tmp.value);
        Z.Union(tmp);
    }
    return tree;
};


/*
    Algorytm Prima tworzenia minimalnego drzewa rozpinajacego dla klasy AMAtrixGraph
*/
AMatrixGraph Prim(AMatrixGraph& original){
    MEdge             tmp;
    PrioList<MEdge>   prio;
    AMatrixGraph      tree;
    List<MVertex>     vertexList(original.verticies()); //lista wierzcholkow
    List<MVertex*>    tmpVertex;                        //tymczasowa lista do tworzenia wierzcholkow
    List<MEdge>       edgeList(original.edges());       //lista krawedzi
    MVertex*          ptr = vertexList.end()->elem;     //wskaznik na pierwszy wierzcholek;
    int i,v,j = 0;
    
    bool *visited = new bool [nVertex];         // Tablica prawdy odwiedzenia wierzcholka
    for(i=0 ; i <nVertex; i++)
        visited[i] = false;
    
    v = 0;
    visited[v] = true;
    tmpVertex.addFront(tree.insertVertex(ptr->value));
    for(i = 1; i<nVertex; i++){                             // Wykonaj dla wszystkich wierzcholkow
        List<MEdge> adjList(original.incidentEdges(ptr));   // Lista przyleglych krawedzi    
        for(auto p = adjList.front() ; p; p = p->next() ){  // Sprawdz wszystkie krawedzie
            if( !visited[p->elem->V2->number])              // Jezeli nieodwiedzony dodaj krawedz do kolejki priorytetowej
                prio.insert(p->elem->value,*p->elem);
        }
        do{
            tmp = prio.removeMin();
        }while(visited[tmp.V2->number]);            // Wybierz najmniejszy z mozliwych nieodwiedzonych wierzcholkow
        tmpVertex.addFront(tree.insertVertex(tmp.V2->value));
        tree.insertEdge(*tmpVertex.end()->elem,*tmpVertex.front()->elem,tmp.value);
        visited[tmp.V2->number] = true;         // Ustaw jako odwiedzony
        tmpVertex.removeElem(tmpVertex.end());
        ptr = tmp.V2;                           // Ustaw jako kolejny           
    }
    return tree;
}


/*
    Algorytm Prima tworzenia minimalnego drzewa rozpinajacego dla klasy AdjacencyListGraph (analoggiczny do poprzedniego)
*/
AdjacencyListGraph Prim(AdjacencyListGraph& original){
    Edge                 tmp;
    PrioList<Edge>       prio;
    AdjacencyListGraph   tree;
    List<Vertex>         vertexList(original.verticies());
    List<Vertex*>        tmpVertex;
    List<Edge>           edgeList(original.edges());
    Vertex*              ptr = vertexList.end()->elem;
    int i,v,j = 0;
    
    bool *visited = new bool [nVertex];
    for(i=0 ; i <nVertex; i++)
        visited[i] = false;
    
    v = 0;
    visited[v] = true;
    tmpVertex.addFront(tree.insertVertex(ptr->value));
    for(i = 1; i<nVertex; i++){
        List<Edge> adjList(original.incidentEdges(ptr));
        for(auto p = adjList.front() ; p; p = p->next() ){
            if( !visited[p->elem->V2->number])
                prio.insert(p->elem->value,*p->elem);
        }
        do{
            tmp = prio.removeMin();
        }while(visited[tmp.V2->number]);
        tmpVertex.addFront(tree.insertVertex(tmp.V2->value));
        tree.insertEdge(*tmpVertex.end()->elem,*tmpVertex.front()->elem,tmp.value);
        visited[tmp.V2->number] = true;
        tmpVertex.removeElem(tmpVertex.end());
        ptr = tmp.V2;    
    }


    return tree;
}

int main(){
    AdjacencyListGraph test;
    std::vector<Vertex*> vertexPtr;
    std::vector<Edge*>   edgePtr;
    
    vertexPtr.push_back(test.insertVertex(1));
    vertexPtr.push_back(test.insertVertex(2));
    vertexPtr.push_back(test.insertVertex(3));
    vertexPtr.push_back(test.insertVertex(4));
    vertexPtr.push_back(test.insertVertex(5));

    edgePtr.push_back(test.insertEdge(vertexPtr[0],vertexPtr[1],5));
    edgePtr.push_back(test.insertEdge(vertexPtr[0],vertexPtr[2],9));
    edgePtr.push_back(test.insertEdge(vertexPtr[0],vertexPtr[3],2));
    edgePtr.push_back(test.insertEdge(vertexPtr[0],vertexPtr[4],8));
    edgePtr.push_back(test.insertEdge(vertexPtr[4],vertexPtr[2],14));
    edgePtr.push_back(test.insertEdge(vertexPtr[3],vertexPtr[2],11));
    edgePtr.push_back(test.insertEdge(vertexPtr[1],vertexPtr[4],3));


    AdjacencyListGraph newtree(Prim(test));
    List<Vertex>     vertexList(newtree.verticies());
    List<Edge>       edgeList(newtree.edges());


    std::cout << "Vertex: \n";
    while(!vertexList.empty()){
        std::cout << vertexList.front()->elem->value << std::endl;
        std::cout << "Links:" << newtree.incidentEdges(vertexList.front()->elem).front()->elem->value << std::endl;
        vertexList.removeElem(vertexList.front());
    }
    
    std::cout << "Edge: \n";
    while(!edgeList.empty()){
        std::cout << edgeList.front()->elem->value << std::endl;
        edgeList.removeElem(edgeList.front());
    }
    
    std::cout << "Hurray!\n";
    return 0;
}