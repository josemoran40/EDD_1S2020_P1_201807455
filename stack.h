#ifndef STACK_H
#define STACK_H


#include <iostream>
#include <cambio.h>
using namespace std;


class Nodo{
public:
    Cambio *cambio;
    Nodo *next;
    Nodo(Cambio *data){
        this->cambio=data;
        next = NULL;
    }
};

class Stack {
private:
    Nodo *top;
public:
    Stack(){
        top = NULL;
    }

    void push(Cambio *data){
        Nodo *n = new Nodo(data);
        if(top ==NULL){
            top =n;
        }else{
            n->next = top;
            top = n;
        }
    }

    Cambio * pop(){
        if(top==NULL){
            return NULL;
        }else{
            Cambio *datatemp =  top->cambio;
            Nodo *temp = top;
            top = top->next;
            delete temp;
            return datatemp;
        }
    }

    void print(){
        if(top==NULL){
            cout<<"La pila esta vacia"<<endl;
        }
        else{
            Nodo *temp = top;
            while (temp!=NULL) {
                cout<<temp->cambio->getPalabra()<<endl;
                temp = temp->next;
            }
        }
    }
};

#endif // STACK_H
