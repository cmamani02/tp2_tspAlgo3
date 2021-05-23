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

const int MAXN = 10000;
const int INF = 1000000000;
const int INFTY = INT_MAX;

struct Edge {
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
    agm = vector<vector<int>>(n+1);
    //vector<Edge> result;
    padre = vector<int>(n+1);
    altura = vector<int>(n+1);
    init(n+1);
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

void printD(vector<int> v){
    cout << "[";
    for(int i=0; i< v.size() -1;i++){
        cout << v[i] << ",";
    }
    if(v.size() > 0){cout << v[v.size()-1];}
    cout <<"]"<< endl;
}

void printT(vector<vector<int>> v){
    cout << "{";
    for(int i=0; i< v.size() -1;i++){
    		printD(v[i]);
        cout << ",";
    }
    if(v.size() > 0){printD(v[v.size()-1]);}
    cout <<"}"<< endl;
}


int main() {
    cin >> n >> m;
    graph.assign(n+1, vector<int>(n+1, INFTY));
    vector<Edge> edges;
    int i, j, c;
    forn(k, m){
        cin >> i >> j >> c;
        graph[i][j] = c;
        graph[j][i] = c;
        edges.push_back({i,j,c});
        // edges.push_back({j,i,c});
    }
    agm_Kruskal(edges,n);   
    // printT(agm);
    cout<<agm.size()<< " " << agm[1].size() << "\n";
	return 0;

}

// {[1,2,3],
// [1,4,5],
// []}


