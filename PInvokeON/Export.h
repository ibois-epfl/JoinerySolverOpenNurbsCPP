#pragma once
// defining OPENNURBS_PUBLIC_INSTALL_DIR enables automatic linking using pragmas
#define OPENNURBS_PUBLIC_INSTALL_DIR "C:/IBOIS57/_Code/Software/CPP/opennurbs-7.6.21127.19001/"
// uncomment the next line if you want to use opennurbs as a DLL
#define OPENNURBS_IMPORTS
#include "C:/IBOIS57/_Code/Software/CPP/opennurbs-7.6.21127.19001/opennurbs_public.h"




#define PINVOKE extern "C" __declspec(dllexport)

PINVOKE void ReleaseInt(int* arr, bool isArray);
PINVOKE void ReleaseFloat(float* arr, bool isArray);
PINVOKE void ReleaseDouble(double* arr, bool isArray);
PINVOKE int Power2(int a);


PINVOKE int UnsafeCollisionDetectionOBB(
    double* PositionsXYZ,
    double* XAxesXYZ,
    double* YAxesXYZ,
    double* HalfSizeXYZ,
    size_t numberOfBoxes,
    int*& pairs, int& numberOfPairs);

