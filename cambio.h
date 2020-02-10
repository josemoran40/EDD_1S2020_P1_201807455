#ifndef CAMBIO_H
#define CAMBIO_H
#include <iostream>

using namespace std;
class Cambio
{

private:
   string palabraBuscada;
   string palabraReemplazada;
   bool estado;
   string palabra;
   int posicion;
   bool agregado;
   string oracion;

public:
   Cambio(string palabraBuscada, string palabraReemplazada, bool estado, string oracion){
       this->palabraBuscada = palabraBuscada;
       this->palabraReemplazada = palabraReemplazada;
       this->estado = estado;
       this->palabra="";
       this->posicion=0;
       this->agregado=NULL;
       this->oracion = oracion;
   }

   Cambio(string palabra, int posicion, bool agregado, string oracion){
       this->palabra = palabra;
       this->posicion = posicion;
       this->agregado = agregado;
       this->palabraBuscada = "";
       this->palabraReemplazada = "";
       this->estado = NULL;
       this->oracion = oracion;
   }

   string getPalabraBuscada(){
       return palabraBuscada;
   }

   string getPalabraReemplazada(){
       return palabraReemplazada;
   }

   string getPalabra(){
       return palabra;
   }

   string getOracion(){
       return oracion;
   }

   bool getEstado(){
       return estado;
   }

   int getPosicion(){
       return posicion;
   }

   bool getAgregado(){
       return agregado;
   }

   void setPalabraBuscada(string palabra){
       this->palabraBuscada=palabra;
   }

   void setPalabraReemplazada(string palabra){
       this->palabraReemplazada=palabra;
   }

   void setPalabra(string palabra){
       this->palabra = palabra;
   }

   void setEstado(bool estado){
       this->estado = estado;
   }

   void setPosicion(int posicion){
       this->posicion = posicion;
   }

   void setAgregado(bool agregado){
       this->agregado = agregado;
   }
};

#endif // CAMBIO_H
