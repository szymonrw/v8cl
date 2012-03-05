#include "v8cl.h"
#include <dlfcn.h>
#include <iostream>

namespace v8cl {
  
  Wrapper wrappers[] = {
    // One-arg void* functions
    { "clRetainContext", OneArgFn, { One<void*> } },
    { "clReleaseContext", OneArgFn, { One<void*> } },
    { "clRetainCommandQueue", OneArgFn, { One<void*> } },
    { "clReleaseCommandQueue", OneArgFn, { One<void*> } },
    { "clRetainMemObject", OneArgFn, { One<void*> } },
    { "clReleaseMemObject", OneArgFn, { One<void*> } },
    { "clRetainSampler", OneArgFn, { One<void*> } },
    { "clReleaseSampler", OneArgFn, { One<void*> } },
    { "clRetainProgram", OneArgFn, { One<void*> } },
    { "clReleaseProgram", OneArgFn, { One<void*> } },
    { "clRetainKernel", OneArgFn, { One<void*> } },
    { "clReleaseKernel", OneArgFn, { One<void*> } },
    { "clFlush", OneArgFn, { One<void*> } },
    { "clFinish", OneArgFn, { One<void*> } },

    // GetInfo functions
    { "clGetPlatformInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
    { "clGetDeviceInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
    { "clGetContextInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
    { "clGetCommandQueueInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
    { "clGetMemObjectInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo }, // TODO: always gives CL_INVALID_VALUE
    { "clGetImageInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
    // { "clGetSamplerInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo }, // TODO: the same as clGetMemObjectInfo
    { "clGetProgramInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
    { "clGetKernelInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },

    // Like GetInfo but requirng to objects to query
    { "clGetProgramBuildInfo", GetDependentInfo, { One<void*>, One<void*>, One<uint32_t> }, ReturnInfo },
    { "clGetKernelWorkGroupInfo", GetDependentInfo, { One<void*>, One<void*>, One<uint32_t> }, ReturnInfo },

    // Individual functions
    { "clGetPlatformIDs", GetPlatformIDs, {}, ReturnPointerArray },
    { "clGetDeviceIDs", GetDeviceIDs, { One<void*>, One<uint32_t> }, ReturnPointerArray },
    { "clCreateContext", CreateContext, { NullTerminatedList, Many<void*> }, ReturnPointer },
    { "clCreateCommandQueue", CreateCommandQueue, { One<void*>, One<void*>, One<uint32_t> }, ReturnPointer },
    // TODO: segfault in libOpenCL.so { "clCreateContextFromType", { NullTerminatedList, One<uint32_t> }, CreateContextFromType, PointerReturner, 2},
    { "clCreateBuffer", CreateBuffer, { One<void*>, One<uint32_t>, One<size_t> }, ReturnPointer },
    { "clCreateSubBuffer", CreateSubBuffer, { One<void*>, One<uint32_t>, One<uint32_t>, BufferRegion }, ReturnPointer },
    { "clCreateImage2D", CreateImage2D, { One<void*>, One<uint32_t>, ImageFormat, One<size_t>, One<size_t> }, ReturnPointer },
    { "clCreateImage3D", CreateImage3D, { One<void*>, One<uint32_t>, ImageFormat, One<size_t>, One<size_t>, One<size_t> }, ReturnPointer },
    { "clGetSupportedImageFormats", GetSupportedImageFormats, { One<void*>, One<uint32_t>, One<uint32_t> }, ReturnImageFormatArray },
    { "clCreateSampler", CreateSampler, { One<void*>, One<uint32_t>, One<uint32_t>, One<uint32_t> }, ReturnPointer },
    { "clCreateProgramWithSource", CreateProgramWithSource, { One<void*>, CharArray }, ReturnPointer },
    { "clBuildProgram", BuildProgram, { One<void*>, Many<void*>, CharArray } },
    { "clCreateKernel", CreateKernel, { One<void*>, CharArray }, ReturnPointer },
    { "clCreateKernelsInProgram", CreateKernelsInProgram, { One<void*> }, ReturnPointerArray },
    { "clSetKernelArg", SetKernelArg, { One<void*>, One<uint32_t>, One<size_t>, TypedArray } },
    { "clEnqueueReadBuffer", EnqueueReadOrWriteBuffer, { One<void*>, One<void*>, One<uint32_t>, TypedArray } },
    { "clEnqueueWriteBuffer", EnqueueReadOrWriteBuffer, { One<void*>, One<void*>, One<uint32_t>, TypedArray } },
    { "clEnqueueNDRangeKernel", EnqueueNDRangeKernel, { One<void*>, One<void*>, Many<size_t>, Many<size_t>, Many<size_t> } },
    { NULL }
  };

  map<int, const char*> errorCodes = GetErrorCodes();
  
  void DeleteAllItems(vector<void*>& data) {
    for(vector<void*>::iterator it = data.begin(), end = data.end();
        it < end; ++it) {
      if (*it) free(*it);
    }
  }

  Handle<Value> InvokeWrapper (const Arguments& args) {
    HandleScope scope;

    Wrapper *wrapper = (Wrapper*) External::Unwrap(args.Data());
    if (!wrapper) {
      return ThrowException(Exception::Error(String::New("Wrapper missing.")));
    }
    if (!wrapper->f) {
      return ThrowException(Exception::Error(String::New("Function not implemented.")));
    }

    int length = args.Length();
    if (length < wrapper->minArgc) {
      return ThrowException(Exception::Error(String::New("Need more arguments.")));
    }
    
    Converter *converter = wrapper->converters;
    vector<void*> natives;
    for (int i = 0; (i < length) && *converter; ++i, ++converter) {
      (*converter)(args[i], natives);
    }

    vector<void*> result;
    int32_t error = wrapper->action(wrapper->f, natives, result);

    if (error) {
      DeleteAllItems(natives);
      DeleteAllItems(result);
      if (errorCodes.count(error)) {
        return scope.Close(ThrowException(Exception::Error(String::New(errorCodes[error]))));
      } else {
        return scope.Close(ThrowException(Exception::Error(String::Concat(String::New("Unknown WebCL error code: "), Integer::New(error)->ToString()))));
      }
    }

    Handle<Value> jsResult = Undefined();

    if (wrapper->returner) {
      jsResult = wrapper->returner(natives, result);
    }

    DeleteAllItems(natives);
    DeleteAllItems(result);
    return scope.Close(jsResult);
  }

  
  void SetWebCL(Handle<Object> target) {
    SetConstants(target);

    Handle<Array> loadingErrors = Array::New();
    target->Set(String::New("loadingErrors"), loadingErrors);

    char* error = dlerror(); // clear any previous errors
    void* opencl = dlopen("libOpenCL.so", RTLD_LAZY | RTLD_LOCAL);
    error = dlerror();
    if (error) {
      loadingErrors->Set(0, String::New(error));
      return;
    }

    uint32_t errorIdx = 0;
    char firstLetter[2] = " ";
    
    for (Wrapper *wrapper = wrappers; wrapper->name; ++wrapper) {
      wrapper->f = dlsym(opencl, wrapper->name);
      error = dlerror();
      if (error) {
        wrapper->f = NULL;
        loadingErrors->Set(errorIdx++, String::New(error));
      }

      if (!wrapper->minArgc) {
        Converter *tmp = wrapper->converters;
        wrapper->minArgc = 0;
        while (*(tmp++)) wrapper->minArgc++;
      }

      Handle<External> data = External::New(wrapper);
      Handle<FunctionTemplate> ftpl = FunctionTemplate::New(InvokeWrapper, data);

      // Convert name from clAaaBbb to aaaBbb
      firstLetter[0] = wrapper->name[2] - ('A' - 'a');
      Handle<String> name = String::Concat(String::New(firstLetter), String::New(wrapper->name + 3));
      target->Set(name, ftpl->GetFunction());
    }
  }
}
