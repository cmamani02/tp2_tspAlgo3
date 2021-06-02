#ifndef __AGMHEUR_H__
#define __AGMHEUR_H__

#ifndef __VECMASCERHEUR_H__
#define __VECMASCERHEUR_H__


#ifndef __TABUSEARCHE_H__
#define __TABUSEARCHE_H__

#ifndef __HEURINSERCION_H__
#define __HEURINSERCION_H__


#include "agmHeur.h"
#include "heurInsercion.h"
#include "vecMasCerHeur.h"
#include "tabuSearchE.h"
#include <algorithm>
pair<Edge,Edge> obtenerMejorC(int costoCiclo, vector<pair<Edge, Edge>>& vecinos, vector<pair<Edge, Edge>>& mem, vector<vector<int>>& graph, bool aspiracion);
vector<int> tabuSearchC(int iters, int t, int porcentaje,vector<vector<int>> &graph,string heuristica);
void recordarC(pair<Edge, Edge> swap, vector<pair<Edge, Edge>> &memo, int index);

#endif
#endif
#endif
#endif