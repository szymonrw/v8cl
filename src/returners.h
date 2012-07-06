#ifndef __RETURNERS_H
#define __RETURNERS_H

#define R(NAME) \
  Handle<Value> NAME (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result)

namespace v8cl {
  R(ReturnPointerArray);
  R(ReturnImageFormatArray);
  R(ReturnNullTerminatedListAsIntegerArray);
  R(ReturnPointer);
  R(ReturnString);
  R(ReturnInfo);
}

#endif
