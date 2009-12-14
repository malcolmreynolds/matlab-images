#ifndef __MEX_IM_UTILS_H
#define __MEX_IM_UTILS_H

#include "mex.h"

//These functions are found in mex_im_utils.c
unsigned int num_elements(const mxArray* array);
unsigned int image_size_matches_mask(const mxArray* im, const mxArray* mask);
void normalise_array(const mxArray* src, mxArray* dest);
void normalise_array_inplace(mxArray* array, double val);

//inline utils
inline double max(double d1, double d2) {
  return (d1 > d2) ? d1 : d2;
}

//*****************************
// Macros to check number of arguments etc.

#define ERR_MSG_SIZE 512

// the do { ... } while(0) means I can have a semi colon after the
// macro invocations, which makes things look super sweet.

//Assert that we have exactly `num' right hand side arguments.
#define ASSERT_NUM_RHS_ARGS_EQUALS(num)					\
  do {									\
    if (nrhs != (num)) {						\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d expected %d rhs arguments, but got %d.",	\
	      __FILE__,__LINE__,(num),nrhs);				\
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

//Assert that we have exactly `num' left hand side arguments
#define ASSERT_NUM_LHS_ARGS_EQUALS(num)					\
  do {									\
    if (nlhs != (num)) {						\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d expected %d lhs arguments, but got %d.",	\
	      __FILE__,__LINE__,(num),nlhs);				\
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

//Assert that we have less than `num' left hand side arguments
#define ASSERT_NUM_LHS_ARGS_LT(num)					\
  do {									\
    if (nlhs >= (num)) {						\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d expected less than %d lhs arguments, but got %d.",\
	      __FILE__,__LINE__,(num),nlhs);				\
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

// Put ASSERT_NUM_RHS_ARGS_LT and others here, once needed.

//***************************
//Macros to check type of args

// Assert the third dimension of an array is of size 3 (as in, an RGB image)
#define ASSERT_HAS_3_CHANNELS(array)					\
  do {									\
    if (mxGetNumberOfDimensions(array) != 3 ||				\
	mxGetDimensions(array)[2] != 3) {				\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d argument should have 3 channels.",		\
	      __FILE__,__LINE__);					\
      mexErrMsgTxt(msgbuf);						\
    } } while(0)


#define ASSERT_2D_ARRAY(array)						\
  do {									\
    if (mxGetNumberOfDimensions(array) != 2) {				\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d argument should be 2 dimensional.",		\
	      __FILE__,__LINE__);					\
      mexErrMsgTxt(msgbuf);						\
    } } while(0) 

#define ASSERT_IS_UINT8(array)						\
  do {									\
    if (!mxIsUint8(array)) {						\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d argument must be of type Uint8.",		\
	      __FILE__,__LINE__);					\
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

#define ASSERT_IS_DOUBLE(array)						\
  do {									\
    if (!mxIsDouble(array)) {						\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d argument must be of type Double.",		\
	      __FILE__,__LINE__);					\
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

#define ASSERT_SCALAR(array)						\
  do {									\
    if (num_elements(array) != 1) {					\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d argument must be a single number.",		\
	      __FILE__,__LINE__);					\
      mexErrMsgTxt(msgbuf);						\
    } } while(0)

//Check that two arrays have the exact same dimensionality.
#define ASSERT_SAME_SIZE(array1,array2)					\
  do {									\
    const mwSize c1nd = mxGetNumberOfDimensions(array1);		\
    const mwSize c2nd = mxGetNumberOfDimensions(array2);		\
    if (c1nd != c2nd) {							\
      char msgbuf[ERR_MSG_SIZE];					\
      sprintf(msgbuf,"%s:%d arrays are not same size! %d dims vs %d dims!", \
	      __FILE__,__LINE__,c1nd,c2nd);				\
      mexErrMsgTxt(msgbuf);						\
    }									\
    const mwSize* dims1 = mxGetDimensions(array1);			\
    const mwSize* dims2 = mxGetDimensions(array2);			\
    unsigned int i;							\
    for (i=0; i<c1nd; i++) {						\
      if (dims1[i] != dims2[i]) {					\
	char msgbuf[ERR_MSG_SIZE];					\
	sprintf(msgbuf,"%s:%d array1 dim %d = %d, array2 dim %d = %d",	\
		__FILE__,__LINE__,i,dims1[i],i,dims2[i]);		\
	mexErrMsgTxt(msgbuf);						\
      }									\
    } } while(0)



#endif
