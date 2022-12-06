#include "Tree.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Tree::Tree() {
	root = 1;
}

Tree Tree::operator++() {
	add_vertex(size());
	return *this;
}

Tree& Tree::operator++(int a) {
	add_vertex(size());
	return *this;
}


void Tree::add_vertex(int a) {

	Node* node = new Node();
	node->data = size() + 1;
	node->next = NULL;
	vertices.push_back(node);

	if (!vertex_exist(a)) {
		return;
	}

	Node* temp = vertices[a - 1];
	
	Node* new_node = new Node();
	new_node->data = size();
	new_node->next = NULL;
	while (temp->next != NULL && temp->next->data < new_node->data) {
		temp = temp->next;
	}
	new_node->next = temp->next;
	temp->next = new_node;
	if (a == size()) {
		return;
	}

	Node* temp2 = vertices[size()-1];
	Node* new_node2 = new Node();
	new_node2->data = a;
	new_node2->next = NULL;
	while (temp2->next != NULL && temp2->next->data < new_node2->data) {
		temp2 = temp2->next;
	}
	new_node2->next = temp2->next;
	temp2->next = new_node2;
}

void Tree::set_root(int node) {
	if (vertex_exist(node)) {
		root = node;
	}
}

Tree Tree::operator--() {
	if (size() == 1) {
		return *this;
	}
	int tempCount = size() - 1;
	int value = vertices[tempCount]->data;

	for (int i = 0; i < size() - 1; i++) {
		if (vertices[i] != NULL) {
			Node* temp = vertices[i];
			while (temp->next != NULL) {
				if (temp->data == value) {
					remove_edge(vertices[i]->data, temp->data);
				}
				temp = temp->next;
			}
			if (temp->data == value) {
				remove_edge(vertices[i]->data, temp->data);
			}
		}
	}
	vertices.pop_back();
	return *this;
}

Tree& Tree::operator--(int a) {
	if (size() == 1) {
		return *this;
	}
	int tempCount = size() - 1;
	int value = vertices[tempCount]->data;

	for (int i = 0; i < size() - 1; i++) {
		if (vertices[i] != NULL) {
			Node* temp = vertices[i];
			while (temp->next != NULL) {
				if (temp->data == value) {
					remove_edge(vertices[i]->data, temp->data);
				}
				temp = temp->next;
			}
			if (temp->data == value) {
				remove_edge(vertices[i]->data, temp->data);
			}
		}
	}
	vertices.pop_back();
	return *this;
}

void Tree::print() {
	vector<bool> visited;
	for (int i = 0; i < size() + 1; i++) {
		visited.push_back(false);
	}
	print(1, root, visited);
}

void Tree::print(int level, int node, vector<bool> visited) {
	for (int i = 1; i < level; i++) {
		if (i == level - 1) {
			cout << "---";
		}
		else {
			cout << "    ";
		}

	}
	cout << to_string(node) << endl;
	visited[node] = true;
	Node* v = vertices[node - 1];
	while (v->next != NULL) {
		if (visited[v->data]) {
			v = v->next;
		}
		else {
			visited[v->data] = true;
			print(level + 1, v->data, visited);
			v = v->next;
		}
	}
	if (visited[v->data]) {
		v = v->next;
	}
	else {
		visited[v->data] = true;
		print(level + 1, v->data, visited);
		v = v->next;
	}
}

int Tree::get_root() {
	return root;
}


ostream& operator <<(ostream& out, Tree t) {
	return out;
}

