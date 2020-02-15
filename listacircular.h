#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
#include <iostream>
#include "archivo.h"
#include <fstream>
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

    void generarGraphvizListaDoble(){
        string cadena ="";
        cadena += "digraph G{\n";


        int n = 1;
        NodoCircular * nodoAux = first;
        for (int i = 1; i<size+1;i++)
        {
            cadena +="p";
            string str= to_string(i);
            cadena +=str;
            cadena+="[label = \"";
            cadena+=nodoAux->data->getNombre();
            cadena+="\" fontname=\"Times New Roman\" shape=parallelogram color=darkorange2];\n";
            n++;
            nodoAux =  nodoAux->next;
        }
        int aux = n;
        int aux2 = n + 1;
        n = 1;


        for (int i = 0; i < aux-2; i++)
        {
            cadena += "p";
            string st= to_string(n);
            cadena +=st;
            cadena+=":c->p";
            string str= to_string(n+1);
            cadena +=str;
            cadena+=";\n";
            n++;
        }

        cadena += "p";
        string st= to_string(n);
        cadena +=st;
        cadena+=":c->p1";
        cadena+=";\n";

        \

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

#endif // LISTACIRCULAR_H
