#include "mex.h"
#include "mex_im_utils.h"

/**
   Returns sum of squared differences of two arbitrarily dimensioned
   arrays. Note the must have the same number of elements and both be
   of type double. This function is nominally for histogram cubes, but
   will work on a reasonable variety of things.  */

const mxArray* cube1;
const mxArray* cube2;
double* c1ptr;
double* c2ptr;
double val;
double total;
unsigned int numPixels;
unsigned int i;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(2);
  ASSERT_IS_DOUBLE(prhs[0]);
  ASSERT_IS_DOUBLE(prhs[1]);
  ASSERT_SAME_SIZE(prhs[0],prhs[1]);

  cube1 = prhs[0];
  cube2 = prhs[1];

  c1ptr = mxGetPr(cube1);
  c2ptr = mxGetPr(cube2);

  numPixels = num_elements(cube1);
  total = 0.0;
  for (i=0; i<numPixels; i++) {
    val = (*c1ptr - *c2ptr);
    //mexPrintf("val=%e\n",val);
    total += val * val;
    c1ptr++;
    c2ptr++;
  }

  mexPrintf("final sse=%d\n",total);
  plhs[0] = mxCreateDoubleScalar(total);
}
    
