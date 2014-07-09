/*
 * ObjectClusterModel.cpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */


#include "ObjectClusterModel.hpp"
#define DEBUG 1

// TODO: static data member 'objectClusterModelID'?


ObjectClusterModel::ObjectClusterModel() {
	if (DEBUG) {
		cout << "Inside the constructor of the class 'ObjectClusterModel' " << endl;
	}
	objectClusterModelID = 0;		// TODO
	istrained = false;
}


ObjectClusterModel::ObjectClusterModel(vector<int> & in ) : categoryLabels( in )
{

	if (DEBUG) {
		cout << "Inside the constructor of the class 'ObjectClusterModel' " << endl;
	}
	objectClusterModelID = 0;		// TODO
	istrained = false;

	for (int i = 0; i < categoryLabels.size(); i++ ) {
		objectPartIDs.push_back(i);
	}


	// Adds also the 'part' corresponding to the table
	// objectPartIDs.push_back(100);


	if (DEBUG) {
		cout << "ObjectClusterModel::ObjectClusterModel after initializing data members " << endl;
	}
	createPairsInitial();
}

void ObjectClusterModel::addCategory(int in) {
	categoryLabels.push_back(in);
	if(DEBUG) {
		cout << "ObjectClusterModel::addCategory : The category has been added: " << in << endl;
	}
}


/*
 * Given the categories that form the cluster
 * computes all pairs of objects.
 */
void ObjectClusterModel::createPairsInitial() {

	int cat1, cat2, id1, id2;
	for (int i = 0; i < categoryLabels.size(); i++ ) {

		cat1 = i;
		id1 = objectPartIDs.at(i);
		for (int j = i; j < categoryLabels.size(); j++) {

			if( j != i ) {

				cat2 = j;
				id2 = objectPartIDs.at(j);
				if (DEBUG) {
					cout << "Adding a pair with categories: " << cat1 << " and " << cat2 << endl;
				}
				ObjectPairModel* currentPair = new ObjectPairModel(cat1, cat2, id1, id2);
				objectPairsInitial.push_back(*currentPair);
			}
		}


		// Adds also the 'object pair' corresponding to the table - current object

		cat2 = 100;
		id2 = 100;
		if (DEBUG) {
			cout << "Adding a pair with categories: " << cat1 << " and Desk  " << cat2 << endl;
		}
		ObjectPairModel* currentPair = new ObjectPairModel(cat1, cat2, id1, id2);
		objectPairsInitial.push_back(*currentPair);

	}
}


void ObjectClusterModel::printAllPairs() {

	cout << endl;
	for (int i = 0; i < objectPairsInitial.size(); i++ ) {
		cout << objectPairsInitial.at(i).getCategoryLabel1() << " ";
		cout << objectPairsInitial.at(i).getCategoryLabel2() << endl;
	}
	cout << endl;
	for (int i = 0; i < objectPairsFinal.size(); i++ ) {
		cout << objectPairsFinal.at(i).getCategoryLabel1() << " ";
		cout << objectPairsFinal.at(i).getCategoryLabel2() << endl;
	}

}

void ObjectClusterModel::createPairsInitial(vector<int> &) {
}


void ObjectClusterModel::setMeans(cv::Mat in, int pairNumber) {
	(objectPairsInitial.at(pairNumber)).setMeans(in);
}

void ObjectClusterModel::setCovs(vector<cv::Mat> in, int pairNumber){
	(objectPairsInitial.at(pairNumber)).setCovs(in);
}

void ObjectClusterModel::setWeights(cv::Mat in, int pairNumber){
	(objectPairsInitial.at(pairNumber)).setWeights(in);
}

void ObjectClusterModel::setQualities(double in, int pairNumber){
	(objectPairsInitial.at(pairNumber)).setQuality(in);
}


/* TODO: delete
void ObjectClusterModel::computeQualityObjectPairs(DatabaseInformation & db) {

	if (istrained == false) {
		cout << "ObjectClusterModel::computeQualityObjectPairs \nError: the database is not yet trained with the object pair parameters. " << endl;
		return;
	}
	else {
		// Gets all the scenes in the input database
		std::vector<SceneInformation> dbScenes = db.getSceneList();

		for (int i = 0; i < dbScenes.size(); i++) {   // dbScenes.size()

			if(DEBUG) {
				cout << "ObjectClusterModel::computeQualityObjectPairs. Scene number  " << i << endl;
			}

			// extract feature vector from the cluster of that scene



		}

*/






