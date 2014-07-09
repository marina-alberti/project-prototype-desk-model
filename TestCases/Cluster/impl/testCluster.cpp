/*
 * testCluster.cpp
 *
 *  Created on: May 20, 2014
 *      Author: marina
 */

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include "utils.hpp"
#include "SceneInformation.hpp"
#include "ApiConvertKTHDB.hpp"
#include "DatabaseInformation.hpp"
#include "ApiFeatureExtractionDatabaseSingleObject.hpp"
#include "ApiFeatureExtractionDatabaseObjectPair.hpp"
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include "ArrangeFeatureTraining.hpp"
#include "DatabaseSingleObjectFeature.hpp"
#include "DatabaseObjectPairFeature.hpp"
#include "Training.hpp"
#include "ModelTrainedIO.hpp"
#include "ArrangeFeatureTestScene.hpp"
#include "Test.hpp"
#include "ApiStatisticsDatabase.hpp"
#include "ApiGraph.hpp"
#include "ConfusionMatrix.hpp"
#include "ApiConvertionResultsTestConfusionMatrix.hpp"
#include "Evaluation.hpp"
#include "PrototypeDesk.hpp"
#include "ObjectClusterModel.hpp"
#include "ObjectPairModel.hpp"
#include "FeaturesObjectPair.hpp"
#include "APIFeatureExtractionObjectPair.hpp"
#include "APITraining.hpp"
#include "Graph.hpp"
#include "Edge.hpp"
#include "FunctionsMST.hpp"
#include "APIConvertionClusterModelToGraph.hpp"
#include "APITest.hpp"


#include "ros/ros.h"


#define DEBUG 1


using namespace std;

int main() {

	// Reads the training database

	string dir = "/home/marina/workspace_eclipse_scene_similarity_measurement/data/data_more_objects/";

	vector<string> listXMLfiles =  storeFileNames(dir);
	DatabaseInformation db;
	db.loadAnnotations_KTH(listXMLfiles);

	cout << "The size of the database is: " << db.getNumberOfScenes() << endl;

	// Creates a model of an object cluster (group of objects, prototype desk)
	// input: a set of object categories
	// assumption: no multiple objects of same category
	// (TODO: to modify)

	vector<int> categories;
	categories.push_back(0); 	// monitor
	categories.push_back(1); 	// keyboard
	categories.push_back(2); 	// mouse
	// categories.push_back(3);  // mug
	// categories.push_back(5);  // pencil


	cout << "After creating vector of category labels" << endl;

	ObjectClusterModel * myCluster =  new ObjectClusterModel(categories);

	cout << "After creating cluster model of objects." << endl;

	myCluster->printAllPairs();


	// Extracts the features from training database into feature matrices

	cout << "Extracting pairwise features from the training scenes." << endl;

	FeaturesObjectPair myFeatures;
	APIFeatureExtractionObjectPair::extractFeatures( db,  *myCluster, myFeatures);


	// cout << "Printing the feature matrices " << endl;
	// myFeatures.printFeatureMatrices();


	// Trains the parameters of all pairs of objects in the prototype desk model

	int numClusters = 2;
	APITraining::trainPairsParameters(myFeatures, *myCluster, numClusters);


	// ClusterModel -> graph conversion and Minimum Spanning Tree algorithm
	// from fully connected graph to tree
	// Finds the set of edges of the final tree for the 'prototype desk' (no cycles)

	Graph g = APIConvertionClusterModelToGraph::convertClusterToGraph(*myCluster);
	vector<Edge> edges = kruskal(g);
	vector<ObjectPairModel> finalPairs = APIConvertionClusterModelToGraph::convertEdgeSetToPairSet(edges, *myCluster);
	(*myCluster).setObjectPairsFinal(finalPairs);

	// printing the pairs
	cout << endl;
	for (int i = 0; i < edges.size(); i++) {

		cout << "Pair:  " << edges[i].vertex1 << " -- " << edges[i].vertex2 << endl;

	}

	//************************************************************************************************
	// Test: compute similarity measurement
	// the test scene

	SceneInformation testScene = db.getSceneList().at(1);

	cout << "\n\nExtracting pairwise features from the test scene " << endl;
	FeaturesObjectPairTest myFeaturesTest;
	APIFeatureExtractionObjectPair::extractFeaturesTest( testScene,  *myCluster, myFeaturesTest );

	APITest::computeLikelihoodPairs(myFeaturesTest, *myCluster, numClusters);


	return 0;
}
