#include "v8cl.h"
#include "constants.h"

namespace v8cl {

  // Decrease reference count
  void DisposeOpenCLObject (Persistent<Value> value, void* f) {
    cout << "Dispose CL " << (uintptr_t) f ;
    if (f && value->IsObject()) {
      Local<Object> object = value->ToObject();
      if (object->InternalFieldCount()) {
        int32_t (*release) (void* smth);
        *(void**) &release = f;
        void *ptr = object->GetPointerFromInternalField(0);
        cout << " " << (uintptr_t) ptr;
        int32_t error = release(ptr);
        if (!error) {
          cout << " SUCCESS";
        } else {
          cout << " ERROR " << error;
        }
      }
    }
    value.Dispose();
    value.Clear();
    cout << endl;
  }

  Handle<Value> WrapPointer (Persistent<ObjectTemplate> tpl, void* ptr, void* retainer = NULL) {
    // Persistent<Value> p = Persistent<Value>::New(External::New(ptr));
    Persistent<Object> p = Persistent<Object>::New(tpl->NewInstance());
    p->SetPointerInInternalField(0, ptr);
    cout << "PTROUT " << (uintptr_t) ptr << endl;
    p.MakeWeak(retainer, DisposeOpenCLObject);
    return p;
  }

  Handle<Value> ReturnPointerArray (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    Local<Array> array = Array::New();
    
    void **nativeArray = (void**) result[0];
    size_t size = 0;
    if (result.size() > 1) size = *(size_t*) result[1] / sizeof(void*);

    for (size_t i = 0; i < size; ++i) {
      // Local<Value> ptr = ;
      // Persistent<Value> p = Persistent<Value>::New(External::New(nativeArray[i]));
      // p.MakeWeak(NULL, IamWeak);
      array->Set(i, WrapPointer(wrapper->objectTemplate, nativeArray[i], wrapper->releaseFunction));
    }

    return array;
  }

  Handle<Value> ReturnPointer (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    // void *ptr = *(void**) result[0];
    // Persistent<Value> p = Persistent<Value>::New(External::New(ptr));
    // p.MakeWeak(NULL, IamWeak);

    cout << wrapper->name << ' ';
    return WrapPointer(wrapper->objectTemplate, *(void**) result[0], wrapper->releaseFunction);
  }


  Handle<Value> ReturnBinaryArray (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    Handle<Array> array = Array::New();
    size_t *sizes = (size_t*) result[0];
    size_t num_binaries = *(size_t*) result[1];

    for (size_t i = 0; i < num_binaries; ++i) {
      array->Set(i, String::New((char*) result[i + 2], sizes[i]));
    }

    return array;
  }

  Handle<Value> ReturnImageFormatArray (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    Handle<Array> array = Array::New();

    cl_image_format *formats = (cl_image_format*) result[0];
    uint32_t size = 0;
    if (result.size() > 1) size = *(uint32_t*) result[1]; 

    for (uint32_t i = 0; i < size; ++i) {
      Handle<Object> obj = Object::New();
      obj->Set(String::New("image_channel_order"), Uint32::New(formats[i].image_channel_order));
      obj->Set(String::New("image_channel_data_type"), Uint32::New(formats[i].image_channel_data_type));
      array->Set(i, obj);
    }

    return array;
  }

  Handle<Value> ReturnImageFormat (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    cl_image_format *format = (cl_image_format*) result[0];
    
    Handle<Object> obj = Object::New();
    obj->Set(String::New("image_channel_order"), Uint32::New(format->image_channel_order));
    obj->Set(String::New("image_channel_data_type"), Uint32::New(format->image_channel_data_type));
  
    return obj;
  }

  Handle<Value> ReturnNullTerminatedListAsIntegerArray (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    intptr_t *nativeArray = (intptr_t*) result[0];
    if (!nativeArray) {
      return Null();
    }
    
    Handle<Array> array = Array::New();
    
    size_t size = 0;
    if (result.size() > 1) size = *(size_t*) result[1] / sizeof(intptr_t*) - 1;

    for (size_t i = 0; i < size; ++i) {
      // TODO: loss of precision?
      array->Set(i, Integer::New(nativeArray[i]));
    }
    
    return array;
  }

  Handle<Value> ReturnString (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    char *ptr = (char*) result[0];
    return String::New(ptr);
  }

  template<typename JSType, typename NativeType>
  Handle<Value> ReturnValue (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    NativeType value = *(NativeType*) result[0];
    return JSType::New(value);
  }
  
  template<typename JSType, typename NativeType>
  Handle<Value> ReturnArray (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    Handle<Array> array = Array::New();
    
    NativeType *nativeArray = (NativeType*) result[0];
    size_t size = 0;
    if (result.size() > 1) size = (*(size_t*) result[1]) / sizeof(NativeType);

    for (size_t i = 0; i < size; ++i) {
      array->Set(i, JSType::New(nativeArray[i]));
    }

    return array;
  }

  Handle<Value> ReturnInfo (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    uint32_t name = *(uint32_t*) natives.back();
    Returner returner = ReturnValue<Uint32, uint32_t>;
    switch (name) {
    case CL_PLATFORM_PROFILE:
    case CL_PLATFORM_VERSION:
    case CL_PLATFORM_NAME:
    case CL_PLATFORM_VENDOR:
    case CL_PLATFORM_EXTENSIONS:
    case CL_DEVICE_NAME:
    case CL_DEVICE_VENDOR:
    case CL_DRIVER_VERSION:
    case CL_DEVICE_PROFILE:
    case CL_DEVICE_VERSION:
    case CL_DEVICE_OPENCL_C_VERSION:
    case CL_DEVICE_EXTENSIONS:
    case CL_PROGRAM_SOURCE:
    case CL_PROGRAM_BUILD_OPTIONS:
    case CL_PROGRAM_BUILD_LOG:
    case CL_KERNEL_FUNCTION_NAME:
      returner = ReturnString;
      break;
    case CL_DEVICE_MAX_WORK_ITEM_SIZES:
    case CL_PROGRAM_BINARY_SIZES:
    case CL_KERNEL_COMPILE_WORK_GROUP_SIZE:
      returner = ReturnArray<Number, size_t>;
      break;
    case CL_DEVICE_MAX_WORK_GROUP_SIZE:
    case CL_DEVICE_IMAGE2D_MAX_WIDTH:
    case CL_DEVICE_IMAGE2D_MAX_HEIGHT:
    case CL_DEVICE_IMAGE3D_MAX_WIDTH:
    case CL_DEVICE_IMAGE3D_MAX_HEIGHT:
    case CL_DEVICE_IMAGE3D_MAX_DEPTH:
    case CL_DEVICE_MAX_PARAMETER_SIZE:
    case CL_DEVICE_PROFILING_TIMER_RESOLUTION:
    case CL_MEM_SIZE:
    case CL_MEM_OFFSET:
    case CL_IMAGE_ELEMENT_SIZE: 
    case CL_IMAGE_ROW_PITCH: 
    case CL_IMAGE_SLICE_PITCH:
    case CL_IMAGE_WIDTH: 
    case CL_IMAGE_HEIGHT:
    case CL_IMAGE_DEPTH:
    case CL_KERNEL_WORK_GROUP_SIZE:
    case CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE:
      returner = ReturnValue<Number, size_t>;
      break;
    case CL_DEVICE_MAX_MEM_ALLOC_SIZE:
    case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:
    case CL_DEVICE_GLOBAL_MEM_SIZE:
    case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:
    case CL_DEVICE_LOCAL_MEM_SIZE:
    case CL_KERNEL_LOCAL_MEM_SIZE:
    case CL_KERNEL_PRIVATE_MEM_SIZE:
      returner = ReturnValue<Number, uint64_t>;
      break;
    case CL_DEVICE_IMAGE_SUPPORT:
    case CL_DEVICE_ERROR_CORRECTION_SUPPORT:
    case CL_DEVICE_HOST_UNIFIED_MEMORY:
    case CL_DEVICE_ENDIAN_LITTLE:
    case CL_DEVICE_AVAILABLE:
    case CL_DEVICE_COMPILER_AVAILABLE:
    case CL_SAMPLER_NORMALIZED_COORDS:
      returner = ReturnValue<Boolean, uint32_t>;
      break;
    case CL_DEVICE_PLATFORM:
    case CL_QUEUE_CONTEXT:
    case CL_QUEUE_DEVICE:
    case CL_MEM_HOST_PTR:
    case CL_MEM_CONTEXT:
    case CL_MEM_ASSOCIATED_MEMOBJECT:
    case CL_SAMPLER_CONTEXT:
    case CL_PROGRAM_CONTEXT:
    case CL_KERNEL_CONTEXT:
    case CL_KERNEL_PROGRAM:
      returner = ReturnPointer;
      break;
    case CL_CONTEXT_DEVICES:
    case CL_PROGRAM_DEVICES:
      returner = ReturnPointerArray;
      break;
    case CL_CONTEXT_PROPERTIES:
      returner = ReturnNullTerminatedListAsIntegerArray;
      break;
    case CL_IMAGE_FORMAT:
      returner = ReturnImageFormat;
      break;
    case CL_PROGRAM_BINARIES: 
      returner = ReturnBinaryArray;
      break;
    case CL_PROGRAM_BUILD_STATUS:
      returner = ReturnValue<Integer, int32_t>;
      break;
    }
    return returner(wrapper, natives, result);
  }
}
