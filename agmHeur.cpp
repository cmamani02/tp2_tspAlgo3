#include <bits/stdc++.h>

using namespace std; 

#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define forn(i,n) forsn(i,0,n)

const int INFTY = INT_MAX;

// implementacion vista en clase

int n, m;
struct Edge
{
    int u, v, weight;
    bool operator<(Edge const& other){
        return weight < other.weight;
    }
};

int n, m;
vector<vector<int>> graph;
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
    return crearCiclo(recorrido_dfs, n);
}

// funciones para imprimir
void printD(vector<int>& v){
    cout << "[";
    for(int i=0; i< v.size() -1;i++){
        cout << v[i] << ",";
    }
    if(v.size() > 0){cout << v[v.size()-1];}
    cout <<"]"<< endl;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    
    graph.assign(n, vector<int>(n, INFTY)); //matriz de adyacencia
    
    int i, j, c;
    // la entrada son nodos de 1 .. n, se representan como 0 .. n-1
    forn(k, m){
        cin >> i >> j >> c;
        i--;
        j--;
        graph[i][j] = c;
        graph[j][i] = c;
        edges.push_back({i,j,c});
    }

    vector<int> test = heur_AGM(graph);
    cout << "AGM: " << endl;
    printT(agm);
    cout << "Recorrido dfs desde vertice 0: " << endl;
    printD(recorrido_dfs);
    cout << "crear ciclo en base a recorrido dfs: " << endl;
    printD(test);
    //cout<<agm.size()<< " " << agm[1].size() << "\n";
    
    // TEST crear ciclo:
    // vector<int> v1 = {1,1};
    // vector<int> test1 = crearCiclo(v1, 2);
    // cout << "T1: " << endl;
    // printD(test1);

    // vector<int> v2 = {1,2,1,1};
    // vector<int> test2 = crearCiclo(v2, 3);
    // cout << "T2: " << endl;
    // printD(test2);

    // vector<int> v3 = {1,2,1,0,2,1};
    // vector<int> test3 = crearCiclo(v3, 3);
    // cout << "T3: " << endl;
    // printD(test3);
	return 0;
}
