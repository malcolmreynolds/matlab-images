#include "mex.h"
#include "mex_im_utils.h"

/** This matches the functionality of im_hist_cube.m - returns a
    256x256x256 histogram cube. It is aware of alpha masks, indeed it
    requires one to run at all. The alpha mask must be a double and
    elements are expected to be in the range 0.0 to 1.0, and the image
    must be a uint8
 */

// obviously this only works when cubePtr is defined
#define CUBEPTR(r,g,b) cubePtr[((b)*CUBE_SIDE*CUBE_SIDE) + ((g)*CUBE_SIDE) + (r)]

// need to change this if for some reason the images aren't uint8 any
// more (ie quantised into 16 bits or something)
#define CUBE_SIDE 256
mwSize DIMENSIONS[] = { CUBE_SIDE, CUBE_SIDE, CUBE_SIDE };
const unsigned int TOTALCUBESIZE = CUBE_SIDE * CUBE_SIDE * CUBE_SIDE;

//Working variables
const mxArray* im;
const mxArray* amask;
double* aMaskPtr;
double* cubePtr;
unsigned char *rPtr;
unsigned char *gPtr;
unsigned char *bPtr;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(2);
  ASSERT_NUM_LHS_ARGS_LT(2);
  
  //grab the arguments
  im = prhs[0];
  amask = prhs[1];
  
  ASSERT_HAS_3_CHANNELS(im,0);
  ASSERT_2D_ARRAY(amask,1);
  ASSERT_IS_UINT8(im,0);
  ASSERT_IS_DOUBLE(amask,1);
 
  if (!imageSizeMatchesMask(im,amask)) {
    mexErrMsgTxt("im_hist_cube_mex image and mask size do not match!");
  }

  //create the 256x256x256 cube
  plhs[0] = mxCreateNumericArray(3,DIMENSIONS,mxDOUBLE_CLASS,mxREAL);
  cubePtr = mxGetPr(plhs[0]);

  //get pointer to the data. r is first
  rPtr = (unsigned char *)mxGetPr(im);
  // the total elements of the mask is one third of the elements in the full image, so 
  // skip forward by this amount to get to the next channel.
  unsigned int numPixels = numElements(amask);
  //  mexPrintf("%d pixels\n",numPixels);
  gPtr = rPtr + numPixels;
  bPtr = rPtr + (2*numPixels);

  //setup the alpha mask
  aMaskPtr = mxGetPr(amask);

  // this is the only bit that actually contains the algorithm
  unsigned int i;
  unsigned char r, g, b;
  double a;
  double total_alpha = 0.0;

  for (i=0; i<numPixels; i++) {
    //get alpha value and colours
    a = *aMaskPtr++;
    r = *rPtr++;
    g = *gPtr++;
    b = *bPtr++; 
    // we won't be adding anything to the cube on this round, so skip.
    if (a == 0.0) continue;
    CUBEPTR(r,g,b) += a;
    //keep track of the total amount of alpha for normalisation.
    total_alpha += a;
  }

  //normalise by the number of pixels in the image
  for (i=0; i<TOTALCUBESIZE; i++) {
    *cubePtr++ /= total_alpha;
  }
}

