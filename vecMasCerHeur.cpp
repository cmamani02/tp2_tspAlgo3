
#include "vecMasCerHeur.h"
int costoTotal = 0;
vector<int> vecinoMasCercano(vector<vector<int>>& g){

    vector<bool> visitados(n+1, false);
    // nodo inicial
    int v0 = 1;
    int v = 1;
    visitados[v] = true;
    vector<int> H;
    H.push_back(v);
    int w;
    for (int i = 2; i < n+1; i++)
    {
        //{4,1,2,8,0}
        w = -1;
        int min = INFTY;
        for (int j = 1; j < n+1; j++)
        {
            if(!visitados[j] && j != v){
                if (min > g[v][j] ){w = j;}
            }
        }
        visitados[w] = true;
        costoTotal += g[v][w];
        H.push_back(w);
        v = w;
    }
    costoTotal += g[w][v0];

    return H;
}

