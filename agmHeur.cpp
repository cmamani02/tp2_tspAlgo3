/**
 * @brief 
 * Heuristica basa en el Algoritmo de Arbol Generador Minimo (AGM) 
 * Lo primero que hace este algoritmo es buscar un AGM del grafo T . 
 * Recorre los vértices según DFS. 
 * Por último, arma un circuito hamiltoniano recorriendo los vértices en este orden y agregando
 * la arista desde el último vertice al primero.
 */


#include "agmHeur.h"

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

/*
iteraciones = 100; //serian los saltos
C --> C1 
Subvecindario(C): C1 es el mejor con aristas <(32,3), (7,26), p >
mientras....
para i j:
    vecindario.push_back({i,j})
i = ramdom(longi(vecindaio))
j = 
(i,....,j)

subvecindario = random(vecindario, 20%)
random_shuffle(vecindario.begin(), vecidario.end());
// T = 10;
memo = [<(32,3), (7,26)>, ......., (e1,e2)]

}
*/

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

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     cin >> n >> m;
    
//     graph.assign(n, vector<int>(n, INFTY)); //matriz de adyacencia
    
//     int i, j, c;
//     // la entrada son nodos de 1 .. n, se representan como 0 .. n-1
//     forn(k, m){
//         cin >> i >> j >> c;
//         i--;
//         j--;
//         graph[i][j] = c;
//         graph[j][i] = c;
//         edges.push_back({i,j,c});
//     }

//     vector<int> test = heur_AGM(graph);
//     // cout << "AGM: " << endl;
//     // printT(agm);
//     // cout << "Recorrido dfs desde vertice 0: " << endl;
//     // printD(recorrido_dfs);
//     // cout << "crear ciclo en base a recorrido dfs: " << endl;
//     // printD(test);
    
//     vector<int> ciclo_tabu = tabuSearch(10,20,30,graph);
//     printD(ciclo_tabu);


//     //cout<<agm.size()<< " " << agm[1].size() << "\n";
    
//     // TEST crear ciclo:
//     // vector<int> v1 = {1,1};
//     // vector<int> test1 = crearCiclo(v1, 2);
//     // cout << "T1: " << endl;
//     // printD(test1);

//     // vector<int> v2 = {1,2,1,1};
//     // vector<int> test2 = crearCiclo(v2, 3);
//     // cout << "T2: " << endl;
//     // printD(test2);

//     // vector<int> v3 = {1,2,1,0,2,1};
//     // vector<int> test3 = crearCiclo(v3, 3);
//     // cout << "T3: " << endl;
//     // printD(test3);
// 	return 0;
// }
