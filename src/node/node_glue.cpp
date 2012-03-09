#include "../v8cl.h"
#include <node.h>

using namespace v8cl;

// Function called in OpenCL-spawned thread
void ShakeNodeEventLoop (void* uv_handle) {
  uv_async_send((uv_async_t*) uv_handle);
}

static void DeleteHandle (uv_handle_t* handle) {
  free(handle);
}

// Function called in node's event loop
static void InvokeHandler (uv_async_t* handle, int status) {
  InvokeBackInEventLoop((EventHandler*) handle->data);
  uv_close((uv_handle_t*) handle, DeleteHandle);
}

static void* RegisterHandler (EventHandler* handler) {
  uv_async_t *uv_handle = (uv_async_t*) malloc(sizeof(uv_async_t));
  uv_async_init(uv_default_loop(), uv_handle, InvokeHandler);
  uv_handle->data = handler;
  return uv_handle;
}

void InitCL (Handle<Object> target) {
  HandleScope scope;
  EventSupport eventsImpl = { RegisterHandler, ShakeNodeEventLoop };
  SetWebCL(target, eventsImpl);
}

NODE_MODULE(cl, InitCL)
