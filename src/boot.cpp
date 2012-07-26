#include "v8cl.h"
#include "constants.h"
#include "dynamic_opencl.h"
#include <iostream>

namespace v8cl {

  Handle<String> ConvertName (const char* name) {
    char firstLetter[2] = " ";
    // Convert first letter after "cl" to lowercase
    firstLetter[0] = name[2] - ('A' - 'a');
    return String::Concat(String::New(firstLetter),
                          String::New(name + 3));
  }

  Handle<Function> CreateJSFunction (Wrapper* wrapper) {
    Handle<External> data = External::New(wrapper);
    Handle<FunctionTemplate> ftpl = FunctionTemplate::New(InvokeWrapper, data);
    return ftpl->GetFunction();
  }

  void PushToArray (Handle<Array> array, Handle<Value> value) {
    array->Set(array->Length(), value);
  }

  bool EnsureCorrectMinArgc (Wrapper* wrapper, Handle<Array> loadingErrors) {
    // Count converters
    Converter *converter = wrapper->converters;
    int argc = 0;
    while (*(converter++)) ++argc;

    if (wrapper->minArgc == 0) {
      wrapper->minArgc = argc;
    } else if (argc < wrapper->minArgc) {
      PushToArray(loadingErrors,
        String::Concat(String::New("Function "),
        String::Concat(String::New(wrapper->name),
        String::Concat(String::New(" requires at least "),
        String::Concat(Int32::New(wrapper->minArgc)->ToString(),
                       String::New(" converters."))))));
      return false;
    }
    return true;
  }

  bool CheckDlsymError (Handle<Array> loadingErrors) {
    const char *error = dlerror();
    if (error) {
      PushToArray(loadingErrors, String::New(error));
      return false;
    }
    return true;
  }

  void* LoadOpenCL (Handle<Array> loadingErrors) {
    void *opencl = dlopen(V8CL_OPENCL_LIB, RTLD_LAZY | RTLD_LOCAL);
    if (CheckDlsymError(loadingErrors)) {
      return opencl;
    } else {
      return NULL;
    }
  }

  void* LoadFunctionFromLib (void* lib,
                             const char* name,
                             Handle<Array> loadingErrors) {
    void *f = dlsym(lib, name);
    if (CheckDlsymError(loadingErrors)) {
      return f;
    } else {
      return NULL;
    }
  }

  void SetWebCL(Handle<Object> target, EventSupport events) {
    SetConstants(target, CONSTANTS);
    SetConstants(target, ERROR_CODES);

    // Setup array to hold non-critical load errors
    Handle<Array> loadingErrors = Array::New();
    target->Set(String::New("loadingErrors"), loadingErrors);

    void* opencl = LoadOpenCL(loadingErrors);
    if (!opencl) {
      // No opencl, no sense in continuing
      return;
    }

    // Setup object template for returners that wrap native OpenCL objects.
    Persistent<ObjectTemplate> objectTemplate =
      Persistent<ObjectTemplate>::New(ObjectTemplate::New());
    objectTemplate->SetInternalFieldCount(1);

    for (Wrapper *wrapper = wrappers; wrapper->name; ++wrapper) {
      // Omit wrappers without action defined.
      if (!wrapper->action) {
        continue;
      }

      wrapper->f = LoadFunctionFromLib(opencl, wrapper->name, loadingErrors);
      if (!wrapper->f) {
        continue;
      }

      // Load function that will decrease returned object's reference count
      if (wrapper->releaseFunctionName) {
        wrapper->releaseFunction =
          LoadFunctionFromLib(opencl, wrapper->releaseFunctionName, loadingErrors);
        if (!wrapper->releaseFunction) {
          wrapper->f = NULL;
          continue;
        }
      }

      if (!EnsureCorrectMinArgc(wrapper, loadingErrors)) {
        wrapper->f = NULL;
        continue;
      }

      wrapper->objectTemplate = objectTemplate;
      wrapper->events = events;

      target->Set(ConvertName(wrapper->name), CreateJSFunction(wrapper));
    }
  }
}
