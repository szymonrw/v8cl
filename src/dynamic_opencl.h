#ifndef _DYNAMIC_OPENCL_H
#define _DYNAMIC_OPENCL_H

#ifndef _WIN32
// Include POSIX headers on Unices

#include <dlfcn.h>
#define V8CL_OPENCL_LIB "libOpenCL.so"

#else
// Wrap around windows dyamic loader and mimic POSIX interface.

#include <windows.h>
#define V8CL_OPENCL_LIB "OpenCL.dll"
#define RTLD_LAZY 0
#define RTLD_LOCAL 0

static const char* dl_error = NULL;

const char* dlerror() {
  const char* err = dl_error;
  dl_error = NULL;
  return err;
}

void* dlopen(const char* libname, int flags) {
  void* lib = LoadLibrary(libname);
  if (!lib) {
    dl_error = libname;
    return NULL;
  } else {
    return lib;
  }
}

void* dlsym (void* lib, const char* name) {
  void* fn = GetProcAddress((HINSTANCE) lib, name);
  if (!fn) {
    dl_error = name;
    return NULL;
  } else {
    return fn;
  }
}
#endif

#endif
