/*
 * FeaturesObjectPairTest.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: marina
 */

#include "FeaturesObjectPairTest.hpp"
#define DEBUG 1



FeaturesObjectPairTest::FeaturesObjectPairTest() {
	objectClusterModelID = 0;
	// TODO: modify pass as argument
}

void FeaturesObjectPairTest::setFeatureMatrices(vector<vector<double> > in) {

	featureMatrices = in;

}
