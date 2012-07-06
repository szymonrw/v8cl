#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "v8cl.h"

#define F(NAME) \
  int32_t NAME (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result)

namespace v8cl {
  F(OneArgFn);
  F(GetInfo);
  F(GetDependentInfo);
  F(GetPlatformIDs);
  F(GetDeviceIDs);
  F(CreateContext);
  F(CreateContextFromType);
  F(CreateCommandQueue);
  F(CreateBuffer);
  F(CreateSubBuffer);
  F(CreateImage2D);
  F(CreateImage3D);
  F(GetSupportedImageFormats);
  F(CreateSampler);
  F(CreateProgramWithSource);
  F(BuildProgram);
  F(CreateKernel);
  F(CreateKernelsInProgram);
  F(SetKernelArg);
  F(EnqueueReadOrWriteBuffer);
  F(EnqueueNDRangeKernel);
  F(SetEventCallback);
}

#undef F
#endif
