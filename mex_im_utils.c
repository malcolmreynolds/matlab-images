#include "mex.h"
#include "mex_im_utils.h"

/**
 Get the number of elements in an mxArray
 */
unsigned int numElements(const mxArray* array) {
  mwSize numDims = mxGetNumberOfDimensions(array);
  const mwSize* dimsArray = mxGetDimensions(array);
  unsigned int num = 1;
  unsigned int i;

  for (i=0; i<numDims; i++) {
    num *= dimsArray[i];
  }

  return num;
}

unsigned int imageSizeMatchesMask(const mxArray* im, const mxArray* mask) {
  const mwSize* imDims = mxGetDimensions(im);
  const mwSize* maskDims = mxGetDimensions(mask);

  //mexPrintf("im is %dx%d\n",imDims[0],imDims[1]);
  //mexPrintf("mask is %dx%d\n",maskDims[0],maskDims[1]);

  if (imDims[0] != maskDims[0]) return 0;
  if (imDims[1] != maskDims[1]) return 0;
  
  //if both match..
  return 1;
}
