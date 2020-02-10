#include <QCoreApplication>
#include <iostream>
#include <conio.h>
#include "listadoble.h"
#include <windows.h>
#include "interfaz.h"
#include <stdio.h>
#include <fstream>
#include <cassert>
#include <cstddef>
#include <stack.h>

#include <string.h>
#include <ctype.h>


using namespace std;

Stack *realizado;
Stack *revertido;

//--------------------------inicioCursor----------------------------------------------------
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

//--------------------------FinCursor----------------------------------------------------


//--------------------------Inicio Editor----------------------------------------------------


string buscarYReemplazar(string text){
    string replacement;
    setearCursor(45,29);
    cout<<"Reemplazar: ";
    cin>>replacement;

      string findMe;
      setearCursor(45,28+2);
      cout<<"Buscar: ";
      cin>>findMe;
      // Find "UFO" in bigNews and overwrite it:
      int pos = text.find(findMe);
      while(pos!=-1){
          text.replace(pos, findMe.size(), replacement);
          Cambio *cambio = new Cambio(findMe, replacement, false, text);
          revertido->push(cambio);
          pos = text.find(findMe, pos + replacement.size());


      }

      return text;
}

string borrar(string text, int pos){
    text.replace(pos-1, 1, " ");
    return text;
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
    string text = "";

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
        }else if(x==23){
            text = buscarYReemplazar(text);
            system("cls");
            interfaz->editor();
            reiniciarCursor();
            cout<<text;
            posx=text.size()+1;
            setearCursor(posx, posy);
            cout<<" ";

        }else if(x == 49){
            setearCursor(0,31);
            realizado->print();
            setearCursor(posx,posy);
        }else if(x == 26){
            //ctrl+z
            Cambio *cambio = realizado->pop();
            text = cambio->getOracion();
            reiniciarCursor();
            cout<<text;
            posx = text.size()+2;
            revertido->push(cambio);
            setearCursor(posx, posy);
        }else if(x==25){
        }

        if(x!=75 && x!=224 && x!= 80 && x!=77 && x!=72 && x!=23){

            if(x==8){
                if(posx!=1){
                    char eliminado = text.at(posx-1);
                    Cambio *cambio = new Cambio(s.append(1,eliminado), posx, false, text);
                    text = borrar(text, posx);
                    reiniciarCursor();
                    cout<<text;
                    realizado->push(cambio);
                    setearCursor(posx, posy);
                    posx--;
                    setearCursor(posx, posy);
                }
            }else{
                posx++;
                s.push_back(x);
                list.append(s);
                text = text.insert(posx-2,s);
                Cambio *cambio = new Cambio(s, posx, true, text);
                realizado->push(cambio);
                reiniciarCursor();
                cout<<text;
                setearCursor(posx, posy);
            }
            s ="";
            t="";
            x = NULL;


        }
    }
}



//--------------------------FinEditor----------------------------------------------------


void leerArchivo(){
    ifstream in; // Open for reading
      string s;
      in.open("D:\\Nombre del equipo.txt");
      if(in.fail()){
          cout<<"El archivo no se pudo abrir";
      }
      int  y = 1;
      while(getline(in, s)){ // Discards newline char
        setearCursor(1,y);
          cout << s << "\n";

        y++;
      }// ... must add it back
}


void menu(){
    realizado = new Stack();
    realizado = new Stack();

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
        //cin>>archivo;
       system("cls");
       interfaz->editor();
        leerArchivo();
        break;
    }
}

int main(){    
    menu();
}




