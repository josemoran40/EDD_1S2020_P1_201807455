#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "cambio.h"
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;

class Node {
public:
    Cambio *data;
    Node *next;

    Node(Cambio * data) {
        this->data = data;
        next = NULL;
    }
};

class LinkedList {
private:
    Node *first;
    Node *last;
    int size;

public:
    LinkedList() {
        first = NULL;
        last = NULL;
        size = 0;
    }

    void append(Cambio * data) {
        Node *n = new Node(data);
        if (first == NULL) {
            first = n;
            last = n;
        } else {
            last->next = n;
            last = n;
        }
        size++;
    }

    void prepend(Cambio *  data) {
        Node *n = new Node(data);
        if (first == NULL) {
            first = n;
            last = n;
        } else {
            Node *temp = first;
            first = n;
            n->next = temp;
        }
        size++;
    }

    void print() {
        Node *temp = first;
        while (temp != NULL) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }

    void removeFirst() {
        if (first != NULL) {
            Node *temp = first;
            first = first->next;
            delete temp;
            --size;
        }
    }

    void removeLast() {
        if (first->next == NULL) {
            removeFirst();
        } else if (first != NULL) {
            Node *cur = first;
            Node *prev;
            while(cur->next !=NULL){
                prev = cur;
                cur = cur->next;
            }
            last = prev;
            prev->next= NULL;
            delete cur;
            size--;
        }
    }

    void removeSpecific(int pos){
        if(pos> size || pos<1)
            return;
        else if (pos == 1)
            removeFirst();
        else if (pos == size)
            removeLast();
        else if (first != NULL){
            Node *prev;
            Node *cur= first;
            for (int i = 0; i < pos; ++i) {
                prev = cur;
                cur = cur->next;
            }
            prev->next = cur->next;
            delete cur;
            size--;
        }
    }

    void insertAt(int pos, Cambio * data){
        if(pos>size+1 || pos<1)
            return;
        else if (pos==1)
            append(data);
        else if (pos==size+1)
            prepend(data);
        else if (first!=NULL){
            Node *n = new Node(data);
            Node *prev;
            Node *cur = first;
            for (int i = 0; i < pos; ++i) {
                prev = cur;
                cur=cur->next;
            }
            prev->next=n;
            n->next=cur;
            size++;
        }
    }

    void deleteList(){
        Node *next;
        while (first!=NULL){
            next = first->next;
            delete first;
            first = next;
        }
    }

    void insertarAlfabeticamente(Cambio *data){
        if(size == 0)
            append(data);
        else{
            Node * nodo_aux = first;
             int cont = 1;
             bool inserto = true;
                    do
                    {
                              if(data->getPalabraBuscada()< nodo_aux->data->getPalabraBuscada())
                              {
                                          insertAt(cont, data);
                                          inserto = false;
                                          break;
                               }
                               nodo_aux  = nodo_aux ->next;

                    }while( (nodo_aux != NULL) );

                    if(inserto){
                        prepend(data);
                    }

        }

    }


    void generarGraphvizListaSimple(){
        string cadena ="";
        cadena += "digraph G{\n";


        int n = 1;
        Node * nodoAux = first;
        for (int i = 1; i<size+1;i++)
        {
            cadena +="p";
            string str= to_string(i);
            cadena +=str;
            cadena+="[label = \"";
            cadena+=nodoAux->data->getPalabraBuscada();
            cadena+="\" fontname=\"Times New Roman\" shape=parallelogram color=darkorange2];\n";
            n++;
            nodoAux =  nodoAux->next;
        }
        int aux = n;
        int aux2 = n + 1;
        n = 1;


        for (int i = 0; i < aux-2; i++)
        {

            n++;
        }

        for (int i = 0; i < aux-2; i++)
        {
            cadena += "p";
            string st= to_string(n);
            cadena +=st;
            cadena+=":c->p";
            string str= to_string(n-1);
            cadena +=str;
            cadena+=";\n";
            n--;
        }


        cadena += "}";

         ofstream archivo;
         archivo.open("C:\\Users\\jose_\\OneDrive\\Escritorio\\edd.txt",ios::out);
         if(archivo.fail()){

             cout<<"no jala el archivo";
             exit(1);
         }
        else{
         archivo<<cadena;
         archivo.close();

         system("dot -Tpng C:\\Users\\jose_\\OneDrive\\Escritorio\\edd.txt -o C:\\Users\\jose_\\OneDrive\\Escritorio\\edd.png");
        }
    }
};
#endif // LINKEDLIST_H
