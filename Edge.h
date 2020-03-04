#pragma once
/**
 * Class representing an edge in a weighted graph.
 */

class Edge {

public:
	Edge() : u(0), v(0), w(0) { }
	Edge(int s, int d, int wt) : u(s), v(d), w(wt) { }

	void setEdge(int s, int d, int wt);

	int u;
	int v;
	int w;
};

void Edge::setEdge(int s, int d, int wt) {
	u = s;
	v = d;
	w = wt;
}