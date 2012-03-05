#include "v8cl.h"
#include "constants.h"

namespace v8cl {
   
  void SetConstants(Handle<Object> target) {
    size_t errors_size = sizeof(ERROR_CODES) / sizeof(ERROR_CODES[0]);
    size_t consts_size = sizeof(CONSTANTS) / sizeof(CONSTANTS[0]);
    
    for (size_t i = 0; i < errors_size; ++i) {
      target->Set(String::New(ERROR_CODES[i].name), Integer::New(ERROR_CODES[i].value));
    }
    for (size_t i = 0; i < consts_size; ++i) {
      target->Set(String::New(CONSTANTS[i].name), Integer::New(CONSTANTS[i].value));
    }
  }

  map<int, const char*> GetErrorCodes() {
    size_t size = sizeof(ERROR_CODES) / sizeof(ERROR_CODES[0]);
    map<int, const char*> result;
    for (size_t i = 0; i < size; ++i) {
      result[ERROR_CODES[i].value] = ERROR_CODES[i].name;
    }
    return result;
  }
}
