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
unsigned char* maskptr;
unsigned int i, num_pixels;
double val, total;


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(3);
  ASSERT_IS_DOUBLE(prhs[0]);
  ASSERT_IS_DOUBLE(prhs[1]);
  ASSERT_IS_UINT8(prhs[2]);
  ASSERT_SAME_SIZE(prhs[0],prhs[1]);
  ASSERT_SAME_SIZE(prhs[1],prhs[2]);

  cube1 = prhs[0];
  cube2 = prhs[1];
  mask = prhs[2];

  c1ptr = mxGetPr(cube1);
  c2ptr = mxGetPr(cube2);
  maskptr = (unsigned char *)mxGetPr(mask);

  num_pixels = num_elements(cube1);
  total = 0.0;
  for (i=0; i<num_pixels; i++) {
    val = (*c1ptr - *c2ptr);
    if (*maskptr) { // if the mask is non zero, then add the value
      total += (val * val);
    }
    c1ptr++;
    c2ptr++;
    maskptr++;
  }

  plhs[0] = mxCreateDoubleScalar(total);
}
