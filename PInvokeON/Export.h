#pragma once
// defining OPENNURBS_PUBLIC_INSTALL_DIR enables automatic linking using pragmas
#define OPENNURBS_PUBLIC_INSTALL_DIR "C:/IBOIS57/_Code/Software/CPP/opennurbs-7.6.21127.19001/"
// uncomment the next line if you want to use opennurbs as a DLL
#define OPENNURBS_IMPORTS
#include "C:/IBOIS57/_Code/Software/CPP/opennurbs-7.6.21127.19001/opennurbs_public.h"




#define PINVOKE extern "C" __declspec(dllexport)



// Windows build
//#if defined (_WIN32)
//#if defined (SAMPLELIBRARY_DLL_EXPORTS)
#define PINVOKE_CPP_CLASS __declspec(dllexport)
#define PINVOKE_CPP_FUNCTION __declspec(dllexport)
#define PINVOKE_C_FUNCTION extern "C" __declspec(dllexport)
//#else
//#define SAMPLELIBRARY_CPP_CLASS __declspec(dllimport)
//#define SAMPLELIBRARY_CPP_FUNCTION __declspec(dllimport)
//#define SAMPLELIBRARY_C_FUNCTION extern "C" __declspec(dllimport)
//#endif // SAMPLELIBRARY_DLL_EXPORTS
//#endif // _WIN32

#define deletePtr(ptr, isArray) if (isArray) {delete[] arr;} else {delete arr;}

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

