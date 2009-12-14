#include "mex.h"
#include "mex_im_utils.h"

/**
   Normalise a colour cube. This is useful enough to have it as a (C)
   library function and also have it accessible from the matlab
   side. Otherwise we will normalise our colour cubes at least twice, and lose precision.
*/

double *ptr, *start;
double total;
unsigned int i, numPixels;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(1);
  ASSERT_IS_DOUBLE(prhs[0],0);

  // create the destination matrix
  plhs[0] = mxCreateNumericArray(mxGetNumberOfDimensions(prhs[0]),
				 mxGetDimensions(prhs[0]),
				 mxDOUBLE_CLASS, mxREAL);
  // use library function to do the actual normalisation
  normalise_array(prhs[0],plhs[0]);
}
  
