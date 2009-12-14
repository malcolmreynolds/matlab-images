#include "mex.h"
#include "mex_im_utils.h"

/**
 Quickly returns the sum of squares of a (probably) 256 x 256 x 256
 colour cube. We don't actually check for the explicit number of
 dimensions / size, we just square and then sum every element.
 */

const mxArray* cube;
double* cubeData;
double val;
double total;
unsigned int numPixels;
unsigned int i;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(1);
  ASSERT_IS_DOUBLE(prhs[0],0);
    
  cube = prhs[0];
  numPixels = numElements(cube);
  cubeData = mxGetPr(cube);

  total = 0.0;
  for (i=0; i<numPixels; i++) {
    val = *cubeData++;
    total += val*val;
  }

  //put the value in the output
  plhs[0] = mxCreateDoubleScalar(total);
}
  
