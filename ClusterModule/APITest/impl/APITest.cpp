/*
 * APITest.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: marina
 */

#include "APITest.hpp"
#define DEBUG 1


double APITest::computeLikelihoodPairs(FeaturesObjectPairTest & features, ObjectClusterModel & myCluster, int nclusters) {

	// for each of the pairs in the model
	vector<vector<double> > feats = features.getFeatureMatrices();
	double totalLikelihood;

	if ( feats.size() > 0 ) {

		totalLikelihood = 1;

		for (int i = 0; i < feats.size(); i++) {

			vector <double> featureCurrentPair = feats.at(i);

			//*************************************************************************************************************

			// TODO: create template function and delete this double -> float conversion
			vector < float> featureCurrentPair2 ;
			for (int j = 0; j < featureCurrentPair.size(); j++ ) {
				float myValue = (float) (featureCurrentPair.at(j)) ;
				featureCurrentPair2.push_back(myValue);
			}

			//************************************************************************************************************

			cv::Mat means;
			cv::Mat weights;
			vector<cv::Mat> covs;

			means = (myCluster.getObjectPairsFinal().at(i)).getMeans();
			weights = (myCluster.getObjectPairsFinal().at(i)).getWeights();
			covs = (myCluster.getObjectPairsFinal().at(i)).getCovs();

			double likelihood;

			likelihood = StatisticalTool::computeGMMProbability(featureCurrentPair2,  means, covs, weights);

			totalLikelihood = totalLikelihood * likelihood;

			if(DEBUG) {
				cout << endl << endl << "The likelihood of pair # '" << i << "' is: " << likelihood << endl;
			}
		}

		if(DEBUG) {
			cout << endl << endl << "The total likelihood  is: " << totalLikelihood << endl;
		}
	}

	// if the size of the feature vectors is 0
	else {
		totalLikelihood = -1;
	}



	return totalLikelihood;

}
