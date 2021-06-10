/* 
===================================================================================================
| TRABAJO PRACTICO 2 -The travelling salesman problem-Algoritmos y Estructura de Datos III - FCEN |
===================================================================================================
*/
#include "agmHeur.cpp" 
#include "heurInsercion.cpp" 
#include "vecMasCerHeur.cpp"
#include "tabuSearchE.cpp" 
#include "tabuSearchC.cpp" 

int main(int argc, char** argv) {

    // Leemos el parametro que indica el algoritmo a ejecutar.
    map<string, string> algoritmos_implementados = {
        {"AGMH", "Heuristica basada en AGM"}, {"VMC", "Heuristica del vecino mas cercano"}, {"HI", "Heuristica por Insercion"}, 
        {"TSE-AGM", "Tabu Seach basada en estructuras, usando AGMH"}, {"TSE-VMC", "Tabu Seach basada en estructuras usando VMC "},{"TSE-HI","Tabu Seach basada en estructuras usando HI"},
        {"TSC-AGM", "Tabu Seach basada en ciclos, usando AGMH"}, {"TSC-VMC", "Tabu Seach basada en ciclos, usando VMC "},{"TSC-HI","Tabu Seach basada en ciclos, usando HI"},

    };

    // Verificar que el algoritmo pedido exista.
    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];
    int iteraciones = 10;
    int longitudMemo = 20;
    int porcentajeVecindad = 30;
    if(argc == 5){
        longitudMemo = stoi(argv[2]);
        porcentajeVecindad = stoi(argv[3]);
        iteraciones = stoi(argv[4]);
    }
    cin >> n >> m;
    int i, j, c;
    graph.assign(n, vector<int>(n, INFTY));
    forn(k, m){
        // vector<int> v(n+1, INFTY);
        cin >> i >> j >> c;
        i--;
        j--;
        graph[i][j] = c;
        graph[j][i] = c;
        edges.push_back({i,j,c});
    }

    
    vector<int> ciclo;
    string heuristica;
    costoTotal = 0;
    auto start = chrono::steady_clock::now();
    //computamos....
    if (algoritmo == "AGMH")
    {
        ciclo = heur_AGM(graph);

    }else if (algoritmo == "VMC")
    {
        ciclo = vecinoMasCercano(graph);

    }else if (algoritmo == "HI")
    {
        ciclo = h_insertion(graph);
    }else if (algoritmo == "TSE-AGM")
    {
        heuristica = "AGM";
        ciclo = tabuSearchE(iteraciones,longitudMemo,porcentajeVecindad,graph,heuristica);
        
    }else if (algoritmo == "TSE-VMC")
    {
        heuristica = "VMC";
        ciclo = tabuSearchE(iteraciones,longitudMemo,porcentajeVecindad,graph,heuristica);

    }else if (algoritmo == "TSE-HI")
    {
        heuristica = "HI";
        ciclo = tabuSearchE(iteraciones,longitudMemo,porcentajeVecindad,graph,heuristica);

    }else if (algoritmo == "TSC-AGM")
    {
        heuristica = "AGM";
        ciclo = tabuSearchC(iteraciones,longitudMemo,porcentajeVecindad,graph,heuristica);
        
    }else if (algoritmo == "TSC-VMC")
    {
        heuristica = "VMC";
        ciclo = tabuSearchC(iteraciones,longitudMemo,porcentajeVecindad,graph,heuristica);

    }else if (algoritmo == "TSC-HI")
    {
        heuristica = "HI";
        ciclo = tabuSearchC(iteraciones,longitudMemo,porcentajeVecindad,graph,heuristica);

    }
    
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();
    int costoSolucion = costo(ciclo,graph);
    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;
    //cout << costoTotal << endl<<flush;
    cout << costoSolucion << endl<<flush;
    // cout << ciclo.size()<< endl;// <<" "<< costoTotal <<endl;
    // for (int i = 0; i < ciclo.size(); i++)
    // {
    //     cout << ciclo[i] <<" ";
    // }
    // cout << endl;
    printD(ciclo);
	return 0;

}

// /cd "/" && g++ -std=c++11 tp2.cpp -o tp2 && "/"tp2cd "/" && g++ -std=c++11 tp2.cpp -o tp2 && "/"tp2