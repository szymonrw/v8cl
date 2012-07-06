#ifndef __CONVERTERS_H
#define __CONVERTERS_H

#define C(NAME) \
  void NAME (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives)

namespace v8cl {
  template<typename T>
    C(One);
  template<typename T>
    C(Many);
  C(NullTerminatedList);
  C(BufferRegion);
  C(ImageFormat);
  C(CharArray);
  C(TypedArray);
  C(TypedArray);
  C(Persist);
}

#endif
