project-prototype-desk-model
============================

System requirements

-  PCL library v. 1.4
-  OpenCV library v. opencv-2.4.6.1 or higher
-  CMake v. 2.6

To build the project

cd /yourPath/project-prototype-desk-model/
mkdir build
cd build
cmake ..
make

Usage

See the test cases (TestCases/Cluster/impl/testCluster.cpp and TestCases/MST/testMST.cpp) for examples of training the prototype desk model and using the Minimum Spanning Tree algorithm to determine the strongest pairs-of-object connections in the model.
