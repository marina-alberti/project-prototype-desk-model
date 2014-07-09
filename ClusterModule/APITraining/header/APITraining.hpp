/*
 * APITraining.hpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */

#ifndef APITRAINING_HPP_
#define APITRAINING_HPP_



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


class APITraining {

private:

public:

	static void trainPairsParameters(FeaturesObjectPair & , ObjectClusterModel &, int);


};




#endif /* APITRAINING_HPP_ */
