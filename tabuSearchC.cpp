
/**
 * @brief 
 * Metaheuristica TabuSearch-Basada en ciclos
 * Guı́a una heurı́stica de búsqueda local para explorar el espacio
 * de soluciones, con el principal objetivo de evitar quedar
 * atascados en un óptimo local.
 */



#include "tabuSearchC.h"

void recordarC(pair<Edge, Edge> swap, vector<pair<Edge, Edge>> &memo, int index){
    int a,b; //e=(a->b) 
    int c,d; //e=(c->d)
    a = get<0>(swap).u;
    b = get<0>(swap).v;
    c = get<1>(swap).u;
    d = get<1>(swap).v;
    // aristas a insertar
    Edge e1 = {a,c,0};
    Edge e2 = {b,d,0};
    pair<Edge,Edge> aristaSwap = make_pair(e1,e2);
    memo[index] = aristaSwap;
}


// antes chequear que vecinos no sea vacio
pair<Edge,Edge> obtenerMejorC(int costoCiclo, vector<pair<Edge, Edge>>& vecinos, vector<pair<Edge, Edge>>& mem, vector<vector<int>>& graph, bool aspiracion){
    Edge e1 = {-1,-1,-1};
    Edge e2 = {-1,-1,-1};
    pair<Edge,Edge> sol = make_pair(e1,e2);
    int a,b; //e=(a->b) 
    int c,d; //e=(c->d)
    a = get<0>(sol).u;
    b = get<0>(sol).v;
    c = get<1>(sol).u;
    d = get<1>(sol).v;
    int costoMinimo = costoCiclo;// - graph[a][b]- graph[c][d] + graph[a][c] + graph[b][d]; 
    for (auto edges : vecinos){
        a = get<0>(edges).u;
        b = get<0>(edges).v;
        c = get<1>(edges).u;
        d = get<1>(edges).v;
        int costo = costoCiclo - graph[a][b]- graph[c][d] + graph[a][c] + graph[b][d];

        vector<pair<Edge, Edge>>::iterator it;
        it = find(mem.begin(),mem.end(),edges);
        bool esTabu = it != mem.end(); //true si edges esta en mem
        // contemplar funcion de aspiracion
        if(!esTabu && costo < costoMinimo){
            costoMinimo = costo;
            sol = edges;
        }
    }
    return sol;
}

vector<int> tabuSearchC(int iters, int t, int porcentaje, vector<vector<int>> &graph, string heuristica){
    vector<int> ciclo;
    if (heuristica == "AGM") ciclo = heur_AGM(graph);
    if (heuristica == "VCM") ciclo = vecinoMasCercano(graph);
    // if (heuristica == "HI") ciclo = heur_AGM(graph);
    
    int costoCiclo = costo(ciclo,graph);
    vector<int> mejor = ciclo;
    int costoMejor = costoCiclo;
    bool aspiracion = false;
    int indexMemo = 0;
    Edge e1 = {-1,-1,-1};
    Edge e2 = {-1,-1,-1};
    pair<Edge,Edge> inicial = make_pair(e1,e2);
    vector<pair<Edge, Edge>> memo(t,inicial);  
    
    for(int i = 0; i<iters; i++){
        vector<pair<Edge, Edge>> vecinos = obtenerSubvecindad(ciclo, porcentaje, graph);
        if(vecinos.empty()) break;
        // busco aristas a quitar
        pair<Edge, Edge> mejoresAristas = obtenerMejor(costoCiclo, vecinos, memo, graph, aspiracion); //for....vecinos...
        if(get<0>(mejoresAristas).u == -1) continue;
        //verificar si obtuve solucion si los pares de aristas son invalidas
        ciclo = reconstruirCiclo(ciclo, mejoresAristas);
        
        // CAMBIAR: se tiene que guardar la operacion inversa
        recordar(mejoresAristas, memo, indexMemo); // guarda el movimiento inverso
        indexMemo++;
        indexMemo %= t;
        costoCiclo = costo(ciclo,graph); 
        if(costoCiclo < costoMejor){
            mejor = ciclo;
            costoMejor = costoCiclo; 
        }
    }
    return mejor;
}

