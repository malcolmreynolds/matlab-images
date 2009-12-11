#ifndef __MEX_IM_UTILS_H
#define __MEX_IM_UTILS_H

#include "mex.h"

unsigned int numElements(const mxArray* array);

unsigned int imageSizeMatchesMask(const mxArray* im, const mxArray* mask);

#endif
