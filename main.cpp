
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
#include <linkedlist.h>
#include <Winuser.h>

#include <string.h>
#include <ctype.h>


using namespace std;


Stack *realizado;
Stack *revertido;
LinkedList *palabrasBuscadas;
LinkedList *palabrasBuscadasAlfabeticamente;
int palabrasRepe = 0;
int arranquex =1;
int arranquey =1;
string textoArranque = "";
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
void imprimirText(string text);

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
          if(arranquex<2352){
          texto+=s;
          for(int j = 0; j<s.size();j++){
              char car = s[j];
              string t(1,car);
              list->append(t);
             arranquex++;
          }
}

      }// ... must add it back
     reiniciarCursor();
      imprimirText(texto);
      Archivo *archivo = new Archivo(ruta, texto);
      listaArchivos->append(archivo);
      textoArranque = texto;
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
            listaArchivos->generarGraphvizListaDoble();
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
    palabrasBuscadas = new LinkedList();
    textoArranque  = "";
    palabrasBuscadasAlfabeticamente = new LinkedList();
    system("cls");
    Interfaz *interfaz = new Interfaz();
    interfaz->principal();
    menuCursor();
    bool elejido = true;
    int eleccion;
    while(elejido){
          eleccion= getch();
         if((eleccion<53 && eleccion>48)){
             elejido=false;
         }
    }
    string archivo;
    string tt(1,eleccion);
    cout<<tt;
    ListaDoble *l = new ListaDoble();
    switch (eleccion) {
    case 49:

        system("cls");
        arranquex=1;
        arranquey=1;
        interfaz->editor();
        reiniciarCursor();
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
    case 52:
        exit(1);
        break;
    }
}






//--------------------------Inicio Editor----------------------------------------------------

void imprimirText(string text){
    int num = 98;
    for(int i = 0; i<text.size(); i++){
        if(i<2450){
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
}


void limpiarEditor(){
    int num = 98;
    for(int i = 0; i<25; i++){
        setearCursor(1,i+1);
        for(int j=0;j<98;j++){
            cout<<" ";
        }
    }
}

string buscarYReemplazar(string text, ListaDoble *&list, int &xx){
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
      Cambio *cambio = new Cambio(findMe, replacement, false, text);
      while(pos!=-1){
          text.replace(pos, findMe.size(), replacement);
          list->eliminarBloque(findMe.size(), pos+1);
          list->reemplazarBloque(replacement, pos);
          xx = xx-findMe.size();
          xx = xx + replacement.size();
          palabrasBuscadasAlfabeticamente->insertarAlfabeticamente(cambio);
          pos = text.find(findMe, pos + replacement.size());
          i++;
      }
      realizado->push(cambio);
      palabrasBuscadas->prepend(cambio);
      setearCursor(35,35);
      palabrasRepe = i;

      return text;
}


string buscarYReemplazarPorCTRL(string text, ListaDoble *&list, string find, string replace, int &xx){
    string replacement = replace;

      string findMe=find;
      // Find "UFO" in bigNews and overwrite it:
      int pos = text.find(findMe);
      int i = 0;
      while(pos!=-1){
          text.replace(pos, findMe.size(), replacement);
          list->eliminarBloque(findMe.size(), pos+1);
          list->reemplazarBloque(replacement, pos);
          xx = xx-findMe.size();
          xx = xx + replacement.size();
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
    int posx = arranquex;
    int posy =arranquey;
    bool limpiar = false;
    Interfaz *interfaz = new Interfaz();

    string text = textoArranque;

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

        }else if(x==24){
        break;
        }else if(x==23){
            text = buscarYReemplazar(text, list,posx);
            system("cls");
            interfaz->editor();
            reiniciarCursor();
            imprimirText(text);
            posx=text.size()+1;
            setearCursor(35,30);
            cout<<"Palabras afectadas: "<<palabrasRepe;
            setearCursor(posx, posy);
            limpiar =true;

        }/*else if(x == 49){
            //setearCursor(0,29);
            //realizado->print();
            //setearCursor(posx,posy);
        }*/else if(x == 26){
            //ctrl+z


            Cambio *cambio = realizado->pop();
             if(cambio!=NULL){
                if(cambio->getTipo()==true){
                    if(!cambio->getAgregado()){
                        cambio->setAgregado(true);
                        list->insertAt(cambio->getPosicion(),cambio->getPalabra());
                        text = cambio->getOracion();
                        limpiarEditor();
                        setearCursor(1,1);
                        imprimirText(text);
                        posx = cambio->getPosicion();
                    }else{
                        cambio->setAgregado(false);
                        list->removeSpecific(cambio->getPosicion());
                        text = borrar(text, cambio->getPosicion()+1);
                        reiniciarCursor();
                        limpiarEditor();
                        setearCursor(1,1);
                        imprimirText(text);

                        //list->print();
                        posx = cambio->getPosicion();
                        setearCursor(posx, posy);
                    }
                }else if(cambio->getTipo()==false){
                    //Buscar y reemplazar por ctrl+z
                    text = buscarYReemplazarPorCTRL(text, list,cambio->getPalabraReemplazada(), cambio->getPalabraBuscada(),posx);
                    system("cls");
                    interfaz->editor();
                    reiniciarCursor();
                    imprimirText(text);
                    posx=text.size()+1;
                    setearCursor(35,30);
                    cout<<"Palabras afectadas: "<<palabrasRepe;
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
                if(cambio->getTipo()==true){
                    if(cambio->getAgregado()){
                        cambio->setAgregado(false);
                        list->removeSpecific(cambio->getPosicion());
                        text = borrar(text, cambio->getPosicion()+1);
                        reiniciarCursor();
                        limpiarEditor();
                        setearCursor(1,1);
                        imprimirText(text);

                        //list->print();
                        posx = cambio->getPosicion();
                        setearCursor(posx, posy);
                    }else{
                        cambio->setAgregado(true);
                        list->insertAt(cambio->getPosicion(),cambio->getPalabra());
                        text = cambio->getOracion();
                        limpiarEditor();
                        setearCursor(1,1);
                        imprimirText(text);
                        posx = cambio->getPosicion()+1;

                    }
                 }else if(cambio->getTipo()==false){
                    //Buscar y reemplazar por ctrl+z
                    text = buscarYReemplazarPorCTRL(text, list, cambio->getPalabraBuscada(),cambio->getPalabraReemplazada(), posx);
                    system("cls");
                    interfaz->editor();
                    reiniciarCursor();
                    imprimirText(text);
                    posx=text.size()+1;
                    setearCursor(35,30);
                    cout<<"Palabras afectadas: "<<palabrasRepe;
                    setearCursor(posx, posy);

                }
                realizado->push(cambio);
                setearCursor(posx, posy);
            }
        }else if (x==27){
            system("cls");
            list->print();
            prueba = false;
        }else if(x==3){
            //Generar Reportes
            setearCursor(35, 28+1);
            cout<<"Reportes: ";
            setearCursor(35, 29+1);
            cout<<"1. Reporte lista";
            setearCursor(35, 30+1);
            cout<<"2. Log de Cambios";
            setearCursor(35, 31+1);
            cout<<"3. Palabras Ordenas";
            bool elejido = true;
            int eleccionReporte;
            while(elejido){
                  eleccionReporte= getch();
                 if((eleccionReporte<53 && eleccionReporte>48)||eleccionReporte==24){
                     elejido=false;
                 }
            }
            if(eleccionReporte!=24){
                if(eleccionReporte==49){
                    list->generarGraphvizListaDoble();
                    ShellExecuteA(NULL, "open","C:\\Users\\jose_\\OneDrive\\Escritorio\\edd.png", NULL, NULL, SW_SHOWNORMAL);
                }else if(eleccionReporte==50){
                    revertido->generarGraphvizRevertidos();
                    ShellExecuteA(NULL, "open","C:\\Users\\jose_\\OneDrive\\Escritorio\\revertido.png", NULL, NULL, SW_SHOWNORMAL);
                    realizado->generarGraphvizRealizados();
                    ShellExecuteA(NULL, "open","C:\\Users\\jose_\\OneDrive\\Escritorio\\realizado.png", NULL, NULL, SW_SHOWNORMAL);
                }else if(eleccionReporte==51){
                    palabrasBuscadas->ordenar();
                    palabrasBuscadas->generarGraphvizListaSimple();
                    ShellExecuteA(NULL, "open","C:\\Users\\jose_\\OneDrive\\Escritorio\\edd.png", NULL, NULL, SW_SHOWNORMAL);
                }
            }

            //limpiar editor
            setearCursor(0, 28);
            for(int i =0;i<10;i++){
                for(int j = 0; j<200;j++){
                    cout<<"   ";
                }
                cout<<"\n";
            }
            reiniciarCursor();
            imprimirText(text);

        }else if(x==19){
            setearCursor(35, 29);
            string nombreArchivo ="";
            cout<<"Ingrese el nombre del archivo: ";
            cin>>nombreArchivo;
            string ruta= "C:\\Users\\jose_\\OneDrive\\Escritorio\\";
            ruta+=nombreArchivo;
            ruta+=".txt";
            ofstream archivo;
            archivo.open(ruta);
            archivo<<text;
            archivo.close();
            ShellExecuteA(NULL, "open", ruta.c_str(), NULL, NULL, SW_SHOWNORMAL);

            setearCursor(0, 28);
            for(int i =0;i<10;i++){
                for(int j = 0; j<200;j++){
                    cout<<"   ";
                }
                cout<<"\n";
            }
            reiniciarCursor();
            imprimirText(text);
            }
            else if(x!=75 && x!=224 && x!= 80 && x!=77 && x!=72 && x!=23 && x!=25 && x!=26 && x!=27){

            if(x==8){
                if(posx!=1){
                    char eliminado = text.at(posx-2);
                    Cambio *cambio = new Cambio(s.append(1,eliminado), posx, false, text);
                    text = borrar(text, posx);
                    reiniciarCursor();
                    limpiarEditor();
                    setearCursor(1,1);
                    imprimirText(text);
                    list->removeSpecific(posx-1);
                    realizado->push(cambio);
                    posx--;
                }
            }else{
                posx++;
                s.push_back(x);
                list->insertAt(posx-1,s);
                text = text.insert(posx-2,s);
                Cambio *cambio = new Cambio(s, posx-1, true, text);
                realizado->push(cambio);
                if(limpiar){
                    setearCursor(0, 28);
                    for(int i =0;i<2;i++){
                        for(int j = 0; j<100;j++){
                            cout<<"   ";
                        }
                        cout<<"\n";
                    }
                    limpiar =false;
                }
                reiniciarCursor();
                imprimirText(text);
                //setearCursor(posx, posy);
            }
            s ="";
            t="";
            x = NULL;


        }
    }
    menu();
}



//--------------------------FinEditor----------------------------------------------------

int main(){
    menu();
}
