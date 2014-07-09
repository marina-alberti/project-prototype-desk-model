/*
 * FunctionsMST.cpp
 *
 *  Created on: May 22, 2014
 *      Author: marina
 */

#include "Edge.hpp"
#include "Graph.hpp"
#include <algorithm>
#include "FunctionsMST.hpp"

#define DEBUG 1

using namespace std;

/*
 * @description:
 * Takes an item an return the disjoint set it belongs to.
 */
char doFind(int vertex) {
	if (PARENT[vertex] == vertex) {
		return PARENT[vertex];
	}
	else {
		return doFind(PARENT[vertex]);
	}
}

/*
 * @description:
 * Merges two "disjoint sets" of the two input items
 * into one disjoint set.
 */
void doUnion(int root1, int root2) {
	if (RANK[root1] > RANK[root2]) {
		PARENT[root2] = root1;
	}
	else if (RANK[root2] > RANK[root1]) {
		PARENT[root1] = root2;
	}
	else{
		PARENT[root1] = root2;
		RANK[root2]++;
	}
}

void makeSet(int vertex) {
	PARENT[vertex] = vertex;
	RANK[vertex] = 0;
}

bool myComparison (Edge x, Edge y) { return x.weight < y.weight; }


vector<Edge> kruskal(Graph & g) {

	vector<Edge> A;

	for (int i = 0; i < g.vertices.size(); i++) {
		makeSet(g.vertices[i]);
	}

	std::sort(g.edges.begin(), g.edges.end(), myComparison);

	for (int i = 0; i < g.edges.size(); i++) {

		int root1 = doFind(g.edges[i].vertex1);
		int root2 = doFind(g.edges[i].vertex2);
		if (root1 != root2) {
			A.push_back(g.edges[i]);
			doUnion(root1, root2);
		}
	}
	return A;
}
