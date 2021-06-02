#ifndef __AGMHEUR_H__
#define __AGMHEUR_H__
#ifndef __VECMASCERHEUR_H__
#define __VECMASCERHEUR_H__
#ifndef __TABUSEARCHC_H__
#define __TABUSEARCHC_H__
#ifndef __HEURINSERCION_H__
#define __HEURINSERCION_H__

#include "agmHeur.h"
#include "heurInsercion.h"
#include "vecMasCerHeur.h"
#include <bits/stdc++.h>
#include <algorithm>
#include "tabuSearchC.h"
using namespace std;

vector<pair<Edge, Edge>> obtenerSubvecindad(vector<int>& ciclo,int porcentaje,vector<vector<int>> &graph);
pair<Edge,Edge> obtenerMejor(int costoCiclo, vector<pair<Edge, Edge>>& vecinos, vector<pair<Edge, Edge>>& mem, vector<vector<int>>& graph, bool aspiracion);
vector<int> reconstruirCiclo(vector<int>& ciclo, pair<Edge,Edge> swap);
vector<int> tabuSearchE(int iters, int t, int porcentaje,vector<vector<int>> &graph,string heuristica);
void recordar(pair<Edge, Edge> swap, vector<pair<Edge, Edge>> &memo, int index);

#endif
#endif
#endif
#endif