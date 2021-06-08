
/**
 * @brief 
 * Metaheuristica TabuSearch-Basada en ciclos
 * Guı́a una heurı́stica de búsqueda local para explorar el espacio
 * de soluciones, con el principal objetivo de evitar quedar
 * atascados en un óptimo local.
 */



#include "tabuSearchC.h"

void recordar(vector<vector<int>> &memo, int index, vector<int> &nuevoCiclo){
    vector<int> tmp = nuevoCiclo;
    memo[index].swap(tmp);
}

bool mismoCiclo(vector<int> &ciclo1, vector<int> &ciclo2){
    if(ciclo1.size() != ciclo2.size()) return false;
    for (int  i = 0; i < ciclo1.size(); i++){
        if (ciclo1[i] != ciclo2[i]) return false;
    }
    return true;
}

bool esTabu(vector<int> &mejorCiclo, vector<vector<int>> &memo){
    for (int i = 0; i < memo.size(); i++){
        if (mismoCiclo(memo[i],mejorCiclo)) return true;
    }
    return false;
}

// antes chequear que vecinos no sea vacio
vector<int> obtenerMejorC(int costoCiclo, vector<pair<Edge, Edge>>& vecinos, vector<vector<int>>& mem, vector<vector<int>>& graph, bool aspiracion,vector<int> &cicloActual){
    int a,b; //e=(a->b) 
    int c,d; //e=(c->d)
    a = get<0>(vecinos[0]).u;
    b = get<0>(vecinos[0]).v;
    c = get<1>(vecinos[0]).u;
    d = get<1>(vecinos[0]).v;
    vector<int> mejorCiclo = reconstruirCiclo(cicloActual,vecinos[0]);
    //vector<int> mejorCiclo = cicloActual;
    //int costoMinimo = costoCiclo;// - graph[a][b]- graph[c][d] + graph[a][c] + graph[b][d]; 
    int costoMinimo = costoCiclo - graph[a][b]- graph[c][d] + graph[a][c] + graph[b][d];//minimo vecino
    for (auto edges : vecinos){
        a = get<0>(edges).u;
        b = get<0>(edges).v;
        c = get<1>(edges).u;
        d = get<1>(edges).v;
        int costoActual = costoCiclo - graph[a][b]- graph[c][d] + graph[a][c] + graph[b][d];
        vector<int> mejorCicloActual = reconstruirCiclo(cicloActual,edges);    
        // contemplar funcion de aspiracion
        if(!esTabu(mejorCicloActual,mem) && costoActual <= costoMinimo){
            costoMinimo = costoActual;
            mejorCiclo = mejorCicloActual;
        }
    }
    return mejorCiclo;
}

vector<int> tabuSearchC(int iters, int t, int porcentaje, vector<vector<int>> &graph, string heuristica){
    vector<int> ciclo;
    if (heuristica == "AGM"){
        ciclo = heur_AGM(graph);
    }else if (heuristica == "VMC"){ 
        ciclo = vecinoMasCercano(graph);
    }else{ 
        ciclo = h_insertion(graph);
    }
    int costoCiclo = costo(ciclo,graph);
    vector<int> mejorCiclo = ciclo;
    int costoMejor = costoCiclo;
    bool aspiracion = false;
    int indexMemo = 0;
    vector<vector<int>> memo(t);

    for(int i = 0; i<iters; i++){
        vector<pair<Edge, Edge>> vecinos = obtenerSubvecindad(ciclo, porcentaje, graph);
        if(vecinos.empty()) break;
        // busco aristas a quitar
        //vector<int> mejorCicloVec = obtenerMejorC(costoCiclo, vecinos, memo, graph, aspiracion,mejorCiclo); //for....vecinos...
        ciclo = obtenerMejorC(costoCiclo, vecinos, memo, graph, aspiracion,ciclo); //for....vecinos...
        if(ciclo.empty()) continue;
        //if(mejorCicloVec.empty()) continue;
        //recordar
        //recordar(memo,indexMemo,mejorCicloVec);
        recordar(memo,indexMemo,ciclo);
        indexMemo++;
        indexMemo %= t;
        //costoCiclo = costo(mejorCicloVec,graph);
        costoCiclo = costo(ciclo,graph);  
        if(costoCiclo < costoMejor){
            //mejorCiclo = mejorCicloVec;
            mejorCiclo = ciclo;
            costoMejor = costoCiclo; 
        }
    }
    costoTotal = costoMejor;
    return mejorCiclo;
}

