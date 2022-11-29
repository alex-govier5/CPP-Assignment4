#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//Default constructor
Graph::Graph() {
	Node* new_node = new Node();
	new_node->data = 1;
	new_node->next = NULL;
	vertices.push_back(new_node);
}

//User constructor
Graph::Graph(int n) {
	if (n <= 0) {
		return;
	}
	for (int i = 0; i < n; i++) {
		Node* new_node = new Node();
		new_node->data = i + 1;
		new_node->next = NULL;
		vertices.push_back(new_node);
	}
}

//Copy constructor
Graph::Graph(const Graph& g) {
	for (int i = 0; i < g.vertices.size(); i++) {
		vertices.push_back(g.vertices[i]);
	}
}

//Destructor
Graph::~Graph() {
	vertices.clear();
}

//Number of vertices
int Graph::size() {
	return vertices.size();
}

//Helper method to see if a vertex exists in a graph
bool Graph::vertex_exist(int n) {
	if (n < 0 || n > size()) {
		return false;
	}
	for (int i = 0; i < size(); i++) {
		if (vertices[i]->data == n) {
			return true;
		}
	}
	return false;
}

//Method to add an edge to the graph
bool Graph::add_edge(int a, int b) {
	if (!(vertex_exist(a) && vertex_exist(b))) {
		
		return false;
	}
	if (edge_exist(a, b)) {
		return false;
	}
	//Adding b to a's list
	Node* temp = vertices[a - 1];
	Node* new_node = new Node();
	new_node->data = b;
	new_node->next = NULL;
	while (temp->next != NULL && temp->next->data < new_node->data) {
		temp = temp->next;
	}
	new_node->next = temp->next;
	temp->next = new_node;
	if (a == b) {
		return true;
	}

	//Adding a to b's list
	Node* temp2 = vertices[b - 1];
	Node* new_node2 = new Node();
	new_node2->data = a;
	new_node2->next = NULL;
	while (temp2->next != NULL && temp2->next->data < new_node2->data) {
		temp2 = temp2->next;
	}
	new_node2->next = temp2->next;
	temp2->next = new_node2;
	return true;
}

//Method to remove a given edge from the graph
void Graph::remove_edge(int a, int b) {
	if (!(vertex_exist(a) && vertex_exist(b))) {
		return;
	}
	if (!edge_exist(a, b)) {
		return;
	}
	//Deleting edge between ab
	Node* current;
	for (current = vertices[a - 1]; current->next != NULL; current = current->next) {
		if (current->next->data == b) {
			Node* temp = current->next;
			current->next = current->next->next;
			delete temp;
			break;
		}
	}
	//Deleting edge between ba
	Node* current2;
	for (current2 = vertices[b - 1]; current2->next != NULL; current2 = current2->next) {
		if (current2->next->data == a) {
			Node* temp2 = current2->next;
			current2->next = current2->next->next;
			delete temp2;
			break;
		}
	}
}

//Method to check if an edge exists in a graph
bool Graph::edge_exist(int a, int b) {
	if (!(vertex_exist(a) && vertex_exist(b))) {
		return false;
	}

	bool result = false;
	int count = 0;
	Node* temp = vertices[a - 1];
	while (temp->next != NULL) {
		if (temp->data == b && count != 0) {
			result = true;
		}
		temp = temp->next;
		count++;
	}
	if (temp->data == b) {
		result = true;
	}
	int count2 = 0;
	Node* temp2 = vertices[b - 1];
	while (temp2->next != NULL) {
		if (temp2->data == a && count2 != 0) {
			result = true;
		}
		temp2 = temp2->next;
		count2++;
	}
	if (temp2->data == a) {
		result = true;
	}
	return result;
}

//Method to get the degree of a given vertex in a graph
int Graph::get_degree(int a) {
	if (!(vertex_exist(a))) {
		return false;
	}
	int result = 0;
	Node* temp = vertices[a - 1];
	while (temp->next != NULL) {
		result++;
		temp = temp->next;
	}
	return result;
}

//Operator that adds a vertex to a graph with no new edges
Graph Graph::operator ++() {
	Node* new_node = new Node();
	new_node->data = size()+1;
	new_node->next = NULL;
	vertices.push_back(new_node);
	return *this;
}

//Operator that adds a vertex to a graph with no new edges
Graph& Graph::operator ++(int a) {
	Node* new_node = new Node();
	new_node->data = size()+1;
	new_node->next = NULL;
	vertices.push_back(new_node);
	return *this;
}

//Operator that removes the last vertex in a graph and all of its corresponding connections
Graph Graph::operator --() {
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

//Operator that removes the last vertex in a graph and all of its corresponding connections
Graph& Graph::operator --(int a) {
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

//BFS algorithm implemented using STL
vector<int> Graph::BFS(int a) {
	if (!vertex_exist(a)) {
		vector<int> tmp;
		return tmp;
	}
	Node* node = vertices[a - 1];

	vector<bool> visited;
	for (int i = 0; i < size(); i++) {
		visited.push_back(false);
	}

	vector<int> result;
	int temp = 0;

	queue<int> holder;
	visited[node->data - 1] = true;
	holder.push(node->data);

	while (holder.size() != 0) {
		temp = holder.front();
		result.push_back(temp);

		holder.pop();
		Node* current = vertices[temp - 1];

		while (current->next != NULL) {
			current = current->next;
			if (!visited[current->data - 1]) {
				visited[current->data - 1] = true;
				holder.push(current->data);
			}
		}
	}
	return result;

}

//Method to check whether a path exists in a graph using BFS
bool Graph::path_exist(int a, int b) {
	if (a == b) {
		return true;
	}
	vector<int> result = BFS(a);
	for (int i = 0; i < result.size(); i++) {
		if (result[i] == b) {
			return true;
		}
	}
	return false;
}

//Getter method to get Node data
int Graph::get_data(Node* n) {
	return n->data;
}

//Getter method to get a Node's next Node
Node* Graph::get_next(Node* n) {
	return n->next;
}

//Operator to output a graph to the user
ostream& operator <<(ostream& out, Graph g) {
	if (g.size() == 0) {
		out << "V = {}" << endl;
		out << "E = {}" << endl;
		return out;
	}
	out << "V = {";
	for (int i = 0; i < g.size() - 1; i++) {
		out << g.get_data(g.vertices[i]) << ", ";
	}
	out << g.get_data(g.vertices[g.size() - 1]);
	out << "}" << endl;
	out << "E = " << endl;
	out << "{" << endl;
	for (int i = 0; i < g.size(); i++) {
		out << "   " << g.get_data(g.vertices[i]) << " => ";
		Node* temp = g.vertices[i];
		if (g.get_next(temp) == NULL) {
			out << "None" << endl;
			continue;
		}
		while (g.get_next(g.get_next(temp)) != NULL) {
			out << g.get_data(g.get_next(temp)) << ", ";
			temp = g.get_next(temp);
		}
		out << g.get_data(g.get_next(temp)) << endl;
	}
	out << "}";
	return out;

}