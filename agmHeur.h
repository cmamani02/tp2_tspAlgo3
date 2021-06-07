#ifndef __TABUSEARCHE_H__
#define __TABUSEARCHE_H__

#ifndef __TABUSEARCHC_H__
#define __TABUSEARCHC_H__

#ifndef __VECMASCERHEUR_H__
#define __VECMASCERHEUR_H__

#ifndef __HEURINSERCION_H__
#define __HEURINSERCION_H__

#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include "tabuSearchE.h"
#include "tabuSearchC.h"
using namespace std; 

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)

const int INFTY = INT_MAX;
// implementacion vista en clase
int inserciones = 0;
int n, m;
int costoTotal;
struct Edge
{
    int u, v, weight;
    bool operator<(Edge const& other){
        return weight < other.weight;
    }
    
};

bool operator==(Edge const& other1,Edge const& other2){
    return other1.v == other2.v && other1.u == other2.u && other1.weight == other2.weight;
}
bool operator==(const pair<Edge,Edge>& lhs, const pair<Edge,Edge>& rhs)
{ return get<0>(lhs) == get<0>(rhs) && get<1>(lhs) == get<1>(rhs); }


vector<vector<int>> graph;
vector<Edge> edges;
vector<int> altura, padre;

void init(int n);
int find(int x);
void union_set(int x, int y);
void agm_Kruskal(vector<Edge>& edges, int n);
void dfs(vector<vector<int>>& g, int v);
vector<int> crearCiclo(vector<int>& rec_dfs, int n);
vector<int> heur_AGM(vector<vector<int>> &graph);
void printD(vector<int>& v);
void printT(vector<vector<int>>& v);
int costo(vector<int>& ciclo, vector<vector<int>> &graph);
#endif
#endif
#endif
#endif