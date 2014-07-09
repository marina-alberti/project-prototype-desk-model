/*
 * PrototypeDesk.cpp
 *
 *  Created on: Mar 18, 2014
 *      Author: marina
 */

#define DEBUG 1

#include "PrototypeDesk.hpp"

PrototypeDesk::PrototypeDesk() {

	numberOfCategories = 0;
	thresholdFrequencySO = 0.9;
}

void PrototypeDesk::extractFrequencySO(DatabaseInformation & db) {
	frequencySO = ApiStatisticsDatabase::computeFrequenciesSingleObject(db);
}


void PrototypeDesk::setThresholdFrequencySO(double i){
	thresholdFrequencySO = i;
}


double PrototypeDesk::getThresholdFrequencySO(){
	return thresholdFrequencySO;
}

int PrototypeDesk::getNumberOfCategories(){
	return numberOfCategories;
}

vector<int> PrototypeDesk::getCategoryList(){
	return categoryList;
}

void PrototypeDesk::computeCategoryList() {


	for (int i = 0; i < frequencySO.size(); i++) {

		if (DEBUG) { cout << "The frequency of category " << i << "  is: " << frequencySO.at(i)  << endl; }

		if (frequencySO.at(i) > thresholdFrequencySO) {
			categoryList.push_back(i);
		}
	}
}

void PrototypeDesk::printCategoryList() {

	cout << "Category List of Prototype Desk object classes::" << endl;

	for (int i = 0; i < categoryList.size(); i++) {

		cout << categoryList.at(i) << endl;

	}

}
