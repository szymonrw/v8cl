#include "v8cl.h"
#include "constants.h"
#include <iostream>

#ifndef _WIN32
#include <dlfcn.h>
#define V8CL_OPENCL_LIB "libOpenCL.so"
#else
#include <windows.h>
#define V8CL_OPENCL_LIB "OpenCL.dll"
#define RTLD_LAZY 0
#define RTLD_LOCAL 0

static const char* dl_error = NULL;
const char* dlerror() {
  const char* err = dl_error;
  dl_error = NULL;
  return err;
}

void* dlopen(const char* libname, int flags) {
  void* lib = LoadLibrary(libname);
  if (!lib) {
    dl_error = libname;
    return NULL;
  } else {
    return lib;
  }
}

void* dlsym (void* lib, const char* name) {
  void* fn = GetProcAddress((HINSTANCE) lib, name);
  if (!fn) {
    dl_error = name;
    return NULL;
  } else {
    return fn;
  }
}
#endif

namespace v8cl {

  Wrapper wrappers[] = {
    { "clFlush", OneArgFn, { One<void*> } },
    { "clGetPlatformInfo",     GetInfo,
                               { One<void*>    /* platform   */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetDeviceInfo",       GetInfo,
                               { One<void*>    /* device     */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetContextInfo",      GetInfo,
                               { One<void*>    /* context    */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetCommandQueueInfo", GetInfo,
                               { One<void*>    /* queue      */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetMemObjectInfo",    GetInfo,
                               { One<void*>    /* mem        */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetImageInfo",        GetInfo,
                               { One<void*>    /* image      */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetSamplerInfo",      GetInfo,
                               { One<void*>    /* sampler    */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetProgramInfo",      GetInfo,
                               { One<void*>    /* program    */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetKernelInfo",       GetInfo,
                               { One<void*>    /* kernel     */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },
    { "clGetEventInfo",        GetInfo,
                               { One<void*>    /* event      */,
                                 One<uint32_t> /* param_name */ },
                               ReturnInfo },

    // Nested info
    { "clGetProgramBuildInfo",    GetDependentInfo,
                                  { One<void*>    /* program    */,
                                    One<void*>    /* device     */,
                                    One<uint32_t> /* param_name */ },
                                  ReturnInfo },
    { "clGetKernelWorkGroupInfo", GetDependentInfo,
                                  { One<void*>    /* kernel     */,
                                    One<void*>    /* device     */,
                                    One<uint32_t> /* param_name */ },
                                  ReturnInfo },

    // Individual functions
    { "clGetPlatformIDs",           GetPlatformIDs, {},
                                    ReturnPointerArray },
    { "clGetDeviceIDs",             GetDeviceIDs,
                                    { One<void*>    /* platform    */,
                                      One<uint32_t> /* device_type */ },
                                    ReturnPointerArray },
    { "clCreateContext",            CreateContext,
                                    { NullTerminatedList /* properties */,
                                      Many<void*>        /* devices    */ },
                                    ReturnPointer, "clReleaseContext" },
    { "clCreateCommandQueue",       CreateCommandQueue,
                                    { One<void*>    /* context    */,
                                      One<void*>    /* device     */,
                                      One<uint32_t> /* properties */ },
                                    ReturnPointer, "clReleaseCommandQueue" },
    // TODO: segfault in libOpenCL.so { "clCreateContextFromType", { NullTerminatedList, One<uint32_t> }, CreateContextFromType, PointerReturner, 2},
    { "clCreateBuffer",             CreateBuffer,
                                    { One<void*>    /* context */,
                                      One<uint32_t> /* flags   */,
                                      One<size_t>   /* size    */ },
                                    ReturnPointer, "clReleaseMemObject" },
    { "clCreateSubBuffer",          CreateSubBuffer,
                                    { One<void*>    /* buffer             */,
                                      One<uint32_t> /* flags              */,
                                      One<uint32_t> /* buffer_create_type */,
                                      BufferRegion  /* buffer_create_info */ },
                                    ReturnPointer, "clReleaseMemObject" },
    { "clCreateImage2D",            CreateImage2D,
                                    { One<void*>    /* context      */,
                                      One<uint32_t> /* flags        */,
                                      ImageFormat   /* image_format */,
                                      One<size_t>   /* width        */,
                                      One<size_t>   /* height       */ },
                                    ReturnPointer, "clReleaseMemObject" },
    { "clCreateImage3D",            CreateImage3D,
                                    { One<void*>     /* context      */,
                                      One<uint32_t>  /* flags        */,
                                      ImageFormat    /* image_format */,
                                      One<size_t>    /* width        */,
                                      One<size_t>    /* height       */,
                                      One<size_t>    /* depth        */ },
                                    ReturnPointer, "clReleaseMemObject" },
    { "clGetSupportedImageFormats", GetSupportedImageFormats,
                                    { One<void*>     /* context    */,
                                      One<uint32_t>  /* flags      */,
                                      One<uint32_t>  /* image_type */ },
                                    ReturnImageFormatArray },
    { "clCreateSampler",            CreateSampler,
                                    { One<void*>    /* context           */,
                                      One<uint32_t> /* normalized_coords */,
                                      One<uint32_t> /* addressing_mode   */,
                                      One<uint32_t> /* filter_mode       */ },
                                    ReturnPointer, "clReleaseMemObject" },
    { "clCreateProgramWithSource",  CreateProgramWithSource,
                                    { One<void*> /* context */,
                                      CharArray  /* src     */ },
                                    ReturnPointer, "clReleaseProgram" },
    { "clBuildProgram",             BuildProgram,
                                    { One<void*>  /* program */,
                                      Many<void*> /* devices */,
                                      CharArray   /* options */ } },
    { "clCreateKernel",             CreateKernel,
                                    { One<void*>  /* program     */,
                                      CharArray   /* kernel_name */ },
                                    ReturnPointer, "clReleaseKernel" },
    { "clCreateKernelsInProgram",   CreateKernelsInProgram,
                                    { One<void*> /* program */ },
                                    ReturnPointerArray, "clReleaseKernel" },
    { "clSetKernelArg",             SetKernelArg,
                                    { One<void*>    /* kernel    */,
                                      One<uint32_t> /* arg_index */,
                                      One<size_t>   /* arg_size  */,
                                      TypedArray    /* arg_value */ } },
    { "clEnqueueReadBuffer",        EnqueueReadOrWriteBuffer,
                                    { One<void*>    /* queue  */,
                                      One<void*>    /* buffer */,
                                      One<uint32_t> /* offset */,
                                      TypedArray    /* ptr    */ },
                                    ReturnPointer, "clReleaseEvent" },
    { "clEnqueueWriteBuffer",       EnqueueReadOrWriteBuffer,
                                    { One<void*>    /* queue  */,
                                      One<void*>    /* buffer */,
                                      One<uint32_t> /* offset */,
                                      TypedArray    /* ptr    */ },
                                    ReturnPointer, "clReleaseEvent" },
    { "clEnqueueNDRangeKernel",     EnqueueNDRangeKernel,
                                    { One<void*>    /* queue  */,
                                      One<void*>    /* kernel */,
                                      Many<size_t>  /* global_work_offset */,
                                      Many<size_t>  /* global_work_size   */,
                                      Many<size_t> },
                                    ReturnPointer, "clReleaseEvent" },
    { "clSetEventCallback",         SetEventCallback,
                                    { Persist      /* event */,
                                      One<int32_t> /* command_exec_callback_type */,
                                      Persist      /* pfn_event_notify           */,
                                      Persist      /* user_data                  */ } },
    { NULL } // terminator listy
  };

  // Wrapper wrappers[] = {
  //   // One-arg void* functions
  //   { "clRetainContext", OneArgFn, { One<void*> } },
  //   { "clReleaseContext", OneArgFn, { One<void*> } },
  //   { "clRetainCommandQueue", OneArgFn, { One<void*> } },
  //   { "clReleaseCommandQueue", OneArgFn, { One<void*> } },
  //   { "clRetainMemObject", OneArgFn, { One<void*> } },
  //   { "clReleaseMemObject", OneArgFn, { One<void*> } },
  //   { "clRetainSampler", OneArgFn, { One<void*> } },
  //   { "clReleaseSampler", OneArgFn, { One<void*> } },
  //   { "clRetainProgram", OneArgFn, { One<void*> } },
  //   { "clReleaseProgram", OneArgFn, { One<void*> } },
  //   { "clRetainKernel", OneArgFn, { One<void*> } },
  //   { "clReleaseKernel", OneArgFn, { One<void*> } },
  //   { "clFlush", OneArgFn, { One<void*> } },
  //   { "clFinish", OneArgFn, { One<void*> } },

  //   // GetInfo functions
  //   { "clGetPlatformInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
  //   { "clGetDeviceInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
  //   { "clGetContextInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
  //   { "clGetCommandQueueInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
  //   { "clGetMemObjectInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo }, // TODO: always gives CL_INVALID_VALUE
  //   { "clGetImageInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
  //   // { "clGetSamplerInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo }, // TODO: the same as clGetMemObjectInfo
  //   { "clGetProgramInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
  //   { "clGetKernelInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },
  //   { "clGetEventInfo", GetInfo, { One<void*>, One<uint32_t> }, ReturnInfo },

  //   // Like GetInfo but requirng to objects to query
  //   { "clGetProgramBuildInfo", GetDependentInfo, { One<void*>, One<void*>, One<uint32_t> }, ReturnInfo },
  //   { "clGetKernelWorkGroupInfo", GetDependentInfo, { One<void*>, One<void*>, One<uint32_t> }, ReturnInfo },

  //   // Individual functions
  //   { "clGetPlatformIDs", GetPlatformIDs, {}, ReturnPointerArray },
  //   { "clGetDeviceIDs", GetDeviceIDs, { One<void*>, One<uint32_t> }, ReturnPointerArray },
  //   { "clCreateContext", CreateContext, { NullTerminatedList, Many<void*> }, ReturnPointer, "clReleaseContext" },
  //   { "clCreateCommandQueue", CreateCommandQueue, { One<void*>, One<void*>, One<uint32_t> }, ReturnPointer, "clReleaseCommandQueue" },
  //   // TODO: segfault in libOpenCL.so { "clCreateContextFromType", { NullTerminatedList, One<uint32_t> }, CreateContextFromType, PointerReturner, 2},
  //   { "clCreateBuffer", CreateBuffer, { One<void*>, One<uint32_t>, One<size_t> }, ReturnPointer, "clReleaseMemObject" },
  //   { "clCreateSubBuffer", CreateSubBuffer, { One<void*>, One<uint32_t>, One<uint32_t>, BufferRegion }, ReturnPointer, "clReleaseMemObject" },
  //   { "clCreateImage2D", CreateImage2D, { One<void*>, One<uint32_t>, ImageFormat, One<size_t>, One<size_t> }, ReturnPointer, "clReleaseMemObject" },
  //   { "clCreateImage3D", CreateImage3D, { One<void*>, One<uint32_t>, ImageFormat, One<size_t>, One<size_t>, One<size_t> }, ReturnPointer, "clReleaseMemObject" },
  //   { "clGetSupportedImageFormats", GetSupportedImageFormats, { One<void*>, One<uint32_t>, One<uint32_t> }, ReturnImageFormatArray },
  //   { "clCreateSampler", CreateSampler, { One<void*>, One<uint32_t>, One<uint32_t>, One<uint32_t> }, ReturnPointer, "clReleaseMemObject" },
  //   { "clCreateProgramWithSource", CreateProgramWithSource, { One<void*>, CharArray }, ReturnPointer, "clReleaseProgram" },
  //   { "clBuildProgram", BuildProgram, { One<void*>, Many<void*>, CharArray } },
  //   { "clCreateKernel", CreateKernel, { One<void*>, CharArray }, ReturnPointer, "clReleaseKernel" },
  //   { "clCreateKernelsInProgram", CreateKernelsInProgram, { One<void*> }, ReturnPointerArray, "clReleaseKernel" },
  //   { "clSetKernelArg", SetKernelArg, { One<void*>, One<uint32_t>, One<size_t>, TypedArray } },
  //   { "clEnqueueReadBuffer", EnqueueReadOrWriteBuffer, { One<void*>, One<void*>, One<uint32_t>, TypedArray }, ReturnPointer, "clReleaseEvent" },
  //   { "clEnqueueWriteBuffer", EnqueueReadOrWriteBuffer, { One<void*>, One<void*>, One<uint32_t>, TypedArray }, ReturnPointer, "clReleaseEvent" },
  //   { "clEnqueueNDRangeKernel", EnqueueNDRangeKernel, { One<void*>, One<void*>, Many<size_t>, Many<size_t>, Many<size_t> }, ReturnPointer, "clReleaseEvent" },
  //   { "clSetEventCallback", SetEventCallback, { One<void*>, One<int32_t>, Persist, Persist } },
  //   { NULL }
  // };

  int32_t (CALL *clGetEventInfo) (void*, uint32_t, size_t, void*, size_t*) = NULL;

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
      return scope.Close(ThrowException(Exception::Error(String::New("Wrapper missing."))));
    }
    if (!wrapper->f) {
      return scope.Close(ThrowException(Exception::Error(String::New("Function not implemented."))));
    }

    int length = args.Length();
    if (length < wrapper->minArgc) {
      return scope.Close(ThrowException(Exception::Error(String::New("Need more arguments."))));
    }

    Converter *converter = wrapper->converters;
    vector<void*> natives;
    for (int i = 0; (i < length) && *converter; ++i, ++converter) {
      (*converter)(wrapper, args[i], natives);
    }

    vector<void*> result;
    int32_t error = wrapper->action(wrapper, natives, result);

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
      jsResult = wrapper->returner(wrapper, natives, result);
    }

    DeleteAllItems(natives);
    DeleteAllItems(result);
    return scope.Close(jsResult);
  }

  void CollectGarbage (Persistent<Value> value, void* params) {
    cout << *(uint64_t*) params << " Collected Garbage\n";
    free(params);
    value.Dispose();
  }

  Handle<Value> TestGCInner(Handle<Value> old) {
    void *mem = malloc(8);
    cout << *(uint64_t*) mem << endl;
    Persistent<Value> handle = Persistent<Value>::New(External::New(mem));
    handle.MakeWeak(mem, CollectGarbage);
    return handle;
  }


  Handle<Value> TestGC (const Arguments& args) {
    HandleScope scope;
    Handle<Value> value = Undefined();
    value = TestGCInner(args[0]);
    return scope.Close(value);
  }



  void SetWebCL(Handle<Object> target, EventSupport events) {
    SetConstants(target);

    Handle<Array> loadingErrors = Array::New();
    target->Set(String::New("loadingErrors"), loadingErrors);

    const char *error = NULL;
    error = dlerror(); // clear any previous errors
    void *opencl = dlopen(V8CL_OPENCL_LIB, RTLD_LAZY | RTLD_LOCAL);
    error = dlerror();
    if (error) {
      loadingErrors->Set(0, String::New(error));
      return;
    }

    uint32_t errorIdx = 0;
    char firstLetter[2] = " ";

    // tmp
    *(void**) &clGetEventInfo = dlsym(opencl, "clGetEventInfo");
    error = dlerror();
    if (error) {
      loadingErrors->Set(errorIdx++, String::New(error));
    }
    // tmpend

    /// testing
    Handle<FunctionTemplate> gctpl = FunctionTemplate::New(TestGC);
    target->Set(String::New("testgc"), gctpl->GetFunction());
    /// end testing

    Persistent<ObjectTemplate> objectTemplate = Persistent<ObjectTemplate>::New(ObjectTemplate::New());
    objectTemplate->SetInternalFieldCount(1);

    for (Wrapper *wrapper = wrappers; wrapper->name; ++wrapper) {
      wrapper->objectTemplate = objectTemplate;
      wrapper->f = dlsym(opencl, wrapper->name);
      wrapper->events = events;
      error = dlerror();
      if (error) {
        wrapper->f = NULL;
        loadingErrors->Set(errorIdx++, String::New(error));
      }

      if (wrapper->releaseFunctionName) {
        wrapper->releaseFunction = dlsym(opencl, wrapper->releaseFunctionName);
        error = dlerror();
        if (error) {
          wrapper->releaseFunction = NULL;
          loadingErrors->Set(errorIdx++, String::New(error));
        }
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
