/*
 *  PG1.CPP - Actividad I de Optimiza!cion.
 *
 *
 *               Autores : Antonio Sedeno Noda, Sergio Alonso.
 *               Fecha : Marzo-2020
 */

#include <string.h>
#include "grafo.h"

using namespace std;

void menu(unsigned dirigido, char &opcion)
//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
{
    cout << "Actividad I, Optimizacion: Carga del grafo y Conectividad" << endl;
    cout << "c. [c]argar grafo desde fichero" << endl;
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    if (dirigido == 1)
    {
        cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
        cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
    }
    if (dirigido == 0)
    {
        cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
        cout << "o. Mostrar c[o]mponentes conexas del grafo" << endl;
    }
    cout << "q. Finalizar el programa" << endl;
};

// El principal es simplemente un gestor de menu, diferenciando acciones para grafo dirigido y para no dirigido
int main(int argc, char *argv[])
{
    int error_apertura;
    char nombrefichero[85], opcion;

    //Cargamos por defecto el fichero que se pasa como argumento del ejecutable
    if (argc > 1)
    {
        cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    }
    else
    {
        cout << "Introduce el nombre completo del fichero de datos: " << endl;
        cin >> nombrefichero;
    }
    GRAFO G(nombrefichero, error_apertura);
    if (error_apertura == 1)
    {
        cout << "Error en la apertura del fichero: revisa nombre y formato" << endl;
    }
    else
    {
        do
        {
            menu(G.Es_dirigido(), opcion);
            cout << "Introduce la letra de la accion a ejecutar > ";
            cin >> opcion;
            cout << endl;
            int l;
            switch (opcion)
            {
            case 'c':
                cout << "Introduce el nombre del nuevo fichero: ";
                cin >> nombrefichero;
                G.actualizar(nombrefichero, error_apertura);
                break;
            case 'i':
                G.Info_Grafo();
                break;
                if (G.Es_dirigido() == 1)
                {
                case 's':
                    l = 1;
                    G.Mostrar_Listas(l);
                    break;
                case 'p':
                    l = -1;
                    G.Mostrar_Listas(l);
                    break;
                }
                if (G.Es_dirigido() == 0)
                {
                case 'a':
                    l = 0;
                    G.Mostrar_Listas(l);
                    break;
                case 'o':
                    G.ComponentesConexas();
                    break;
                case 'q':
                    break;
                }
            default:
                cout << "Opcion no encontrada. Intentalo de nuevo" << endl
                     << endl;
            }
        } while (opcion != 'q');
    };
    cout << "Fin del programa" << endl;
    return (0);
};
