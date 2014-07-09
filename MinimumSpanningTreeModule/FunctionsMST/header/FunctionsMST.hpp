/*
 * FunctionsMST.hpp
 *
 *  Created on: May 22, 2014
 *      Author: marina
 */

#ifndef FUNCTIONSMST_HPP_
#define FUNCTIONSMST_HPP_


#include "Edge.hpp"
#include "Graph.hpp"
#include <algorithm>
#include <cstdio>
#include <vector>

#define DEBUG 1

using namespace std;

map<int, int> PARENT;
map<int, int> RANK;

char doFind(int vertex);

void doUnion(int root1, int root2);

void makeSet(int vertex);

vector<Edge> kruskal(Graph & g);



#endif /* FUNCTIONSMST_HPP_ */
