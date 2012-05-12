var f = function() {
  var cl = require('cl');
  var util = require('util');

  console.log("errors?", cl.loadingErrors);

  function spitArray(arr, name) {
    if (name) process.stdout.write(util.format("%s: ", name));
    for (var i = 0; i < 10; ++i) {
      process.stdout.write(util.format("%d ", arr[i]));
    }
    process.stdout.write('... ');
    for (var i = arr.length - 10; i < arr.length; ++i) {
      process.stdout.write(util.format("%d ", arr[i]));
    }
    process.stdout.write("\n");
  }

  var platforms = cl.getPlatformIDs();
  console.log("platforms", platforms);
  var device = cl.getDeviceIDs(platforms[0], cl.DEVICE_TYPE_ALL)[0];
  var context = cl.createContext(null, [device]);

  var src = [
    "__kernel void axpy1 (__global double *y, __global double *x, const double a) {",
    "  int i = get_group_id(0);",
    "  y[i] += a * x[i];",
    "}",
    "__kernel void axpy2 (__global double *y, __global double *x, const double a) {",
    "  int i = get_group_id(0);",
    "  y[i] += a * x[i];",
    "}",
    "__kernel void axpy3 (__global double *y, __global double *x, const double a) {",
    "  int i = get_group_id(0);",
    "  y[i] += a * x[i];",
    "}",
    "__kernel void axpy4 (__global double *y, __global double *x, const double a) {",
    "  int i = get_group_id(0);",
    "  y[i] += a * x[i];",
    "}"
  ].join('\n');

  var program = cl.createProgramWithSource(context, src);
  cl.buildProgram(program, [device], "");
  console.log(cl.getProgramBuildInfo(program, device, cl.PROGRAM_BUILD_LOG));

  var kernel_list = cl.createKernelsInProgram(program);
  var kernels = {};
  kernel_list.forEach(function (kernel) {
    var name = cl.getKernelInfo(kernel, cl.KERNEL_FUNCTION_NAME);
    kernels[name] = kernel;
  });
  console.log(kernels);
};

f();