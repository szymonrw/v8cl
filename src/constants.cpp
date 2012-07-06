#include "v8cl.h"
#include "constants.h"

namespace v8cl {

  void SetConstant (const StrToInt* constant, Handle<Object> target) {
    target->Set(String::New(constant->name), Integer::New(constant->value));
  }

  void SetConstants (Handle<Object> target, const StrToInt* list) {
    do {
      SetConstant(list, target);
    } while ((++list)->name);
  }

  map<int, const char*> GetErrorCodes() {
    map<int, const char*> result;

    const StrToInt* errorCode = ERROR_CODES;
    do {
      result[errorCode->value] = errorCode->name;
    } while ((++errorCode)->name);

    return result;
  }
}
