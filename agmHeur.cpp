/**
 * @brief 
 * Heuristica basa en el Algoritmo de Arbol Generador Minimo (AGM) 
 * Lo primero que hace este algoritmo es buscar un AGM del grafo T . 
 * Recorre los vértices según DFS. 
 * Por último, arma un circuito hamiltoniano recorriendo los vértices en este orden y agregando
 * la arista desde el último vertice al primero.
 */


#include "agmHeur.h"
// ciclo = v u .. w v
int costo(vector<int>& ciclo, vector<vector<int>> &graph){
    int costo = 0;
    for (int i = 1; i < ciclo.size(); i++){
        costo += graph[ciclo[i-1]][ciclo[i]];
    }
    return costo;
}
// OJO: inicializar los vectores con longitud n
void init(int n){
    forn(i, n){
        altura[i] = 1; // altura es una cota superior de la altura
        padre[i] = i;
    }
}

int find(int x){
    if(padre[x] != x)
        padre[x] = find(padre[x]);
    return padre[x];
} 

void union_set(int x, int y){
    x = find(x), y = find(y); // tomo los representantes de cada conjunto
    if(altura[x] < altura[y]){
        padre[x] = y;
    }
    else{
        padre[y] = x;
    }
    if(altura[x] == altura[y])
        altura[x]++;
}

// int cost = 0;
vector<vector<int>> agm;
void agm_Kruskal(vector<Edge>& edges, int n){
    agm = vector<vector<int>>(n);
    //vector<Edge> result;
    padre = vector<int>(n);
    altura = vector<int>(n);
    init(n);
    sort(edges.begin(), edges.end());

    // kruskal + disjoint set union    

    for(Edge e : edges){
        if(find(e.u) != find(e.v)){ // nodos de distintas componentes conexas
            // cost += e.weight;
            agm[e.u].push_back(e.v);
            agm[e.v].push_back(e.u);
            //result.push_back(e);
            union_set(e.u, e.v);
        }
    }
}
// no devuelve lista de aristas, simplemente completa el agm

// PASO 2:
// inicializar con tamaño n
vector<int> recorrido_dfs;
vector<bool> visited;

void dfs(vector<vector<int>>& g, int v){
    recorrido_dfs.push_back(v);
    visited[v] = true;
    for(int y: g[v]){
        if(!visited[y]){
            dfs(g, y);
            recorrido_dfs.push_back(v);      
        }
    }
}

vector<int> crearCiclo(vector<int>& rec_dfs, int n){
    vector<int> H;
    vector<bool> agregados(n, false);
    for (int i = 0; i < rec_dfs.size(); i++)
    {
        if (!agregados[rec_dfs[i]]){
            agregados[rec_dfs[i]] = true;
            H.push_back(rec_dfs[i]);
        }
    }
    int size = rec_dfs.size();
    if(rec_dfs.size() > 0) H.push_back(rec_dfs[size-1]);
    return H;
}

vector<int> heur_AGM(vector<vector<int>> &graph){
    agm_Kruskal(edges,n);
    visited = vector<bool>(n, false); //inicializacion
    dfs(agm, 0);
    vector<int> ciclo = crearCiclo(recorrido_dfs, n);
    costoTotal = 0;
    costoTotal = costo(ciclo,graph);
    return ciclo;
}

// funciones para imprimir
void printD(vector<int>& v){
    //cout << "[";
    for(int i=0; i< v.size() -1;i++){
        cout << v[i]+1 << " ";
    }
    //if(v.size() > 0){cout << v[v.size()-1];}
    //cout <<"]"<< endl;
}

void printT(vector<vector<int>>& v){
    cout << "{";
    for(int i=0; i< v.size() -1;i++){
    	printD(v[i]);
        cout << ",";
    }
    if(v.size() > 0){printD(v[v.size()-1]);}
    cout <<"}"<< endl;
}
