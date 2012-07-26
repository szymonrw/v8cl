#include "v8cl.h"

#define V8CL_ERROR_WRAPPER_MISSING          "Wrapper missing."
#define V8CL_ERROR_FUNCTION_NOT_IMPLEMENTED "Function not implemented."
#define V8CL_ERROR_NEED_MORE_ARGUMENTS      "Need more arguments, in total:"
#define V8CL_ERROR_UNKNOWN_OPENCL_ERROR     "Unknown WebCL error code:"

#define V8CL_INVOCATION_ARGS (Wrapper*& wrapper,       \
                              const Arguments& args,   \
                              vector<void*>& natives,  \
                              vector<void*>& result,   \
                              Handle<Value>& jsResult, \
                              int32_t& errorNumber)

namespace v8cl {
  map<int, const char*> errorCodes = GetErrorCodes();

  void DeleteAllItems(vector<void*>& data) {
    for(vector<void*>::iterator it = data.begin(), end = data.end();
        it < end; ++it) {
      if (*it) free(*it);
    }
  }

  const char* CheckWrapper V8CL_INVOCATION_ARGS {
    if (!wrapper) {
      return V8CL_ERROR_WRAPPER_MISSING;
    }
    if (!wrapper->f || !wrapper->action) {
      return V8CL_ERROR_FUNCTION_NOT_IMPLEMENTED;
    }
    return NULL;
  }

  const char* ConvertArguments V8CL_INVOCATION_ARGS {
    int length = args.Length();
    if (length < wrapper->minArgc) {
      errorNumber = wrapper->minArgc;
      return V8CL_ERROR_NEED_MORE_ARGUMENTS;
    }

    // Invoke converters for given arguments
    Converter *converter = wrapper->converters;
    for (int i = 0;
         *converter && (i < length) && (i < V8CL_MAX_CONVERTERS);
         ++i, ++converter) {
      (*converter)(wrapper, args[i], natives);
    }
    return NULL;
  }

  const char* InvokeAction V8CL_INVOCATION_ARGS {
    int32_t error = wrapper->action(wrapper, natives, result);
    if (error) {
      // Show name of error instead of number if it's of known name
      if (errorCodes.count(error)) {
        return errorCodes[error];
      } else {
        errorNumber = error;
        return V8CL_ERROR_UNKNOWN_OPENCL_ERROR;
      }
    }
    return NULL;
  }

  const char* ConvertResult V8CL_INVOCATION_ARGS {
    if (wrapper->returner) {
      jsResult = wrapper->returner(wrapper, natives, result);
    }
    return NULL;
  }

  typedef const char* (*InvocationStep) V8CL_INVOCATION_ARGS;

  InvocationStep invocationSteps[] = {
    CheckWrapper,
    ConvertArguments,
    InvokeAction,
    ConvertResult,
    NULL
  };

  Handle<Value> InvokeWrapper (const Arguments& args) {
    HandleScope scope;

    Handle<Value> jsResult = Undefined();
    vector<void*> natives;
    vector<void*> result;
    const char* error;
    int32_t errorNumber = 0;
    Wrapper *wrapper = (Wrapper*) External::Unwrap(args.Data());

    for (InvocationStep *step = invocationSteps;
         *step;
         ++step) {
      error = (*step)(wrapper, args, natives, result, jsResult, errorNumber);

      if (error) {
        Handle<String> message = String::New(error);
        if (errorNumber) {
          message = String::Concat(
            message,
            String::Concat(String::New(" "),
                           Integer::New(errorNumber)->ToString()));
        }
        jsResult = ThrowException(Exception::Error(message));
        break;
      }
    }

    DeleteAllItems(natives);
    DeleteAllItems(result);
    return scope.Close(jsResult);
  }
}
