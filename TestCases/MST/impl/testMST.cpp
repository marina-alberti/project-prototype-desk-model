/*
 * testMST.cpp
 *
 *  Created on: May 22, 2014
 *      Author: marina
 */


#include "Graph.hpp"
#include "Edge.hpp"
#include "FunctionsMST.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>


#define DEBUG 1


using namespace std;

int main() {

	//char t[] = {'a', 'b', 'c', 'd', 'e', 'f'};

	int t[] = {1, 2, 3, 4, 5, 6};

	Graph g;

	g.vertices = vector<int>(t, t + sizeof(t) / sizeof (t[0]) );

	g.edges.push_back(Edge(1, 2, 4));
	g.edges.push_back(Edge(1, 6, 2));
	g.edges.push_back(Edge(6, 2, 5));
	g.edges.push_back(Edge(3, 2, 6));
	g.edges.push_back(Edge(3, 6, 1));
	g.edges.push_back(Edge(6, 5, 4));
	g.edges.push_back(Edge(4, 5, 2));
	g.edges.push_back(Edge(4, 3, 3));


	vector<Edge> out = kruskal(g);

	// printing the edges of the minimum spanning tree
	for (int i = 0; i < out.size(); i++ ) {
		cout << out[i].vertex1 << " --- " << out[i].vertex2 << " : " << out[i].weight << endl;
	}

	return 0;

}





