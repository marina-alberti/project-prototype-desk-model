/*
 * Edge.hpp
 *
 *  Created on: May 22, 2014
 *      Author: marina
 */

#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include "utils.hpp"
#include "SceneInformation.hpp"
#include "ApiConvertKTHDB.hpp"
#include "DatabaseInformation.hpp"
#include "ApiFeatureExtractionDatabaseSingleObject.hpp"
#include "ApiFeatureExtractionDatabaseObjectPair.hpp"
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include "ArrangeFeatureTraining.hpp"
#include "DatabaseSingleObjectFeature.hpp"
#include "DatabaseObjectPairFeature.hpp"
#include "Training.hpp"
#include "ModelTrainedIO.hpp"
#include "ArrangeFeatureTestScene.hpp"
#include "Test.hpp"
#include "ApiStatisticsDatabase.hpp"
#include "ApiGraph.hpp"
#include "ConfusionMatrix.hpp"
#include "ApiConvertionResultsTestConfusionMatrix.hpp"
#include "Evaluation.hpp"
#include "PrototypeDesk.hpp"
#include "ObjectClusterModel.hpp"
#include "ObjectPairModel.hpp"
#include "FeaturesObjectPair.hpp"
#include "APIFeatureExtractionObjectPair.hpp"
#include "APITraining.hpp"


struct Edge {

	int vertex1;
	int vertex2;
	double weight;
	Edge(int v1, int v2, double w): vertex1(v1), vertex2(v2), weight(w) {}

};



#endif /* EDGE_HPP_ */
