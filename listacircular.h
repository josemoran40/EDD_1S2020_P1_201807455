#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
#include <iostream>
#include "archivo.h"
using namespace std;

class NodoCircular{
public:
    Archivo *data;
    NodoCircular *next;

    NodoCircular(Archivo * data) {
        this->data = data;
        next = NULL;
    }
};
class Listacircular
{
 private:
    NodoCircular *first;
    NodoCircular *last;
    int size;
public:
    Listacircular(){
        first = NULL;
        last = NULL;
        size = 0;
    };

    void append(Archivo * data) {
            NodoCircular *n = new NodoCircular(data);
            if (first == NULL) {
                first = n;
                last = n;
                last->next = first;
            } else {
                last->next = n;
                n->next = first;
                last = n;
            }
            size++;
      }
    void print(){
        NodoCircular *n = first;

        if(size ==0)
            return;
        else{
            char x = 186;

            for(int i = 0;i<size;i++){

                cout<<"                       "<<i+1<<". "<<n->data->getNombre()<<endl;
                cout<<x;
            }
        }

    }

    NodoCircular * buscarArchivo(int pos){
        NodoCircular *aux = NULL;
        if(first!=NULL && pos<=size){
            aux = first;
            for(int i =0; i<pos;i++){
                if(i<=size){
                    aux = aux->next;
                }else{
                    aux = NULL;
                }
            }
        }

        return aux;
    }



};

#endif // LISTACIRCULAR_H
