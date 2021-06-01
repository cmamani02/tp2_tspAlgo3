
#include "tabuSearch.h"
// #include "agmHeur.cpp"


// ciclo = v u .. w v
int costo(vector<int>& ciclo, vector<vector<int>> &graph){
    int costo = 0;
    for (int i = 1; i < ciclo.size(); i++){
        costo += graph[ciclo[i-1]][ciclo[i]];
    }
    return costo;
}
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
    // falta retornar porcentaje de vecindad random
    random_shuffle(vecindad.begin(), vecindad.end());
    int subvecindad = (vecindad.size()*porcentaje)/100;
    vecindad.resize(subvecindad);
    return vecindad;
}

// antes chequear que vecinos no sea vacio
pair<Edge,Edge> obtenerMejor(int costoCiclo, vector<pair<Edge, Edge>>& vecinos, vector<pair<Edge, Edge>>& mem, vector<vector<int>>& graph, bool aspiracion){
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

vector<int> tabuSearch(int iters, int t, int porcentaje, vector<vector<int>> &graph){
    vector<int> ciclo = heur_AGM(graph);
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

