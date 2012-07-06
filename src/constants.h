#ifndef V8CL_CONSTANTS
#define V8CL_CONSTANTS

#include "v8cl.h"

/* Error Codes */
#define CL_SUCCESS                                  0
#define CL_DEVICE_NOT_FOUND                         -1
#define CL_DEVICE_NOT_AVAILABLE                     -2
#define CL_COMPILER_NOT_AVAILABLE                   -3
#define CL_MEM_OBJECT_ALLOCATION_FAILURE            -4
#define CL_OUT_OF_RESOURCES                         -5
#define CL_OUT_OF_HOST_MEMORY                       -6
#define CL_PROFILING_INFO_NOT_AVAILABLE             -7
#define CL_MEM_COPY_OVERLAP                         -8
#define CL_IMAGE_FORMAT_MISMATCH                    -9
#define CL_IMAGE_FORMAT_NOT_SUPPORTED               -10
#define CL_BUILD_PROGRAM_FAILURE                    -11
#define CL_MAP_FAILURE                              -12
#define CL_MISALIGNED_SUB_BUFFER_OFFSET             -13
#define CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST -14

#define CL_INVALID_VALUE                            -30
#define CL_INVALID_DEVICE_TYPE                      -31
#define CL_INVALID_PLATFORM                         -32
#define CL_INVALID_DEVICE                           -33
#define CL_INVALID_CONTEXT                          -34
#define CL_INVALID_QUEUE_PROPERTIES                 -35
#define CL_INVALID_COMMAND_QUEUE                    -36
#define CL_INVALID_HOST_PTR                         -37
#define CL_INVALID_MEM_OBJECT                       -38
#define CL_INVALID_IMAGE_FORMAT_DESCRIPTOR          -39
#define CL_INVALID_IMAGE_SIZE                       -40
#define CL_INVALID_SAMPLER                          -41
#define CL_INVALID_BINARY                           -42
#define CL_INVALID_BUILD_OPTIONS                    -43
#define CL_INVALID_PROGRAM                          -44
#define CL_INVALID_PROGRAM_EXECUTABLE               -45
#define CL_INVALID_KERNEL_NAME                      -46
#define CL_INVALID_KERNEL_DEFINITION                -47
#define CL_INVALID_KERNEL                           -48
#define CL_INVALID_ARG_INDEX                        -49
#define CL_INVALID_ARG_VALUE                        -50
#define CL_INVALID_ARG_SIZE                         -51
#define CL_INVALID_KERNEL_ARGS                      -52
#define CL_INVALID_WORK_DIMENSION                   -53
#define CL_INVALID_WORK_GROUP_SIZE                  -54
#define CL_INVALID_WORK_ITEM_SIZE                   -55
#define CL_INVALID_GLOBAL_OFFSET                    -56
#define CL_INVALID_EVENT_WAIT_LIST                  -57
#define CL_INVALID_EVENT                            -58
#define CL_INVALID_OPERATION                        -59
#define CL_INVALID_GL_OBJECT                        -60
#define CL_INVALID_BUFFER_SIZE                      -61
#define CL_INVALID_MIP_LEVEL                        -62
#define CL_INVALID_GLOBAL_WORK_SIZE                 -63
#define CL_INVALID_PROPERTY                         -64

/* OpenCL Version */
#define CL_VERSION_1_0                              1
#define CL_VERSION_1_1                              1

/* cl_bool */
#define CL_FALSE                                    0
#define CL_TRUE                                     1

/* cl_platform_info */
#define CL_PLATFORM_PROFILE                         0x0900
#define CL_PLATFORM_VERSION                         0x0901
#define CL_PLATFORM_NAME                            0x0902
#define CL_PLATFORM_VENDOR                          0x0903
#define CL_PLATFORM_EXTENSIONS                      0x0904

/* cl_device_type - bitfield */
#define CL_DEVICE_TYPE_DEFAULT                      (1 << 0)
#define CL_DEVICE_TYPE_CPU                          (1 << 1)
#define CL_DEVICE_TYPE_GPU                          (1 << 2)
#define CL_DEVICE_TYPE_ACCELERATOR                  (1 << 3)
#define CL_DEVICE_TYPE_ALL                          0xFFFFFFFF

/* cl_device_info */
#define CL_DEVICE_TYPE                              0x1000
#define CL_DEVICE_VENDOR_ID                         0x1001
#define CL_DEVICE_MAX_COMPUTE_UNITS                 0x1002
#define CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS          0x1003
#define CL_DEVICE_MAX_WORK_GROUP_SIZE               0x1004
#define CL_DEVICE_MAX_WORK_ITEM_SIZES               0x1005
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR       0x1006
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT      0x1007
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT        0x1008
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG       0x1009
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT      0x100A
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE     0x100B
#define CL_DEVICE_MAX_CLOCK_FREQUENCY               0x100C
#define CL_DEVICE_ADDRESS_BITS                      0x100D
#define CL_DEVICE_MAX_READ_IMAGE_ARGS               0x100E
#define CL_DEVICE_MAX_WRITE_IMAGE_ARGS              0x100F
#define CL_DEVICE_MAX_MEM_ALLOC_SIZE                0x1010
#define CL_DEVICE_IMAGE2D_MAX_WIDTH                 0x1011
#define CL_DEVICE_IMAGE2D_MAX_HEIGHT                0x1012
#define CL_DEVICE_IMAGE3D_MAX_WIDTH                 0x1013
#define CL_DEVICE_IMAGE3D_MAX_HEIGHT                0x1014
#define CL_DEVICE_IMAGE3D_MAX_DEPTH                 0x1015
#define CL_DEVICE_IMAGE_SUPPORT                     0x1016
#define CL_DEVICE_MAX_PARAMETER_SIZE                0x1017
#define CL_DEVICE_MAX_SAMPLERS                      0x1018
#define CL_DEVICE_MEM_BASE_ADDR_ALIGN               0x1019
#define CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE          0x101A
#define CL_DEVICE_SINGLE_FP_CONFIG                  0x101B
#define CL_DEVICE_GLOBAL_MEM_CACHE_TYPE             0x101C
#define CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE         0x101D
#define CL_DEVICE_GLOBAL_MEM_CACHE_SIZE             0x101E
#define CL_DEVICE_GLOBAL_MEM_SIZE                   0x101F
#define CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE          0x1020
#define CL_DEVICE_MAX_CONSTANT_ARGS                 0x1021
#define CL_DEVICE_LOCAL_MEM_TYPE                    0x1022
#define CL_DEVICE_LOCAL_MEM_SIZE                    0x1023
#define CL_DEVICE_ERROR_CORRECTION_SUPPORT          0x1024
#define CL_DEVICE_PROFILING_TIMER_RESOLUTION        0x1025
#define CL_DEVICE_ENDIAN_LITTLE                     0x1026
#define CL_DEVICE_AVAILABLE                         0x1027
#define CL_DEVICE_COMPILER_AVAILABLE                0x1028
#define CL_DEVICE_EXECUTION_CAPABILITIES            0x1029
#define CL_DEVICE_QUEUE_PROPERTIES                  0x102A
#define CL_DEVICE_NAME                              0x102B
#define CL_DEVICE_VENDOR                            0x102C
#define CL_DRIVER_VERSION                           0x102D
#define CL_DEVICE_PROFILE                           0x102E
#define CL_DEVICE_VERSION                           0x102F
#define CL_DEVICE_EXTENSIONS                        0x1030
#define CL_DEVICE_PLATFORM                          0x1031
/* 0x1032 reserved for CL_DEVICE_DOUBLE_FP_CONFIG */
/* 0x1033 reserved for CL_DEVICE_HALF_FP_CONFIG */
#define CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF       0x1034
#define CL_DEVICE_HOST_UNIFIED_MEMORY               0x1035
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR          0x1036
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT         0x1037
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_INT           0x1038
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG          0x1039
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT         0x103A
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE        0x103B
#define CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF          0x103C
#define CL_DEVICE_OPENCL_C_VERSION                  0x103D

/* cl_device_fp_config - bitfield */
#define CL_FP_DENORM                                (1 << 0)
#define CL_FP_INF_NAN                               (1 << 1)
#define CL_FP_ROUND_TO_NEAREST                      (1 << 2)
#define CL_FP_ROUND_TO_ZERO                         (1 << 3)
#define CL_FP_ROUND_TO_INF                          (1 << 4)
#define CL_FP_FMA                                   (1 << 5)
#define CL_FP_SOFT_FLOAT                            (1 << 6)

/* cl_device_mem_cache_type */
#define CL_NONE                                     0x0
#define CL_READ_ONLY_CACHE                          0x1
#define CL_READ_WRITE_CACHE                         0x2

/* cl_device_local_mem_type */
#define CL_LOCAL                                    0x1
#define CL_GLOBAL                                   0x2

/* cl_device_exec_capabilities - bitfield */
#define CL_EXEC_KERNEL                              (1 << 0)
#define CL_EXEC_NATIVE_KERNEL                       (1 << 1)

/* cl_command_queue_properties - bitfield */
#define CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE      (1 << 0)
#define CL_QUEUE_PROFILING_ENABLE                   (1 << 1)

/* cl_context_info  */
#define CL_CONTEXT_REFERENCE_COUNT                  0x1080
#define CL_CONTEXT_DEVICES                          0x1081
#define CL_CONTEXT_PROPERTIES                       0x1082
#define CL_CONTEXT_NUM_DEVICES                      0x1083

/* cl_context_info + cl_context_properties */
#define CL_CONTEXT_PLATFORM                         0x1084

/* cl_command_queue_info */
#define CL_QUEUE_CONTEXT                            0x1090
#define CL_QUEUE_DEVICE                             0x1091
#define CL_QUEUE_REFERENCE_COUNT                    0x1092
#define CL_QUEUE_PROPERTIES                         0x1093

/* cl_mem_flags - bitfield */
#define CL_MEM_READ_WRITE                           (1 << 0)
#define CL_MEM_WRITE_ONLY                           (1 << 1)
#define CL_MEM_READ_ONLY                            (1 << 2)
#define CL_MEM_USE_HOST_PTR                         (1 << 3)
#define CL_MEM_ALLOC_HOST_PTR                       (1 << 4)
#define CL_MEM_COPY_HOST_PTR                        (1 << 5)

/* cl_channel_order */
#define CL_R                                        0x10B0
#define CL_A                                        0x10B1
#define CL_RG                                       0x10B2
#define CL_RA                                       0x10B3
#define CL_RGB                                      0x10B4
#define CL_RGBA                                     0x10B5
#define CL_BGRA                                     0x10B6
#define CL_ARGB                                     0x10B7
#define CL_INTENSITY                                0x10B8
#define CL_LUMINANCE                                0x10B9
#define CL_Rx                                       0x10BA
#define CL_RGx                                      0x10BB
#define CL_RGBx                                     0x10BC

/* cl_channel_type */
#define CL_SNORM_INT8                               0x10D0
#define CL_SNORM_INT16                              0x10D1
#define CL_UNORM_INT8                               0x10D2
#define CL_UNORM_INT16                              0x10D3
#define CL_UNORM_SHORT_565                          0x10D4
#define CL_UNORM_SHORT_555                          0x10D5
#define CL_UNORM_INT_101010                         0x10D6
#define CL_SIGNED_INT8                              0x10D7
#define CL_SIGNED_INT16                             0x10D8
#define CL_SIGNED_INT32                             0x10D9
#define CL_UNSIGNED_INT8                            0x10DA
#define CL_UNSIGNED_INT16                           0x10DB
#define CL_UNSIGNED_INT32                           0x10DC
#define CL_HALF_FLOAT                               0x10DD
#define CL_FLOAT                                    0x10DE

/* cl_mem_object_type */
#define CL_MEM_OBJECT_BUFFER                        0x10F0
#define CL_MEM_OBJECT_IMAGE2D                       0x10F1
#define CL_MEM_OBJECT_IMAGE3D                       0x10F2

/* cl_mem_info */
#define CL_MEM_TYPE                                 0x1100
#define CL_MEM_FLAGS                                0x1101
#define CL_MEM_SIZE                                 0x1102
#define CL_MEM_HOST_PTR                             0x1103
#define CL_MEM_MAP_COUNT                            0x1104
#define CL_MEM_REFERENCE_COUNT                      0x1105
#define CL_MEM_CONTEXT                              0x1106
#define CL_MEM_ASSOCIATED_MEMOBJECT                 0x1107
#define CL_MEM_OFFSET                               0x1108

/* cl_image_info */
#define CL_IMAGE_FORMAT                             0x1110
#define CL_IMAGE_ELEMENT_SIZE                       0x1111
#define CL_IMAGE_ROW_PITCH                          0x1112
#define CL_IMAGE_SLICE_PITCH                        0x1113
#define CL_IMAGE_WIDTH                              0x1114
#define CL_IMAGE_HEIGHT                             0x1115
#define CL_IMAGE_DEPTH                              0x1116

/* cl_addressing_mode */
#define CL_ADDRESS_NONE                             0x1130
#define CL_ADDRESS_CLAMP_TO_EDGE                    0x1131
#define CL_ADDRESS_CLAMP                            0x1132
#define CL_ADDRESS_REPEAT                           0x1133
#define CL_ADDRESS_MIRRORED_REPEAT                  0x1134

/* cl_filter_mode */
#define CL_FILTER_NEAREST                           0x1140
#define CL_FILTER_LINEAR                            0x1141

/* cl_sampler_info */
#define CL_SAMPLER_REFERENCE_COUNT                  0x1150
#define CL_SAMPLER_CONTEXT                          0x1151
#define CL_SAMPLER_NORMALIZED_COORDS                0x1152
#define CL_SAMPLER_ADDRESSING_MODE                  0x1153
#define CL_SAMPLER_FILTER_MODE                      0x1154

/* cl_map_flags - bitfield */
#define CL_MAP_READ                                 (1 << 0)
#define CL_MAP_WRITE                                (1 << 1)

/* cl_program_info */
#define CL_PROGRAM_REFERENCE_COUNT                  0x1160
#define CL_PROGRAM_CONTEXT                          0x1161
#define CL_PROGRAM_NUM_DEVICES                      0x1162
#define CL_PROGRAM_DEVICES                          0x1163
#define CL_PROGRAM_SOURCE                           0x1164
#define CL_PROGRAM_BINARY_SIZES                     0x1165
#define CL_PROGRAM_BINARIES                         0x1166

/* cl_program_build_info */
#define CL_PROGRAM_BUILD_STATUS                     0x1181
#define CL_PROGRAM_BUILD_OPTIONS                    0x1182
#define CL_PROGRAM_BUILD_LOG                        0x1183

/* cl_build_status */
#define CL_BUILD_SUCCESS                            0
#define CL_BUILD_NONE                               -1
#define CL_BUILD_ERROR                              -2
#define CL_BUILD_IN_PROGRESS                        -3

/* cl_kernel_info */
#define CL_KERNEL_FUNCTION_NAME                     0x1190
#define CL_KERNEL_NUM_ARGS                          0x1191
#define CL_KERNEL_REFERENCE_COUNT                   0x1192
#define CL_KERNEL_CONTEXT                           0x1193
#define CL_KERNEL_PROGRAM                           0x1194

/* cl_kernel_work_group_info */
#define CL_KERNEL_WORK_GROUP_SIZE                   0x11B0
#define CL_KERNEL_COMPILE_WORK_GROUP_SIZE           0x11B1
#define CL_KERNEL_LOCAL_MEM_SIZE                    0x11B2
#define CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE 0x11B3
#define CL_KERNEL_PRIVATE_MEM_SIZE                  0x11B4

/* cl_event_info  */
#define CL_EVENT_COMMAND_QUEUE                      0x11D0
#define CL_EVENT_COMMAND_TYPE                       0x11D1
#define CL_EVENT_REFERENCE_COUNT                    0x11D2
#define CL_EVENT_COMMAND_EXECUTION_STATUS           0x11D3
#define CL_EVENT_CONTEXT                            0x11D4

/* cl_command_type */
#define CL_COMMAND_NDRANGE_KERNEL                   0x11F0
#define CL_COMMAND_TASK                             0x11F1
#define CL_COMMAND_NATIVE_KERNEL                    0x11F2
#define CL_COMMAND_READ_BUFFER                      0x11F3
#define CL_COMMAND_WRITE_BUFFER                     0x11F4
#define CL_COMMAND_COPY_BUFFER                      0x11F5
#define CL_COMMAND_READ_IMAGE                       0x11F6
#define CL_COMMAND_WRITE_IMAGE                      0x11F7
#define CL_COMMAND_COPY_IMAGE                       0x11F8
#define CL_COMMAND_COPY_IMAGE_TO_BUFFER             0x11F9
#define CL_COMMAND_COPY_BUFFER_TO_IMAGE             0x11FA
#define CL_COMMAND_MAP_BUFFER                       0x11FB
#define CL_COMMAND_MAP_IMAGE                        0x11FC
#define CL_COMMAND_UNMAP_MEM_OBJECT                 0x11FD
#define CL_COMMAND_MARKER                           0x11FE
#define CL_COMMAND_ACQUIRE_GL_OBJECTS               0x11FF
#define CL_COMMAND_RELEASE_GL_OBJECTS               0x1200
#define CL_COMMAND_READ_BUFFER_RECT                 0x1201
#define CL_COMMAND_WRITE_BUFFER_RECT                0x1202
#define CL_COMMAND_COPY_BUFFER_RECT                 0x1203
#define CL_COMMAND_USER                             0x1204

/* command execution status */
#define CL_COMPLETE                                 0x0
#define CL_RUNNING                                  0x1
#define CL_SUBMITTED                                0x2
#define CL_QUEUED                                   0x3

/* cl_buffer_create_type  */
#define CL_BUFFER_CREATE_TYPE_REGION                0x1220

/* cl_profiling_info  */
#define CL_PROFILING_COMMAND_QUEUED                 0x1280
#define CL_PROFILING_COMMAND_SUBMIT                 0x1281
#define CL_PROFILING_COMMAND_START                  0x1282
#define CL_PROFILING_COMMAND_END                    0x1283


namespace v8cl {

  const StrToInt ERROR_CODES[] = {
    { "SUCCESS",                                     0 },
    { "DEVICE_NOT_FOUND",                           -1 },
    { "DEVICE_NOT_AVAILABLE",                       -2 },
    { "COMPILER_NOT_AVAILABLE",                     -3 },
    { "MEM_OBJECT_ALLOCATION_FAILURE",              -4 },
    { "OUT_OF_RESOURCES",                           -5 },
    { "OUT_OF_HOST_MEMORY",                         -6 },
    { "PROFILING_INFO_NOT_AVAILABLE",               -7 },
    { "MEM_COPY_OVERLAP",                           -8 },
    { "IMAGE_FORMAT_MISMATCH",                      -9 },
    { "IMAGE_FORMAT_NOT_SUPPORTED",                -10 },
    { "BUILD_PROGRAM_FAILURE",                     -11 },
    { "MAP_FAILURE",                               -12 },
    { "MISALIGNED_SUB_BUFFER_OFFSET",              -13 },
    { "EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST", -14 },
    { "INVALID_VALUE",                             -30 },
    { "INVALID_DEVICE_TYPE",                       -31 },
    { "INVALID_PLATFORM",                          -32 },
    { "INVALID_DEVICE",                            -33 },
    { "INVALID_CONTEXT",                           -34 },
    { "INVALID_QUEUE_PROPERTIES",                  -35 },
    { "INVALID_COMMAND_QUEUE",                     -36 },
    { "INVALID_HOST_PTR",                          -37 },
    { "INVALID_MEM_OBJECT",                        -38 },
    { "INVALID_IMAGE_FORMAT_DESCRIPTOR",           -39 },
    { "INVALID_IMAGE_SIZE",                        -40 },
    { "INVALID_SAMPLER",                           -41 },
    { "INVALID_BINARY",                            -42 },
    { "INVALID_BUILD_OPTIONS",                     -43 },
    { "INVALID_PROGRAM",                           -44 },
    { "INVALID_PROGRAM_EXECUTABLE",                -45 },
    { "INVALID_KERNEL_NAME",                       -46 },
    { "INVALID_KERNEL_DEFINITION",                 -47 },
    { "INVALID_KERNEL",                            -48 },
    { "INVALID_ARG_INDEX",                         -49 },
    { "INVALID_ARG_VALUE",                         -50 },
    { "INVALID_ARG_SIZE",                          -51 },
    { "INVALID_KERNEL_ARGS",                       -52 },
    { "INVALID_WORK_DIMENSION",                    -53 },
    { "INVALID_WORK_GROUP_SIZE",                   -54 },
    { "INVALID_WORK_ITEM_SIZE",                    -55 },
    { "INVALID_GLOBAL_OFFSET",                     -56 },
    { "INVALID_EVENT_WAIT_LIST",                   -57 },
    { "INVALID_EVENT",                             -58 },
    { "INVALID_OPERATION",                         -59 },
    { "INVALID_GL_OBJECT",                         -60 },
    { "INVALID_BUFFER_SIZE",                       -61 },
    { "INVALID_MIP_LEVEL",                         -62 },
    { "INVALID_GLOBAL_WORK_SIZE",                  -63 },
    { "INVALID_PROPERTY",                          -64 },
    { NULL }
  };
  const StrToInt CONSTANTS[] = {
    /* OpenCL Version */
    { "VERSION_1_0",                              1 },
    { "VERSION_1_1",                              1 },
    /* cl_bool */
    { "FALSE",                                    0 },
    { "TRUE",                                     1 },
    /* cl_platform_info */
    { "PLATFORM_PROFILE",                         0x0900 },
    { "PLATFORM_VERSION",                         0x0901 },
    { "PLATFORM_NAME",                            0x0902 },
    { "PLATFORM_VENDOR",                          0x0903 },
    { "PLATFORM_EXTENSIONS",                      0x0904 },
    /* cl_device_type - bitfield */
    { "DEVICE_TYPE_DEFAULT",                      (1 << 0) },
    { "DEVICE_TYPE_CPU",                          (1 << 1) },
    { "DEVICE_TYPE_GPU",                          (1 << 2) },
    { "DEVICE_TYPE_ACCELERATOR",                  (1 << 3) },
    { "DEVICE_TYPE_ALL",                          0xFFFFFFFF },
    /* cl_device_info */
    { "DEVICE_TYPE",                              0x1000 },
    { "DEVICE_VENDOR_ID",                         0x1001 },
    { "DEVICE_MAX_COMPUTE_UNITS",                 0x1002 },
    { "DEVICE_MAX_WORK_ITEM_DIMENSIONS",          0x1003 },
    { "DEVICE_MAX_WORK_GROUP_SIZE",               0x1004 },
    { "DEVICE_MAX_WORK_ITEM_SIZES",               0x1005 },
    { "DEVICE_PREFERRED_VECTOR_WIDTH_CHAR",       0x1006 },
    { "DEVICE_PREFERRED_VECTOR_WIDTH_SHORT",      0x1007 },
    { "DEVICE_PREFERRED_VECTOR_WIDTH_INT",        0x1008 },
    { "DEVICE_PREFERRED_VECTOR_WIDTH_LONG",       0x1009 },
    { "DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT",      0x100A },
    { "DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE",     0x100B },
    { "DEVICE_MAX_CLOCK_FREQUENCY",               0x100C },
    { "DEVICE_ADDRESS_BITS",                      0x100D },
    { "DEVICE_MAX_READ_IMAGE_ARGS",               0x100E },
    { "DEVICE_MAX_WRITE_IMAGE_ARGS",              0x100F },
    { "DEVICE_MAX_MEM_ALLOC_SIZE",                0x1010 },
    { "DEVICE_IMAGE2D_MAX_WIDTH",                 0x1011 },
    { "DEVICE_IMAGE2D_MAX_HEIGHT",                0x1012 },
    { "DEVICE_IMAGE3D_MAX_WIDTH",                 0x1013 },
    { "DEVICE_IMAGE3D_MAX_HEIGHT",                0x1014 },
    { "DEVICE_IMAGE3D_MAX_DEPTH",                 0x1015 },
    { "DEVICE_IMAGE_SUPPORT",                     0x1016 },
    { "DEVICE_MAX_PARAMETER_SIZE",                0x1017 },
    { "DEVICE_MAX_SAMPLERS",                      0x1018 },
    { "DEVICE_MEM_BASE_ADDR_ALIGN",               0x1019 },
    { "DEVICE_MIN_DATA_TYPE_ALIGN_SIZE",          0x101A },
    { "DEVICE_SINGLE_FP_CONFIG",                  0x101B },
    { "DEVICE_GLOBAL_MEM_CACHE_TYPE",             0x101C },
    { "DEVICE_GLOBAL_MEM_CACHELINE_SIZE",         0x101D },
    { "DEVICE_GLOBAL_MEM_CACHE_SIZE",             0x101E },
    { "DEVICE_GLOBAL_MEM_SIZE",                   0x101F },
    { "DEVICE_MAX_CONSTANT_BUFFER_SIZE",          0x1020 },
    { "DEVICE_MAX_CONSTANT_ARGS",                 0x1021 },
    { "DEVICE_LOCAL_MEM_TYPE",                    0x1022 },
    { "DEVICE_LOCAL_MEM_SIZE",                    0x1023 },
    { "DEVICE_ERROR_CORRECTION_SUPPORT",          0x1024 },
    { "DEVICE_PROFILING_TIMER_RESOLUTION",        0x1025 },
    { "DEVICE_ENDIAN_LITTLE",                     0x1026 },
    { "DEVICE_AVAILABLE",                         0x1027 },
    { "DEVICE_COMPILER_AVAILABLE",                0x1028 },
    { "DEVICE_EXECUTION_CAPABILITIES",            0x1029 },
    { "DEVICE_QUEUE_PROPERTIES",                  0x102A },
    { "DEVICE_NAME",                              0x102B },
    { "DEVICE_VENDOR",                            0x102C },
    { "DRIVER_VERSION",                           0x102D },
    { "DEVICE_PROFILE",                           0x102E },
    { "DEVICE_VERSION",                           0x102F },
    { "DEVICE_EXTENSIONS",                        0x1030 },
    { "DEVICE_PLATFORM",                          0x1031 },
    /* 0x1032 reserved for CL_DEVICE_DOUBLE_FP_CONFIG */
    /* 0x1033 reserved for CL_DEVICE_HALF_FP_CONFIG */
    { "DEVICE_PREFERRED_VECTOR_WIDTH_HALF",       0x1034 },
    { "DEVICE_HOST_UNIFIED_MEMORY",               0x1035 },
    { "DEVICE_NATIVE_VECTOR_WIDTH_CHAR",          0x1036 },
    { "DEVICE_NATIVE_VECTOR_WIDTH_SHORT",         0x1037 },
    { "DEVICE_NATIVE_VECTOR_WIDTH_INT",           0x1038 },
    { "DEVICE_NATIVE_VECTOR_WIDTH_LONG",          0x1039 },
    { "DEVICE_NATIVE_VECTOR_WIDTH_FLOAT",         0x103A },
    { "DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE",        0x103B },
    { "DEVICE_NATIVE_VECTOR_WIDTH_HALF",          0x103C },
    { "DEVICE_OPENCL_C_VERSION",                  0x103D },
    /* cl_device_fp_config - bitfield */
    { "FP_DENORM",                                (1 << 0) },
    { "FP_INF_NAN",                               (1 << 1) },
    { "FP_ROUND_TO_NEAREST",                      (1 << 2) },
    { "FP_ROUND_TO_ZERO",                         (1 << 3) },
    { "FP_ROUND_TO_INF",                          (1 << 4) },
    { "FP_FMA",                                   (1 << 5) },
    { "FP_SOFT_FLOAT",                            (1 << 6) },
    /* cl_device_mem_cache_type */
    { "NONE",                                     0x0 },
    { "READ_ONLY_CACHE",                          0x1 },
    { "READ_WRITE_CACHE",                         0x2 },
    /* cl_device_local_mem_type */
    { "LOCAL",                                    0x1 },
    { "GLOBAL",                                   0x2 },
    /* cl_device_exec_capabilities - bitfield */
    { "EXEC_KERNEL",                              (1 << 0) },
    { "EXEC_NATIVE_KERNEL",                       (1 << 1) },
    /* cl_command_queue_properties - bitfield */
    { "QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE",      (1 << 0) },
    { "QUEUE_PROFILING_ENABLE",                   (1 << 1) },
    /* cl_context_info  */
    { "CONTEXT_REFERENCE_COUNT",                  0x1080 },
    { "CONTEXT_DEVICES",                          0x1081 },
    { "CONTEXT_PROPERTIES",                       0x1082 },
    { "CONTEXT_NUM_DEVICES",                      0x1083 },
    /* cl_context_info + cl_context_properties */
    { "CONTEXT_PLATFORM",                         0x1084 },
    /* cl_command_queue_info */
    { "QUEUE_CONTEXT",                            0x1090 },
    { "QUEUE_DEVICE",                             0x1091 },
    { "QUEUE_REFERENCE_COUNT",                    0x1092 },
    { "QUEUE_PROPERTIES",                         0x1093 },
    /* cl_mem_flags - bitfield */
    { "MEM_READ_WRITE",                           (1 << 0) },
    { "MEM_WRITE_ONLY",                           (1 << 1) },
    { "MEM_READ_ONLY",                            (1 << 2) },
    { "MEM_USE_HOST_PTR",                         (1 << 3) },
    { "MEM_ALLOC_HOST_PTR",                       (1 << 4) },
    { "MEM_COPY_HOST_PTR",                        (1 << 5) },
    /* cl_channel_order */
    { "R",                                        0x10B0 },
    { "A",                                        0x10B1 },
    { "RG",                                       0x10B2 },
    { "RA",                                       0x10B3 },
    { "RGB",                                      0x10B4 },
    { "RGBA",                                     0x10B5 },
    { "BGRA",                                     0x10B6 },
    { "ARGB",                                     0x10B7 },
    { "INTENSITY",                                0x10B8 },
    { "LUMINANCE",                                0x10B9 },
    { "Rx",                                       0x10BA },
    { "RGx",                                      0x10BB },
    { "RGBx",                                     0x10BC },
    /* cl_channel_type */
    { "SNORM_INT8",                               0x10D0 },
    { "SNORM_INT16",                              0x10D1 },
    { "UNORM_INT8",                               0x10D2 },
    { "UNORM_INT16",                              0x10D3 },
    { "UNORM_SHORT_565",                          0x10D4 },
    { "UNORM_SHORT_555",                          0x10D5 },
    { "UNORM_INT_101010",                         0x10D6 },
    { "SIGNED_INT8",                              0x10D7 },
    { "SIGNED_INT16",                             0x10D8 },
    { "SIGNED_INT32",                             0x10D9 },
    { "UNSIGNED_INT8",                            0x10DA },
    { "UNSIGNED_INT16",                           0x10DB },
    { "UNSIGNED_INT32",                           0x10DC },
    { "HALF_FLOAT",                               0x10DD },
    { "FLOAT",                                    0x10DE },
    /* cl_mem_object_type */
    { "MEM_OBJECT_BUFFER",                        0x10F0 },
    { "MEM_OBJECT_IMAGE2D",                       0x10F1 },
    { "MEM_OBJECT_IMAGE3D",                       0x10F2 },
    /* cl_mem_info */
    { "MEM_TYPE",                                 0x1100 },
    { "MEM_FLAGS",                                0x1101 },
    { "MEM_SIZE",                                 0x1102 },
    { "MEM_HOST_PTR",                             0x1103 },
    { "MEM_MAP_COUNT",                            0x1104 },
    { "MEM_REFERENCE_COUNT",                      0x1105 },
    { "MEM_CONTEXT",                              0x1106 },
    { "MEM_ASSOCIATED_MEMOBJECT",                 0x1107 },
    { "MEM_OFFSET",                               0x1108 },
    /* cl_image_info */
    { "IMAGE_FORMAT",                             0x1110 },
    { "IMAGE_ELEMENT_SIZE",                       0x1111 },
    { "IMAGE_ROW_PITCH",                          0x1112 },
    { "IMAGE_SLICE_PITCH",                        0x1113 },
    { "IMAGE_WIDTH",                              0x1114 },
    { "IMAGE_HEIGHT",                             0x1115 },
    { "IMAGE_DEPTH",                              0x1116 },
    /* cl_addressing_mode */
    { "ADDRESS_NONE",                             0x1130 },
    { "ADDRESS_CLAMP_TO_EDGE",                    0x1131 },
    { "ADDRESS_CLAMP",                            0x1132 },
    { "ADDRESS_REPEAT",                           0x1133 },
    { "ADDRESS_MIRRORED_REPEAT",                  0x1134 },
    /* cl_filter_mode */
    { "FILTER_NEAREST",                           0x1140 },
    { "FILTER_LINEAR",                            0x1141 },
    /* cl_sampler_info */
    { "SAMPLER_REFERENCE_COUNT",                  0x1150 },
    { "SAMPLER_CONTEXT",                          0x1151 },
    { "SAMPLER_NORMALIZED_COORDS",                0x1152 },
    { "SAMPLER_ADDRESSING_MODE",                  0x1153 },
    { "SAMPLER_FILTER_MODE",                      0x1154 },
    /* cl_map_flags - bitfield */
    { "MAP_READ",                                 (1 << 0) },
    { "MAP_WRITE",                                (1 << 1) },
    /* cl_program_info */
    { "PROGRAM_REFERENCE_COUNT",                  0x1160 },
    { "PROGRAM_CONTEXT",                          0x1161 },
    { "PROGRAM_NUM_DEVICES",                      0x1162 },
    { "PROGRAM_DEVICES",                          0x1163 },
    { "PROGRAM_SOURCE",                           0x1164 },
    { "PROGRAM_BINARY_SIZES",                     0x1165 },
    { "PROGRAM_BINARIES",                         0x1166 },
    /* cl_program_build_info */
    { "PROGRAM_BUILD_STATUS",                     0x1181 },
    { "PROGRAM_BUILD_OPTIONS",                    0x1182 },
    { "PROGRAM_BUILD_LOG",                        0x1183 },
    /* cl_build_status */
    { "BUILD_SUCCESS",                            0 },
    { "BUILD_NONE",                               -1 },
    { "BUILD_ERROR",                              -2 },
    { "BUILD_IN_PROGRESS",                        -3 },
    /* cl_kernel_info */
    { "KERNEL_FUNCTION_NAME",                     0x1190 },
    { "KERNEL_NUM_ARGS",                          0x1191 },
    { "KERNEL_REFERENCE_COUNT",                   0x1192 },
    { "KERNEL_CONTEXT",                           0x1193 },
    { "KERNEL_PROGRAM",                           0x1194 },
    /* cl_kernel_work_group_info */
    { "KERNEL_WORK_GROUP_SIZE",                   0x11B0 },
    { "KERNEL_COMPILE_WORK_GROUP_SIZE",           0x11B1 },
    { "KERNEL_LOCAL_MEM_SIZE",                    0x11B2 },
    { "KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE",0x11B3 },
    { "KERNEL_PRIVATE_MEM_SIZE",                  0x11B4 },
    /* cl_event_info  */
    { "EVENT_COMMAND_QUEUE",                      0x11D0 },
    { "EVENT_COMMAND_TYPE",                       0x11D1 },
    { "EVENT_REFERENCE_COUNT",                    0x11D2 },
    { "EVENT_COMMAND_EXECUTION_STATUS",           0x11D3 },
    { "EVENT_CONTEXT",                            0x11D4 },
    /* cl_command_type */
    { "COMMAND_NDRANGE_KERNEL",                   0x11F0 },
    { "COMMAND_TASK",                             0x11F1 },
    { "COMMAND_NATIVE_KERNEL",                    0x11F2 },
    { "COMMAND_READ_BUFFER",                      0x11F3 },
    { "COMMAND_WRITE_BUFFER",                     0x11F4 },
    { "COMMAND_COPY_BUFFER",                      0x11F5 },
    { "COMMAND_READ_IMAGE",                       0x11F6 },
    { "COMMAND_WRITE_IMAGE",                      0x11F7 },
    { "COMMAND_COPY_IMAGE",                       0x11F8 },
    { "COMMAND_COPY_IMAGE_TO_BUFFER",             0x11F9 },
    { "COMMAND_COPY_BUFFER_TO_IMAGE",             0x11FA },
    { "COMMAND_MAP_BUFFER",                       0x11FB },
    { "COMMAND_MAP_IMAGE",                        0x11FC },
    { "COMMAND_UNMAP_MEM_OBJECT",                 0x11FD },
    { "COMMAND_MARKER",                           0x11FE },
    { "COMMAND_ACQUIRE_GL_OBJECTS",               0x11FF },
    { "COMMAND_RELEASE_GL_OBJECTS",               0x1200 },
    { "COMMAND_READ_BUFFER_RECT",                 0x1201 },
    { "COMMAND_WRITE_BUFFER_RECT",                0x1202 },
    { "COMMAND_COPY_BUFFER_RECT",                 0x1203 },
    { "COMMAND_USER",                             0x1204 },
    /* command execution status */
    { "COMPLETE",                                 0x0 },
    { "RUNNING",                                  0x1 },
    { "SUBMITTED",                                0x2 },
    { "QUEUED",                                   0x3 },
    /* cl_buffer_create_type  */
    { "BUFFER_CREATE_TYPE_REGION",                0x1220 },
    /* cl_profiling_info  */
    { "PROFILING_COMMAND_QUEUED",                 0x1280 },
    { "PROFILING_COMMAND_SUBMIT",                 0x1281 },
    { "PROFILING_COMMAND_START",                  0x1282 },
    { "PROFILING_COMMAND_END",                    0x1283 },
    { NULL }
  };
}

#endif
