#pragma once
#include "Forest.h"
#include "Graph.h"
#include <iostream>
#include <vector>
using namespace std;

class Tree : public Forest {

    public:
        Tree();
        Tree operator ++();
        Tree operator --();
        void remove_edge(int, int);
        void add_vertex(int, int); // isn't this just add edge?
        void set_root(int);
        friend ostream& operator <<(ostream&, Tree);
};