/**
 * @brief 
 * Heuristica Constructiva del Vecino Mas Cercano (VMC)
 * En cada paso elegimos como siguiente lugar a vistar el que, 
 * entre los que todavı́a no visitados, se encuentre más cerca de donde nos encontramos.
 */

#include "vecMasCerHeur.h"
vector<int> vecinoMasCercano(vector<vector<int>> &g){
    costoTotal = 0;
    vector<bool> visitados(n, false);
    // nodo inicial
    int v0 = 0;
    int v = 0;
    visitados[v] = true;
    vector<int> H;
    H.push_back(v);
    int w;
    for (int i = 1; i < n; i++)
    {
        //{4,1,2,8,0}
        w = -1;
        int min = INFTY;
        for (int j = 0; j < n; j++)
        {
            if(!visitados[j] && j != v){
                if (min > g[v][j] ){
                    w = j;
                    min = g[v][j];
                }
            }
        }
        visitados[w] = true;
        costoTotal += g[v][w];
        H.push_back(w);
        v = w;
    }
    costoTotal += g[w][v0];
    H.push_back(H[0]);
    return H;
}

