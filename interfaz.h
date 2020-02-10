#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <iostream>
#include <conio.h>

using namespace std;

class Interfaz
{
public:
    Interfaz();


    void editor(){
        system("color E0");
        //-----------------
        for(int i = 0; i<100;i++){
            char x;
            if(i==0){
            x=201;
            }else if(i==99){
                x=187;
            }else{
            x  = 205;
            }
            cout<<x;
        }cout<<" "<<endl;

        for(int i = 0; i<25;i++){
            char x = 186;
            cout<<x;
            for(int j = 0;j<98;j++){
                cout<<" ";

            }

            cout<<x<<endl;
        }
        for(int i = 0; i<100;i++){
            char x;
            if(i==0){
            x=200;
            }else if(i==99){
                x=188;
            }else{
            x  = 205;
            }
            cout<<x;
        }cout<<" "<<endl;
        cout<<"             ";
        for(int i =0; i<3;i++){
            if(i==0){
                cout<<"Buscar y reemplezar(^w)";
            }else if(i==1){
                cout<<"Reportes(^c)";
            }else if(i==2){
                cout<<"Guardar(^s)";
            }
            cout<<"             ";
        }cout<<endl;
        //--------------------------------------

    }

    void principal(){
        system("color E0");
        for(int i = 0; i<100;i++){
            char x;
            if(i==0){
            x=201;
            }else if(i==99){
                x=187;
            }else{
            x  = 205;
            }
            cout<<x;
        }cout<<" "<<endl;

        for(int i = 0; i<25;i++){
            char x = 186;
            cout<<x;
            if(i==0){
                cout<<"       UNIVERSIDAD SAN CARLOS DE GUATEMALA       ";
            }else if(i==1){
                cout<<"       FACULTAD DE INGENIERIA                    ";
            }else if(i==2){
                cout<<"       ESTRUCTURAS DE DATOS                      ";
            }else if(i==3){
                cout<<"       PRACTICA 1                                ";
            }else if(i==4){
                cout<<"       JOSE EDUARDO MORAN REYES                  ";
            }else if(i==5){
                cout<<"       201807455                                 ";
            }else if(i==14){
                cout<<"       MENU                                      ";
            }else if(i==15){
                cout<<"       1.Crear Archivo                           ";
            }else if(i==16){
                cout<<"       2.Abrir Archivo                           ";
            }else if(i==17){
                cout<<"       3.Abrir Archivos Recientes                ";
            }else if(i==18){
                cout<<"       4.Salir                                   ";
            }else if(i==20){
                cout<<"       Seleccione una opcion:                    ";
            }else{
                cout<<"                                                 ";
            }

            for(int j = 0;j<98-49;j++){
                cout<<" ";

            }
            cout<<x<<endl;
        }
        for(int i = 0; i<100;i++){
            char x;
            if(i==0){
            x=200;
            }else if(i==99){
                x=188;
            }else{
            x  = 205;
            }
            cout<<x;
        }cout<<" "<<endl;
    }


};

#endif // INTERFAZ_H
