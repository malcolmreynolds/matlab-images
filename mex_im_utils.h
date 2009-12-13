#ifndef __MEX_IM_UTILS_H
#define __MEX_IM_UTILS_H

#include "mex.h"

//These functions are found in mex_im_utils.c
unsigned int numElements(const mxArray* array);
unsigned int imageSizeMatchesMask(const mxArray* im, const mxArray* mask);

//*****************************
// Macros to check number of arguments etc.

#define ERR_MSG_SIZE 512

// the do { ... } while(0) means I can have a semi colon after the
// macro invocations, which makes things look super sweet.

//Assert that we have exactly `num' right hand side arguments.
#define ASSERT_NUM_RHS_ARGS_EQUALS(num)					\
  do { if (nrhs != (num)) {						\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d expected %d rhs arguments, but got %d.",__FILE__,__LINE__,(num),nrhs); \
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

//Assert that we have exactly `num' left hand side arguments
#define ASSERT_NUM_LHS_ARGS_EQUALS(num)					\
  do { if (nlhs != (num)) {						\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d expected %d lhs arguments, but got %d.",__FILE__,__LINE__,(num),nlhs); \
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

//Assert that we have less than `num' left hand side arguments
#define ASSERT_NUM_LHS_ARGS_LT(num)					\
  do { if (nlhs >= (num)) {						\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d expected less than %d lhs arguments, but got %d.",__FILE__,__LINE__,(num),nlhs); \
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

// Put ASSERT_NUM_RHS_ARGS_LT and others here, once needed.

//***************************
//Macros to check type of args

// Assert the third dimension of an array is of size 3 (as in, an RGB image)
#define ASSERT_HAS_3_CHANNELS(array,argnum)		  \
  do { if (mxGetNumberOfDimensions(array) != 3 || \
	   mxGetDimensions(array)[2] != 3) {				\
         char msgbuf[ERR_MSG_SIZE];					\
	 sprintf(msgbuf,"%s:%d argument number %d should have 3 channels.",__FILE__,__LINE__,argnum); \
	 mexErrMsgTxt(msgbuf);						\
    } } while(0)


#define ASSERT_2D_ARRAY(array,argnum) \
  do { if (mxGetNumberOfDimensions(array) != 2) { \
    char msgbuf[ERR_MSG_SIZE];			  \
    sprintf(msgbuf,"%s:%d argument number %d should be 2 dimensional.",__FILE__,__LINE__,argnum); \
    mexErrMsgTxt(msgbuf);						\
  } } while(0) 

#define ASSERT_IS_UINT8(array,argnum) \
  do { if (!mxIsUint8(array)) {	   \
    char msgbuf[ERR_MSG_SIZE];	   \
    sprintf(msgbuf,"%s:%d argument number %d must be of type Uint8.",__FILE__,__LINE__,argnum); \
    mexErrMsgTxt(msgbuf); \
  } } while(0)

#define ASSERT_IS_DOUBLE(array,argnum) \
  do { if (!mxIsDouble(array)) { \
    char msgbuf[ERR_MSG_SIZE];	 \
    sprintf(msgbuf,"%s:%d argument number %d must be of type Double.",__FILE__,__LINE__,argnum); \
    mexErrMsgTxt(msgbuf); \
  } } while(0)


#endif
