#pragma once
/**
 * Class representing a weighted graph.
 */
#include "Edge.h"

class Graph {
public:
	Graph() : V(0), E(0), edges(0) { }
	Graph(int numV, int numE);
	~Graph();

	int V;
	int E;
	Edge* edges;
};

Graph::Graph(int numV, int numE) : V(numV), E(numE) {
	if (E != 0) {
		edges = new Edge[E];
	}
}

Graph::~Graph() {
	if (edges != 0) {
		delete[] edges;
	}
}
