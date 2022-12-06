#pragma once
#include "Forest.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Tree : public Forest {

protected:
    int root;

public:
    Tree();
    Tree operator ++();
    Tree& operator ++(int);
    Tree operator --();
    Tree& operator --(int);
    int get_root();
    void add_vertex(int); 
    void set_root(int);
    void print();
    void print(int, int, vector<bool>);
    friend ostream& operator <<(ostream&, Tree);
};
