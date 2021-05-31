#include "agmHeur.h"
#include <algorithm>


#ifndef __AGMHEUR_H__
#define __AGMHEUR_H__

#ifndef __VECMASCERHEUR_H__
#define __VECMASCERHEUR_H__



vector<pair<Edge, Edge>> obtenerSubvecindad(vector<int>& ciclo,int porcentaje,vector<vector<int>> &graph);
pair<Edge,Edge> obtenerMejor(int costoCiclo, vector<pair<Edge, Edge>>& vecinos, vector<pair<Edge, Edge>>& mem, vector<vector<int>>& graph, bool aspiracion);
vector<int> reconstruirCiclo(vector<int>& ciclo, pair<Edge,Edge> swap);
vector<int> tabuSearch(int iters, int t, int porcentaje,vector<vector<int>> &graph);
int costo(vector<int>& ciclo, vector<vector<int>> &graph);
void recordar(pair<Edge, Edge> swap, vector<pair<Edge, Edge>> &memo, int index);

#endif
#endif