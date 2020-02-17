#ifndef STACK_H
#define STACK_H


#include <iostream>
#include <cambio.h>
#include <fstream>
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
    int size;
public:
    Stack(){
        top = NULL;
        size = 0;
    }

    void push(Cambio *data){
        Nodo *n = new Nodo(data);
        if(top ==NULL){
            top =n;
        }else{
            n->next = top;
            top = n;
        }
        size++;
    }

    Cambio * pop(){
        if(top==NULL){
            return NULL;
        }else{
            Cambio *datatemp =  top->cambio;
            Nodo *temp = top;
            top = top->next;
            delete temp;

            size--;
            return datatemp;
        }
    }

    void print(){
        if(top==NULL){
        }
        else{
            Nodo *temp = top;
            while (temp!=NULL) {
                cout<<temp->cambio->getPalabra()<<endl;
                temp = temp->next;
            }
        }
    }


    void generarGraphvizRealizados(){
        string cadena ="";
        cadena += "digraph G{\n";


        int n = 1;
        Nodo * nodoAux = top;
        for (int i = 1; i<size+1;i++)
        {
            cadena +="p";
            string str= to_string(i);
            cadena +=str;
            cadena+="[label = \"";
            if(nodoAux->cambio->getTipo()==true){
                cadena+="Palabra Buscada: NULL \\n";
                cadena+="Palabra Remplazada: NULL \\n";
                cadena+="Estado: No revertido \\n";
                cadena+="Palabra: ";cadena+=nodoAux->cambio->getPalabra();
                cadena+="\\n Posicion: ";//cadena+=nodoAux->cambio->getPosicion();
                cadena+="\\n Agregado";
                if(nodoAux->cambio->getAgregado()){
                    cadena+=" si\" shape=box ,fillcolor=\"#00b33c\" , style=filled]";
                }else{

                    cadena += " no\" shape=box ,fillcolor=\"#00b33c\" , style=filled]";
                }
            }else{

                cadena+="Palabra Buscada: ";cadena+=nodoAux->cambio->getPalabraBuscada();
                cadena+="\\n Palabra Remplazada: ";cadena+=nodoAux->cambio->getPalabraReemplazada();
                cadena+="\\n Estado: No revertido\\n";
                cadena+="Palabra: NULL";
                cadena+="\\n Posicion: NULL";
                cadena+="\\n Agregado: NULL";
                    cadena+="\"shape=box ,fillcolor=\"#00b33c\" , style=filled ;]";

            }
            cadena+="  \n";
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
         archivo.open("C:\\Users\\jose_\\OneDrive\\Escritorio\\realizado.txt",ios::out);
         if(archivo.fail()){

             cout<<"no jala el archivo";
             exit(1);
         }
        else{
         archivo<<cadena;
         archivo.close();

         system("dot -Tpng C:\\Users\\jose_\\OneDrive\\Escritorio\\realizado.txt -o C:\\Users\\jose_\\OneDrive\\Escritorio\\realizado.png");
        }
    }

    void generarGraphvizRevertidos(){
        string cadena ="";
        cadena += "digraph G{\n";


        int n = 1;
        Nodo * nodoAux = top;
        for (int i = 1; i<size+1;i++)
                {
                    cadena +="p";
                    string str= to_string(i);
                    cadena +=str;
                    cadena+="[label = \"";
                    if(nodoAux->cambio->getTipo()==true){
                        cadena+="Palabra Buscada: NULL \\n";
                        cadena+="Palabra Remplazada: NULL \\n";
                        cadena+="Estado: Revertido \\n";
                        cadena+="Palabra: ";cadena+=nodoAux->cambio->getPalabra();
                        cadena+="\\n Posicion: ";//cadena+=nodoAux->cambio->getPosicion();
                        cadena+="\\n Agregado";
                        if(nodoAux->cambio->getAgregado()){
                            cadena+=" si\" shape=box ,fillcolor=\"#ff3333\" , style=filled]";
                        }else{

                            cadena += " no\" shape=box ,fillcolor=\"#ff3333\" , style=filled]";
                        }
                    }else{

                        cadena+="Palabra Buscada: ";cadena+=nodoAux->cambio->getPalabraBuscada();
                        cadena+="\\n Palabra Remplazada: ";cadena+=nodoAux->cambio->getPalabraReemplazada();
                        cadena+="\\n Estado: Revertido\\n";
                        cadena+="Palabra: NULL";
                        cadena+="\\n Posicion: NULL";
                        cadena+="\\n Agregado: NULL";
                            cadena+="\"shape=box ,fillcolor=\"#ff3333\" , style=filled ;]";

                    }
                    cadena+="  \n";
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

         system("dot -Tpng C:\\Users\\jose_\\OneDrive\\Escritorio\\edd.txt -o C:\\Users\\jose_\\OneDrive\\Escritorio\\revertido.png");
        }
    }
};


#endif // STACK_H
