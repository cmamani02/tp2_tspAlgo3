#include <bits/stdc++.h>

using namespace std; 

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)

const int MAXN = 10000;
const int INF = 1000000000;

// implementacion vista en clase

int n, m;
struct Edge
{
    int u, v, weight;
    bool operator<(Edge const& other){
        return weight < other.weight;
    }
};

vector<Edge> edges;

vector<int> altura, padre;

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

void dfs(int v){
    recorrido_dfs.push_back(v);
    visited[v] = true;
    for(int y: g[v]){
        if(!visited[y]){
            dfs(y);
            recorrido_dfs.push_back(v);      
        }
    }
}

vector<int> crearCiclo(vector<int>&rec_dfs){
    vector<int> H;
    vector<bool> agregados(rec_dfs.size(),false);
    for (int i = 0; i < rec_dfs.size(); i++)
    {
        if (!agregados[i]){
            agregados[i] = true;
            H.push_back(i);
        }
    }
    return H;
}

vector<int> heur_AGM(vector<vector<int>> &graph){
    agm_Kruskal(edges,n);
    dfs(1);
    return crearCiclo(recorrido_dfs);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // inicializar y probar.
    // visitado.resize(n, false);
    // int a,b;

    // forn(i,m){
    //     cin >> a >> b;
    //     a--;
    //     b--;
    //     g[a].push_back(b);
    //     g[b].push_back(a);
    // }

	return 0;
}
