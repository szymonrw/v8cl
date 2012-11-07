# V8 + OpenCL = V8CL

This is a thin OpenCL wrapper intended to be used in any V8-enabled application. It's tested on node.js but do not depend on it.

## Goals

- ✔ Dynamically linked at runtime (atm using dlopen/dlsym)
- ✔ C-style OpenCL API (not the C++ one, the OO wrapper can be potentially implemented in pure JS)
- ✔ Converts data returned from CL functions to readable JS objects
- ✔ Tested on node.js (as node.js module)
- ✔ Clean (almost declarative) internals
- ✔ Fairly close to the metal implementation
- ▓ Cover the whole OpenCL where possible

## Differences from OpenCL

V8CL is designed to be as close to original OpenCL as possible, making specific user documentation not necessary. However, some differences were made, with JavaScript specifics and user's convenience in mind.

To follow conventions from WebGL, all `CL_` and `cl` prefixes are dropped, so `CL_SUCCESS` is `cl.SUCCESS` and `clGetPlatformIDs` are `cl.getPlatformIDs` (where `cl` is name of the object where you imported V8CL).

### cl_error => Exceptions

All functions that return `cl_error` in V8CL return their meaningful value (like an array of platform ids is returned by `cl.getPlatformIDs()`).

All `cl_error` are converted to exceptions and thrown. Exception will contain name of the error as a string.

### Arguments & Return Values

V8CL converts JS arguments to appropriate native values and return values to sensible JS objects. What that means is when some OpenCL function returns, say, array of size_t, returned value will be JavaScript Array.

All OpenCL native objects are returned in form of `External` objects. They print like numbers in JS but they're not.

```js
cl.getPlatformIDs();
=> [ 2745304 ]
```
In all `get*Info` functions allocation is done automatically for the user and result is translated to JavaScript object. For example:

```js
cl.getPlatformInfo(platform, cl.PLATFORM_NAME);
=> "Intel(R) OpenCL"
```
### Function-specific Differences

Where not specified, all arguments that give sizes of other arguments (as `num_devices` next to `device_list`) are dropped.

#### cl.createContext & cl.createContextFromType

First argument `properties` is translated from array. `callback` and `user_data` arguments are dropped at this time.

```js
var context = cl.createContext([cl.CONTEXT_PLATFORM, platform], [device]);
```
#### cl.createBuffer

`host_ptr` argument is dropped atm (TODO).

#### cl.createSubBuffer

`buffer_create_type` argument is translated from JavaScript object.

```js
var subbuffer = cl.createSubBuffer(buffer, cl.MEM_WRITE_ONLY,
                  cl.BUFFER_CREATE_TYPE_REGION,
                  { origin: 0, size: 10 });
```
#### cl.createImage2D & cl.createImage3D

`image_format` is translated from JavaScript object.
`host_ptr` argument is dropped (TODO).

```js
var img3d = cl.clCreateImage3D(context, cl.MEM_WRITE_ONLY, {
  image_channel_order: cl.RGBA,
  image_channel_data_type: cl.UNSIGNED_INT16
}, 100, 300, 200);
```
#### cl.createProgramWithSource

Takes only two arguments: `context` and program source code as one string (original OpenCL takes array of strings and concatenate them).

#### cl.setKernelArg

All arguments that are not buffers, samplers or images have to be passed as typed arrays (for example Int32Array). This guaranties memory and type safety. Moreover, it enables you to pass `long` values as an array of two `Int32`'s (or 8 `Int8`'s, etc.):

```js
cl.setKernelArg(kernel, 0, 8, new Int32Array([-1, -1]));
```
#### cl.enqueueReadBuffer & cl.enqueueWriteBuffer

`blocking_write` and `blocking_read` are dropped and fixed at `FALSE` to possibly disable blocking UI thread in a browser.

`ptr` argument have to be a typed array. `cb` argument (number of bytes to copy) is taken from it's size. If you want to pass only portion of the array, use it's
`subarray` method.

#### cl.enqueueNDRangeKernel

`global_work_offset` can be `null` or `[]`. `work_dim` is dropped and taken as a minimum of sizes of `global_work_offset` (if not `null` or `[]`), `global_work_size` and `local_work_size` arrays.

## Licence

MIT, see COPYING file.
