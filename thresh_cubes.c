#include "mex.h"
#include "mex_im_utils.h"

/**
   Takes 2 histogram cubes and thresholds their difference to find the areas which
   are most important. Thresholding takes place some configurable
   fraction below the max element of the whole cube. Returns a cube
   the same size (currently of type double) containing either one or zero.
*/

// I could use createLogicalArray but meh.
#ifdef UINT_MASK //produce the mask as uint8s to save space

#define OUTPUT_TYPE_CONSTANT mxUINT8_CLASS
#define OUTPUT_C_TYPE unsigned char
#define OUTPUT_PTR_TYPE unsigned char *
#define ABOVE_THRESH 1
#define BELOW_THRESH 0

#else

#define OUTPUT_TYPE_CONSTANT mxDOUBLE_CLASS
#define OUTPUT_C_TYPE double
#define OUTPUT_PTR_TYPE double*
#define ABOVE_THRESH 1.0
#define BELOW_THRESH 0.0

#endif  //UINT_MASK

unsigned int numPixels, i;
double *p1, *p2;
double diff, max_diff, threshold;
OUTPUT_PTR_TYPE output;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(3);
  ASSERT_IS_DOUBLE(prhs[0],0);
  ASSERT_IS_DOUBLE(prhs[1],1);
  ASSERT_SAME_SIZE(prhs[0],prhs[1]);
  ASSERT_SCALAR(prhs[2],2);

  //create destination
  plhs[0] = mxCreateNumericArray(mxGetNumberOfDimensions(prhs[0]),
				 mxGetDimensions(prhs[0]),
				 OUTPUT_TYPE_CONSTANT, mxREAL);

  //first find max difference, we need to know how much to threshold by
  numPixels = num_elements(prhs[0]);
  p1 = mxGetPr(prhs[0]);
  p2 = mxGetPr(prhs[1]);
  max_diff = 0.0;
  for (i=0; i<numPixels; i++) {
    diff = abs(*p1++ - *p2++);
    max_diff = max(diff,max_diff);
  }

  // get the parameter which says what proportion of max diff will be
  // the threshold and calculate this limit
  threshold = *(mxGetPr(prhs[2])) * max_diff;

  p1 = mxGetPr(prhs[0]);
  p2 = mxGetPr(prhs[1]);
  output = (OUTPUT_PTR_TYPE)mxGetPr(plhs[0]);

  for (i=0; i<numPixels; i++) {
    diff = abs(*p1++ - *p2++);
    if (diff > threshold) {
      *output++ = ABOVE_THRESH;
    } else {
      *output++ = BELOW_THRESH;
    }
  }
}


