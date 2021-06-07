/**
 * @brief 
 * Metaheuristica TabuSearch-Basada en estructuras (aristas)
 * Guı́a una heurı́stica de búsqueda local para explorar el espacio
 * de soluciones, con el principal objetivo de evitar quedar
 * atascados en un óptimo local.
 */



#include "tabuSearchE.h"


void recordar(pair<Edge, Edge> swap, vector<pair<Edge, Edge>> &memo, int index){
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
// porcentaje es un valor en el rango [1 .. 100]
vector<pair<Edge, Edge>> obtenerSubvecindad(vector<int>& ciclo, int porcentaje, vector<vector<int>> &graph){
    vector<pair<Edge, Edge>> vecindad;
    int s = ciclo.size();
    forn(i,s){
        for(int j = i+2; j < s-1; j++){
            Edge ar1 = {ciclo[i],ciclo[i+1],0};
            Edge ar2 = {ciclo[j],ciclo[j+1],0};
            vecindad.push_back(make_pair(ar1,ar2));
            //cout<<"("<<ciclo[i]<<"-"<<ciclo[i+1]<< ")"<<"("<<ciclo[j]<<"-"<<ciclo[j+1]<< ")"<<endl;
        }
        //cout<<"-\n";
    }
    random_shuffle(vecindad.begin(), vecindad.end());
    int subvecindad = (vecindad.size()*porcentaje)/100;
    vecindad.resize(subvecindad);
    //cout<<"vecindad: "<<vecindad.size()<<endl;
    return vecindad;
}

// antes chequear que vecinos no sea vacio
pair<Edge,Edge> obtenerMejor(int costoCiclo, vector<pair<Edge, Edge>>& vecinos, vector<pair<Edge, Edge>>& mem, vector<vector<int>>& graph, bool aspiracion){
    Edge e1 = {-1,-1,-1};
    Edge e2 = {-1,-1,-1};
    pair<Edge,Edge> sol = make_pair(e1,e2);
    int a,b; //e=(a->b) 
    int c,d; //e=(c->d)
    //a = get<0>(sol).u;
    //b = get<0>(sol).v;
    //c = get<1>(sol).u;
    //d = get<1>(sol).v;
    a = get<0>(vecinos[0]).u;
    b = get<0>(vecinos[0]).v;
    c = get<1>(vecinos[0]).u;
    d = get<1>(vecinos[0]).v;
    //int costoMinimo = costoCiclo;
    int costoMinimo = costoCiclo - graph[a][b]- graph[c][d] + graph[a][c] + graph[b][d];//minimo vecino
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
        if(!esTabu && costo <= costoMinimo){//int((costo*99)/100) //int((costo*80)/100) 1000inserciones
            costoMinimo = costo;
            sol = edges;
        }
    }
    return sol;
}

vector<int> reconstruirCiclo(vector<int>& ciclo, pair<Edge,Edge> swap){
    vector<int> nuevoCiclo = ciclo;
    int a,b; //e=(a->b) 
    int c,d; //e=(c->d)
    a = get<0>(swap).u;
    b = get<0>(swap).v;
    c = get<1>(swap).u;
    d = get<1>(swap).v;
    int i = 0, j = 0;
    for(int k = 0; k<ciclo.size(); k++){
        if(ciclo[k] == a) i = k;
        if(ciclo[k] == c){
          j = k;
          break;  
        }
    }
    // ciclo = .. a b .. c d ..
    // nuevoCiclo = .. a c .. b d ..
    //swap
    nuevoCiclo[i+1] = ciclo[j]; // (a,b) ==> (a,c)
    nuevoCiclo[j] = ciclo[i+1]; // (c,d) ==> (b,d)
    /*
        ciclo[i] = a;
        ciclo[i+1] = b;
        ciclo[i+2] = ..
        ..
        ciclo[j-1] = ..
        ciclo[j] = c;
        ciclo[j+1] = d;
    */
    //dar vuelta nuevoCiclo[c..b]
    int l1 = i+2;
    int l2 = j-1;
    while(l1 < j){
        nuevoCiclo[l1] = ciclo[l2];
        l1++;
        l2--;
    }
    return nuevoCiclo;
}

vector<int> tabuSearchE(int iters, int t, int porcentaje, vector<vector<int>> &graph, string heuristica){
    vector<int> ciclo;
    if (heuristica == "AGM"){
        ciclo = heur_AGM(graph);
    }else if (heuristica == "VMC"){ 
        ciclo = vecinoMasCercano(graph);
    }else{ 
        ciclo = h_insertion(graph);
    }
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
        //else inserciones++; 
        //verificar si obtuve solucion si los pares de aristas son invalidas
        ciclo = reconstruirCiclo(ciclo, mejoresAristas);
        
        recordar(mejoresAristas, memo, indexMemo); // guarda el movimiento inverso
        indexMemo++;
        indexMemo %= t;
        costoCiclo = costo(ciclo,graph); 
        if(costoCiclo < costoMejor){
            mejor = ciclo;
            costoMejor = costoCiclo; 
        }
    }
    //cout<<"total inserciones: "<<inserciones<<endl;
    costoTotal = costoMejor;
    return mejor;
}

