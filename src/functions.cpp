#include "v8cl.h"
#include "constants.h"
#include "callbacks.h"

namespace v8cl {

  // clFlush
  int32_t OneArgFn (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clFn) (void* smth);
    *(void**) &clFn = wrapper->f;

    void* smth = *(void**) natives[0];

    return clFn(smth);
  }


  int32_t GetProgramBinaries (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result);

  // All clGet*Info
  int32_t GetInfo (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    uint32_t param_name = *(uint32_t*) natives[1];
    if (param_name == CL_PROGRAM_BINARIES) {
      return GetProgramBinaries(wrapper, natives, result);
    }

    int32_t (CALL *clGetInfo) (void*, uint32_t, size_t, void*, size_t*);
    *(void**) &clGetInfo = wrapper->f;

    void *object = *(void**) natives[0];

    size_t size = 0;
    int32_t error = clGetInfo(object, param_name, 0, NULL, &size);
    if (error) return error;

    void *info = malloc(size);

    error = clGetInfo(object, param_name, size, info, NULL);
    if (error) {
      free(info);
      return error;
    }

    result.push_back(info);
    PushBackWrapped(result, size);
    return 0;
  }

  int32_t GetProgramBinaries (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clGetInfo) (void*, uint32_t, size_t, void*, size_t*);
    *(void**) &clGetInfo = wrapper->f;

    void *object = *(void**) natives[0];
    size_t size = 0;
    size_t error = clGetInfo(object, CL_PROGRAM_BINARY_SIZES, 0, NULL, &size);
    if (error) return error;

    size_t *sizes = (size_t*) malloc(size);
    error = clGetInfo(object, CL_PROGRAM_BINARY_SIZES, size, sizes, 0);
    if (error) {
      free(sizes);
      return 0;
    }

    size_t num_binaries = size / sizeof(size);
    unsigned char **binaries = (unsigned char**) malloc(num_binaries * sizeof(char**));
    for (size_t i = 0; i < num_binaries; ++i) {
      binaries[0] = (unsigned char*) malloc(sizes[i]);
    }

    error = clGetInfo(object, CL_PROGRAM_BINARIES, sizeof(char**), binaries, NULL);
    if (error) {
      for (size_t i = 0; i < num_binaries; ++i) {
        free(sizes);
        free(binaries[0]);
        free(binaries);
        return error;
      }
    }

    result.push_back(sizes);
    PushBackWrapped(result, num_binaries);
    for (size_t i = 0; i < num_binaries; ++i) {
      result.push_back(binaries[i]);
    }

    free(binaries);
    return 0;
  }

  // clGetProgramBuildInfo, clGetKernelWorkGroupInfo
  int32_t GetDependentInfo (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clGetDependentInfo) (void*, void*, uint32_t, size_t, void*, size_t*);
    *(void**) &clGetDependentInfo = wrapper->f;

    void *main = *(void**) natives[0];
    void *sub = *(void**) natives[1];
    uint32_t param_name = *(uint32_t*) natives[2];

    size_t size = 0;
    int32_t error = clGetDependentInfo(main, sub, param_name, 0, NULL, &size);
    if (error) return error;

    void *info = malloc(size);
    error = clGetDependentInfo(main, sub, param_name, size, info, NULL);
    if (error) {
      free(info);
      return error;
    }

    result.push_back(info);
    PushBackWrapped(result, size);
    return 0;
  }

  int32_t GetSupportedImageFormats (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clGetSupportedImageFormats) (void*, uint64_t, uint32_t, uint32_t, cl_image_format*, uint32_t*);
    *(void**) &clGetSupportedImageFormats = wrapper->f;

    void *context = *(void**) natives[0];
    uint32_t flags = *(uint32_t*) natives[1];
    uint32_t type = *(uint32_t*) natives[2];

    uint32_t size = 0;
    int32_t error = clGetSupportedImageFormats(context, flags, type, 0, NULL, &size);
    if (error) return error;

    cl_image_format *formats = (cl_image_format*) malloc(sizeof(cl_image_format) * size);
    error = clGetSupportedImageFormats(context, flags, type, size, formats, NULL);
    if (error) {
      free(formats);
      return error;
    }

    result.push_back(formats);
    PushBackWrapped(result, size);
    return 0;
  }

  int32_t GetPlatformIDs (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clGetPlatformIDs) (size_t, void*, size_t*);
    *(void**) &clGetPlatformIDs = wrapper->f;

    size_t size = 0;
    int32_t error = clGetPlatformIDs(0, NULL, &size);
    if (error) return error;

    void *platforms = malloc(sizeof(void*) * size);
    error = clGetPlatformIDs(size, platforms, NULL);
    if (error) {
      free(platforms);
      return error;
    }

    result.push_back(platforms);

    PushBackWrapped(result, size * sizeof(void*));
    return 0;
  }

  int32_t GetDeviceIDs (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clGetDeviceIDs) (void*, uint64_t, size_t, void*, size_t*);
    *(void**) &clGetDeviceIDs = wrapper->f;

    void *platform = *(void**) natives[0];
    // uint32_t because js doesn't support uint64_t
    uint32_t device_type = *(uint32_t*) natives[1];

    size_t size = 0;
    int32_t error = clGetDeviceIDs(platform, device_type, 0, NULL, &size);
    if (error) return error;

    void *devices = malloc(sizeof(void*) * size);
    error = clGetDeviceIDs(platform, device_type, size, devices, NULL);
    if (error) {
      free(devices);
      return error;
    }

    result.push_back(devices);

    PushBackWrapped(result, size * sizeof(void*));
    return 0;
  }

  int32_t CreateContext (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateContext) (intptr_t*, uint32_t, void*, void*, void*, int32_t*);
    *(void**) &clCreateContext = wrapper->f;

    intptr_t *properties = (intptr_t*) natives[0];

    void *devices = natives[1];
    size_t size = *(size_t*) natives[2];

    int32_t error = 0;
    void *context = clCreateContext(properties, size, devices, NULL, NULL, &error);
    if (error) {
      return error;
    }

    PushBackWrapped(result, context);
    return 0;
  }

  int32_t CreateContextFromType (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateContextFromType) (intptr_t*, uint64_t, void*, void*, int32_t*);
    *(void**) &clCreateContextFromType = wrapper->f;

    intptr_t *properties = (intptr_t*) natives[0];

    uint32_t device_type = *(uint32_t*) natives[1];

    int32_t error = 0;
    void *context = clCreateContextFromType(properties, device_type, NULL, NULL, &error);
    if (error) {
      return error;
    }

    PushBackWrapped(result, context);
    return 0;
  }

  int32_t CreateCommandQueue (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateCommandQueue) (void*, void*, uint64_t, int32_t*);
    *(void**) &clCreateCommandQueue = wrapper->f;

    void *context = *(void**) natives[0];
    void *device = *(void**) natives[1];
    uint32_t flags = *(uint32_t*) natives[2];

    int32_t error = 0;
    void *queue = clCreateCommandQueue(context, device, flags, &error);
    if (error) {
      return error;
    }

    PushBackWrapped(result, queue);
    return 0;
  }

  int32_t CreateBuffer (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateBuffer) (void*, uint64_t, size_t, void*, int32_t*);
    *(void**) &clCreateBuffer = wrapper->f;

    void *context = *(void**) natives[0];
    uint32_t flags = *(uint32_t*) natives[1];
    size_t size = *(size_t*) natives[2];
    void *host_ptr = NULL;

    int32_t error = 0;
    void *mem = clCreateBuffer(context, flags, size, host_ptr, &error);
    if (error) {
      return error;
    }

    PushBackWrapped(result, mem);
    return 0;
  }

  int32_t CreateSubBuffer (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateSubBuffer) (void*, uint64_t, uint32_t, void*, int32_t*);
    *(void**) &clCreateSubBuffer = wrapper->f;

    void *mem = *(void**) natives[0];
    uint32_t flags = *(uint32_t*) natives[1];
    uint32_t create_type = *(uint32_t*) natives[2];
    cl_buffer_region *create_info = (cl_buffer_region*) natives[3];

    int32_t error = 0;
    void *submem = clCreateSubBuffer(mem, flags, create_type, create_info, &error);
    if (error) {
      return error;
    }

    PushBackWrapped(result, submem);
    return 0;
  }


  int32_t CreateImage2D (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateImage2D) (void*, uint64_t, cl_image_format*, size_t, size_t, size_t, void*, int32_t*);
    *(void**) &clCreateImage2D = wrapper->f;

    void *context = *(void**) natives[0];
    uint32_t flags = *(uint32_t*) natives[1];
    cl_image_format *image_format = (cl_image_format*) natives[2];
    size_t width = *(size_t*) natives[3];
    size_t height = *(size_t*) natives[4];
    size_t row_pitch = 0;
    void *host_ptr = NULL;

    int32_t error = 0;
    void *mem = clCreateImage2D(context, flags, image_format, width, height, row_pitch, host_ptr, &error);
    if (error) {
      return error;
    }

    PushBackWrapped(result, mem);
    return 0;
  }

  int32_t CreateImage3D (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateImage3D) (void*, uint64_t, cl_image_format*, size_t, size_t, size_t, size_t, size_t, void*, int32_t*);
    *(void**) &clCreateImage3D = wrapper->f;

    void *context = *(void**) natives[0];
    uint32_t flags = *(uint32_t*) natives[1];
    cl_image_format *image_format = (cl_image_format*) natives[2];
    size_t width = *(size_t*) natives[3];
    size_t height = *(size_t*) natives[4];
    size_t depth = *(size_t*) natives[5];
    size_t row_pitch = 0;
    size_t slice_pitch = 0;
    void *host_ptr = NULL;

    int32_t error = 0;
    void *mem = clCreateImage3D(context, flags, image_format, width, height, depth, row_pitch, slice_pitch, host_ptr, &error);
    if (error) {
      return error;
    }

    PushBackWrapped(result, mem);
    return 0;
  }

  int32_t CreateSampler (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateSampler) (void*, uint32_t, uint32_t, uint32_t, int32_t*);
    *(void**) &clCreateSampler = wrapper->f;

    void *context = *(void**) natives[0];
    uint32_t norm_coords = *(uint32_t*) natives[1];
    uint32_t addressing_mode = *(uint32_t*) natives[2];
    uint32_t filter_mode = *(uint32_t*) natives[3];

    int32_t error = 0;
    void *sampler = clCreateSampler(context, norm_coords, addressing_mode, filter_mode, &error);
    if (error) return error;

    PushBackWrapped(result, sampler);
    return 0;
  }

  int32_t CreateProgramWithSource (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateProgramWithSource) (void*, uint32_t, char**, size_t*, int32_t*);
    *(void**) &clCreateProgramWithSource = wrapper->f;

    void *context = *(void**) natives[0];
    char *code = (char*) natives[1];
    size_t size = *(size_t*) natives[2];

    int32_t error = 0;
    void* program = clCreateProgramWithSource(context, 1, &code, &size, &error);
    if (error) return error;

    PushBackWrapped(result, program);
    return 0;
  }

  int32_t BuildProgram (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clBuildProgram) (void*, uint32_t, void*, char*, void*, void*);
    *(void**) &clBuildProgram = wrapper->f;

    void *program = *(void**) natives[0];
    void *devices = natives[1];
    size_t num_devices = *(size_t*) natives[2];
    char *options = (char*) natives[3];
    // natives[4] is the size of options

    uint32_t error = clBuildProgram(program, num_devices, devices, options, NULL, NULL);
    return error;
  }

  int32_t CreateKernel (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    void* (CALL *clCreateKernel) (void*, char*, int32_t*);
    *(void**) &clCreateKernel = wrapper->f;

    void *program = *(void**) natives[0];
    char *name = (char*) natives[1];

    int32_t error = 0;
    void *kernel = clCreateKernel(program, name, &error);
    if (error) return error;

    PushBackWrapped(result, kernel);
    return 0;
  }

  int32_t CreateKernelsInProgram (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clCreateKernelsInProgram) (void*, uint32_t, void*, uint32_t*);
    *(void**) &clCreateKernelsInProgram = wrapper->f;

    void *program = *(void**) natives[0];

    uint32_t size = 0;
    int32_t error = clCreateKernelsInProgram(program, 0, NULL, &size);
    if (error) return error;

    void *kernels = malloc(size * sizeof(void*));
    error = clCreateKernelsInProgram(program, size, kernels, 0);
    if (error) {
      free(kernels);
      return error;
    }

    result.push_back(kernels);
    PushBackWrapped(result, size * sizeof(void*));
    return 0;
  }

  int32_t SetKernelArg (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clSetKernelArg) (void*, uint32_t, size_t, void*);
    *(void**) &clSetKernelArg = wrapper->f;

    void *kernel = *(void**) natives[0];
    uint32_t index = *(uint32_t*) natives[1];
    size_t size = *(size_t*) natives[2];
    void *value = natives[3];
    size_t valueSize = *(size_t*) natives[4];
    if (valueSize) {
      if (size > valueSize) size = valueSize;
      value = *(void**) value;
    }

    return clSetKernelArg(kernel, index, size, value);
  }

  // clEnqueueReadBuffer, clEnqueueWriteBuffer
  int32_t EnqueueReadOrWriteBuffer (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clEnqueueReadOrWriteBuffer) (void*, void*, uint32_t, size_t, size_t, void*, uint32_t, void*, void*);
    *(void**) &clEnqueueReadOrWriteBuffer = wrapper->f;

    void *queue = *(void**) natives[0];
    void *mem = *(void**) natives[1];
    uint32_t offset = *(uint32_t*) natives[2];
    void *ptr = *(void**) natives[3];
    size_t size = *(size_t*) natives[4];
    void *event = 0;

    int32_t error = clEnqueueReadOrWriteBuffer(queue, mem, 0 /* false */, offset, size, ptr, 0, NULL, &event);
    PushBackWrapped(result, event);
    return error;
  }

  int32_t EnqueueNDRangeKernel (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clEnqueueNDRangeKernel) (void*, void*, uint32_t, size_t*, size_t*, size_t*, uint32_t, void*, void*);
    *(void**) &clEnqueueNDRangeKernel = wrapper->f;

    void *queue = *(void**) natives[0];
    void *kernel = *(void**) natives[1];
    size_t *global_work_offset = (size_t*) natives[2];
    size_t *global_work_size = (size_t*) natives[4];
    size_t *local_work_size = (size_t*) natives[6];
    uint32_t work_dim1 = *(uint32_t*) natives[3];
    uint32_t work_dim2 = *(uint32_t*) natives[5];
    uint32_t work_dim3 = *(uint32_t*) natives[7];
    void *event = 0;

    if (work_dim1 == 0) {
      global_work_offset = NULL;
    }
    if (work_dim1 == 0 || work_dim2 < work_dim1) work_dim1 = work_dim2;
    if (work_dim1 == 0 || work_dim3 < work_dim1) work_dim1 = work_dim3;

    if (work_dim1) {
      int32_t error = clEnqueueNDRangeKernel(queue, kernel, work_dim1, global_work_offset, global_work_size, local_work_size, 0, NULL, &event);
      PushBackWrapped(result, event);
      return error;
    } else {
      return CL_INVALID_WORK_DIMENSION;
    }
  }

  int32_t SetEventCallback (const Wrapper* wrapper, vector<void*>& natives, vector<void*>& result) {
    int32_t (CALL *clSetEventCallback) (void*, int32_t, pfn_notify, void*);
    *(void**) &clSetEventCallback = wrapper->f;

    EventHandler *handler = new EventHandler;
    handler->events = wrapper->events;
    handler->event = *(Persistent<Value>*) natives[0];
    int32_t type = *(int32_t*) natives[1];
    handler->f = *(Persistent<Value>*) natives[2];
    handler->data = *(Persistent<Value>*) natives[3];
    void *event = Get<void*>(handler->event);

    int32_t error = clSetEventCallback(event, type, FireEvent, handler);
    if (error) {
      delete handler;
      return error;
    }

    handler->implHandle = handler->events.add(handler);

    return 0;
  }
}
