#include "Tree.h"
#include <iostream>
#include <vector>
using namespace std;

Tree::Tree(){
    Node* new_Node = new Node();
	new_Node->data = 1;
	new_Node->next = NULL;
	vertices.push_back(new_Node);
}

Tree Tree::operator++(){
    Node* new_node = new Node();
	new_node->data = size()+1;
	new_node->next = NULL;
	vertices.push_back(new_node);
    add_edge(size()-1, new_node->data);
	return *this;
}

void Tree::add_vertex(int a, int b){
	add_edge(a, b);
}

void Tree::set_root(int node){

}

Tree Tree::operator--(){
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

int main(){
    return 0;
}