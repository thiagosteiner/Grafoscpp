#include "Graphs.h"
#include "Heap.h"

void Graphs::Dijkstra(int root)
{
    vector <double> dist;
    vector <int> S;
    //S.resize(number_vertex);
    dist.resize(number_vertex+1,INT_MAX);
    vector<int>::iterator it;
    vector<double>::iterator it2;
    vector <bool> mark;
    mark.resize(number_vertex+1,0);
    Heap* myheap = new Heap();

    S.clear();

    dist[root] = 0;
    myheap->insert(dist[root]);
    mark[root] = 1;
    mark[0] = 1;
    while(S.size() != number_vertex)
    {
//        myheap->print();
        int min = myheap->getmin();
        myheap->deletemin();
        it2 = find(dist.begin(),dist.end(),min);
        if(it2 == dist.end())
        {
            min = myheap->getmin();
            myheap->deletemin();
            it2 = find(dist.begin(),dist.end(),min);
        }
        int u = distance(dist.begin(),it2);
        cout << u << endl;
        if(mark[u] == 1)
        {
            it2++;
            it2 = find(it2,dist.end(),min);
            u = distance(dist.begin(),it2);
        }
        mark[u] = 1;
        S.push_back(u+1);
        getneighbours(u+1);
        for(int i = 0; i < neighbours.size(); i++)
        {
            if(dist[neighbours[i] - 1] > dist[u] + edge_weight[i])
            {
                dist[neighbours[i] - 1] = dist[u] + edge_weight[i];
                myheap->insert(dist[neighbours[i] - 1]);
            }
        }
    }
    delete myheap;

    for (it2 = dist.begin(); it2 != dist.end(); it2++)
        cout << *it2 << "\n";
//    cout << endl;
//    for (it = S.begin(); it != S.end(); it++)
//        cout << *it << "\n";
}

void Graphs::getneighbours(int root)
{
    vector<int>::iterator it;
    vector<int>::iterator it2;
    vector<double>::iterator it3;
    neighbours.erase(it = neighbours.begin(), it = neighbours.end());
    edge_weight.erase(it3 = edge_weight.begin(), it3 = edge_weight.end());
    it = edges_list.begin();
    int counter = count(edges_list.begin(),edges_list.end(),root);
    while(counter > 0)
    {
        it = find(it,edges_list.end(),root);
        int dist = distance(edges_list.begin(),it);
        counter--;
        if(dist % 2 == 0)
        {
            it2 = it;
            it2++;
            neighbours.push_back(*it2);
            edge_weight.push_back(weight[dist/2]);
        }
        else
        {
            it2 = it;
            it2--;
            neighbours.push_back(*it2);
            dist -= 1;
            edge_weight.push_back(weight[dist/2]);
        }
        it++;
    }
//    for(it = neighbours.begin(),it3 = edge_weight.begin();it != neighbours.end(),it3 != edge_weight.end();it++,it3++)
//        cout << root << " " << *it << " " << *it3 << "\n";
}

