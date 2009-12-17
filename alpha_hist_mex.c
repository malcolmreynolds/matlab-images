#include "mex.h"
#include "mex_im_utils.h"

/** Calculates the 1D histogram for data given in sint32 format. Args as follows:

    prhs[0]: data in sint32
    prhs[1]: alpha mask in double
    prhs[2]: offset to add to each value to get what bin of the histogram to put it in
             - note this is from Matlab, so decrement these to get the actual offset - uint32
    prhs[3]: number of bins to put value into. - uint32
*/

// Could definitely extend this to have 2 more arguments saying giving offset and
// length into the data to go... save that until once this version is tested.

const mxArray *im, *amask;
signed int *dataptr;
double *amaskptr, *histptr;
signed int dataval;
double aval, total_alpha;
unsigned int offset, histlength, numpixels, i;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(4);
  
  ASSERT_IMAGE_AND_MASK(prhs[0],prhs[1]);
  ASSERT_IS_SINT32(prhs[0]);
  ASSERT_IS_DOUBLE(prhs[1]);
  ASSERT_IS_UINT32(prhs[2]);
  ASSERT_IS_UINT32(prhs[3]);

  ASSERT_IS_SCALAR(prhs[2]);
  ASSERT_IS_SCALAR(prhs[3]);

  im = prhs[0];
  amask = prhs[1];
  offset = SCALAR_GET_UINT32(prhs[2]) - 1; // subtract 1 because matlab has 1 indexed arrays
  histlength = SCALAR_GET_UINT32(prhs[3]);

  //create output histogram
  plhs[0] = mxCreateNumericMatrix(1,histlength,mxDOUBLE_CLASS,mxREAL);
  histptr = (double *)getMxPr(plhs[0]);

  // in future maybe we just use offset and length into data..
  numpixels = num_elements(im);
  dataptr = (signed int *)mxGetPr(im);
  amaskptr = (double *)mxGetPtr(amask);
  total_alpha = 0.0;
  for (i=0; i<numpixels; i++) {
    dataval = *dataptr++;
    aval = *amaskptr++;
    //add offset
    dataval += offset;
    //check we haven't been given fucked data.. Don't remove this in future!
    if ((dataval < 0) || (dataval > histlength)) {
      char msgbuf[ERR_MSG_SIZE];
      sprintf(msgbuf,"%s:%d pix %d prouced value %d outside of valid range.",
	      __FILE__,__LINE__,i,dataval);
      mexErrMsgTxt(msgbuf);
    }

    // nothing to add on?
    if (aval == 0.0) continue;
    
    histptr[dataval] += aval;
  }
}
