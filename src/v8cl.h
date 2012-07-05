#ifndef _V8CL_H
#define _V8CL_H

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <map>

#include <v8.h>

#ifdef _WIN32
#define CALL __stdcall
#else
#define CALL
#endif

#define V8CL_MAX_CONVERTERS 10

namespace v8cl {
  using namespace v8;
  using namespace std;

  struct EventHandler;
  struct Wrapper;

  typedef void (*Converter) (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);
  typedef int32_t (*Action) (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  typedef Handle<Value> (*Returner) (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);

  /**
    Event Support consists of two functions.

    `add` sets up event to be invoked later and associates it with
    given EventHandler. Returns native implementation-specific
    pointer. This pointer is given to `shake` function when event
    occurs.

    `shake` needs to queue the event in event loop. It's
    responsibility is to cause invokation of
    InvokeBackInEventLoop(EventHandler*) _inside_ the event loop and
    clean up any implementation specific state (at any time after the
    event).

    `shake` is possibly invoked in auxiliary thread so it needs to be
    thread-safe.
  */
  struct EventSupport {
    void* (*add) (EventHandler* handler);
    void (*shake) (void* their_handle);
  };

  struct EventHandler {
    EventSupport events;
    Persistent<Value> f;
    Persistent<Value> data;
    Persistent<Value> event;

    int32_t type;
    void* impl_handle;
  };

  struct Wrapper {
    const char *name;
    Action action;
    Converter converters[V8CL_MAX_CONVERTERS];
    Returner returner;
    const char *releaseFunctionName;
    int minArgc;
    void *f;
    Persistent<ObjectTemplate> objectTemplate;
    void *releaseFunction;
    EventSupport events;
  };

  Handle<Value> InvokeWrapper (const Arguments& args);
  void InvokeBackInEventLoop (EventHandler* handler);

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

  // Converters
  template<typename T>
  void One (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);
  template<typename T>
  void Many (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);

  void NullTerminatedList (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);
  void BufferRegion (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);
  void ImageFormat (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);
  void CharArray (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);
  void TypedArray (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);
  void TypedArray (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);
  void Persist (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives);

  // Exposed Returners
  Handle<Value> ReturnPointerArray (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnImageFormatArray (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnNullTerminatedListAsIntegerArray (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnPointer (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnString (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);
  Handle<Value> ReturnInfo (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);

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

  template<typename T>
  T Get (Handle<Value> value);

  // Global state
  extern Wrapper wrappers[];

  // tmp
  void PrintBinaryData(void* data, size_t size);
}

#endif
