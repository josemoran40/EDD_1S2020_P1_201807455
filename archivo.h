#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
using namespace std;
class Archivo
{
private:
    string nombre;
    string contenido;

public:
    Archivo(string nombre, string contenido){
        this->nombre=nombre;
        this->contenido=contenido;
    };

    void setNombre(string nombre){
        this->nombre=nombre;
    }

    void setContenido(string contenido){
        this->contenido=contenido;
    }

    string getNombre(){
        return nombre   ;
    }

    string getContenido(){
        return contenido;
    }
};

#endif // ARCHIVO_H
