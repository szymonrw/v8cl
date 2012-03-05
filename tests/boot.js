var cl = require('cl');

console.log("errors?", cl.loadingErrors);

platform = cl.clGetPlatformIDs()[0];

console.log("platforms", cl.clGetPlatformIDs());

[cl.CL_PLATFORM_PROFILE, cl.CL_PLATFORM_VERSION, cl.CL_PLATFORM_NAME, cl.CL_PLATFORM_EXTENSIONS].forEach( function(info) {
  console.log(info, cl.clGetPlatformInfo(platform, info));
});

console.log(cl.clGetDeviceIDs(platform, cl.CL_DEVICE_TYPE_CPU | cl.CL_DEVICE_TYPE_GPU));
console.log(cl.clGetDeviceIDs(platform, cl.CL_DEVICE_TYPE_ALL));

device = cl.clGetDeviceIDs(platform, cl.CL_DEVICE_TYPE_ALL)[0];
console.log('device', device);

//console.log(cl.clGetDeviceInfo(device, cl.CL_DEVICE_NAME));
console.log(cl.clGetDeviceInfo(device, cl.CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS));

console.log(cl.clGetDeviceInfo(device, cl.CL_DEVICE_MAX_WORK_ITEM_SIZES));

// context
context = cl.clCreateContext([cl.CL_CONTEXT_PLATFORM, platform], [device]);
console.log(context);
console.log(cl.clGetContextInfo(context, cl.CL_CONTEXT_PROPERTIES));
queue = cl.clCreateCommandQueue(context, device, 0);
context2 = cl.clCreateContext(null, [device]);
console.log(context2);
cl.clRetainContext(context2);
cl.clReleaseContext(context2);
console.log(cl.clGetContextInfo(context2, cl.CL_CONTEXT_DEVICES));
queue2 = cl.clCreateCommandQueue(context2, device, cl.CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | cl.CL_QUEUE_PROFILING_ENABLE);
console.log(queue2);
cl.clRetainCommandQueue(queue2);
cl.clReleaseCommandQueue(queue2);

var buffer = cl.clCreateBuffer(context, cl.CL_MEM_WRITE_ONLY, 1024);
console.log('buf1', buffer);

var buffer2 = cl.clCreateBuffer(context, cl.CL_MEM_READ_ONLY, 1024);
console.log('buf2', buffer2);
console.log('const', cl.CL_BUFFER_CREATE_TYPE_REGION);
var subbuffer = cl.clCreateSubBuffer(buffer, cl.CL_MEM_WRITE_ONLY, cl.CL_BUFFER_CREATE_TYPE_REGION, { origin: 0, size: 10 });
console.log(subbuffer);

var img2dformat = { image_channel_order: cl.CL_RGBA, image_channel_data_type: cl.CL_UNSIGNED_INT8 };
var img2d = cl.clCreateImage2D(context, cl.CL_MEM_WRITE_ONLY, img2dformat, 100, 300);
console.log(img2d);
console.log(img2dformat);
console.log(cl.clGetImageInfo(img2d, cl.CL_IMAGE_FORMAT));

var img3d = cl.clCreateImage3D(context, cl.CL_MEM_WRITE_ONLY, {
  image_channel_order: cl.CL_RGBA, image_channel_data_type: cl.CL_UNSIGNED_INT16
}, 100, 300, 200);
console.log(img3d);

//console.log("2d img formats", cl.clGetSupportedImageFormats(context, cl.CL_MEM_WRITE_ONLY, cl.  CL_MEM_OBJECT_IMAGE2D));
//console.log("2d img formats", cl.clGetSupportedImageFormats(context, cl.CL_MEM_WRITE_ONLY, cl.CL_MEM_OBJECT_IMAGE3D));

var sampler = cl.clCreateSampler(context, false, cl.CL_ADDRESS_MIRRORED_REPEAT, cl.CL_FILTER_LINEAR);
console.log("sampler", sampler);
cl.clRetainSampler(sampler);
cl.clReleaseSampler(sampler);

var src = [
  "__kernel void axpy (const int y, __global double *x, const double a) {}",
  "__kernel void k2 (const int a) {}"
  // "  int i = get_group_id(0);",
  // "  y[i] += a * x[i];",
  // "}"
].join("\n");
console.log(src);

var program = cl.clCreateProgramWithSource(context, src);
console.log(program);
cl.clRetainProgram(program);
cl.clReleaseProgram(program);

console.log("programctx", cl.clGetProgramInfo(program, cl.CL_PROGRAM_CONTEXT));
console.log("prgdevices", cl.clGetProgramInfo(program, cl.CL_PROGRAM_DEVICES));
console.log("programsrc", cl.clGetProgramInfo(program, cl.CL_PROGRAM_SOURCE));

try {
  cl.clBuildProgram(program, [device], "");
  console.log(cl.clGetProgramInfo(program, cl.CL_PROGRAM_BINARY_SIZES));
  console.log(cl.clGetProgramInfo(program, cl.CL_PROGRAM_BINARIES));

  var axpy = cl.clCreateKernel(program, "axpy");
  console.log("kernel", axpy);
  cl.clRetainKernel(axpy);
  cl.clReleaseKernel(axpy);
  cl.clSetKernelArg(axpy, 0, 4, "abcdefghijklmno");
  var kernels = cl.clCreateKernelsInProgram(program);
  console.log("kernels", kernels);
  kernels.forEach(function(kernel) {
    console.log("name", cl.clGetKernelInfo(kernel, cl.CL_KERNEL_FUNCTION_NAME));
    console.log("args", cl.clGetKernelInfo(kernel, cl.CL_KERNEL_NUM_ARGS));
    console.log("refs", cl.clGetKernelInfo(kernel, cl.CL_KERNEL_REFERENCE_COUNT));
    console.log("ctx ", cl.clGetKernelInfo(kernel, cl.CL_KERNEL_CONTEXT));
    console.log("prg ", cl.clGetKernelInfo(kernel, cl.CL_KERNEL_PROGRAM));
    console.log("wgsz", cl.clGetKernelWorkGroupInfo(kernel, device, cl.CL_KERNEL_COMPILE_WORK_GROUP_SIZE));
  });
} catch (e) {
  console.log(e);
  console.log("status", cl.clGetProgramBuildInfo(program, device, cl.CL_PROGRAM_BUILD_STATUS));
  console.log("option", cl.clGetProgramBuildInfo(program, device, cl.CL_PROGRAM_BUILD_OPTIONS));
  console.log("log   ", cl.clGetProgramBuildInfo(program, device, cl.CL_PROGRAM_BUILD_LOG));
}

cl.clFlush(queue2);
cl.clFinish(queue2);

var natarr = new Uint32Array([1,2,3,4]);
var subarr = natarr.subarray(1, 100);
cl.clEnqueueReadBuffer(queue, buffer, 10, subarr);
var node_buff = new Buffer("asdf");
cl.clEnqueueWriteBuffer(queue, buffer, 10, node_buff);
cl.clEnqueueReadBuffer(queue, buffer, 10, node_buff);
cl.clFinish(queue);

// Not working:
//console.log(cl.clGetMemObjectInfo(subbuffer, cl.CL_MEM_TYPE));
//console.log("sampler norm_coords", cl.clGetSamplerInfo(sampler, cl.CL_SAMPLER_CONTEXT));
//console.log(cl.clCreateContextFromType([cl.CL_CONTEXT_PLATFORM, platform], cl.CL_DEVICE_TYPE_ALL));

// shouldFail:
// context3 = cl.clCreateContext();
// context3 = cl.clCreateContext(null, null);
