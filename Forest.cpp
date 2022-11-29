#include "Forest.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

Forest::Forest() {
	Node* new_Node = new Node();
	new_Node->data = 1;
	new_Node->next = NULL;
	vertices.push_back(new_Node);
}

Forest::Forest(int n) {
	if (n <= 0) {
		return;
	}
	for (int i = 0; i < n; i++) {
		Node* new_Node = new Node();
		new_Node->data = i + 1;
		new_Node->next = NULL;
		vertices.push_back(new_Node);
	}
}

Forest::Forest(const Forest& f) {
	for (int i = 0; i < f.vertices.size(); i++) {
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
	Forest test = Forest(*this);
	Node* temp = test.vertices[a - 1];
	Node* new_Node = new Node();
	new_Node->data = b;
	new_Node->next = NULL;
	while (temp->next != NULL && temp->next->data < new_Node->data) {
		temp = temp->next;
	}
	new_Node->next = temp->next;
	temp->next = new_Node;

	Node* temp2 = test.vertices[b - 1];
	Node* new_Node2 = new Node();
	new_Node2->data = a;
	new_Node2->next = NULL;
	while (temp2->next != NULL && temp2->next->data < new_Node2->data) {
		temp2 = temp2->next;
	}
	new_Node2->next = temp2->next;
	temp2->next = new_Node2;

	vector<bool> visited;
	for (int i = 0; i < test.size(); i++) {
		visited.push_back(false);
	}

	for (int i = 0; i < test.size(); i++) {
		if (!visited[i]) {
			if (is_cycle(i, visited)) {
				return false;
			}
		}
	}

	Node* temp3 = test.vertices[a - 1];
	Node* new_Node3 = new Node();
	new_Node3->data = b;
	new_Node3->next = NULL;
	while (temp3->next != NULL && temp3->next->data < new_Node3->data) {
		temp3 = temp3->next;
	}
	new_Node3->next = temp3->next;
	temp3->next = new_Node3;

	Node* temp4 = vertices[b - 1];
	Node* new_Node4 = new Node();
	new_Node4->data = a;
	new_Node4->next = NULL;
	while (temp4->next != NULL && temp4->next->data < new_Node4->data) {
		temp4 = temp4->next;
	}
	new_Node4->next = temp4->next;
	temp4->next = new_Node4;
	return true;
}

bool Forest::is_cycle(int node, vector<bool> visited) {
	queue<vector<int>> queue;
	visited[node] = true;
	vector<int> v{ node,-1 };
	queue.push(v);
	while (!queue.empty()) {
		for (int i = 0; i < queue.size(); i++) {
			vector<int> temp = queue.front();
			queue.pop();
			int current = temp[0];
			int parent = temp[1];
			Node* child = vertices[current - 1];
			while (child->next != NULL) {
				child = child->next;
				if (visited[child->data - 1] && child->data != parent) {
					return true;
				}
				if (!visited[child->data - 1]) {
					visited[child->data - 1] = true;
					vector<int> v2{ child->data,current };
					queue.push(v2);
				}
			}
		}
	}
	return false;
}