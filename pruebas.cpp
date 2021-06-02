
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


// asume matriz de adyacencia
/*
vector<int> localSearch2opt(vector<vector<int>> &graph){
    vector<int> ciclo = heur_AGM(graph);
    int mejorCosto = 0; // costoCiclo(H);
    vector<int> cicloCandidato = ciclo;
    //mientras "haya mejora en ciclo"
    //ciclos => c1,c2,c3,...ck
    for(int k = 0; k<5; k++){// reveer esto
        forn(i, n){
            for(int j = i+1; j < n-1 && j-i > 1; j++){
                int nuevoCosto = mejorCosto;
                // si son consecutivos no hace falta
                int c_ui = graph[ciclo[i]][ciclo[i+1]]; // (i,i+1)
                int c_uj = graph[ciclo[j]][ciclo[j+1]]; // (j,j+1)
                //1,2,3,4,5,1  => 1,2, 5,1  => 1,4,5,1
                // resto 2 aristas, sumo 2 aristas
                nuevoCosto = mejorCosto - c_ui - c_uj + graph[ciclo[i]][ciclo[j]] + graph[ciclo[i+1]][ciclo[j+1]];      
                if(nuevoCosto < mejorCosto){
                    mejorCosto = nuevoCosto;
                    //ciclo = nuevo ciclo;
                    cicloCandidato = ciclo; //copia
                    cicloCandidato[i+1] = ciclo[j];
                    cicloCandidato[j] = ciclo[i+1];
                    int l1 = i+2;
                    //i i+1 [i+2  ... ] j, j+1
                    int l2 = j-1;
                    while(l1 < j){
                        cicloCandidato[l1] = ciclo[l2];
                        l2--;
                        l1++;
                    }
                }
            } 
        }
        //ciclo = cicloCandidato;        
    }
    return cicloCandidato;
}
*/

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
    // cin >> n >> m;
    // graph.assign(n+1, vector<int>(n+1, INFTY));
    // vector<Edge> edges;
    // int i, j, c;
    // forn(k, m){
    //     cin >> i >> j >> c;
    //     graph[i][j] = c;
    //     graph[j][i] = c;
    //     edges.push_back({i,j,c});
    //     // edges.push_back({j,i,c});
    // }
    // agm_Kruskal(edges,n);   
    // // printT(agm);
    // cout<<agm.size()<< " " << agm[1].size() << "\n"
    int t =3;
    int indice = 0;
    vector<vector<int>> memo(t);
    // int* pointer = memo[indice];
    vector<int> dato1 = {1,2,3};
    vector<int> dato2 = {11,21,31};
    vector<int> dato3 = {21,22,32};
    vector<int> dato4 = {212,222,232};
    // memo.at(indice) = dato1; 
    // memo.at(indice) = dato2; 
    // memo.at(indice) = dato3; 
    // printT(memo);
    memo[indice].swap(dato1);
    indice++;
    memo[indice].swap(dato2);
    indice++;
    memo[indice].swap(dato3);
    printT(memo);


	return 0;

}

/*
n m
4 6 
1 2 3
1 3 5
1 4 -1
2 3 1
2 4 10
3 4 3
*/
