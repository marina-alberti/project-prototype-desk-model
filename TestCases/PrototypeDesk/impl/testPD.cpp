/*
 * testPD.cpp
 *
 *  Created on: Mar 18, 2014
 *      Author: marina
 */


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

#include "ros/ros.h"
#include "strands_qsr_msgs/GetGroupClassification.h"
#include "strands_qsr_msgs/BBox.h"
#include "strands_qsr_msgs/ObjectClassification.h"


#define DEBUG 1



using namespace std;

int main() {

	string dir = "/home/marina/workspace_eclipse_scene_similarity_measurement/data/data_more_objects/";

	vector<string> listXMLfiles =  storeFileNames(dir);
	DatabaseInformation db;
	db.loadAnnotations_KTH(listXMLfiles);
	vector<SceneInformation> allScenes = db.getSceneList();
	cout << "The size of the database is: " << db.getNumberOfScenes() << endl;

	// db.printSceneInformation();

	PrototypeDesk desk1;
	desk1.setThresholdFrequencySO(0.9);
	desk1.extractFrequencySO(db);
	desk1.computeCategoryList();
	desk1.printCategoryList();
	vector<int> categoryList = desk1.getCategoryList();


	/*
	// // TODO
	// // In the next step I should only extract the features that are in the category list.
	 */

	// // ************************************************************************
	// // Feature extraction
	// // ************************************************************************

	DatabaseSingleObjectFeature dbSof;
	ApiFeatureExtractionDatabaseSingleObject::extract(db, dbSof);
	DatabaseObjectPairFeature dbOpf;
	ApiFeatureExtractionDatabaseObjectPair::extract(db, dbOpf);


	// // ************************************************************************
	// // Arrange the features into feature matrices
	// // ************************************************************************

	vector<vector<vector<float> > > FMSingleObject;
	ArrangeFeatureTraining::setFeatureMatrixSingleObject(dbSof, FMSingleObject);
	vector<vector<vector<vector<float> > > > FMObjectPair;
	ArrangeFeatureTraining::setFeatureMatrixObjectPair(dbOpf, FMObjectPair);


	// // ************************************************************************

	/*
	// // // TODO
	// // // Or as another option, here I select the feature matrix (single object and object pair)
	// // // that contain only the categories in the categoryList of the PrototypeDesk.
	*/

	vector<vector<vector<float> > > FMSingleObjectPD;
	for (int i = 0; i < categoryList.size(); i++ ) {
		int currenCategory = categoryList.at(i);
		vector<vector<float> > currentCategoryData = FMSingleObject.at(currenCategory);
		FMSingleObjectPD.push_back(currentCategoryData);
	}
	cout << "The size of FMSingleObjectPD is : " << FMSingleObjectPD.size() << endl;
	vector<vector<vector<vector<float> > > > FMObjectPairPD;
	for (int i = 0; i < categoryList.size(); i++ ) {

			int currenCategory1 = categoryList.at(i);
			vector<vector<vector<float> > >  tmp;
			for (int j = 0; j < categoryList.size(); j++ ) {
				int currentCategory2 = categoryList.at(j);
				vector<vector<float> > currentCategoryPairData = FMObjectPair.at(currenCategory1).at(currentCategory2);
				tmp.push_back(currentCategoryPairData);
			}
			FMObjectPairPD.push_back(tmp);
	}
	cout << "The size of FMObjectPairPD is : " << FMObjectPairPD.size() << endl;
	// // ************************************************************************



	/*
	// print
	//cout << "size of feature matrix is: " <<  FMSingleObject.size() << endl;
	//cout << "size of feature matrix dim 2 is: " <<  FMSingleObject.at(0).size() << endl;
	//cout << "size of feature matrix dim 3 is: " << FMSingleObject.at(0).at(0).size() << endl;

	ArrangeFeatureTraining::printFeatureMatrixSingleObject(FMSingleObject);
	ArrangeFeatureTraining::printFeatureMatrixObjectPair(FMObjectPair);



		// Learning

		int nclusters = 2;
		int normalizationOption = 0;
		Training doTraining;
		doTraining.learnGMMSingleObjectFeature(FMSingleObject, nclusters, normalizationOption);
		doTraining.learnGMMObjectPairFeature(FMObjectPair, nclusters, normalizationOption);

		// compute object frequencies and co-occurrence frequency on training database

		vector<double> frequenciesSingleObject = ApiStatisticsDatabase::computeFrequenciesSingleObject(trainingDB);
		vector<vector<double> > frequenciesObjectPair = ApiStatisticsDatabase::computeFrequenciesObjectPair(trainingDB);

		// storing to file

		string storingFolder = "params";
		ModelTrainedIO::storeTrainingToFile(doTraining, storingFolder);
		ModelTrainedIO::storefrequencies(frequenciesSingleObject, frequenciesObjectPair, storingFolder);


		// ******************************************************************************************************
		// Test

		//string testFile = listXMLfiles.at(0);
		//ApiConvertKTHDB testSceneConverter;

		ConfusionMatrix totalCMatrix;

		// for each test scene among the test scenes
		for (int i = 0; i < testScenes.size(); i++) {

			SceneInformation testScene = testScenes.at(i);

			vector<int> objectids = testScene.getObjectIds();
			vector<int> categoryList;

			for (int k = 0; k < NOBJECTCLASSES; k++) {
				categoryList.push_back(k);
			}

			ApiGraph mygraph(objectids, categoryList);
			mygraph.findAllPaths();
			// mygraph.printAllPaths();
			vector<path> allPaths = mygraph.getAllPaths();


			// // feature extraction

			SceneSingleObjectFeature sceneSof;
			SceneObjectPairFeature sceneOpf;
			ApiFeatureExtractionSceneSingleObject::extract(testScene, sceneSof);
			ApiFeatureExtractionSceneObjectPair::extract(testScene, sceneOpf);

			// // Arrange features of test scene

			ArrangeFeatureTestScene arrangeFeaturesTest;
			arrangeFeaturesTest.arrangeTestFeatures(sceneSof, sceneOpf);

			// // testing

			Test testingScene;

			// // option tag for loading from the files

			bool loadfromfile = false;
			if (loadfromfile) {
				ModelTrainedIO::loadTrainedGMMsFile(storingFolder, testingScene);
				ModelTrainedIO::loadfrequencies(storingFolder, testingScene);
			}
			else {
				// // loading directly from the saved models into the training class - no use of the files
				testingScene.loadTrainedGMMs(doTraining);
				testingScene.loadLearnedObjectCategoryFrequency(frequenciesSingleObject, frequenciesObjectPair);
			}

			// vector<strands_qsr_msgs::ObjectClassification> estimate ;

			int optionTestFunction = 1;
			path resultsPath;

			if (optionTestFunction == 0) {

				resultsPath = testingScene.predictObjectClassesOnlySOF(arrangeFeaturesTest, normalizationOption);
			}

			if (optionTestFunction == 1) {

				// prepare the input for the voting strategy
				vector<vector<double> > votingTable;

				resultsPath = testingScene.voting(arrangeFeaturesTest, normalizationOption, votingTable);
			}

			if (optionTestFunction == 2) {

				resultsPath = testingScene.exhaustiveSearch(arrangeFeaturesTest, normalizationOption, allPaths);
			}

			if (optionTestFunction == 3) {

				// prepare the input for the voting strategy
				vector<vector<double> > votingTable;

				path resultVoting = testingScene.voting(arrangeFeaturesTest, normalizationOption, votingTable);

				vector<vector<pairScore> > votingTableComplete = Test::createVotingTableComplete(votingTable, arrangeFeaturesTest);

				resultsPath = testingScene.optimizationGreedy(arrangeFeaturesTest, votingTableComplete, normalizationOption);

			}

		    ConfusionMatrix cMatrix;
		    ApiConvertionResultsTestConfusionMatrix::convertResultsToMatrix(resultsPath, testScene, cMatrix, categoryList);
		    cMatrix.printConfusionMatrix();
		    totalCMatrix.sumConfusionMatrix(cMatrix);

		}

		totalCMatrix.printConfusionMatrix();
		Evaluation * evaluate;
		evaluate = new Evaluation(totalCMatrix);
		evaluate->evaluatePerformance();
		*/

	return 0;
}
