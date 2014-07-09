/*
 * FeaturesObjectPair.cpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */


#include "FeaturesObjectPair.hpp"

FeaturesObjectPair::FeaturesObjectPair() {
	objectClusterModelID = 0;
	// TODO: modify pass as argument
}

void FeaturesObjectPair::setFeatureMatrices(vector<vector<vector<double> > > in) {

	featureMatrices = in;

}

void FeaturesObjectPair::printFeatureMatrices() {

	cout << "Feature matrices" << endl;

	// for each object pair
	for (int i = 0; i < featureMatrices.size(); i++) {

		cout << endl;

		// for each feature sample
		for (int j = 0; j < featureMatrices.at(i).size(); j++) {

			// for each feature dimension
			for (int k = 0; k < featureMatrices.at(i).at(j).size(); k++) {
				cout << featureMatrices.at(i).at(j).at(k) << " ";
			}
			cout << endl;
		}
	}
}
