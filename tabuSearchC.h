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

vector<int> obtenerMejorC(int costoCiclo, vector<pair<Edge, Edge>>& vecinos, vector<vector<int>>& mem, vector<vector<int>>& graph, bool aspiracion,vector<int> &cicloActual);
vector<int> tabuSearchC(int iters, int t, int porcentaje,vector<vector<int>> &graph,string heuristica);
void recordar(vector<vector<int>> &memo, int index, vector<int> &nuevoCiclo);

#endif
#endif
#endif
#endif

