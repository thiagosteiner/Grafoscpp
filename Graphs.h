/* 
 * File:   Graphs.h
 * Author: Administrador
 *
 * Created on 17 de Janeiro de 2013, 01:11
 */

#ifndef GRAPHS_H
#define GRAPHS_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <float.h>
using namespace std;

class Graphs {
public:
    vector <int> edges_list;
    vector <int> degrees_list;
    vector <int> degrees_counter;
    vector <double> weight;
    vector < vector<bool> > adjacency_matrix;
    vector < vector<int> > adjacency_list;
    vector < vector< vector <int> > > adjacency_list_weight;
    int number_vertex;
    int number_edges;
    double medium_degree;
    vector<int> level;
    vector<int> father;
    vector<bool> mark;
    vector<int> neighbours;
    vector<double> edge_weight;

    void open(const char* file_name);

    void output(const char* fname);

    void matrix();

    void list_adj();

    void BFS(int root);

    void DFS(int root);

    void representation_out(const char* fname);

    void components(int root, const char *fname);

    void Dijkstra(int root);

public:
    bool choice; //if you run by matrix choice=false and bfs,dfs runs by matrix and if you by list choice=true and bfs,dfs runs by list
    void getneighbours(int root);
};

#endif // GRAPHS_H


