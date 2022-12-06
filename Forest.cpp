#include "Forest.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

Forest::Forest() {

}

Forest::Forest(int n) {
	if (n <= 0) {
		return;
	}
	for (int i = 1; i < n; i++) {
		Node* new_Node = new Node();
		new_Node->data = i + 1;
		new_Node->next = NULL;
		vertices.push_back(new_Node);
	}
}

Forest::Forest(const Forest& f) {
	for (int i = 1; i < f.vertices.size(); i++) {
		vertices.push_back(f.vertices[i]);
	}
}

Forest::~Forest() {
	vertices.clear();
}

bool Forest::add_edge(int a, int b) {
	if (!(vertex_exist(a) && vertex_exist(b))) {

		return false;
	}
	if (edge_exist(a, b)) {
		return false;
	}

	Node* temp = vertices[a - 1];
	Node* new_Node = new Node();
	new_Node->data = b;
	new_Node->next = NULL;
	while (temp->next != NULL && temp->next->data < new_Node->data) {
		temp = temp->next;
	}
	new_Node->next = temp->next;
	temp->next = new_Node;

	Node* temp2 = vertices[b - 1];
	Node* new_Node2 = new Node();
	new_Node2->data = a;
	new_Node2->next = NULL;
	while (temp2->next != NULL && temp2->next->data < new_Node2->data) {
		temp2 = temp2->next;
	}
	new_Node2->next = temp2->next;
	temp2->next = new_Node2;
	
	vector<bool> visited;
	for (int i = 0; i < size()+1; i++) {
		visited.push_back(false);
	}
	
	for (int i = 1; i < size()+1; i++) {
		if (!visited[i]) {
			if (is_cycle(i, visited)) {
				remove_edge(a, b);
				return false;
			}
		}
	}

	
	return true;
}

bool Forest::is_cycle(int node, vector<bool> visited) {
	queue<vector<int>> queue;
	visited[node] = true;
	vector<int> v{ node,-1 };
	queue.push(v);
	while (!queue.empty()) {
		for (int i = 0; i < queue.size(); i++) {
			int current = queue.front()[0];
			int parent = queue.front()[1];
			queue.pop();
			Node* child = vertices[current-1];
			while (child->next != NULL) {
				child = child->next;
				if (visited[child->data] && child->data != parent) {
					cout << "HELLO" << endl;
					return true;
				}
				if (!visited[child->data]) {
					visited[child->data] = true;
					vector<int> v2{ child->data,current };
					queue.push(v2);
				}
			}
		}
	}
	return false;
}