/*
 * FeaturesObjectPair.hpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */

#ifndef FEATURESOBJECTPAIR_HPP_
#define FEATURESOBJECTPAIR_HPP_



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


class FeaturesObjectPair {

private:

	int objectClusterModelID;
	vector<vector<vector<double> > > featureMatrices;
	vector<int> objectPairsIDs;

public:

	FeaturesObjectPair();
	void setFeatureMatrices(vector<vector<vector<double> > >);
	vector<vector<vector<double> > > getFeatureMatrices() { return featureMatrices; }
	void printFeatureMatrices();


};


#endif /* FEATURESOBJECTPAIR_HPP_ */
