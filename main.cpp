#include <QCoreApplication>
#include <iostream>
#include <conio.h>
#include "listadoble.h"
#include <windows.h>
#include "interfaz.h"
#include <stdio.h>
#include <fstream>

#include <string.h>
#include <ctype.h>


using namespace std;


void menuCursor(){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 30;
    pos.Y = 21;

    SetConsoleCursorPosition(hcon, pos);
}

void reiniciarCursor(){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 1;
    pos.Y = 1;

    SetConsoleCursorPosition(hcon, pos);
}

void setearCursor(int x, int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(hcon, pos);
}

void editor(){
    ListaDoble list;
    bool prueba = true;
    std::string s,t;
    int posx = 1;
    int posy = 1;

    Interfaz *interfaz = new Interfaz();
    interfaz->editor();

    reiniciarCursor();


    while (prueba) {
        int x = getch();
        char caracter =  x;
        if(x==75){
            posx--;
            setearCursor(posx, posy);
        }else if(x==80){
            posy++;
            setearCursor(posx, posy);
        }else if(x==77){
            posx++;
            setearCursor(posx, posy);
        }else if(x==72){
            posy--;
            setearCursor(posx, posy);
        }else if (x==13) {
            posx = 2;
            posy++;
            setearCursor(posx, posy);
        }
        if(x!=75 && x!=224 && x!= 80 && x!=77 && x!=72){
        s.push_back(x);
        list.append(s);
        cout<<s;

        if(x==104){
           // list.print();
        }else if(x==8){
            if(posx!=1){
            cout<<" ";
            posx--;
            setearCursor(posx, posy);
            }
        }else{
            posx++;
        }
        s ="";
        t="";
        x = NULL;


    }}
}

void leerArchivo(){
    ifstream in; // Open for reading
      string s;
      in.open("D:\\Nombre del equipo.txt");
      if(in.fail()){
          cout<<"El archivo no se pudo abrir";
      }
      while(getline(in, s)) // Discards newline char
        cout << s << "\n"; // ... must add it back
}

void menu(){
    Interfaz *interfaz = new Interfaz();
    interfaz->principal();
    menuCursor();
    int eleccion = getch();
    string archivo;
    cout<<eleccion;
    switch (eleccion) {
    case 49:

        system("cls");
        editor();
        break;
    case 50:setearCursor(1,22);
        cout<<"       Ingrese la ruta del archivo";

        cin>>archivo;
       // system("cls");
        //leerArchivo();
        break;
    }
}


int main(){
    menu();
}




