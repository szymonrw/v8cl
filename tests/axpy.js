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

var yh = new Float64Array(40 * 1024  * 1024);
var xh = new Float64Array(yh.length);

yh[0] = 0;
xh[0] = 0;
for (var i = 1; i < yh.length; ++i) {
  yh[i] = yh[i-1] + 1;
  xh[i] = xh[i-1] + 10;
}

var platforms = cl.getPlatformIDs();
console.log("platforms", platforms);
var device = cl.getDeviceIDs(platforms[0], cl.DEVICE_TYPE_ALL)[0];
var context = cl.createContext(null, [device]);

var queue = cl.createCommandQueue(context, device, 0);

var src = [
  "__kernel void axpy (__global double *y, __global double *x, const double a) {",
  "  int i = get_group_id(0);",
  "  y[i] += a * x[i];",
  "}"
].join('\n');

program = cl.createProgramWithSource(context, src);
cl.buildProgram(program, [device], "");
console.log(cl.getProgramBuildInfo(program, device, cl.PROGRAM_BUILD_LOG));

var axpy = cl.createKernel(program, "axpy");
// var kernels = cl.createKernelsInProgram(program);

var yd = cl.createBuffer(context, cl.MEM_READ_WRITE, yh.byteLength);
var xd = cl.createBuffer(context, cl.MEM_READ_ONLY, xh.byteLength);

cl.setKernelArg(axpy, 0, 8, yd);
cl.setKernelArg(axpy, 1, 8, xd);
cl.setKernelArg(axpy, 2, 8, new Float64Array([5]));
//cl.setKernelArg(axpy, 2, 8, new Buffer([1,2,3,4,5,6,7,8]));

events = [];
events.push(cl.enqueueWriteBuffer(queue, yd, 0, yh));
//console.log("yh refcount: ")
events.push(cl.enqueueWriteBuffer(queue, xd, 0, xh)); 
cl.setEventCallback(events[1], cl.COMPLETE, null, xh);
events.push(cl.enqueueNDRangeKernel(queue, axpy, [], [yh.length], [1]));
events.push(cl.enqueueReadBuffer(queue, yd, 0, yh));


spitArray(yh, "y");
console.log("   + 5 *");
spitArray(xh, "x");
console.log("   =");

//cl.releaseMemObject(yd);

//console.log(events);
cl.setEventCallback(events[3], cl.COMPLETE, function(event, status, data) {
  console.log("EVENT", status, data);
  spitArray(yh, "y");
}, ["to są dane", 1,2,3]);

// cl.finish(queue);
cl.flush(queue);

};



f();

for (var i = 0; i < 1000; ++i) {
  gc();
}

// setTimeout(function() {
//   console.log("bye");
// },30000);