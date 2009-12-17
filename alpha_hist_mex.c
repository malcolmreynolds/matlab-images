#include "mex.h"
#include "mex_im_utils.h"

/** Calculates the 1D histogram for data given in sint32 format. Args as follows:

    prhs[0]: data in sint32
    prhs[1]: offset into the data to start at - uint32
    prhs[2]: length through the data to consider - this arg and the previous one allow
             channels to be 'histogrammed' separately without having to split channels in
	     matlab, which we can hardly rely upon to be fast... - uint32
    prhs[3]: alpha mask in double

    prhs[4]: offset to add to each value to get what bin of the histogram to put it in
             - note this is from Matlab, so decrement these to get the actual offset - uint32
    prhs[5]: number of bins to put value into. - uint32
*/

// Could definitely extend this to have 2 more arguments saying giving offset and
// length into the data to go... save that until once this version is tested.

const mxArray *im, *amask;
signed int *dataptr;
double *amaskptr, *histptr;
signed int dataval;
double aval, total_alpha;
unsigned int data_offset, data_length, offset, histlength, i;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(6);
   
  ASSERT_IMAGE_AND_MASK(prhs[0],prhs[3]);
  ASSERT_IS_SINT32(prhs[0]);
  ASSERT_IS_UINT32(prhs[1]);
  ASSERT_IS_UINT32(prhs[2]);
  ASSERT_IS_DOUBLE(prhs[3]);
  ASSERT_IS_UINT32(prhs[4]);
  ASSERT_IS_UINT32(prhs[5]);

  ASSERT_IS_SCALAR(prhs[1]);
  ASSERT_IS_SCALAR(prhs[2]);
  ASSERT_IS_SCALAR(prhs[4]);
  ASSERT_IS_SCALAR(prhs[5]);

  im = prhs[0];
  data_offset = SCALAR_GET_UINT32(prhs[1]);
  data_length = SCALAR_GET_UINT32(prhs[2]);
  amask = prhs[3];
  offset = SCALAR_GET_UINT32(prhs[4]) - 1; // subtract 1 because matlab has 1 indexed arrays
  histlength = SCALAR_GET_UINT32(prhs[5]);

  //create output histogram
  plhs[0] = mxCreateNumericMatrix(1,histlength,mxDOUBLE_CLASS,mxREAL);
  histptr = (double *)mxGetPr(plhs[0]);

  //get the data pointer, then increment to get to the right place in the data
  dataptr = (signed int *)mxGetPr(im);
  dataptr += data_offset;
  
  amaskptr = (double *)mxGetPr(amask);
  total_alpha = 0.0;
  for (i=0; i<data_length; i++) {
    dataval = *dataptr++;
    aval = *amaskptr++;
    //add offset
    dataval += offset;
    //check we haven't been given fucked data.. Don't remove this in future 
    //unless pretty damn sure the ranges etc supplied are correct!
    if ((dataval < 0) || (dataval > histlength)) {
      char msgbuf[ERR_MSG_SIZE];
      sprintf(msgbuf,"%s:%d pix %d prouced value %d outside of valid range.",
	      __FILE__,__LINE__,i,dataval);
      mexErrMsgTxt(msgbuf);
    }

    // nothing to add on?t
    if (aval == 0.0) continue;
    
    histptr[dataval] += aval;
    total_alpha += aval;
  }

  //now we need to normalise
  for (i=0; i<histlength; i++) {
    *histptr++ /= total_alpha;
  }
}
