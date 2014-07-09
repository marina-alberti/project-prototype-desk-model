/*
 * APITraining.cpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */


#include "APITraining.hpp"
#define DEBUG 1



void APITraining::trainPairsParameters(FeaturesObjectPair & features , ObjectClusterModel & myCluster, int nclusters) {

	int minSamples = 5;

	// for each of the pairs in the model
	vector<vector<vector<double> > > feats = features.getFeatureMatrices();

	for (int i = 0; i < feats.size(); i++) {


		vector< vector <double> > featureCurrentPair = feats.at(i);

		//***************************************
		// TODO: create template function and delete this double -> float conversion
		vector <vector< float> > featureCurrentPair2 ;
		for (int j = 0; j < featureCurrentPair.size(); j++ ) {
			vector<float> tmp;
			for (int z = 0; z < featureCurrentPair.at(j).size(); z++) {
				float myValue = (float) (featureCurrentPair.at(j).at(z)) ;
				tmp.push_back(myValue);
			}
			featureCurrentPair2.push_back(tmp);
		}
		//*****************************************

		cv::Mat means;
		cv::Mat weights;
		vector<cv::Mat> covs;

		if (featureCurrentPair.size() > minSamples) {
			StatisticalTool::trainGMM(featureCurrentPair2, nclusters,  means, weights, covs);
		}

		myCluster.setMeans(means, i);
		myCluster.setCovs(covs, i);
		myCluster.setWeights(weights, i);
		myCluster.setTrainedTrue();

		if(DEBUG) {
			cout << endl << endl << "The means matrix is: " << endl;
			cout << means << endl;
			cout << "The weights are: " << endl;
			cout << weights << endl;
		}

		// Computes the 'quality measure' of the current (i-th) object pair of the cluster
		// as the product of the likelihood values over all the training examples,
		// given the trained values of the model parameters

		double totalQuality = 0;

		// for each row of the matrix i.e. for each training example
		for(int j = 0; j < featureCurrentPair2.size(); j++) {

			double currentQuality = log( StatisticalTool::computeGMMProbability(featureCurrentPair2.at(j), means, covs, weights) );

			totalQuality = totalQuality + currentQuality;

			if(0) {
				cout << "Pair: " << (myCluster.getObjectPairsInitial()).at(i).getCategoryLabel1() << " -- " <<
						(myCluster.getObjectPairsInitial()).at(i).getCategoryLabel2() << endl;
				cout << "current quality measure is : " << currentQuality << endl;
			}

		}

		// Computes the negative log , for compatibility with Minimum Spanning Tree algorithm
		totalQuality = - (totalQuality);

		myCluster.setQualities(totalQuality, i);

		if(DEBUG) {
			cout << "Pair: " << (myCluster.getObjectPairsInitial()).at(i).getCategoryLabel1() << " -- " <<
					(myCluster.getObjectPairsInitial()).at(i).getCategoryLabel2() << endl;
			cout << "The quality measure is : " << totalQuality << endl;
		}

	}

}
