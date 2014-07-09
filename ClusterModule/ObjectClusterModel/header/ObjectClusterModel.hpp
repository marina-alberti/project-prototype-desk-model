/*
 * ObjectClusterModel.hpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */

#ifndef OBJECTCLUSTERMODEL_HPP_
#define OBJECTCLUSTERMODEL_HPP_


#include <string.h>
#include <boost/property_tree/ptree.hpp>
#include "Object.hpp"
#include "ApiConvertKTHDB.hpp"
#include "SceneInformation.hpp"
#include "DatabaseInformation.hpp"
#include "ApiStatisticsDatabase.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <opencv2/opencv.hpp>
#include <cmath>
#include "ApiConvertSimulationDB.hpp"
#include "ApiConvertRealWorldDB.hpp"
#include "ObjectPairModel.hpp"

class ObjectClusterModel {

private:

	int objectClusterModelID;
	vector<int> categoryLabels;
	vector<int> objectPartIDs;
	vector<ObjectPairModel> objectPairsInitial;
	vector<ObjectPairModel> objectPairsFinal;
	bool istrained;

	void createPairsInitial();

public:

	ObjectClusterModel();
	ObjectClusterModel(vector<int> &);
	void createPairsInitial(vector<int> &);
	void addCategory(int);
	void printAllPairs();
	void addPairToFinalList(ObjectPairModel &);

	vector<int> getCategoryLabels() { return categoryLabels; }
	vector<int> getObjectPartIDs() { return objectPartIDs; }
	int getObjectClusterModelID() { return objectClusterModelID; }
	vector<ObjectPairModel> getObjectPairsInitial() { return objectPairsInitial; }
	vector<ObjectPairModel> getObjectPairsFinal() { return objectPairsFinal; }

	void setMeans(cv::Mat in, int pairNumber);
	void setCovs(vector<cv::Mat> in, int pairNumber);
	void setWeights(cv::Mat in, int pairNumber);
	void setQualities(double in, int pairNumber);
	void setTrainedTrue() { istrained = true; }
	void setObjectPairsFinal(vector<ObjectPairModel> & in ) { objectPairsFinal = in; }

};



#endif /* OBJECTCLUSTERMODEL_HPP_ */
