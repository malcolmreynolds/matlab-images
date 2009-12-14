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

  cube1 = prhs[0];
  cube2 = prhs[1];

  ASSERT_IS_DOUBLE(cube1,0);
  ASSERT_IS_DOUBLE(cube2,1);

  numPixels = num_elements(cube1);
  if (numPixels != num_elements(cube2)) {
    mexErrMsgTxt("cube_diff_sse: both arguments must have same number of elements");
  }

  c1ptr = mxGetPr(cube1);
  c2ptr = mxGetPr(cube2);

  total = 0.0;
  for (i=0; i<numPixels; i++) {
    val = (*c1ptr - *c2ptr);
    total += val * val;
    c1ptr++;
    c2ptr++;
  }

  plhs[0] = mxCreateDoubleScalar(total);
}
    
