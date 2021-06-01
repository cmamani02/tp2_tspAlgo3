/* 
===================================================================================================
| TRABAJO PRACTICO 2 -The travelling salesman problem-Algoritmos y Estructura de Datos III - FCEN |
===================================================================================================
*/

#include "agmHeur.cpp" 
#include "tabuSearch.cpp" 
#include "vecMasCerHeur.cpp" 

int main(int argc, char** argv) {

    // Leemos el parametro que indica el algoritmo a ejecutar.
    map<string, string> algoritmos_implementados = {
        {"AGMH", "Heuristica basada en AGM"}, {"VMC", "Heuristica del vecino mas cercano"}, {"HI", "Heuristica por Insercion"}, 
        {"TS-AGM", "Tabu Seach usando AGMH"}, {"TS-VMC", "Tabu Seach usando VMC "},{"TS-HI","Tabu Seach usando HI"}
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



    cin >> n >> m;
    graph.assign(n, vector<int>(n, INFTY));
    int i, j, c;
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
    // costoTotal = 1;
    auto start = chrono::steady_clock::now();
    //computamos....
    if (algoritmo == "AGMH")
    {
        //ciclo = heur_AGM(graph);
        ciclo = tabuSearch(10,20,30,graph);

    }else if (algoritmo == "VMC")
    {
        ciclo = vecinoMasCercano(graph);

    }else if (algoritmo == "HI")
    {
        

    }else if (algoritmo == "TS-AGMH")
    {


    }else if (algoritmo == "TS-VCM")
    {

    }else if (algoritmo == "TS-HI")
    {

    }
    
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();
    
    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;
    cout << costoTotal << endl<<flush;
    cout << ciclo.size()<< endl;// <<" "<< costoTotal <<endl;
    // for (int i = 0; i < ciclo.size(); i++)
    // {
    //     cout << ciclo[i] <<" ";
    // }
    // cout << endl;
    printD(ciclo);
	return 0;

}

// /cd "/" && g++ -std=c++11 tp2.cpp -o tp2 && "/"tp2cd "/" && g++ -std=c++11 tp2.cpp -o tp2 && "/"tp2