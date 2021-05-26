#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>
using namespace std;


const int INFTY = INT_MAX;
int costoTotal = 0;
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)

int n, m; 
vector<vector<int>> graph;
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



int main() {

    cin >> n >> m;
    graph.assign(n+1, vector<int>(n+1, INFTY));
    int i, j, c;
    forn(k, m){
        // vector<int> v(n+1, INFTY);
        cin >> i >> j >> c;
        i--;
        j--;
        graph[i][j] = c;
        graph[j][i] = c;
        
        //cout << cc << "\n";
    }

    
    auto start = chrono::steady_clock::now();
    //computamos....
    vector<int> H = vecinoMasCercano(graph);
    
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();
    
    // Imprimimos el tiempo de ejecución por stderr.
    // clog << total_time << endl;
    cout << H.size() <<" "<< costoTotal <<endl;
    for (int i = 0; i < H.size(); i++)
    {
        cout << H[i] <<" ";
    }
    cout << endl;
    
	return 0;

}

// /cd "/" && g++ -std=c++11 tp2.cpp -o tp2 && "/"tp2cd "/" && g++ -std=c++11 tp2.cpp -o tp2 && "/"tp2