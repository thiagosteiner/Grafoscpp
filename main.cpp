/* 
 * File:   main.cpp
 * Author: Administrador
 *
 * Created on 17 de Janeiro de 2013, 00:49
 */

#include <cstdlib>

#include "Graphs.h"
#include <time.h>

using namespace std;
Graphs graphs;

int main()
{
    clock_t t1;
    t1 = clock();
    graphs.open("C:/Users/Administrador/Documents/Dropbox/Teoria Grafos/Trabalhos/Trabalho C++/entradas/grafo_1.txt");
    double diff = (double)(clock() - t1)/CLOCKS_PER_SEC ;
    cout << endl << "The time taken for Breadth first search: "<< diff << endl;
//    graphs.output("C:/Users/Thiago/Documents/grafo_1_out.txt");
//    graphs.matrix();
//    graphs.list_adj();
//    clock_t t1;
//    t1 = clock();
//    graphs.BFS(1);
//    double diff = (double)(clock() - t1)/CLOCKS_PER_SEC ;
//    cout << endl << "The time taken for Breadth first search: "<< diff << endl;
//    graphs.representation_out("C:/Users/Thiago/Documents/grafo_1_bfs.txt");
//    graphs.DFS(1);
//    graphs.representation_out("C:/Users/Thiago/Documents/grafo_1_dfs.txt");
//    graphs.Dijkstra(1);
//    for(int i = 0; i < graphs.number_vertex; i++)
//    {
//        graphs.getneighbours(i+1);
//        if(graphs.neighbours.size() == 0)
//            cout << i+1 << " " << "desconexo" << endl;
//    }
//    graphs.getneighbours(92);

    return 0;
}


