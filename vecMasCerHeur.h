#ifndef __AGMHEUR_H__
#define __AGMHEUR_H__

#ifndef __TABUSEARCHE_H__
#define __TABUSEARCHE_H__

#ifndef __TABUSEARCHC_H__
#define __TABUSEARCHC_H__

#ifndef __HEURINSERCION_H__
#define __HEURINSERCION_H__

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

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)

int n, m; 
const int INFTY = INT_MAX;
vector<vector<int>> graph;
vector<int> vecinoMasCercano(vector<vector<int>> &graph);

#endif
#endif
#endif
#endif
