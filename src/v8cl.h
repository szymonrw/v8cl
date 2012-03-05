#ifndef _V8CL_H
#define _V8CL_H

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <map>

#include <v8.h>

namespace v8cl {
  using namespace v8;
  using namespace std;

  typedef void (*Converter) (Handle<Value> value, vector<void*>& natives);
  typedef int32_t (*Action) (void *f, vector<void*>& natives, vector<void*>& result);
  typedef Handle<Value> (*Returner) (vector<void*>& natives, vector<void*>& result);
  
  struct Wrapper {
    const char *name;
    Action action;
    Converter converters[20];
    Returner returner;
    int minArgc;
    void *f;
  };
  
  // Functions
  int32_t OneArgFn (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t GetInfo (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t GetDependentInfo (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t GetPlatformIDs (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t GetDeviceIDs (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateContext (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateContextFromType (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateCommandQueue (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateBuffer (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateSubBuffer (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateImage2D (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateImage3D (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t GetSupportedImageFormats (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateSampler (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateProgramWithSource (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t BuildProgram (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateKernel (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t CreateKernelsInProgram (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t SetKernelArg (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t EnqueueReadOrWriteBuffer (void *f, vector<void*>& natives, vector<void*>& result);
  int32_t EnqueueNDRangeKernel (void *f, vector<void*>& natives, vector<void*>& result);
  
  // Converters
  template<typename T>
  void One (Handle<Value> value, vector<void*>& natives);
  template<typename T>
  void Many (Handle<Value> value, vector<void*>& natives);

  void NullTerminatedList (Handle<Value> value, vector<void*>& natives);
  void BufferRegion (Handle<Value> value, vector<void*>& natives);
  void ImageFormat (Handle<Value> value, vector<void*>& native);
  void CharArray (Handle<Value> value, vector<void*>& natives);
  void TypedArray (Handle<Value> value, vector<void*>& natives);
  void TypedArray (Handle<Value> value, vector<void*>& natives);

  // Exposed Returners
  Handle<Value> ReturnPointerArray (vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnImageFormatArray (vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnNullTerminatedListAsIntegerArray (vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnPointer (vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnString (vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnInfo (vector<void*>& natives, vector<void*>& result);

  // Constants
  void SetConstants(Handle<Object> target);
  map<int, const char*> GetErrorCodes();

  // Put whole WebCL api on target obejct using this function
  void SetWebCL(Handle<Object> target);

  // Native CL structs
  struct cl_buffer_region {
    size_t origin;
    size_t size;
  };

  struct cl_image_format {
    uint32_t image_channel_order;
    uint32_t image_channel_data_type;
  };

  // templates

  template<typename T>
  void PushBackWrapped(vector<void*>& result, T value) {
    T *ptr = (T*) malloc(sizeof(T));
    *ptr = value;
    result.push_back(ptr);
  }

  // tmp
  void PrintBinaryData(void* data, size_t size);

}

#endif
