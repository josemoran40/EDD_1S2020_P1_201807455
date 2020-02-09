#ifndef LISTADOBLE_H
#define LISTADOBLE_H


#include <iostream>
using namespace std;

class NodoDoble{
public:
    string data;
    NodoDoble *next;
    NodoDoble *prev;
    NodoDoble(string data){
        this->data=data;
        next = NULL;
        prev = NULL;
    }
};

class ListaDoble {
private:
    NodoDoble *first;
    NodoDoble *last;
    int size;

public:
    ListaDoble() {
        first = NULL;
        last = NULL;
        size = 0;
    }

    void print() {
        NodoDoble *temp = first;
        int i = 1;
        while (temp != NULL) {
            cout << "Posicion "<<i<<" :"<<temp->data << endl;
            temp = temp->next;
            i++;
        }
    }

    void deleteList(){
        NodoDoble *next;
        while (first!=NULL){
            next = first->next;
            delete first;
            first = next;
        }
    }

    void prepend(string data) {
        NodoDoble *n = new NodoDoble(data);
        if (first == NULL) {
            first = n;
            last = n;
        } else {
            first->prev=n;
            n->next=first;
            first = n;
        }
        size++;
    }

    void append(string data) {
        NodoDoble *n = new NodoDoble(data);
        if (first == NULL) {
            first = n;
            last = n;
        } else {
            last->next = n;
            n->prev= last;
            last = n;
        }
        size++;
    }

    void insertAt(int pos, string data){
        if(pos>size+1 || pos<1)
            return;
        else if (pos==1)
            prepend(data);
        else if (pos==size+1)
            append(data);
        else if (first!=NULL){
            NodoDoble *n = new NodoDoble(data);
            NodoDoble *cur = first;
            for (int i = 0; i < pos; ++i) {
                cur=cur->next;
            }
            cur->prev->next=n;
            n->prev=cur->prev;
            n->next=cur;
            cur->prev=n;
            size++;
        }
    }

    void removeFirst() {
        if (first->next != NULL) {
            delete first;
            first = NULL;
            last = NULL;
            --size;
        }else if(first != NULL){
            first = first->next;
            delete first->prev;
            first->prev = NULL;
            --size;
        }
    }

    void removeSpecific(int pos){
        if(pos> size || pos<1)
            return;
        else if (pos == 1)
            removeFirst();
        else if (pos == size)
           // removeLast();
        {}
        else if (first != NULL){
            NodoDoble *cur= first;
            for (int i = 0; i < pos; ++i) {
                cur = cur->next;
            }
            cur->prev->next= cur->next;
            cur->next->prev=cur->prev;
            delete cur;
            size--;
        }
    }

    void removeLast() {
        if (first->next == NULL) {
            removeFirst();
        } else if (first != NULL) {
            last = last->prev;
            delete last->next;
            last->next =NULL;
            size--;
        }
    }
};
#endif // LISTADOBLE_H
