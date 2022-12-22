 /*
 *  GRAFO.CPP - Implementación de la clase GRAFOS
 *
 *
 *  Autor : Antonio Sedeno Noda, Sergio Alonso
 *  Fecha : 2013-2020
 */

#include "grafo.h"

using namespace std;

GRAFO::~GRAFO()
{
     for (unsigned int i = 0; i < LS.size(); ++i){
        LS[i].clear();
        LS[i].shrink_to_fit();
    }
    LS.clear(); LS.shrink_to_fit();

    for (unsigned int i = 0; i < LP.size(); ++i){
        LP[i].clear();
        LP[i].shrink_to_fit();
    }
    LP.clear(); LP.shrink_to_fit();
}

void GRAFO::actualizar(char nombrefichero[85], int &errorapertura)
{
    for (unsigned int i = 0; i < LS.size(); ++i){
        LS[i].clear();
        LS[i].shrink_to_fit();
    }
    LS.clear(); LS.shrink_to_fit();

    for (unsigned int i = 0; i < LP.size(); ++i){
        LP[i].clear();
        LP[i].shrink_to_fit();
    }
    LP.clear(); LP.shrink_to_fit();
    build(nombrefichero, errorapertura);
}

void GRAFO::Info_Grafo()
{
    if (dirigido == 1)
    {
        cout << "Grafo dirigido ";
    }
    else
    {
        cout << "Grafo no dirigido ";
    };
    cout << " | nodos " << n << " | ";
    if (dirigido == 1)
    {
        cout << " arcos ";
    }
    else
    {
        cout << "aristas ";
    };
    cout << endl;
}

unsigned GRAFO::Es_dirigido()
{
	return dirigido;
}

//void Mostrar_Lista(vector<LA_nodo> L) {};

void GRAFO::Mostrar_Listas (int l)
{
   if (l == 1){
        cout << "|Dirigido|" << endl;
        cout << "|Nodos sucesores|" << endl;
        for (auto i = 0; i < LS.size(); ++i){
            cout << "[" << i+1 << "]: ";
            for (auto j = 0; j < LS[i].size(); ++j){
                cout << LS[i][j].j+1 << "|";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (l == 0){
        cout << "|No dirigido|" << endl;
        cout << "|Lista de adyacencias|" << endl;
        for (auto i = 0; i < LS.size(); ++i){
            cout << "[" << i+1 << "]: ";
            for (auto j = 0; j < LS[i].size(); ++j){
                cout << LS[i][j].j+1 << "|";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (l == -1){
        cout << "|Lista de predecesores|" << endl;
        for (auto i = 0; i < LP.size(); ++i){
            cout << "[" << i+1 << "]: ";
            for (auto j = 0; j < LP[i].size(); ++j){
                cout << LP[i][j].j+1 << "|";
            }
            cout << endl;
        }
        cout << endl;
    } 
};

void GRAFO::dfs(unsigned i, vector<bool> &visitado)
{
	visitado[i] = true;
    cout << i+1 << ", ";
	for (unsigned j=0;j<LS[i].size();j++)
             if (visitado[LS[i][j].j] == false)
                 dfs(LS[i][j].j, visitado);
}

void GRAFO::ComponentesConexas()
{
int componentesConexas = 0;
    vector<bool> visitado;
    visitado.resize((*this).n);

    for (auto i = 0; i < visitado.size(); ++i)
        visitado[i] = false;
    
    for (auto i = 0; i < visitado.size(); ++i){
        if (visitado[i] == false){
            ++componentesConexas;
            cout << "Componente conexa numero " << componentesConexas << " {";
            dfs(i,visitado);
            cout << "}" << endl;
        }
    }
    if (componentesConexas == 1)
        cout << "Es un grafo conexo" << endl << endl;
    else cout << "Es un grafo no conexo" << endl << endl;
}


//void GRAFO::ListaPredecesores() {}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
    build(nombrefichero, errorapertura);
}


void
GRAFO::build(char nombrefichero[85], int &errorapertura)
{
    int i, j;
    ElementoLista dummy;
    ifstream textfile;
    textfile.open(nombrefichero);

    if (textfile.is_open())
    {
        errorapertura = 0;
        textfile >> static_cast<unsigned&> (n) 
                 >> static_cast<unsigned&> (m) 
                 >> static_cast<unsigned&> (dirigido);

        (*this).LS.resize(n);
        if (Es_dirigido() == 1){
            LP.resize(n);
            for (unsigned int k = 0; k < m; ++k){
                textfile >> i >> j;
                dummy.j = j-1;
                LS[i-1].push_back(dummy);
                dummy.j = i-1;
                LP[j-1].push_back(dummy);
            }
        }
        if (Es_dirigido() == 0){
            for (unsigned int k = 0; k < m; ++k){
                textfile >> i >> j;
                if (i == j){}
                dummy.j = j-1;
                LS[i-1].push_back(dummy);
                if (i != j){
                    dummy.j = i-1;
                    LS[j-1].push_back(dummy);
                }
            }
        }
    }
    else errorapertura = 1;
}


