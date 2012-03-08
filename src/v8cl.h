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

  struct EventHandler;
  struct Wrapper;

  typedef void (*Converter) (Handle<Value> value, vector<void*>& natives);
  typedef int32_t (*Action) (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  typedef Handle<Value> (*Returner) (vector<void*>& natives, vector<void*>& result);

  // Stuff needed to be implemented to support events
  struct EventSupport {
    void* (*add) (EventHandler* handler);
    void (*shake) (void* their_handle);
    //void (*remove) (EventHandler* handler);
  };
  //typedef void (*EventLoopShaker) (EventHandler* handler);

  struct Wrapper {
    const char *name;
    Action action;
    Converter converters[20];
    Returner returner;
    int minArgc;
    void *f;
    EventSupport events;
  };

  struct EventHandler {
    EventSupport events;
    Persistent<Value> f;
    Persistent<Value> data;
    void* event;
    int32_t type;
    void* impl_handle;
  };

    
  // Functions
  int32_t OneArgFn (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t GetInfo (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t GetDependentInfo (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t GetPlatformIDs (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t GetDeviceIDs (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateContext (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateContextFromType (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateCommandQueue (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateBuffer (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateSubBuffer (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateImage2D (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateImage3D (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t GetSupportedImageFormats (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateSampler (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateProgramWithSource (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t BuildProgram (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateKernel (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t CreateKernelsInProgram (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t SetKernelArg (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t EnqueueReadOrWriteBuffer (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t EnqueueNDRangeKernel (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  int32_t SetEventCallback (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  void InvokeBackInEventLoop (EventHandler* handler);
  
  // Converters
  template<typename T>
  void One (Handle<Value> value, vector<void*>& natives);
  template<typename T>
  void Many (Handle<Value> value, vector<void*>& natives);

  void NullTerminatedList (Handle<Value> value, vector<void*>& natives);
  void BufferRegion (Handle<Value> value, vector<void*>& natives);
  void ImageFormat (Handle<Value> value, vector<void*>& natives);
  void CharArray (Handle<Value> value, vector<void*>& natives);
  void TypedArray (Handle<Value> value, vector<void*>& natives);
  void TypedArray (Handle<Value> value, vector<void*>& natives);
  void Persist (Handle<Value> value, vector<void*>& natives);

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
  void SetWebCL(Handle<Object> target, EventSupport events);

  // Native CL structs
  struct cl_buffer_region {
    size_t origin;
    size_t size;
  };

  struct cl_image_format {
    uint32_t image_channel_order;
    uint32_t image_channel_data_type;
  };

  typedef void (*pfn_notify) (void*, int32_t, void*);

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
