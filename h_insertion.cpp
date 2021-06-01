#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int n, m;
int INFINIT = INT_MAX;
vector<vector<int>> graph;          /** matriz de adyacencia **/

vector<int> ciclo_h;                /** vector que me da el recorrido del ciclo hamiltoniano**/
vector<int> ciclo;                  /** vector de vértices que están en el ciclo hamiltoniano**/
vector<bool> usado;
int costo;

//vector<int> no_visitados;
//for(int i = 4; i <= n; i++) no_visitados.push_back(i);

vector<int> h_insertion(vector<vector<int>> &graph){

    /** inicializo las estracturas de datos usadas **/
    ciclo_h.assign(n+1, 0);
    ciclo_h[1] = 2, ciclo_h[2] = 3, ciclo_h[3]= 1;
    costo = graph[1][2] + graph[2][3] + graph[3][1];

    //ciclo.assign(n+1, 0);
    //for(int i = 1;i <= 3; i++) ciclo.push_back(i);

    //ciclo.assign(n, 0);
    for(int i = 1; i <= 3; i++) ciclo.push_back(i);

    usado.assign(n+1, false);
    for(int i = 1; i <= 3; i++) usado[i] = true;

    int arista = INFINIT;
    int adyacente;
    int min_costo_aux, dif_aristas;
    int new_vertex, vertice, aux_vertex;

    while(ciclo.size() != n){
        /** ELEGIR: busco el vertice mas cercano al ciclo **/
        for(int v: ciclo){
            for(int i = 1; i <= n; i++){
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
            dif_aristas = costo + graph[v][new_vertex] + graph[new_vertex][adyacente] - graph[v][adyacente];
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
        costo = min_costo_aux;

    }

    /** Armo la solución **/
    vector<int> res;
    int v = 1;
    while(res.size() != n){
        res.push_back(v);
        v = ciclo_h[v];
        if(v == 1) break;
    }

    return res;
}

int main() {

    cin >> n >> m;
    graph.assign(n+1, vector<int>(n+1, INFINIT));       // incializo la matriz de adyacencia
    int v1, v2, arista;

    for(int i = 0; i < m; i++){
        cin >> v1 >> v2 >> arista;
        graph[v1][v2] = arista;
        graph[v2][v1] = arista;
    }

    vector<int> hamiltoniano = h_insertion(graph);

    /** imprimo por pantalla los resultados **/
    cout << hamiltoniano.size() << " " << costo << endl;
    for(int i = 0; i < hamiltoniano.size(); i++){
        cout << hamiltoniano[i] << " ";
    }
    cout << endl;

    return 0;
}
