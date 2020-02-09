#ifndef STACK_H
#define STACK_H


#include <iostream>
using namespace std;

class NodoPila{
public:
    string data;
    NodoPila *next;
    NodoPila(string data){
        this->data=data;
        next = NULL;
    }
};

class Stack {
private:
    NodoPila *top;
public:
    Stack(){
        top = NULL;
    }

    void push(string data){
        NodoPila *n = new NodoPila(data);
        if(top ==NULL){
            top =n;
        }else{
            n->next = top;
            top = n;
        }
    }

    string pop(){
        if(top==NULL){
            cout<<"La pila esta vacia"<<endl;
        }else{
            string datatemp =  top->data;
            NodoPila *temp = top;
            top = top->next;
            delete temp;
            return datatemp;
        }
    }
};

#endif // STACK_H
