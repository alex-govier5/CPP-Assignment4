#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Node {
	friend class Graph;
	friend class Forest;

	int data;
	Node* next;
};

class Graph {

protected:
	vector<Node*> vertices;

public:
	Graph();
	Graph(int);
	Graph(const Graph&);
	~Graph();
	int size();
	bool vertex_exist(int);
	bool add_edge(int, int);
	void remove_edge(int, int);
	bool edge_exist(int, int);
	int get_degree(int);
	Graph operator ++();
	Graph& operator++(int);
	Graph operator --();
	Graph& operator--(int);
	bool path_exist(int, int);
	vector<int> BFS(int);
	int get_data(Node*);
	Node* get_next(Node*);
	friend ostream& operator <<(ostream&, Graph);

};