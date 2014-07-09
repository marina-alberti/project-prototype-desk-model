/*
 * ObjectPairModel.cpp
 *
 *  Created on: May 19, 2014
 *      Author: marina
 */


#include "ObjectPairModel.hpp"

// int ObjectPairModel::objectPairID = 0;


ObjectPairModel::ObjectPairModel(int cat1, int cat2, int id1, int id2) {

	objectPairID = 0; // TODO: change! static?
	categoryLabel1 = cat1;
	categoryLabel2 = cat2;
	objectPartID1 = id1;
	objectPartID2 = id2;

}
