#include "v8cl.h"
#include "functions.h"
#include "converters.h"
#include "returners.h"

namespace v8cl {
  Wrapper wrappers[] = {
    { "clFlush", OneArgFn,
      { One<void*>    /* queue      */ } },

    // Get*Info

    { "clGetPlatformInfo", GetInfo,
      { One<void*>    /* platform   */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetDeviceInfo", GetInfo,
      { One<void*>    /* device     */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetContextInfo", GetInfo,
      { One<void*>    /* context    */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetCommandQueueInfo", GetInfo,
      { One<void*>    /* queue      */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetMemObjectInfo", GetInfo,
      { One<void*>    /* mem        */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetImageInfo", GetInfo,
      { One<void*>    /* image      */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetSamplerInfo", GetInfo,
      { One<void*>    /* sampler    */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetProgramInfo", GetInfo,
      { One<void*>    /* program    */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetKernelInfo", GetInfo,
      { One<void*>    /* kernel     */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetEventInfo", GetInfo,
      { One<void*>    /* event      */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    // Get**Info (nested info)

    { "clGetProgramBuildInfo", GetDependentInfo,
      { One<void*>    /* program    */,
        One<void*>    /* device     */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    { "clGetKernelWorkGroupInfo", GetDependentInfo,
      { One<void*>    /* kernel     */,
        One<void*>    /* device     */,
        One<uint32_t> /* param_name */ },
      ReturnInfo },

    // Individual functions

    { "clGetPlatformIDs", GetPlatformIDs,
      {},
      ReturnPointerArray },

    { "clGetDeviceIDs", GetDeviceIDs,
      { One<void*>    /* platform    */,
        One<uint32_t> /* device_type */ },
      ReturnPointerArray },

    { "clCreateContext", CreateContext,
      { NullTerminatedList /* properties */,
        Many<void*>        /* devices    */ },
      ReturnPointer, "clReleaseContext" },

    { "clCreateCommandQueue", CreateCommandQueue,
      { One<void*>    /* context    */,
        One<void*>    /* device     */,
        One<uint32_t> /* properties */ },
      ReturnPointer, "clReleaseCommandQueue" },

    { "clCreateBuffer", CreateBuffer,
      { One<void*>    /* context */,
        One<uint32_t> /* flags   */,
        One<size_t>   /* size    */ },
      ReturnPointer, "clReleaseMemObject" },

    { "clCreateSubBuffer", CreateSubBuffer,
      { One<void*>    /* buffer             */,
        One<uint32_t> /* flags              */,
        One<uint32_t> /* buffer_create_type */,
        BufferRegion  /* buffer_create_info */ },
      ReturnPointer, "clReleaseMemObject" },

    { "clCreateImage2D", CreateImage2D,
      { One<void*>    /* context      */,
        One<uint32_t> /* flags        */,
        ImageFormat   /* image_format */,
        One<size_t>   /* width        */,
        One<size_t>   /* height       */ },
      ReturnPointer, "clReleaseMemObject" },

    { "clCreateImage3D", CreateImage3D,
      { One<void*>     /* context      */,
        One<uint32_t>  /* flags        */,
        ImageFormat    /* image_format */,
        One<size_t>    /* width        */,
        One<size_t>    /* height       */,
        One<size_t>    /* depth        */ },
      ReturnPointer, "clReleaseMemObject" },

    { "clGetSupportedImageFormats", GetSupportedImageFormats,
      { One<void*>     /* context    */,
        One<uint32_t>  /* flags      */,
        One<uint32_t>  /* image_type */ },
      ReturnImageFormatArray },

    { "clCreateSampler", CreateSampler,
      { One<void*>    /* context           */,
        One<uint32_t> /* normalized_coords */,
        One<uint32_t> /* addressing_mode   */,
        One<uint32_t> /* filter_mode       */ },
      ReturnPointer, "clReleaseMemObject" },

    { "clCreateProgramWithSource", CreateProgramWithSource,
      { One<void*>    /* context */,
        CharArray     /* src     */ },
      ReturnPointer, "clReleaseProgram" },

    { "clBuildProgram", BuildProgram,
      { One<void*>    /* program */,
        Many<void*>   /* devices */,
        CharArray     /* options */ } },

    { "clCreateKernel", CreateKernel,
      { One<void*>    /* program     */,
        CharArray     /* kernel_name */ },
      ReturnPointer, "clReleaseKernel" },

    { "clCreateKernelsInProgram", CreateKernelsInProgram,
      { One<void*>    /* program */ },
      ReturnPointerArray, "clReleaseKernel" },

    { "clSetKernelArg", SetKernelArg,
      { One<void*>    /* kernel    */,
        One<uint32_t> /* arg_index */,
        One<size_t>   /* arg_size  */,
        TypedArray    /* arg_value */ } },

    { "clEnqueueReadBuffer", EnqueueReadOrWriteBuffer,
      { One<void*>    /* queue  */,
        One<void*>    /* buffer */,
        One<uint32_t> /* offset */,
        TypedArray    /* ptr    */ },
      ReturnPointer, "clReleaseEvent" },

    { "clEnqueueWriteBuffer", EnqueueReadOrWriteBuffer,
      { One<void*>    /* queue  */,
        One<void*>    /* buffer */,
        One<uint32_t> /* offset */,
        TypedArray    /* ptr    */ },
      ReturnPointer, "clReleaseEvent" },

    { "clEnqueueNDRangeKernel", EnqueueNDRangeKernel,
      { One<void*>    /* queue              */,
        One<void*>    /* kernel             */,
        Many<size_t>  /* global_work_offset */,
        Many<size_t>  /* global_work_size   */,
        Many<size_t>  /* local_work_size    */ },
      ReturnPointer, "clReleaseEvent" },

    { "clSetEventCallback", SetEventCallback,
      { Persist       /* event                      */,
        One<int32_t>  /* command_exec_callback_type */,
        Persist       /* pfn_event_notify           */,
        Persist       /* user_data                  */ } },

    { NULL } // list terminator
  };
}
