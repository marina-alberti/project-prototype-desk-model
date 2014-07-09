/*
 * APIConvertionClusterModelToGraph.cpp
 *
 *  Created on: May 22, 2014
 *      Author: marina
 */

#include "APIConvertionClusterModelToGraph.hpp"

using namespace std;

#define DEBUG 1


Graph APIConvertionClusterModelToGraph::convertClusterToGraph(ObjectClusterModel & myCluster) {

	Graph g;

	vector<int> objectPartList = myCluster.getObjectPartIDs();

	for ( int i = 0; i < objectPartList.size(); i++ ) {
		g.vertices.push_back(objectPartList.at(i));
	}

	// Adds the vertices of the table / desk reference system
	g.vertices.push_back(100);


	vector<ObjectPairModel> pairList = myCluster.getObjectPairsInitial();

	for (int i = 0; i < pairList.size(); i++) {

		ObjectPairModel currentPair = pairList.at(i);
		int id1 = currentPair.getObjectPartID1();
		int id2 = currentPair.getObjectPartID2();
		double quality = currentPair.getQuality();

		g.edges.push_back(Edge(id1, id2, quality));
	}

	return g;
}


vector<ObjectPairModel> APIConvertionClusterModelToGraph::convertEdgeSetToPairSet(vector<Edge> & edges, ObjectClusterModel & myCluster) {

	vector<ObjectPairModel> out;
	vector<ObjectPairModel> allPairs = myCluster.getObjectPairsInitial();

	// for each of the initial object pairs, i check if it is contained into the output set of edges
	for (int i = 0; i < allPairs.size(); i++) {

		ObjectPairModel currentPairModel = allPairs.at(i);
		bool finalPairModel = false;

		// for all the final edges returned by the MST algorithm
		for (int j = 0; j < edges.size(); j++) {

			Edge currentEdge = edges[j];

			// TODO: check if I need to check also the other combination:: ( ID1 == vertex2 && ID2 == vertex1 )
			if (currentPairModel.getObjectPartID1() == currentEdge.vertex1 && currentPairModel.getObjectPartID2() == currentEdge.vertex2) {
				finalPairModel = true;
				out.push_back(currentPairModel);
			}
		}
	}
	return out;
}
