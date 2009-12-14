#include "mex.h"
#include "mex_im_utils.h"

/**
   Returns sum of squared differences of two arrays which have the
   same number of elements. The difference is only counted when a
   corresponding mask is non-zero, allowing only relevant parts of the
   colour spectrum to be considered.
*/

const mxArray* cube1;
const mxArray* cube2;
const mxArray* mask;
double* c1ptr;
double* c2ptr;


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(3);
  ASSERT_IS_DOUBLE(prhs[0],0);
  ASSERT_IS_DOUBLE(prhs[1],1);
  ASSERT_IS_UINT8(prhs[2],2);
  cube1 = prhs[0];
  cube2 = prhs[1];
  
