/*
 * ObjectPairModel.hpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */

#ifndef OBJECTPAIRMODEL_HPP_
#define OBJECTPAIRMODEL_HPP_

//#include "ObjectClusterModel.hpp"
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


using namespace std;
using namespace cv;

class ObjectPairModel {

private:

	int objectPairID;
	int categoryLabel1;
	int categoryLabel2;
	int objectPartID1;
	int objectPartID2;

	/*
	 * The parameters of the pairwise model after learning in training phase
	 */
	cv::Mat means;
	vector<cv::Mat> covs;
	cv::Mat weights;

	double quality;


public:

	ObjectPairModel(int, int, int, int);

	int getObjectPairID() { return objectPairID; }
	int getCategoryLabel1() { return categoryLabel1; }
	int getCategoryLabel2() { return categoryLabel2; }
	int getObjectPartID1() { return objectPartID1; }
	int getObjectPartID2() { return objectPartID2; }

	cv::Mat getMeans() { return means; }
	vector<cv::Mat> getCovs() { return covs; }
	cv::Mat getWeights() { return weights; }

	void setMeans(cv::Mat in) { means = in; }
	void setCovs(vector<cv::Mat> in) { covs = in; }
	void setWeights(cv::Mat in) { weights = in; }

	void setQuality(double in) { quality = in; }
	double getQuality() { return quality; }


};



#endif /* OBJECTPAIRMODEL_HPP_ */
