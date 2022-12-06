#pragma once
#include "Graph.h"
#include <iostream>
#include <vector>
using namespace std;

class Forest : public Graph {

public:

	Forest();
	Forest(int);
	Forest(const Forest&);
	~Forest();
	bool add_edge(int, int);
	bool is_cycle(int, vector<bool>);

};