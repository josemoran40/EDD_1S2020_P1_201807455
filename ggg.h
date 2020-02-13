/*#include <QCoreApplication>
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

void reinicioFullCursor(){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = 0;

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


/*string buscarYReemplazar(string text){
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
}*/

/*
ListaDoble * buscaryReemplazar(ListaDoble *lista){
    string replacement;
    setearCursor(45,29);
    cout<<"Reemplazar: ";
    cin>>replacement;

     string findMe;
      setearCursor(45,28+2);
      cout<<"Buscar: ";
      cin>>findMe;

      lista->buscarCoincidencias(findMe,replacement);
      return lista;
}


string borrar(string text, int pos){
    text.replace(pos-1, 1, " ");
    return text;
}

void editor(int pos1, int pos2){
    ListaDoble *list = new ListaDoble();

    realizado = new Stack();
    revertido = new Stack();
    bool prueba = true;
    std::string s,t;
    int posx = pos1;
    int posy = pos2;

    Interfaz *interfaz = new Interfaz();


    reiniciarCursor();
    string text = "";

    while (prueba) {
        int x = getch();

        char caracter =  x;
        if(x==75){
            posx--;
            setearCursor(posx, posy);
        }else if(x==80){
            //posy++;
            //setearCursor(posx, posy);
        }else if(x==77){
            posx++;
            setearCursor(posx, posy);
        }else if(x==72){
            /*posy--;
            setearCursor(posx, posy);*/
  /*      }else if (x==13) {
            posx = 2;
            posy++;
            setearCursor(posx, posy);
        }else if(x==23){
           // text = buscarYReemplazar(text);
            //system("cls");
            //interfaz->editor();
            list = buscaryReemplazar(list);
            reiniciarCursor();
            list->printEditor();
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
                if(cambio!=NULL){
                reiniciarCursor();
                if(!cambio->getAgregado()){
                    cambio->setAgregado(true);
                    list->insertAt(cambio->getPosicion(),cambio->getPalabra());
                    list->printEditor();
                    posx = cambio->getPosicion();
                    setearCursor(posx, posy);
                }else{
                    cambio->setAgregado(false);
                    list->removeSpecific(cambio->getPosicion());
                    list->printEditor();
                    cout<<" ";
                    posx = cambio->getPosicion();
                    setearCursor(posx, posy);
                }
                revertido->push(cambio);
                setearCursor(posx, posy);
            }
        }else if(x==25){
            //ctrl+y
            Cambio *cambio = revertido->pop();
            if(cambio!=NULL){
                reiniciarCursor();
                if(!cambio->getAgregado()){
                    cambio->setAgregado(true);
                    list->insertAt(cambio->getPosicion(),cambio->getPalabra());
                    list->printEditor();
                    posx = cambio->getPosicion();
                    setearCursor(posx, posy);
                }else{
                    cambio->setAgregado(false);
                    list->removeSpecific(cambio->getPosicion());
                    list->printEditor();

                    posx = cambio->getPosicion();
                    setearCursor(posx, posy);
                }
                realizado->push(cambio);
                setearCursor(posx, posy);
            }
        }

        if(x!=75 && x!=224 && x!= 80 && x!=77 && x!=72 && x!=23 && x!=26 && x!=25){

            if(x==8){
                //Borrar
                if(posx!=1){
                    Cambio *cambio = new Cambio(list->getData(posx), posx, false, text);

                    list->removeSpecific(posx-1);

                    reiniciarCursor();

                    list->printEditor();
                    cout<<" ";
                    realizado->push(cambio);
                    setearCursor(posx, posy);
                    posx--;
                    setearCursor(posx, posy);
                }
            }else{
                posx++;
                s.push_back(x);
                list->insertAt(posx-1,s);
                Cambio *cambio = new Cambio(s, posx, true, text);
                realizado->push(cambio);
                reiniciarCursor();
                list->printEditor();
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

    Interfaz *interfaz = new Interfaz();
    interfaz->principal();
    menuCursor();
    int eleccion = getch();
    string archivo;
    cout<<eleccion;
    switch (eleccion) {
    case 49:

        system("cls");
        interfaz->editor();
        editor(1,1);
        break;
    case 50:setearCursor(1,22);
        cout<<"       Ingrese la ruta del archivo";
        //cin>>archivo;
       system("cls");
       interfaz->editor();
        leerArchivo();
        editor(1,1);
        break;
    }
}

int main(){
    menu();
}

*/


