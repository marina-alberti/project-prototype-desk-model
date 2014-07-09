/*
 * APIFeatureExtractionObjectPair.hpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */

#ifndef APIFEATUREEXTRACTIONOBJECTPAIR_HPP_
#define APIFEATUREEXTRACTIONOBJECTPAIR_HPP_


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
#include "FeaturesObjectPairTest.hpp"

using namespace std;

typedef map<int, Object> assignment;

class APIFeatureExtractionObjectPair {

private:

	static double computeDistanceX(Object & refObject, Object & targetObject);
	static double computeDistanceY(Object & refObject, Object & targetObject);
	static double computeDistanceZ(Object & refObject, Object & targetObject);

public:

	static void extractFeatures( DatabaseInformation &,  ObjectClusterModel &, FeaturesObjectPair & );
	void computeClusterCentroid();
	static void utilsRecursion( map<int, vector<Object> > & , map<int, vector<Object> >::iterator, int, assignment & , vector<assignment> &);
	static void extractFeaturesTest( SceneInformation & scene,  ObjectClusterModel & cluster, FeaturesObjectPairTest & feats );

};


#endif /* APIFEATUREEXTRACTIONOBJECTPAIR_HPP_ */
