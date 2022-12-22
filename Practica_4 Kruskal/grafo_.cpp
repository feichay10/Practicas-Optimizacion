 /*
 *  GRAFO.CPP - Implementaci�n de la clase GRAFOS
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

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
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
    cout << m << " " << endl << endl;
}

unsigned GRAFO::Es_dirigido()
{
    return dirigido;
}

//void Mostrar_Lista(vector<LA_nodo> L){}


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


//void GRAFO::ListaPredecesores(){}

void GRAFO::Kruskal()
{
    vector<AristaPesada> Aristas;

    /*Usaremos la busqueda del menor en cada momento, pues es el mejor para Kruskal que no exige tener todas las aristas ordenadas*/
    /*Cargamos todas las aristas de la lista de adyacencia*/

    Aristas.resize(m);

    unsigned k = 0;
    for (unsigned i = 0; i < n; i++){
        for (unsigned j = 0; j < LS[i].size(); j++){
            if (i < LS[i][j].j) {
                Aristas[k].extremo1 = i;
                Aristas[k].extremo2 = LS[i][j].j;
                Aristas[k++].peso = LS[i][j].c;
                }
        }
    };
    /*Inicializamos el indice a la cabeza del vector*/
    unsigned head = 0;
    AristaPesada AristaDummy; //Para los intercambios en la ordenacion parcial

    /*Inicializamos el contador de aristas en la soluci�n*/
    unsigned a = 0;

    /*Inicializamos el peso de la solucion*/
    unsigned pesoMST = 0;

    /*Inicializamos el registro de componentes conexas: cada nodo est� en su compomente conexa*/
    vector<unsigned> Raiz;
    Raiz.resize(n);
    for (unsigned q = 0; q < n; q++){
        Raiz[q] = q;
    };
    /*Comenzamos Kruskal*/
    do {
        /* Implementamos el algoritmo de Kruskal */

        AristaDummy = Aristas[head];                            /* AristaDummy tiene una copia de la arista del vector Aristas apuntada por head */
        unsigned indice = head;                                 /* Indice usado para intercambios en el vector Aristas */
        unsigned extremo1, extremo2;                            /* Valores usados para intercambio en vector Aristas */
        int peso;                                               /* Valor para intercambio en vector Aristas */
        
        for (unsigned i = head; i < Aristas.size(); ++i)
        {
            if (AristaDummy.peso > Aristas[i].peso)             /* Si el peso de la arista apuntada por head es mayor que alguna otra arista actualiza */
            {
                AristaDummy = Aristas[i];
                indice = i;                                     /* Guarda el indice usado para el intercambio de posiciones */
            }
        }

        if (indice != head)                                         /* Si la arista está en la posición apuntada por head, no haría ningún intercambio */
        {
            extremo1 = Aristas[head].extremo1;                      /* extremo1 ahora tiene el valor de extremo1 de la arista apuntada por head */
            extremo2 = Aristas[head].extremo2;                      /* extremo2 ahora tiene el valor de extremo2 de la arista apuntada por head */
            peso = Aristas[head].peso;                              /* peso ahora tiene el valor de peso de la arista apuntada por head */
            Aristas[head] = AristaDummy;                            /* Pongo en head la arista con menor peso */
            AristaDummy.extremo1 = extremo1;                        /* AristaDummy tiene en extremo1 el antiguo extremo1 guardado anteriormente */
            AristaDummy.extremo2 = extremo2;                        /* AristaDummy tiene en extremo2 el antiguo extremo2 guardado anteriormente */
            AristaDummy.peso = peso;                                /* AristaDummy tiene en peso el antiguo peso guardado anteriormente */
            Aristas[indice] = AristaDummy;                          /* Pongo en la posicion indice (puesto de la arista cambiada de sitio )en vector Aristas el contenido de AristasDummy */
        }

        if (Raiz[Aristas[head].extremo1] != Raiz[Aristas[head].extremo2])   /* Si las componentes conexas son distintas, es candidato a solución */
        {
            pesoMST = pesoMST + Aristas[head].peso;                         /* Incrementamos el peso de MST */
            Raiz[Aristas[head].extremo1] = Raiz[Aristas[head].extremo2];    /* Igualamos las componentes conexas */
            a = a + 1;                                                      /* Incrementamos contador de aristas */
            cout << "Arista numero " << a << " incorporada (" << Aristas[head].extremo1 + 1 << ", " << Aristas[head].extremo2 + 1 << "), con peso " << Aristas[head].peso << endl;
        }
        head = head + 1;                                                    /* Incrementamos head, ahora apunta a la siguiente posicion */

        } while ((a < (n-1)) && (head < m));

        if (a == (n - 1)){
            cout << "El peso del arbol generador de minimo coste es " << pesoMST << endl << endl;
        }
        else {
            cout << "El grafo no es conexo, y el bosque generador de minimo coste tiene peso " << pesoMST << endl << endl;
        };
}


GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
    build(nombrefichero, errorapertura);
}

GRAFO
GRAFO::build(char nombrefichero[], int &errorapertura)
{
    int i, j, c;
    ElementoLista dummy;
    std::ifstream textfile;
    textfile.open(nombrefichero);

    if (textfile.is_open())
    {
        errorapertura = 0;
        textfile >> static_cast<unsigned&> (n)
                 >> static_cast<unsigned&> (m)
                 >> static_cast<unsigned&> (dirigido);

        (*this).LS.resize(n);
        if (Es_dirigido() == 1){
            (*this).LP.resize(n);
            for (unsigned int k = 0; k < (*this).m; ++k){
                textfile >> i >> j >> c;
                dummy.j = j - 1;
                dummy.c = c;
                LS[i-1].push_back(dummy);
                dummy.j = i - 1;
                dummy.c = c;
                LP[j-1].push_back(dummy);
            }
        }
        if (Es_dirigido() == 0){
            for (unsigned int k = 0; k < (*this).m; ++k){
                textfile >> i >> j >> c;
                dummy.j = j - 1;
                dummy.c = c;
                LS[i-1].push_back(dummy);
                if (i != j){
                    dummy.j = i - 1;
                    dummy.c = c;
                    LS[j-1].push_back(dummy);
                }
            }
        }
    }
    else errorapertura = 1;
    return *this;
}




