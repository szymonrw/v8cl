#ifdef _WITH_NODE
#include <node.h>
#include <node_buffer.h>
#include <node_version.h>
#endif

#include "v8cl.h"

namespace v8cl {

  void PrintBinaryData(void* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
      cout << (uint32_t) ((uint8_t*) data)[i] << " | ";
    }
    cout << endl;
  }

  template<typename T>
  T Get (Handle<Value> value);

  template<>
  void* Get<void*> (Handle<Value> value) {
    return External::Unwrap(value);
  }

  template<>
  uint32_t Get<uint32_t> (Handle<Value> value) {
    return value->Uint32Value();
  }

  template<>
  int32_t Get<int32_t> (Handle<Value> value) {
    return value->Int32Value();
  }


  template<>
  size_t Get<size_t> (Handle<Value> value) {
    return value->IntegerValue();
  }

  template<typename T>
  void One (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
    T native = Get<T>(value);
    PushBackWrapped(natives, native);
  }

  // void PointerArray (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
  //   if (!value->IsArray()) {
  //     natives.push_back(NULL);
  //     // set size = 0;
  //     PushBackWrapped(natives, 0);
  //     return;
  //   }
    
  //   Handle<Array> array = Handle<Array>::Cast<Value>(value);
  //   const size_t size = array->Length();
  //   void **nativeArray = (void**) malloc(sizeof(void*) * size);
    
  //   for (size_t i = 0; i < size; ++i) {
  //     nativeArray[i] = External::Unwrap(array->Get(i));
  //   }

  //   natives.push_back(nativeArray);
  //   PushBackWrapped(natives, size);
  // }

  template<typename T>
  void Many (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
    if (!value->IsArray()) {
      natives.push_back(NULL);
      // set size = 0;
      PushBackWrapped<size_t>(natives, 0);
      return;
    }
    
    Handle<Array> array = Handle<Array>::Cast<Value>(value);
    const size_t size = array->Length();
    T *nativeArray = (T*) malloc(sizeof(T) * size);
    
    for (size_t i = 0; i < size; ++i) {
      nativeArray[i] = Get<T>(array->Get(i));
    }

    natives.push_back(nativeArray);
    PushBackWrapped(natives, size);
  }
  

  // Forces generation of templates for types used.
  void _force_templates () {
    vector<void*> tmp;
    One<void*>(NULL, String::New(""), tmp);
    One<uint32_t>(NULL, String::New(""), tmp);
    One<int32_t>(NULL, String::New(""), tmp);
    One<size_t>(NULL, String::New(""), tmp);

    Many<void*>(NULL, String::New(""), tmp);
    Many<uint32_t>(NULL, String::New(""), tmp);
    Many<int32_t>(NULL, String::New(""), tmp);
    Many<size_t>(NULL, String::New(""), tmp);
  }

  void NullTerminatedList (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
    if (!value->IsArray()) {
      natives.push_back(NULL);
      return;
    }
    Handle<Array> array = Handle<Array>::Cast<Value>(value);
    const size_t size = array->Length() + 1;
    intptr_t *nativeArray = (intptr_t*) malloc(sizeof(intptr_t) * size);

    for (size_t i = 0; i < size - 1; ++i) {
      nativeArray[i] = array->Get(i)->IntegerValue();
    }
    nativeArray[size - 1] = 0;

    natives.push_back(nativeArray);
  }

  void BufferRegion (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
    Handle<Object> object = Handle<Object>::Cast<Value>(value);
    cl_buffer_region *region = (cl_buffer_region*) malloc(sizeof(cl_buffer_region));
    region->origin = object->Get(String::New("origin"))->IntegerValue();
    region->size = object->Get(String::New("size"))->IntegerValue();
    natives.push_back(region);
  }

  void ImageFormat (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
    Handle<Object> object = Handle<Object>::Cast<Value>(value);
    cl_image_format *format = (cl_image_format*) malloc(sizeof(cl_image_format));
    format->image_channel_order = object->Get(String::New("image_channel_order"))->Uint32Value();
    format->image_channel_data_type = object->Get(String::New("image_channel_data_type"))->Uint32Value();
    natives.push_back(format);
  }

  void CharArray (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
    Handle<String> str = Handle<String>::Cast<Value>(value);
    size_t size = str->Utf8Length() + 1;
    char* chars = (char*) malloc(size);
    str->WriteUtf8(chars, size);
    natives.push_back(chars);
    PushBackWrapped(natives, size);
  }

  void TypedArray (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
    uint8_t *buff = NULL;
    size_t byteOffset = 0;
    size_t byteLength = 0;
    
    if (value->IsObject()) {
      Handle<Object> obj = Handle<Object>::Cast<Value>(value);

      // ArrayBuffer or other typed array.
      byteOffset = obj->Get(String::New("byteOffset"))->Uint32Value();
      byteLength = obj->Get(String::New("byteLength"))->Uint32Value();
      // This will work only if obj is ArrayBuffer. 
      buff = (uint8_t*) External::Unwrap(obj->GetInternalField(0));

      // If it's other typed array, value is kept in "buffer" field.
      if (!buff) {
        buff = (uint8_t*) External::Unwrap(Handle<Object>::Cast<Value>(
          obj->Get(String::New("buffer")))->GetInternalField(0));
        #ifdef _WITH_NODE
        if (!buff) {
          byteLength = node::Buffer::Length(obj);  
          buff = (uint8_t*) node::Buffer::Data(obj);
          byteOffset = 0;
        }
        #endif
      }
    } else {
      buff = (uint8_t*) External::Unwrap(value);
    }
    
    PushBackWrapped(natives, buff + byteOffset);
    PushBackWrapped(natives, byteLength);
  }
  
  void Persist (const Wrapper* wrapper, Handle<Value> value, vector<void*>& natives) {
    Persistent<Value> *persisted = (Persistent<Value>*) malloc(sizeof(Persistent<Value>));
    *persisted = Persistent<Value>::New(value);
    natives.push_back(persisted);
  }
}
