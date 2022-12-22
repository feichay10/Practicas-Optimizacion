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
    for (unsigned int i = 0; i < LS.size(); ++i)
    {
        LS[i].clear();
        LS[i].shrink_to_fit();
    }
    LS.clear();
    LS.shrink_to_fit();

    for (unsigned int i = 0; i < LP.size(); ++i)
    {
        LP[i].clear();
        LP[i].shrink_to_fit();
    }
    LP.clear();
    LP.shrink_to_fit();
}

void GRAFO::actualizar(char nombrefichero[85], int &errorapertura)
{
    for (unsigned int i = 0; i < LS.size(); ++i)
    {
        LS[i].clear();
        LS[i].shrink_to_fit();
    }
    LS.clear();
    LS.shrink_to_fit();

    for (unsigned int i = 0; i < LP.size(); ++i)
    {
        LP[i].clear();
        LP[i].shrink_to_fit();
    }
    LP.clear();
    LP.shrink_to_fit();
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
    cout << m << " " << endl
         << endl;
}

unsigned GRAFO::Es_dirigido()
{
    return dirigido;
}

//void Mostrar_Lista(vector<LA_nodo> L){}

void GRAFO::Mostrar_Listas(int l)
{
    if (l == 1)
    {
        cout << "|Dirigido|" << endl;
        cout << "|Nodos sucesores|" << endl;
        for (auto i = 0; i < LS.size(); ++i)
        {
            cout << "[" << i + 1 << "]: ";
            for (auto j = 0; j < LS[i].size(); ++j)
            {
                cout << LS[i][j].j + 1 << "|";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (l == 0)
    {
        cout << "|No dirigido|" << endl;
        cout << "|Lista de adyacencias|" << endl;
        for (auto i = 0; i < LS.size(); ++i)
        {
            cout << "[" << i + 1 << "]: ";
            for (auto j = 0; j < LS[i].size(); ++j)
            {
                cout << LS[i][j].j + 1 << "|";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (l == -1)
    {
        cout << "|Lista de predecesores|" << endl;
        for (auto i = 0; i < LP.size(); ++i)
        {
            cout << "[" << i + 1 << "]: ";
            for (auto j = 0; j < LP[i].size(); ++j)
            {
                cout << LP[i][j].j + 1 << "|";
            }
            cout << endl;
        }
        cout << endl;
    }
};

void GRAFO::dfs(unsigned i, vector<bool> &visitado)
{
    visitado[i] = true;
    cout << i + 1 << ", ";
    for (unsigned j = 0; j < LS[i].size(); j++)
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

    for (auto i = 0; i < visitado.size(); ++i)
    {
        if (visitado[i] == false)
        {
            ++componentesConexas;
            cout << "Componente conexa numero " << componentesConexas << " {";
            dfs(i, visitado);
            cout << "}" << endl;
        }
    }
    if (componentesConexas == 1)
        cout << "Es un grafo conexo" << endl
             << endl;
    else
        cout << "Es un grafo no conexo" << endl
             << endl;
}

//void GRAFO::ListaPredecesores(){}

void GRAFO::Kruskal()
{
    vector<AristaPesada> Aristas;

    /*Usaremos la busqueda del menor en cada momento, pues es el mejor para Kruskal que no exige tener todas las aristas ordenadas*/
    /*Cargamos todas las aristas de la lista de adyacencia*/

    Aristas.resize(m);

    unsigned k = 0;
    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < LS[i].size(); j++)
        {
            if (i < LS[i][j].j)
            {
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
    for (unsigned q = 0; q < n; q++)
    {
        Raiz[q] = q;
    };
    /*Comenzamos Kruskal*/
    do
    {
        /* Implementamos el algoritmo de Kruskal */

        AristaDummy = Aristas[head]; /* AristaDummy tiene una copia de la arista del vector Aristas apuntada por head */
        unsigned indice = head;      /* Indice usado para intercambios en el vector Aristas */
        unsigned extremo1, extremo2; /* Valores usados para intercambio en vector Aristas */
        int peso;                    /* Valor para intercambio en vector Aristas */

        for (unsigned i = head; i < Aristas.size(); ++i)
        {
            if (AristaDummy.peso > Aristas[i].peso) /* Si el peso de la arista apuntada por head es mayor que alguna otra arista actualiza */
            {
                AristaDummy = Aristas[i];
                indice = i; /* Guarda el indice usado para el intercambio de posiciones */
            }
        }

        if (indice != head) /* Si la arista está en la posición apuntada por head, no haría ningún intercambio */
        {
            extremo1 = Aristas[head].extremo1; /* extremo1 ahora tiene el valor de extremo1 de la arista apuntada por head */
            extremo2 = Aristas[head].extremo2; /* extremo2 ahora tiene el valor de extremo2 de la arista apuntada por head */
            peso = Aristas[head].peso;         /* peso ahora tiene el valor de peso de la arista apuntada por head */
            Aristas[head] = AristaDummy;       /* Pongo en head la arista con menor peso */
            AristaDummy.extremo1 = extremo1;   /* AristaDummy tiene en extremo1 el antiguo extremo1 guardado anteriormente */
            AristaDummy.extremo2 = extremo2;   /* AristaDummy tiene en extremo2 el antiguo extremo2 guardado anteriormente */
            AristaDummy.peso = peso;           /* AristaDummy tiene en peso el antiguo peso guardado anteriormente */
            Aristas[indice] = AristaDummy;     /* Pongo en la posicion indice (puesto de la arista cambiada de sitio )en vector Aristas el contenido de AristasDummy */
        }

        if (Raiz[Aristas[head].extremo1] != Raiz[Aristas[head].extremo2]) /* Si las componentes conexas son distintas, es candidato a solución */
        {
            pesoMST = pesoMST + Aristas[head].peso;                      /* Incrementamos el peso de MST */
            Raiz[Aristas[head].extremo1] = Raiz[Aristas[head].extremo2]; /* Igualamos las componentes conexas */
            a = a + 1;                                                   /* Incrementamos contador de aristas */
            cout << "Arista numero " << a << " incorporada (" << Aristas[head].extremo1 + 1 << ", " << Aristas[head].extremo2 + 1 << "), con peso " << Aristas[head].peso << endl;
        }
        head = head + 1; /* Incrementamos head, ahora apunta a la siguiente posicion */

    } while ((a < (n - 1)) && (head < m));

    if (a == (n - 1))
    {
        cout << "El peso del arbol generador de minimo coste es " << pesoMST << endl
             << endl;
    }
    else
    {
        cout << "El grafo no es conexo, y el bosque generador de minimo coste tiene peso " << pesoMST << endl
             << endl;
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
        textfile >> static_cast<unsigned &>(n) >> static_cast<unsigned &>(m) >> static_cast<unsigned &>(dirigido);

        (*this).LS.resize(n);
        if (Es_dirigido() == 1)
        {
            (*this).LP.resize(n);
            for (unsigned int k = 0; k < (*this).m; ++k)
            {
                textfile >> i >> j >> c;
                dummy.j = j - 1;
                dummy.c = c;
                LS[i - 1].push_back(dummy);
                dummy.j = i - 1;
                dummy.c = c;
                LP[j - 1].push_back(dummy);
            }
        }
        if (Es_dirigido() == 0)
        {
            for (unsigned int k = 0; k < (*this).m; ++k)
            {
                textfile >> i >> j >> c;
                dummy.j = j - 1;
                dummy.c = c;
                LS[i - 1].push_back(dummy);
                if (i != j)
                {
                    dummy.j = i - 1;
                    dummy.c = c;
                    LS[j - 1].push_back(dummy);
                }
            }
        }
    }
    else
        errorapertura = 1;
    return *this;
}

void MostrarCamino(unsigned s, unsigned i, std::vector<unsigned> pred)
{
    if (i != s)
    {
        MostrarCamino(s, pred[i], pred);
        std::cout << pred[i] + 1 << " -> ";
    }
}

void GRAFO::Dijkstra()
{
    vector<bool> PermanentementeEtiquetado;
    vector<int> d;
    vector<unsigned> pred;
    int min;
    unsigned s, candidato;

    //Inicialmente no hay ningun nodo permanentemente etiquetado
    PermanentementeEtiquetado.resize(n, false);
    //Inicialmente todas las etiquetas distancia son infinito
    d.resize(n, maxint);
    //Inicialmente el pred es null
    pred.resize(n, UERROR);

    //Solicitamos al usuario el nodo origen
    cout << endl;
    cout << "Caminos minimos: Dijkstra" << endl;
    cout << "Nodo de partida? [1-" << n << "]: ";
    cin >> (unsigned &)s;
    //La etiqueta distancia del nodo origen es 0, y es su propio pred
    d[--s] = 0;
    pred[s] = s;
    do
    {
        min = maxint; // La menor etiqueta distancia inicialmente es infinito

        for (int i = 0; i < n; ++i) // Recorremos los nodos del grafo buscando la menor etiqueta distancia
        {
            // Si el nodo i no esta permanentemente etiquetado y min vale infinito o si la etiqueta distancia del
            // nodo candidato es mayor que la etiqueta distancia del nodo i, actualizamos el valor min (menor etiqueta distancia) y el nodo candidato a ser permanentemente etiquetado
            if ((PermanentementeEtiquetado[i] == false) && (min == maxint || d[candidato] > d[i]))
            {
                if (d[i] != maxint) /* Si la etiqueta distancia de i no es infinito actualizamos el valor de la menor etiqueta distancia y guardamos el nodo candidato a ser permanentemente etiquetado */
                {
                    min = d[i];    /* min tiene el valor de la menor etiqueta distancia */
                    candidato = i; /* Guardamos el nodo candidato a ser permanentemente etiquetado */
                }
            }
        }

        if (min < maxint)
        {
            PermanentementeEtiquetado[candidato] = true; /* Etiquetamos permanentemente el nodo candidato */

            for (unsigned j = 0; j < LS[candidato].size(); ++j) /* Revisamos los nodos sucesores del nodo permanentemente etiquetado para buscar posibles atajos */
            {
                // Si el nodo sucesor j no esta permanentemente etiquetado y, ademas, si la etiqueta distancia
                // del nodo sucesor j es mayor que el coste del arco candidato-j + la etiqueta distancia del nodo candidato, actualizamos su etiqueta distancia y su pred
                if ((PermanentementeEtiquetado[LS[candidato][j].j] == false) && (d[LS[candidato][j].j] > LS[candidato][j].c + d[candidato]))
                {
                    {
                        d[LS[candidato][j].j] = LS[candidato][j].c + d[candidato]; /* La nueva etiqueta distancia del nodo sucesor j es: coste del arco candidato-j mas la etiqueta distancia del nodo candidato */
                        pred[LS[candidato][j].j] = candidato;                      /* El pred del nodo sucesor j es el nodo candidato */
                    }
                }
            }
        }

    } while (min < maxint);

    cout << "Soluciones:" << endl;
    //En esta parte del codigo, mostramos los caminos minimos, si los hay

    for (unsigned i = 0; i < n; ++i)
    {
        if (i != s)
        {
            // Si el pred del nodo i está definido, mostramos el camino
            if (pred[i] != UERROR)
            {
                cout << "Camino minimo del nodo " << s + 1 << " a " << i + 1 << ": ";
                MostrarCamino(s, i, pred);
                cout << i + 1 << " de longitud: " << d[i] << endl;
            }
            // Si el pred no está definido (UERROR), no hay camino minimo
            else
            {
                cout << "\nNo hay caminos minimos de " << s + 1 << " a " << i + 1 << endl;
            }
        }
    }
}

void GRAFO::BellmanEndFord()
{
    vector<int> d;
    vector<unsigned> pred;

    unsigned s, numeromejoras = 0;
    bool mejora;

    d.resize(n, maxint);
    pred.resize(n, UERROR);

    cout << "Encontrar caminos minimos con el algoritmo de Bellman-Ford-Moore" << endl;
    cout << "Nodo de partida? [1-" << n << "]: ";
    cin >> s;

    if (s < 1 || s > n)
        cout << "Ese nodo no existe." << endl;
    else
    {
        d[--s] = 0;
        pred[s] = s;

        do
        {
            mejora = false;
            for (int i = 0; i < LS.size(); i++)
            {
                for (int j = 0; j < LS[i].size(); j++)
                {
                    if (LS[i][j].c + d[i] < d[LS[i][j].j])
                    {
                        d[LS[i][j].j] = d[i] + LS[i][j].c;
                        pred[LS[i][j].j] = i;
                        mejora = true;
                    }
                }
            }
            numeromejoras++;

        } while ((mejora == true) && (numeromejoras < n));

        if (mejora == true)
            cout << "\nNo existen caminos mayores que 0.\n"
                 << endl;
        else
        {
            cout << "Soluciones: " << endl;
            for (int i = 0; i < n; i++)
            {
                if (i != s)
                {
                    if (pred[i] != UERROR)
                    {
                        cout << "\nCamino mínimo de " << s + 1 << " a " << i + 1 << ": { ";
                        MostrarCamino(s, i, pred);
                        cout << i + 1 << "} \t-Coste:" << d[i] << endl;
                    }
                    else
                        cout << "\nNo hay caminos mínimos de " << s + 1 << " a " << i + 1 << endl;
                }
            }
        }
    }
}