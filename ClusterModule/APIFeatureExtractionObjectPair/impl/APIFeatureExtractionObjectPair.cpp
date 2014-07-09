/*
 * APIFeatureExtractionObjectPair.cpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */


#include "APIFeatureExtractionObjectPair.hpp"
#include <math.h>

#define DEBUG 1


/*
 * Extracts features function - training
 * for each TRAINING SCENE: {
	IF (all the objects in the clusterModel are present) {
		IF (there are multiple instances of some of the parts in the example scene) {
			compute all possible combinations of the object classes in the clusterModel with the object instances in the current scene
			FOR_EACH combination {
				compute cluster centroid
				compute average distance of all object centroids from the cluster centroid
			}
			Select the combination of object instances in the scene with the lowest distance
		}
		Extract features:
		(for each object)
		for each pair
		 including all pairs with the desk - all objects VS. desk
		Add the features to the appropriate feature matrices stored in the other class 'FeaturesObjectPair'.
	}
}
 */
void APIFeatureExtractionObjectPair::extractFeatures( DatabaseInformation & db,  ObjectClusterModel & cluster, FeaturesObjectPair & feats ) {

	if(DEBUG) {
		cout << "APIFeatureExtractionObjectPair::extractFeatures" << endl;
	}

	vector<vector<vector<double> > > features;

	// initialize the feature matrices: as many matrices as the number of pairs in the cluster model
	for (int i = 0; i < ( cluster.getObjectPairsInitial() ).size(); i++) {

		vector<vector<double> > featureMatrixCurrentPair;
		features.push_back(featureMatrixCurrentPair);
	}

	// Gets all the scenes in the input database
	std::vector<SceneInformation> dbScenes = db.getSceneList();

	// For each scene in the database
	for (int i = 0; i < dbScenes.size(); i++) {   // dbScenes.size()

		if(DEBUG) {
			cout << "APIFeatureExtractionObjectPair::extractFeatures. Scene number  " << i << endl;
		}

		// // Maps the category Label (int) in the cluster model
		// // to the corresponding 'object instance' in the scene
		assignment clusterObjectToSceneId;

		// this one in case there are multiple instances
		map<int, vector<Object> > clusterObjectToVectorObjects;

		SceneInformation currentScene = dbScenes.at(i);

		// Gets all the objects ('Object') in the scene
		vector<Object> objectListScene = currentScene.getObjectList();

		// Gets all the labels of the cluster of objects model (int identifiers)
		vector<int> categoryListCluster = cluster.getCategoryLabels();

		// Indicates if the cluster model of objects is present in the current scene
		bool clusterPresent = true;

		//*****************************************************************************************************

		if(DEBUG) {
			cout << "Finding the first set of correspondences" << endl;
		}
		for (int j = 0; j < categoryListCluster.size(); j++) {

			bool currentObjectPresent = false;

			int currentCategoryCluster = categoryListCluster.at(j);

			vector<Object>::iterator itObject;

			// For each object instance in the current scene
			for (itObject = objectListScene.begin() ; itObject != objectListScene.end() ; itObject++) {

				// Gets the category label ID of the current object instance
				int categoryCurrentObject = (*itObject).getActualObjectID();

				// If the object instance is the same as the current category label in the cluster model
				if (categoryCurrentObject == currentCategoryCluster) {
					currentObjectPresent = true;
					clusterObjectToSceneId[currentCategoryCluster] = (*itObject); //.getInstanceID();

					// vector of possible object instances
					clusterObjectToVectorObjects[currentCategoryCluster].push_back(*itObject);

				}
			}
			// // If the current object in the cluster is not found, then the cluster is not found in the scene
			if (currentObjectPresent == false)  {
				clusterPresent = false;
			}
		}

		if (clusterPresent == true) {

			// *************************************************************************

			// // // Finds all possible combinations from object category labels in
			// // // cluster model to object instances with corresponding category label
			// // // in the scene instance

			if(DEBUG) {
				cout << "Finding all possible combinations" << endl;
			}

			vector<assignment> allpaths;
			assignment mypath;


			map<int, vector<Object> >::iterator it = clusterObjectToVectorObjects.begin();

			for (int j = 0; j < (*it).second.size(); j++) {
				utilsRecursion(clusterObjectToVectorObjects, it, j, mypath, allpaths);
			}

			// prints all paths
			if (DEBUG) {
				for ( int n = 0; n < allpaths.size(); n++ ) {

					cout << endl << "New path:: " << endl;
					for (map<int, Object>::iterator it2 = allpaths.at(n).begin(); it2 != allpaths.at(n).end(); it2++) {

						cout << "Cluster category: " << (*it2).first << " ---  Object category label: " << (*it2).second.getActualObjectID()
								<< " --- Object Instance ID: " << (*it2).second.getInstanceID() << endl;
					}
				}
			}

			// *************************************************************************

			// // Computes which is the combination (path) having MINIMUM
			// // average distance of the objects from the geometrical centroid of the cluster
			// // as the OPTIMAL combination and selects that.

			vector<double> distancesClusters;

			// for each of the paths
			for (int count = 0; count < allpaths.size(); count++) {

				// Computes cluster centroid

				double xcentroid = 0;
				double ycentroid = 0;
				double zcentroid = 0;

				// for each of the objects in the current path
				for (assignment::iterator iter = allpaths.at(count).begin(); iter !=  allpaths.at(count).end(); iter++ ) {
					pcl::PointXYZ currentObjectCentroid = (*iter).second.getCentroid();

					double xcoord = currentObjectCentroid.x;
					double ycoord = currentObjectCentroid.y;
					double zcoord = currentObjectCentroid.z;
					xcentroid += xcoord;
					ycentroid += ycoord;
					zcentroid += zcoord;

				}

				xcentroid = xcentroid / allpaths.at(count).size();
				ycentroid = ycentroid / allpaths.at(count).size();
				zcentroid = zcentroid / allpaths.at(count).size();

				// Computes average distance objects - cluster centroid
				// for each of the objects in the current path

				double distanceCluster = 0;
				for (assignment::iterator iter = allpaths.at(count).begin(); iter !=  allpaths.at(count).end(); iter++ ) {
					pcl::PointXYZ currentObjectCentroid = (*iter).second.getCentroid();
					double xcoord = currentObjectCentroid.x;
					double ycoord = currentObjectCentroid.y;
					double zcoord = currentObjectCentroid.z;
					double currentObjectDistance = sqrt(pow( (xcoord - xcentroid), 2) + pow( (ycoord - ycentroid), 2) + pow( (zcoord - zcentroid), 2));
					distanceCluster += currentObjectDistance;
				}
				distancesClusters.push_back(distanceCluster);

			}
			int maxPosition = computeMaximum(distancesClusters);
			assignment chosenAssignment = allpaths.at(maxPosition);

			if (DEBUG) {
				cout << endl << "Chosen assignment:: " << endl;
				for (map<int, Object>::iterator it3 = chosenAssignment.begin(); it3 != chosenAssignment.end(); it3++) {

					cout << "Cluster category: " << (*it3).first << " ---  Object category label: " << (*it3).second.getActualObjectID()
												<< " --- Object Instance ID: " << (*it3).second.getInstanceID() << endl;
				}
			}

			// ***************************************************************

			// // Computation of pairwise features

			// // TODO : add also all the pairwise features: each object / desk

			vector<ObjectPairModel> objectPairList = cluster.getObjectPairsInitial();

			// For each pair of objects in the cluster: gets the corresponding pair in the scene
			for ( int k = 0; k < objectPairList.size(); k++ ) {

				double distX, distY, distZ;

				int category1 = objectPairList.at(k).getCategoryLabel1();
				int category2 = objectPairList.at(k).getCategoryLabel2();

				// if it is NOT a pair containing the desk

				if ( category1 != 100 && category2 != 100 ) {
					Object instance1 = chosenAssignment[category1];
					Object instance2 = chosenAssignment[category2];

					// Computes the pairwise features between 'instance1' and 'instance2'
					distX = computeDistanceX(instance1, instance2);
					distY = computeDistanceY(instance1, instance2);
					distZ = computeDistanceZ(instance1, instance2);

				}  else if (category2 == 100) {

					Object instance1 = chosenAssignment[category1];
					distX = (instance1.getCentroid()).x;
					distY = (instance1.getCentroid()).y;
					distZ = (instance1.getCentroid()).z;
				}
				else {
					cout << "Error: the desk pair is not set correctly." << endl;
				}

				double arr[] = {distX, distY, distZ};
				vector<double> featCurrentSample (arr, arr + sizeof(arr) / sizeof(arr[0]) );

				// Add the feature row to the corresponding pair-matrix (the k-th pair of the cluster)
				if (DEBUG) {
					cout << "Adding to the pair: " << k << endl;
				}
				features.at(k).push_back(featCurrentSample);
			}
		}
	}

	feats.setFeatureMatrices(features);
}


/*
 * @description:
 * This functions helps the recursion to find all possible combination of
 * 'cluster model -> scene with object instances' assignments
 * in case there are multiple object instances for each of the
 * object categories in the cluster model.
 */
void APIFeatureExtractionObjectPair::utilsRecursion(map<int, vector<Object> > & mymap, map<int, vector<Object> >::iterator it, int j, assignment & mypath, vector<assignment> & allpaths) {

	if (DEBUG) {
		cout << "Calling recursion" << endl;
	}

	mypath[(*it).first] = (*it).second.at(j);

	cout << "Adding:  category in model:: " << (*it).first << " -- Category in scene:: " <<  (*it).second.at(j).getActualObjectID()
			<< " -- Instance ID in scene:: " << (*it).second.at(j).getInstanceID() << endl;

	++it;

	// check the "next" object in the cluster, check if it is still a valid one
	if ( (it) != mymap.end() ) {

		for (int j = 0; j < (*(it)).second.size(); j++) {
			utilsRecursion(mymap, it, j, mypath, allpaths);
		}
	}
	else {
		allpaths.push_back(mypath);
	}
}



double APIFeatureExtractionObjectPair::computeDistanceX(Object & refObject, Object & targetObject) {

  pcl::PointXYZ centroidReferenceObject = refObject.getCentroid();
  double xReference = centroidReferenceObject.x;
  pcl::PointXYZ centroidTargetObject = targetObject.getCentroid();
  double xTarget = centroidTargetObject.x;
  double out = xTarget - xReference;

  if (DEBUG) {
    cout << "The Euclidean distance in x between the two objects is : " << out << endl;
  }

  return out;
}



double APIFeatureExtractionObjectPair::computeDistanceY(Object & refObject, Object & targetObject) {

  pcl::PointXYZ centroidReferenceObject = refObject.getCentroid();
  double yReference = centroidReferenceObject.y;
  pcl::PointXYZ centroidTargetObject = targetObject.getCentroid();
  double yTarget = centroidTargetObject.y;
  double out = yTarget - yReference;

  if (DEBUG) {
    cout << "The Euclidean distance in y between the two objects is : " << out << endl;
  }
  return out;

}



double APIFeatureExtractionObjectPair::computeDistanceZ(Object & refObject, Object & targetObject) {

  pcl::PointXYZ centroidReferenceObject = refObject.getCentroid();
  double zReference = centroidReferenceObject.z;
  pcl::PointXYZ centroidTargetObject = targetObject.getCentroid();
  double zTarget = centroidTargetObject.z;
  double out = zTarget - zReference;

  if (DEBUG) {
    cout << "The Euclidean distance in z between the two objects is : " << out << endl;
  }

  return out;
}




void APIFeatureExtractionObjectPair::extractFeaturesTest( SceneInformation & currentScene,  ObjectClusterModel & cluster, FeaturesObjectPairTest & feats ) {

	if(DEBUG) {
		cout << "APIFeatureExtractionObjectPair::extractFeaturesTest" << endl;
	}

	// // < numberObjectPairs X featDim >
	vector<vector<double> > features;

	// // Maps the 'category Label' ('int' identifier) in the cluster model
	// // to the corresponding 'object instance' in the scene
	assignment clusterObjectToSceneId;

	// this one in case there are multiple instances of Object for the same 'category label'
	map<int, vector<Object> > clusterObjectToVectorObjects;

	// Gets all the object instance ('Object') in the scene
	vector<Object> objectListScene = currentScene.getObjectList();

	// Gets all the labels of the cluster of objects model ('int' identifiers)
	vector<int> categoryListCluster = cluster.getCategoryLabels();

	// Indicates if the cluster model of objects is present in the current scene
	bool clusterPresent = true;

	if(DEBUG) {
		cout << "Finding the first set of correspondences" << endl;
	}

	// ******************************************************************************************************

	// // for each element in the object cluster model
	for (int j = 0; j < categoryListCluster.size(); j++) {

		bool currentObjectPresent = false;

		int currentCategoryCluster = categoryListCluster.at(j);

		vector<Object>::iterator itObject;

		// For each object instance in the current scene
		for (itObject = objectListScene.begin() ; itObject != objectListScene.end() ; itObject++) {

			// Gets the 'category label ID' of the current object instance
			int categoryCurrentObject = (*itObject).getActualObjectID();

			// If the object instance is the same as the current category label in the cluster model
			if (categoryCurrentObject == currentCategoryCluster) {

				currentObjectPresent = true;

				clusterObjectToSceneId[currentCategoryCluster] = (*itObject);

				// vector of possible object instances in case of multiple possibilities
				clusterObjectToVectorObjects[currentCategoryCluster].push_back(*itObject);

			}
		}
		// // IF the current object in the cluster is not found, then the cluster is not found in the scene
		if (currentObjectPresent == false)  {
			clusterPresent = false;
		}
	}

	//********************************************************************************************************

	if (clusterPresent == true) {

		if (DEBUG) {
			cout << "The object cluster model is present in the current test scene" << endl;
		}

		assignment chosenAssignment;

		// Iterates over the map: clusterObjectToVectorObjects[currentCategoryCluster], map<int, vector<Object> >
		for (map<int, vector<Object> >::iterator it = clusterObjectToVectorObjects.begin(); it != clusterObjectToVectorObjects.end(); it++) {

			if (DEBUG) {
				cout << endl << "New element of the cluster model" << endl;
			}

			// if multiple possible object instances:: choose the one that minimizes likelihood (that object category VS. desk)
			if ((*it).second.size() > 1) {

				if(DEBUG) {
					cout << "There are multiple object instances in the scene for current category of the model" << endl;
				}

				vector<double> allLikelihoodScores;

				// for each of the possibilities
				for (int i = 0; i < (*it).second.size(); i++) {

					if(DEBUG) {
						cout << "There are multiple object instances : possibility : " << i << endl;
					}

					// the current object instance
					Object currentObject = ((*it).second).at(i);

					// the category label of the current object instance
					int currentCategoryLabel = currentObject.getActualObjectID();



					// // Computes the likelihood value for corresponding pair (desk - that current object)
					for (int count = 0; count < cluster.getObjectPairsInitial().size(); count++ ) {

						ObjectPairModel currentPair = cluster.getObjectPairsInitial().at(count);
						int category1 = currentPair.getCategoryLabel1();
						int category2 = currentPair.getCategoryLabel2();

						if (  category1 == currentCategoryLabel && category2 == 100 ) {

							cv::Mat means = currentPair.getMeans();
							cv::Mat weights = currentPair.getWeights();
							vector<cv::Mat> covs = currentPair.getCovs();
							double likelihood;
							vector<float> feats;
							float xcoord = (float)((currentObject.getCentroid()).x);
							float ycoord = (float)((currentObject.getCentroid()).y);
							float zcoord = (float)((currentObject.getCentroid()).z);

							feats.push_back(xcoord);
							feats.push_back(ycoord);
							feats.push_back(zcoord);

							likelihood = StatisticalTool::computeGMMProbability(feats,  means, covs, weights);
							allLikelihoodScores.push_back(likelihood);

							if (DEBUG) {
								cout << "likelihood = " << likelihood << endl;
							}

						}
					}
				}

				if (DEBUG) {
					cout << "Selecting the most likely possibility" << endl;
				}

				// choose the maximum
				int maxPos = computeMaximum(allLikelihoodScores);



				chosenAssignment[(*it).first] = (*it).second.at(maxPos);

			}
			else {

				chosenAssignment[(*it).first] = (*it).second.at(0);
			}

		}

		if (DEBUG) {
			cout << "After selecting the assignment of object instances to cluster model objects" << endl;
		}

		// **********************************************************************************************************

		// // Computation of pairwise features

		vector<ObjectPairModel> objectPairList = cluster.getObjectPairsFinal();

		// For each pair of objects in the cluster: gets the corresponding pair in the scene
		for ( int k = 0; k < objectPairList.size(); k++ ) {

			double distX, distY, distZ;

			int category1 = objectPairList.at(k).getCategoryLabel1();
			int category2 = objectPairList.at(k).getCategoryLabel2();

			if (DEBUG) {
				cout << "Extracting feature in test scene from the pair " << category1 << " -- " << category2 << endl;
			}

			// if it is NOT a pair containing the desk

			if ( category1 != 100 && category2 != 100 ) {
				Object instance1 = chosenAssignment[category1];
				Object instance2 = chosenAssignment[category2];

				// Computes the pairwise features between 'instance1' and 'instance2'

				distX = computeDistanceX(instance1, instance2);
				distY = computeDistanceY(instance1, instance2);
				distZ = computeDistanceZ(instance1, instance2);

			}

			// IF it is a pair with the desk (category label ID == 100)

			else if (category2 == 100) {

				// Computes the pairwise features between 'instance1' and 'desk' corner (0,0,0)

				Object instance1 = chosenAssignment[category1];
				distX = (instance1.getCentroid()).x;
				distY = (instance1.getCentroid()).y;
				distZ = (instance1.getCentroid()).z;
			}
			else {
				cout << "Error: the desk pair is not set correctly." << endl;
			}

			double arr[] = {distX, distY, distZ};
			vector<double> featCurrentSample (arr, arr + sizeof(arr) / sizeof(arr[0]) );

			// Add the feature row to the corresponding pair-matrix (the k-th pair of the cluster)

			features.push_back(featCurrentSample);

			if (DEBUG) {
				cout << "FeatureExtraction:: The size of the test features current pair, pair # '" << k << "', is " << featCurrentSample.size() << endl;
			}

			}
		}

	if (DEBUG) {
		cout << "FeatureExtraction:: The size of the test features is " << features.size() << endl;
	}

	feats.setFeatureMatrices(features);

}







