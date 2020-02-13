
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
#include <listacircular.h>

#include <string.h>
#include <ctype.h>


using namespace std;

Stack *realizado;
Stack *revertido;
int palabrasRepe = 0;
int arranquex =0;
int arranquey =0;
void menu();



static Listacircular *listaArchivos = new Listacircular();

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


void leerArchivo(string ruta, ListaDoble *list){
    ifstream in; // Open for reading
      string s;
      //"D:\\Nombredelequipo.txt"
      in.open(ruta);
      if(in.fail()){
          cout<<"El archivo no se pudo abrir";
      }
      int  y = 1;
      string texto = "";
      while(getline(in, s)){ // Discards newline char
        setearCursor(1,y);
          cout << s << "\n";
          texto+=s;
          for(int j = 0; j<s.size();j++){
              char car = s[j];
              string t(1,car);
              list->append(t);
          }
        y++;
      }// ... must add it back
      Archivo *archivo = new Archivo(ruta, texto);
      listaArchivos->append(archivo);
}

void eleccionArchivo(){
    setearCursor(35,3);
    cout<<"Archivos Recientes";
    setearCursor(1,5);
    listaArchivos->print();
    setearCursor(15,20);
    cout<<"Presione el numero del archivo para abrirlo";

    setearCursor(15,21);
    cout<<"Presione x para generar reporte de archivos";
    bool eleccion = true;

    while(eleccion){
        char tecla = getch();
        if(tecla==120){
            //Generar reporte
            menu();
        }else if(tecla>40&&tecla<30){
                string s(1,tecla);
                int p = std::stoi(s);
                NodoCircular *nodo = listaArchivos->buscarArchivo(p);
                if(nodo!=NULL){
                    ListaDoble *listax = new ListaDoble();
                    Interfaz *interfaz = new Interfaz();
                    eleccion = false;
                    system("cls");
                    interfaz->editor();
                    leerArchivo(nodo->data->getNombre(),listax);

                }

        }else if(tecla == 27){
            menu();
        }

    }
}

void editor(ListaDoble *listaParametro);

void menu(){
    realizado = new Stack();
    revertido = new Stack();
    system("cls");
    Interfaz *interfaz = new Interfaz();
    interfaz->principal();
    menuCursor();
    int eleccion = getch();
    string archivo;
    cout<<eleccion;
    ListaDoble *l = new ListaDoble();
    switch (eleccion) {
    case 49:

        system("cls");
        arranquex=1;
        arranquey=1;
        interfaz->editor();
        editor(l);
        break;
    case 50:setearCursor(1,22);
        cout<<"       Ingrese la ruta del archivo: ";
        cin>>archivo;
       system("cls");
       interfaz->editor();
        leerArchivo(archivo, l);
        editor(l);
        break;
    case 51:
        system("cls");
        interfaz->archivo();
        eleccionArchivo();
        break;
    }
}






//--------------------------Inicio Editor----------------------------------------------------

void imprimirText(string text){
    int num = 98;
    for(int i = 0; i<text.size(); i++){
        char a = text[i];
        if(i==num){
            num+=98;
            cout<<"\n";
            char x = 186;
            cout<<x;
        }
        cout<<a;
    }
}

string buscarYReemplazar(string text, ListaDoble *&list){
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
      int i = 0;
      while(pos!=-1){
          text.replace(pos, findMe.size(), replacement);
          Cambio *cambio = new Cambio(findMe, replacement, false, text);
          list->eliminarBloque(findMe.size(), pos+1);
          list->reemplazarBloque(replacement, pos);
          cout<<pos;
          revertido->push(cambio);
          pos = text.find(findMe, pos + replacement.size());
          i++;
      }
      setearCursor(35,35);
      palabrasRepe = i;

      return text;
}

string borrar(string text, int pos){
    text.replace(pos-2, 1, "");
    return text;
}



void editor(ListaDoble *listaParametro){
    ListaDoble *list = listaParametro;
    bool prueba = true;
    std::string s,t;
    int posx = 1;
    int posy = 1;

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
            //posy--;
            //setearCursor(posx, posy);
        }else if (x==13) {
            posx = 2;
            posy++;
            setearCursor(posx, posy);
        }else if(x==23){
            text = buscarYReemplazar(text, list);
            system("cls");
            interfaz->editor();
            reiniciarCursor();
            cout<<text;
            posx=text.size()+1;
            setearCursor(35,30);
            cout<<"Palabras afectadas: "<<palabrasRepe;
            setearCursor(posx, posy);
            cout<<" ";

        }else if(x == 49){
            setearCursor(0,29);
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
                    text = cambio->getOracion();
                    imprimirText(text);
                    posx = cambio->getPosicion();
                    setearCursor(posx, posy);
                }else{
                    cambio->setAgregado(false);
                    list->removeSpecific(cambio->getPosicion());
                    text = borrar(text, cambio->getPosicion()+1);
                    reiniciarCursor();
                    imprimirText(text);

                    //list->print();
                    posx = cambio->getPosicion();
                    cout<<" ";
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
                if(cambio->getAgregado()){
                    cambio->setAgregado(false);
                    list->removeSpecific(cambio->getPosicion());
                    text = borrar(text, cambio->getPosicion()+1);
                    reiniciarCursor();
                    imprimirText(text);

                    //list->print();
                    posx = cambio->getPosicion();
                    cout<<" ";
                    setearCursor(posx, posy);
                }else{
                    cambio->setAgregado(true);
                    list->insertAt(cambio->getPosicion(),cambio->getPalabra());
                    text = cambio->getOracion();
                    imprimirText(text);
                    posx = cambio->getPosicion();
                    setearCursor(posx, posy);
                }
                realizado->push(cambio);
                setearCursor(posx, posy);
            }
        }else if (x==27){
            system("cls");
            list->print();
            menu();
        }else if(x==55){
            list->generarGraphvizListaDoble();
        }

        if(x!=75 && x!=224 && x!= 80 && x!=77 && x!=72 && x!=23 && x!=25 && x!=26 && x!=27){

            if(x==8){
                if(posx!=1){
                    char eliminado = text.at(posx-2);
                    Cambio *cambio = new Cambio(s.append(1,eliminado), posx, false, text);
                    text = borrar(text, posx);
                    reiniciarCursor();
                    imprimirText(text);
                    cout<<" ";
                    list->removeSpecific(posx-1);
                    realizado->push(cambio);
                    setearCursor(posx, posy);
                    posx--;
                    setearCursor(posx, posy);
                }
            }else{
                posx++;
                s.push_back(x);
                list->insertAt(posx-1,s);
                text = text.insert(posx-2,s);
                Cambio *cambio = new Cambio(s, posx-1, true, text);
                realizado->push(cambio);
                reiniciarCursor();
                imprimirText(text);
                setearCursor(posx, posy);
            }
            s ="";
            t="";
            x = NULL;


        }
    }
}



//--------------------------FinEditor----------------------------------------------------

int main(){
    menu();
}
