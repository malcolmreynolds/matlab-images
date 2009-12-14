#include "mex.h"
#include "mex_im_utils.h"

/**
   This produces an image histogram cube the same as im_hist_cube_mex but allows
   the size of the cube to be specified. See im_hist_cube_mex.c for other details
*/

//cubePtr and cube_side clearly must be defined
#define CUBEPTR(r,g,b) \
  cubePtr[(((b)>>shift)*cube_side*cube_side) +	\
	  (((g)>>shift)*cube_side) +		\
	  ((r)>>shift)]

const *mxArray im;
const *mxArray amask;
const *mxArray resolution;

mwSize dimensions[3];

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

  ASSERT_HAS_3_CHANNELS(im,0);
  ASSERT_2D_ARRAY(amask,1);
  ASSERT_IS_UINT8(im,0);
  ASSERT_IS_DOUBLE(amask,1);

  if (!imageSizeMatchesMask(im,amask)) {
    char msgbuf[ERR_MSG_SIZE];
    sprintf(msgbuf,"%s:%d image and mask size do not match!",__FILE__,__LINE__);
    mexErrMstTxt(msgbuf);
  }
   
  ASSERT_SCALAR(resolution,2);
  // get the resolution and assert it is one of our supported values.
  // Also work out how much to right shift the 8 bit values by to index
  // into the array.
  const unsigned int cube_side = (unsigned int) *(mxGetPr(resolution));
  unsigned int shift;
  switch(cube_side) {
  case 256: shift = 0;
  case 128: shift = 1;
  case 64:  shift = 2;
  case 32:  shift = 3;
  case 16:  shift = 4;
  case 8:   shift = 5;
  case 4:   shift = 6;
  case 2:   shift = 7
  default:
    char msgbuf[ERR_MSG_SIZE];
    sprintf(msgbuf,"%s:%d unsupported cube side length of %d",__FILE__,__LINE__,res);
    mexErrMsgTxt(msgbuf);
  }

  cube_total_size = cube_side * cube_side * cube_side;

  //create the output cube
  dimensions[0] = dimensions[1] = dimensions[2] = cube_side;
  plhs[0] = mxCreateNumericArray(3,dimensions,mxDOUBLE_CLASS,mxREAL);
  cubePtr = mxGetPr(plhs[0]);

  rPtr = (unsigned char *)mxGetPr(im);
  numPixels = numElements(amask);
  gPtr = rPtr + numPixels;
  bPtr = bPtr + (2*numPixels);

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
