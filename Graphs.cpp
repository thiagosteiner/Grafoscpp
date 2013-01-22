/* 
 * File:   Graphs.cpp
 * Author: Administrador
 * 
 * Created on 17 de Janeiro de 2013, 01:11
 */

#include "Graphs.h"
#include "Heap.h"

void Graphs::open(const char* file_name)
{
    vector <int> ::iterator it;
    vector <double> ::iterator it2;
    number_vertex = 0;
    number_edges = 0;
    medium_degree = 0;
    edges_list.erase(it = edges_list.begin(), it = edges_list.end());
    degrees_list.erase(it = degrees_list.begin(), it = degrees_list.end());
    degrees_counter.erase(it = degrees_counter.begin(), it = degrees_counter.end());
    weight.erase(it2 = weight.begin(), it2 = weight.end());


    ifstream myfile_open(file_name);

    if(myfile_open.is_open())
    {
        string first_line;
        getline(myfile_open,first_line); //takes the first line
        stringstream ss(first_line);
        ss >> number_vertex; // loads into number_vertex


        while(myfile_open)
        {
            string line_counter;
            string token;
            int edges_aux;
            getline(myfile_open,line_counter); // takes all the lines except the first
            number_edges++;
            stringstream iss(line_counter);

            while(getline(iss, token, ' ')) // brakes lines in the space
            {
                stringstream ess(token);
                ess >> edges_aux; //loads into edges_aux
                edges_list.push_back(edges_aux); // puts edges_aux in the vector edges_list
            }

        }

        number_edges = number_edges -1;

        if(edges_list.size() == 3 * number_edges)
        {
            for(int i = 2; i < edges_list.size(); i+=2)
            {
                weight.push_back(edges_list[i]);
                edges_list.erase(edges_list.begin()+i);
            }
        }


        for(int i = 1; i <= number_vertex; i++)
        {
            int counter = count(edges_list.begin(),edges_list.end(),i); // counts the degrees of all vertex
            //          cout << counter << "\n";
            degrees_list.push_back(counter); // puts counter in the vector degrees_list
        }

        int max_degree;
        int min_degree;
        max_degree = *max_element(degrees_list.begin(),degrees_list.end()); // takes the bigger degree
        min_degree = *min_element(degrees_list.begin(),degrees_list.end()); // takes the lower degree



        for(int i = 0; i <= max_degree; i++)
        {
            int counter = count(degrees_list.begin(),degrees_list.end(),i); // counts how many times a degree appears
            degrees_counter.push_back(counter); // puts counter in the vector degrees_counter
        }
        //        cout << degrees_counter.size() << "\n";


        myfile_open.close();

        medium_degree = 2.0*number_edges/number_vertex;


        cout << "# n = " << number_vertex << "\n";
        cout << "# m = " << number_edges << "\n";
        cout << "# d_medio = " << medium_degree << "\n";
//                cout << edges_list.size() << "\n";
//                cout << max_degree << "\n";
//                cout << min_degree << "\n";
//                cout << degrees_list.size() << "\n";
//                for (it = edges_list.begin(); it != edges_list.end(); it++)
//                    cout << *it << "\n";
//                for (it2 = weight.begin(); it2 != weight.end(); it2++)
//                    cout << *it2 << "\n";


    }

    else cout << "File not found" << "\n";

}


void Graphs::output(const char* fname)
{
    ofstream myfile_out;
    myfile_out.open(fname);
    if(myfile_out.is_open())
    {
        myfile_out << "# n = " << number_vertex << "\n";
        myfile_out << "# m = " << number_edges << "\n";
        myfile_out << "# d_medio = " << medium_degree << "\n";
        for(int i = 0; i < degrees_counter.size(); i++)
        {
            myfile_out << i << "  " << 1.0*degrees_counter[i]/number_vertex << "\n"; // empirical distribution
        }
        myfile_out.close();
    }
    else cout << "Unable to create file" << "\n";
}


void Graphs::matrix()
{
    adjacency_matrix.resize(number_vertex+1,vector<bool>(number_vertex+1,false));

    int i = 0;
    int j = 1;
    for (i,j; i <= edges_list.size(),j <= edges_list.size(); i+=2,j+=2)
    {
        int aux_i = edges_list[i];
        int aux_j = edges_list[j];
        adjacency_matrix[aux_i][aux_j] = 1;
        adjacency_matrix[aux_j][aux_i] = 1;
    }
//        for(int i = 1; i <= number_vertex; i++)
//            for(int j = 1; j <= number_vertex; j++)
//                cout << i << " " << j << " " << adjacency_matrix[i][j] << "\n";
    choice = 0;
}

void Graphs::list_adj()
{
    adjacency_list.resize(number_vertex+1);

    int i = 0;
    int j = 1;
    for (i,j; i <= edges_list.size(),j <= edges_list.size(); i+=2,j+=2)
    {
        int aux_i = edges_list[i];
        int aux_j = edges_list[j];
        adjacency_list[aux_i].push_back(aux_j);
        adjacency_list[aux_j].push_back(aux_i);
    }
//        for(int i = 1; i <= number_vertex; i++)
//            for(int j = 0; j < adjacency_list[i].size(); j++)
//                cout << i << " " << j << " " << adjacency_list[i][j] << "\n";
    choice = 1;
}

void Graphs::BFS(int root)
{
    queue<int> queue_bfs;

    for(int i = 0; i < number_vertex; i++)
        mark.push_back(0);
    mark.insert(mark.begin()+root,1);
    for(int i = 0; i < number_vertex; i++)
        level.push_back(0);
    level.insert(level.begin()+root,0);
    for(int i = 0; i < number_vertex; i++)
        father.push_back(0);
    father.insert(father.begin()+root,0);
    queue_bfs.push(root);
    if(choice == 0)
    {
        while(!queue_bfs.empty())
        {
            int queue_first = queue_bfs.front();
            queue_bfs.pop();
            for(int i = 1; i <= number_vertex; i++)
            {
                if(adjacency_matrix[queue_first][i] == 1 && mark[i] == 0)
                {
                    mark[i] = 1;
                    queue_bfs.push(i);
                    level[i] = level[queue_first] + 1;
                    father[i] = queue_first;
                }
            }
        }
    }

    if(choice == 1)
    {
        while(!queue_bfs.empty())
        {
            int queue_first = queue_bfs.front();
            queue_bfs.pop();
            for(int j = 0; j < degrees_list[queue_first-1]; j++)
                if(mark[adjacency_list[queue_first][j]] == 0)
                {
                    mark[adjacency_list[queue_first][j]] = 1;
                    queue_bfs.push(adjacency_list[queue_first][j]);
                    level[adjacency_list[queue_first][j]] = level[queue_first] + 1;
                    father[adjacency_list[queue_first][j]] = queue_first;
                }
        }
    }
}


void Graphs::DFS(int root)
{
    stack<int> stack_dfs;

    for(int i = 0; i < number_vertex; i++)
        mark.push_back(0);
    for(int i = 0; i < number_vertex; i++)
        level.push_back(0);
    level.insert(level.begin()+root,0);
    for(int i = 0; i < number_vertex; i++)
        father.push_back(0);
    father.insert(father.begin()+root,0);
    stack_dfs.push(root);

    if(choice == 0)
    {
        while(!stack_dfs.empty())
        {
            int stack_first = stack_dfs.top();
            stack_dfs.pop();
            if(mark[stack_first] == 0)
            {
                mark[stack_first] = 1;
                for(int i = number_vertex; i >= 1; i--)
                {
                    if(adjacency_matrix[stack_first][i] == 1 && mark[i] == 0)
                    {
                        stack_dfs.push(i);
                        level[i] = level[stack_first] + 1;
                        father[i] = stack_first;
                    }
                }
            }
        }
    }

    if(choice == 1)
    {
        while(!stack_dfs.empty())
        {
            int stack_first = stack_dfs.top();
            stack_dfs.pop();
            if(mark[stack_first] == 0)
            {
                mark[stack_first] = 1;
                for(int j = 0; j < degrees_list[stack_first-1]; j++)
                    if(mark[adjacency_list[stack_first][j]] == 0)
                    {
                        stack_dfs.push(adjacency_list[stack_first][j]);
                        level[adjacency_list[stack_first][j]] = level[stack_first] + 1;
                        father[adjacency_list[stack_first][j]] = stack_first;
                    }
            }
        }
    }
}

void Graphs::representation_out(const char *fname)
{
    ofstream myfile_out;
    myfile_out.open(fname);
    if(myfile_out.is_open())
    {
        for(int i = 1; i <= number_vertex; i++)
            myfile_out << i << " " << "level = " << level[i] << " " << "father = " << father[i] << "\n";
        myfile_out.close();
    }
    else cout << "Unable to create file" << "\n";
}

stringstream comp;

void Graphs::components(int root,const char *fname)
{
    queue<int> queue_component;
    vector<int> component_vertex;
    int number_components = 1;
    vector <int> ::iterator it;

    component_vertex.erase(it = component_vertex.begin(), it = component_vertex.end());

        mark.resize(number_vertex);
        mark.insert(mark.begin()+root,1);
        queue_component.push(root);
        component_vertex.push_back(root);
        if(choice == 0)
        {
            while(!queue_component.empty())
            {
                int queue_first = queue_component.front();
                queue_component.pop();
                for(int i = 1; i <= number_vertex; i++)
                {
                    if(adjacency_matrix[queue_first][i] == 1 && mark[i] == 0)
                    {
                        mark[i] = 1;
                        queue_component.push(i);
                        component_vertex.push_back(i);
                    }
                }
            }
        }

        if(choice == 1)
        {
            while(!queue_component.empty())
            {
                int queue_first = queue_component.front();
                queue_component.pop();
                for(int j = 0; j < degrees_list[queue_first-1]; j++)
                    if(mark[adjacency_list[queue_first][j]] == 0)
                    {
                        mark[adjacency_list[queue_first][j]] = 1;
                        queue_component.push(adjacency_list[queue_first][j]);
                        component_vertex.push_back(adjacency_list[queue_first][j]);
                    }
            }
        }


        comp << "Numero de vertices da componente abaixo = " << component_vertex.size() << "\n";
        for(int i = 0; i < component_vertex.size(); i++)
            comp << component_vertex[i] << "\n";

    for(int i = root; i < mark.size(); i++)
    {
        if(mark[i] != 1)
        {
            number_components++;
            components(i,fname);
        }
    }

        ofstream myfile_out;
        myfile_out.open(fname);
        string dummy;
        if(myfile_out.is_open())
        {
            dummy = comp.str();
            myfile_out << dummy;
        }
        else cout << "Unable to create file" << "\n";

    myfile_out << "Numero de componentes conexas = " << number_components << "\n";
    myfile_out.close();

}


