/*
 * FeaturesObjectPairTest.hpp
 *
 *  Created on: Jun 5, 2014
 *      Author: marina
 */

#ifndef FEATURESOBJECTPAIRTEST_HPP_
#define FEATURESOBJECTPAIRTEST_HPP_



#include "ObjectClusterModel.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/ml/ml.hpp"
#include <string.h>
#include <boost/property_tree/ptree.hpp>
#include "Object.hpp"
#include "ApiConvertKTHDB.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include "FeaturesObjectPair.hpp"
#include "DatabaseInformation.hpp"
#include "SceneInformation.hpp"
#include <algorithm>
#include "StatisticalTool.hpp"

class FeaturesObjectPairTest {

private:

	int objectClusterModelID;
		vector<vector<double> > featureMatrices;
		vector<int> objectPairsIDs;

	public:

		FeaturesObjectPairTest();
		void setFeatureMatrices(vector<vector<double> >);
		vector<vector<double> > getFeatureMatrices() { return featureMatrices; }
		void printFeatureMatrices();

};



#endif /* FEATURESOBJECTPAIRTEST_HPP_ */
