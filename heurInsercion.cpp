/**
 * @brief 
 * Heuristica Constructiva de Insercion
 * Las heurı́sticas de inserción comienzan con un ciclo cualquiera y en cada 
 * iteración incorporan un vértice al ciclo hasta llegar a incorporar a 
 * todos los vértices. En general la selección del próximo vértice a incorporar y donde
 * insertarlo son decisiones golosas.
 */



#include "heurInsercion.h"

vector<int> ciclo_h;                /** vector que me da el recorrido del ciclo hamiltoniano**/
vector<int> ciclo;                  /** vector de vértices que están en el ciclo hamiltoniano**/
vector<bool> usado;
int INFINIT = INT_MAX;

vector<int> h_insertion(vector<vector<int>> &graph){
    
    /** inicializo las estracturas de datos usadas **/
    ciclo_h.assign(n, 0);
    ciclo_h[0] = 1, ciclo_h[1] = 2, ciclo_h[2]= 0;
    costoTotal = graph[0][1] + graph[1][2] + graph[2][0];

    for(int i = 0; i < 3; i++) ciclo.push_back(i);

    usado.assign(n, false);
    for(int i = 0; i < 3; i++) usado[i] = true;

    int arista = INFINIT;
    int adyacente;
    int min_costo_aux, dif_aristas;
    int new_vertex, vertice, aux_vertex;

    while(ciclo.size() != n){
        arista = INFINIT;
        /** ELEGIR: busco el vertice mas cercano al ciclo **/
        for(int v: ciclo){
            for(int i = 0; i < n; i++){
                if(graph[v][i] < arista && usado[i] == false){
                    arista = graph[v][i];
                    new_vertex = i;
                }
            }
        }

        min_costo_aux = INFINIT;

        /** INSERTAR: inserto el nuevo vertice al ciclo **/
        for(int v: ciclo){
            adyacente = ciclo_h[v];                             /** vertice adyacente a v en el ciclo **/
            dif_aristas = costoTotal + graph[v][new_vertex] + graph[new_vertex][adyacente] - graph[v][adyacente];
            if(dif_aristas < min_costo_aux){
                //min = dif_aristas;
                min_costo_aux = dif_aristas;
                vertice = v;
            }
        }

        /** Actualizo el ciclo hamiltoniano y los vectores de datos**/
        aux_vertex = ciclo_h[vertice];
        ciclo_h[vertice] = new_vertex;
        ciclo_h[new_vertex] = aux_vertex;
        usado[new_vertex] = true;
        ciclo.push_back(new_vertex);
        costoTotal = min_costo_aux;

    }

    /** Armo la solución **/
    vector<int> res;
    int v = 0;
    while(res.size() != n){
        res.push_back(v);
        v = ciclo_h[v];
        if(v == 0) break;
    }
    res.push_back(res[0]);
    costoTotal = costo(res,graph);
    return res;
}

// int main() {

//     cin >> n >> m;
//     graph.assign(n+1, vector<int>(n+1, INFINIT));       // incializo la matriz de adyacencia
//     int v1, v2, arista;

//     for(int i = 0; i < m; i++){
//         cin >> v1 >> v2 >> arista;
//         graph[v1][v2] = arista;
//         graph[v2][v1] = arista;
//     }

//     vector<int> hamiltoniano = h_insertion(graph);

//     /** imprimo por pantalla los resultados **/
//     cout << hamiltoniano.size() << " " << costo << endl;
//     for(int i = 0; i < hamiltoniano.size(); i++){
//         cout << hamiltoniano[i] << " ";
//     }
//     cout << endl;

//     return 0;
// }
