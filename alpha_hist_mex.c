#include "mex.h"
#include "mex_im_utils.h"

unsigned int offset, histlength;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  ASSERT_NUM_RHS_ARGS_EQUALS(4);
  
  ASSERT_IMAGE_AND_MASK(prhs[0],prhs[1]);
  ASSERT_IS_SINT32(prhs[0]);
  ASSERT_IS_DOUBLE(prhs[1]);
  ASSERT_IS_UINT32(prhs[2]);
  ASSERT_IS_UINT32(prhs[3]);

  ASSERT_IS_SCALAR(prhs[2]);
  ASSERT_IS_SCALAR(prhs[3]);

  offset = SCALAR_GET_UINT32(prhs[2]);
  histlength = SCALAR_GET_UINT32(prhs[3]);

  




}
