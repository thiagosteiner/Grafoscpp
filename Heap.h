/* 
 * File:   Head.h
 * Author: Administrador
 *
 * Created on 17 de Janeiro de 2013, 01:03
 */

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

class Heap {
public:
    Heap();
    ~Heap();
    void insert(int element, int position);
    void insert(int element);
    int deletemin();
    void print();
    int size();
    int getmin();
private:
    int left(int parent);
    int right(int parent);
    int parent(int child);
    void heapifyup(int index);
    void heapifydown(int index);
private:
    vector<double> heap;
};

#endif // HEAP_H


