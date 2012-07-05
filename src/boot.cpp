#include "v8cl.h"
#include "constants.h"
#include "dynamic_opencl.h"
#include <iostream>

namespace v8cl {

  // Handle<Value> InvokeWrapper_OLD (const Arguments& args) {
  //   HandleScope scope;

  //   Handle<Value> jsResult = Undefined();
  //   vector<void*> natives;
  //   vector<void*> result;
  //   int32_t error = 0;

  //   // Unwrap wrapper hold in data field of args
  //   Wrapper *wrapper = (Wrapper*) External::Unwrap(args.Data());

  //   if (!wrapper) {
  //     error = 1;
  //     jsResult = ThrowException(Exception::Error(String::New("Wrapper missing.")));
  //   }
  //   if (!wrapper->f) {
  //     error = 1;
  //     jsResult = ThrowException(Exception::Error(String::New("Function not implemented.")));
  //   }

  //   // Check if all mandatory arguments are passed
  //   int length = args.Length();
  //   if (length < wrapper->minArgc) {
  //     return scope.Close(ThrowException(Exception::Error(String::New("Need more arguments."))));
  //   }

  //   // Invoke converters for given arguments
  //   Converter *converter = wrapper->converters;
  //   for (int i = 0;
  //        (i < length) && *converter && (i < V8CL_MAX_CONVERTERS);
  //        ++i, ++converter) {
  //     (*converter)(wrapper, args[i], natives);
  //   }

  //   // Invoke action, which will invoke native OpenCL function
  //   error = wrapper->action(wrapper, natives, result);

  //   // Check for error and throw an exception if occured
  //   if (error) {
  //     // Delete all converted values and any elements in 'result'
  //     DeleteAllItems(natives);
  //     DeleteAllItems(result);

  //     // Show name of error instead of number if it's of known name
  //     if (errorCodes.count(error)) {
  //       return scope.Close(ThrowException(Exception::Error(String::New(errorCodes[error]))));
  //     } else {
  //       return scope.Close(ThrowException(Exception::Error(String::Concat(String::New("Unknown WebCL error code: "), Integer::New(error)->ToString()))));
  //     }
  //   }

  //   if (wrapper->returner) {
  //     jsResult = wrapper->returner(wrapper, natives, result);
  //   }

  //   DeleteAllItems(natives);
  //   DeleteAllItems(result);
  //   return scope.Close(jsResult);
  // }

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
      } else {
        // TODO: check if amount of converters and minArgc are consistent
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
