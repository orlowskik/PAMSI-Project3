#pragma once
#include <iostream>
#include <functional>

template <class TYPE>
class List;

template <class TYPE>
struct Node{
        TYPE*  elem;
        Node*  nextNode;
        Node*  prevNode;

        Node(TYPE* newElem, Node* prevN, Node* nextN):
            elem(newElem),
            nextNode(nextN),
            prevNode(prevN){};

        Node* next(){return nextNode;};
        Node* prev(){return prevNode;}; 
};


template <typename TYPE>
class List{
    private:
        Node<TYPE>* head; // Wskaznik na pierwszy element
        Node<TYPE>* tail; // Wskaznik na ostatni element

    public: // Interfejs klasy
        List():
            head(nullptr),
            tail(nullptr){}; // Konstruktor klasy.Ochrona przed zrzutem pamieci

        List(const List& original):
            head(nullptr), tail(nullptr)
        {
            for(auto originalPtr = original.front();originalPtr;originalPtr = originalPtr->next()){
                addEnd(*(originalPtr->elem));
            }
        }
        // Destruktor klasy. Zwalnia pamiec od poczatku listy 
        ~List(){
            for(auto tmp = head; tmp != tail;){
                auto nextNode = tmp->next();
                delete tmp->elem;
                delete tmp;
                tmp = nextNode;
            }
        }
        

        bool empty() const {return !head;}; // Funkcja sprawdzajaca, czy lista jest pusta
        Node<TYPE>* front() const {return head;};  // Funkja zwracajaca pierwszy wezel. Tylko do odczytu
        Node<TYPE>* end()   const {return tail;};  // Funkcja zwracajaca ostatni wezel. Tylko do odczytu
        Node<TYPE>* addFront(TYPE e);                    // Funkcja dodajaca element na poczatek listy
        Node<TYPE>* addEnd(TYPE e);                      // Funkcja dodajaca element na koniec listy
        void removeFront();                          // Funkca usuwajaca pierwszy element 
        void removeEnd();                            // Funkca usuwajaca ostatni element
        void removeElem(Node<TYPE>* elem);        // Funkca usuwajaca wskazany element
        Node<TYPE>* find(const TYPE& value);
        Node<TYPE>* find(std::function<bool(const TYPE&)>);
};


template <class TYPE>
Node<TYPE>* List<TYPE>::addFront(TYPE e){
    TYPE* newElem = new TYPE(e);
    Node<TYPE>* newNode = new Node<TYPE>(newElem,nullptr,head);

    if(head)
        head->prevNode = newNode;
    if(!tail)
        tail = newNode;
    head = newNode;

    return head;
}


template <class TYPE>
Node<TYPE>* List<TYPE>::addEnd(TYPE e){
    TYPE* newElem = new TYPE(e);
    Node<TYPE>* newNode = new Node<TYPE>(newElem,tail,nullptr);

    if(tail)
        tail->nextNode = newNode;
    if(!head)
        head = newNode;
    tail = newNode;

    return tail;
}


/*
template <class TYPE>
void List<TYPE>::removeFront(){
    Node<TYPE>* tmp;
    if(empty())
        return;
    else{
        tmp = head;
        if(head == tail){
            head = nullptr;
            tail = nullptr;

            delete tmp;
        }
        else{
            head = head->nextNode;
            delete tmp;
        }
    }
}



template <class TYPE>
void List<TYPE>::removeEnd(){
    Node<TYPE>* tmp = new Node<TYPE>;

    if(empty()){
        return;
    }
    tmp = head;
    if(head == tail){
        head = nullptr;
        tail = nullptr;
        delete tmp;
    }
    while(tmp->getNext() != tail)
        tmp = tmp->getNext();
    tmp->nextNode = nullptr;
    delete tail;
    tail = tmp;
}
*/

template <class TYPE>
void List<TYPE>::removeElem(Node<TYPE>* elem){

    if(elem == head){
        head = elem->nextNode;
    }
    if(elem == tail){
        tail = elem->prevNode;
    }
    
    if(elem->nextNode)
        elem->nextNode->prevNode = elem->prevNode;
    if(elem->prevNode)
        elem->prevNode->nextNode = elem->nextNode;
    
    delete elem->elem;
    delete elem;
        
}


template <class TYPE>
Node<TYPE>* List<TYPE>::find(const TYPE& value){
    for(auto actualNode = head; actualNode; actualNode = actualNode->next){
        if(*actualNode->elem == value)
            return actualNode;
    }
    return nullptr;
}


template <class TYPE>
Node<TYPE>* List<TYPE>::find(std::function<bool(const TYPE&)> predicate){
    for(auto actualNode = head; actualNode; actualNode = actualNode->next){
        if(predicate(*actualNode->elem))
            return actualNode;
    }
    return nullptr;
}