#include "mex.h"
#include "mex_im_utils.h"

/**
   This produces an image histogram cube the same as im_hist_cube_mex but allows
   the size of the cube to be specified. See im_hist_cube_mex.c for other details.

   This can be tested by doing this and projecting down to 3 separate channels, and 
   comparing to doing a full res cube, projecting that down the dimensions and then doing combine_bins.
   
*/

int blah = 4;;

const mxArray* im;
const mxArray* amask;
const mxArray* resolution;  

mwSize dimensions[3];


//cubePtr and cube_side clearly must be defined
#define CUBEPTR(r,g,b) cubePtr[(((b)>>shift)*cube_side*cube_side) +	\
	  (((g)>>shift)*cube_side) +		\
	  ((r)>>shift)]

char msgbuf[ERR_MSG_SIZE];
unsigned char *rPtr;
unsigned char *gPtr;
unsigned char *bPtr;
double* cubePtr;
double* aMaskPtr;
unsigned int numPixels, i, cube_total_size;
unsigned char r, g, b;
double a, total_alpha;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(3);
  ASSERT_NUM_LHS_ARGS_LT(2);

  im = prhs[0];
  amask = prhs[1];
  resolution = prhs[2];

  ASSERT_HAS_3_CHANNELS(im);
  ASSERT_2D_ARRAY(amask);
  ASSERT_IS_UINT8(im);
  ASSERT_IS_DOUBLE(amask);

  if (!image_size_matches_mask(im,amask)) {
    char msgbuf[ERR_MSG_SIZE];
    sprintf(msgbuf,"%s:%d image and mask size do not match!",__FILE__,__LINE__);
    mexErrMsgTxt(msgbuf);
  }
   
  /* mexPrintf("mxGetNumberOfDimensions(resolution) = %d\n",mxGetNumberOfDimensions(resolution)); */
  /* mexPrintf("mxGetDimensions(resolution)[0] = %d\n",mxGetDimensions(resolution)[0]); */
  /* mexPrintf("mxGetDimensions(resolution)[1] = %d\n",mxGetDimensions(resolution)[1]); */

  ASSERT_IS_SCALAR(resolution);
  // get the resolution and assert it is one of our supported values.
  // Also work out how much to right shift the 8 bit values by to index
  // into the array.
  const unsigned int cube_side = (unsigned int) *(mxGetPr(resolution));
  unsigned int shift = 0;
  switch(cube_side) {
  case 256: break; // shift is already initialised to zero...
  case 128: shift = 1; break;
  case 64:  shift = 2; break;
  case 32:  shift = 3; break;
  case 16:  shift = 4; break;
  case 8:   shift = 5; break;
  case 4:   shift = 6; break;
  case 2:   shift = 7; break;
  default:
    sprintf(msgbuf,"%s:%d unsupported cube side length of %d",__FILE__,__LINE__,cube_side);
    mexErrMsgTxt(msgbuf);
  }

  cube_total_size = cube_side * cube_side * cube_side;

  //mexPrintf("cube_side=%d shift=%d total_size=%d\n",cube_side,shift,cube_total_size);

  //create the output cube
  dimensions[0] = dimensions[1] = dimensions[2] = cube_side;
  plhs[0] = mxCreateNumericArray(3,dimensions,mxDOUBLE_CLASS,mxREAL);
  cubePtr = mxGetPr(plhs[0]);

  rPtr = (unsigned char *)mxGetPr(im);
  numPixels = num_elements(amask);
  gPtr = rPtr + numPixels;
  bPtr = rPtr + (2*numPixels);

  aMaskPtr = mxGetPr(amask);
  total_alpha = 0;

  for (i=0; i<numPixels; i++) {
    a = *aMaskPtr++;
    r = *rPtr++;
    g = *gPtr++;
    b = *bPtr++;
    //nothing to add this pixel?
    if (a == 0.0) continue;
    CUBEPTR(r,g,b) += a;
    total_alpha += a;
  }


  for (i=0; i<cube_total_size; i++) {
    *cubePtr++ /= total_alpha;
  }
}
