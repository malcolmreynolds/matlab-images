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
double new_diff, max_diff, this_diff, threshold, factor, p1val, p2val;
OUTPUT_PTR_TYPE output;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

  mexErrMsgTxt("This function is parked because I think it's fucked in some way. Use matlab version for moment.\n");

  ASSERT_NUM_RHS_ARGS_EQUALS(3);
  //FIRST TWO ARGS SHOULD BE UINT8!!!
  ASSERT_IS_DOUBLE(prhs[0]);
  ASSERT_IS_DOUBLE(prhs[1]);
  ASSERT_SAME_SIZE(prhs[0],prhs[1]);
  ASSERT_IS_DOUBLE(prhs[2]);
  ASSERT_IS_SCALAR(prhs[2]);

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
    p1val = *p1++;
    p2val = *p2++;
    new_diff = abs(p1val - p2val);
    mexPrintf("p1=%e p2=%e diff=%e max_diff=%e\n",p1val,p2val,new_diff,max_diff);
    if (new_diff > max_diff) {
      max_diff = new_diff;
    }
  }

  // get the parameter which says what proportion of max diff will be
  // the threshold and calculate this limit
  factor = *(mxGetPr(prhs[2]));
  threshold = factor * max_diff;
  mexPrintf("max=%e factor=%e threshold=%e\n",max_diff,factor,threshold);

  p1 = mxGetPr(prhs[0]);
  p2 = mxGetPr(prhs[1]);
  output = (OUTPUT_PTR_TYPE)mxGetPr(plhs[0]);

  for (i=0; i<numPixels; i++) {
    this_diff = abs(*p1++ - *p2++);
    if (this_diff > threshold) {
      mexPrintf("entry %d is %e, above thresh\n",i,this_diff);
      *output++ = ABOVE_THRESH;
    } else {
      *output++ = BELOW_THRESH;
    }
  }
}


