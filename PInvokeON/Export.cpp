#include "pch.h"
#include "Export.h"
#include <fstream>
#include <iostream>
#include <vector>


PINVOKE void ReleaseInt(int* arr, bool isArray) {
	deletePtr(arr, isArray);
}

PINVOKE void ReleaseFloat(float* arr, bool isArray) {
	deletePtr(arr, isArray);
}

PINVOKE void ReleaseDouble(double* arr, bool isArray) {
	deletePtr(arr, isArray);
}

PINVOKE int Power2(int a) {
	return a * a;
}




PINVOKE int UnsafeCollisionDetectionOBB(
    double* PositionsXYZ,
    double* XAxesXYZ,
    double* YAxesXYZ,
    double* HalfSizeXYZ,
    size_t numberOfBoxes,
    int*& pairs, int& numberOfPairs) {

    //////////////////////////////////////////////////////////////////////////////
    //create the R-tree from the input points.
    //////////////////////////////////////////////////////////////////////////////
    ON_RTree tree;
    tree.~ON_RTree();







    //////////////////////////////////////////////////////////////////////////////
    // Convert Parameters to ON_Box
    //////////////////////////////////////////////////////////////////////////////
    ON_SimpleArray<ON_Box> OBB(numberOfBoxes);
    ON_SimpleArray<ON_BoundingBox> AABB(numberOfBoxes);

    for (int i = 0; i < numberOfBoxes; i++) {

        //Create OBB
        ON_Box box;
        ON_Point position(PositionsXYZ[i * 3], PositionsXYZ[i * 3 + 1], PositionsXYZ[i * 3 + 2]);
        ON_Point xAxis(XAxesXYZ[i * 3], XAxesXYZ[i * 3 + 1], XAxesXYZ[i * 3 + 2]);
        ON_Point yAxis(YAxesXYZ[i * 3], YAxesXYZ[i * 3 + 1], YAxesXYZ[i * 3 + 2]);
        box.plane = ON_Plane(position, xAxis, yAxis);
        box.dx = ON_Interval(-HalfSizeXYZ[i * 3], HalfSizeXYZ[i * 3]);
        box.dy = ON_Interval(-HalfSizeXYZ[i * 3 + 1], HalfSizeXYZ[i * 3 + 1]);
        box.dz = ON_Interval(-HalfSizeXYZ[i * 3 + 2], HalfSizeXYZ[i * 3 + 2]);
        OBB[i] = box;

        //Get AABB
        ON_BoundingBox bbox = box.BoundingBox();
        tree.Insert(bbox.Min(), bbox.Max(), i);
        AABB[i] = bbox;
    }

    //////////////////////////////////////////////////////////////////////////////
    // Search Closest Boxes | Skip duplicates pairs | Perform callback with OBB
    //////////////////////////////////////////////////////////////////////////////
    std::vector<int> pairsList;
    for (int i = 0; i < numberOfBoxes; i++) {
        ON_SimpleArray<int> neighbours;

        tree.Search(AABB[i].Min(), AABB[i].Min(), neighbours);

        for (int j = 0; j < neighbours.Count(); j++) {
            if (neighbours[j] > i) {
                pairsList.push_back(i);
                pairsList.push_back(neighbours[j]);
            }

        }

    }

    //////////////////////////////////////////////////////////////////////////////
    // Create array
    //////////////////////////////////////////////////////////////////////////////
    numberOfPairs = pairsList.size() * 0.5;
    pairs = new int[pairsList.size()];

    for (int i = 0; i < pairsList.size(); i++) {
        pairs[i] = pairsList[i];
    }
    return 0;
}
