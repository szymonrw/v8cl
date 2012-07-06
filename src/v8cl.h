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

  // Constants
  struct StrToInt { const char *name; int value; };
  void SetConstants(Handle<Object> target, const StrToInt* list);
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
