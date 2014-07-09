/*
 * PrototypeDesk.hpp
 *
 *  Created on: Mar 18, 2014
 *      Author: marina
 */

#ifndef PROTOTYPEDESK_HPP_
#define PROTOTYPEDESK_HPP_


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
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include "ApiConvertRealWorldDB.hpp"


class PrototypeDesk{

private:

  double thresholdFrequencySO;
  vector<int> categoryList;
  int numberOfCategories;
  vector<double> frequencySO;

public:

  PrototypeDesk();

  void extractFrequencySO(DatabaseInformation &);

  void computeCategoryList();


  // // set functions

  void setThresholdFrequencySO(double);

  // // get functions

  double getThresholdFrequencySO();
  int getNumberOfCategories();
  vector<int> getCategoryList();
  void printCategoryList();


};



#endif /* PROTOTYPEDESK_HPP_ */
