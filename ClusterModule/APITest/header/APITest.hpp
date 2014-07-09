/*
 * APITest.hpp
 *
 *  Created on: Jun 5, 2014
 *      Author: marina
 */

#ifndef APITEST_HPP_
#define APITEST_HPP_



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



class APITest {

private:


public:

	static double computeLikelihoodPairs(FeaturesObjectPairTest & , ObjectClusterModel &, int);


};



#endif /* APITEST_HPP_ */
