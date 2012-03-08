#include "../v8cl.h"
#include <node.h>

using namespace v8cl;

static uv_async_t run_handler;

volatile EventHandler* event_handler;

// Function called in OpenCL-spawned thread
void ShakeNodeEventLoop (EventHandler* handler) {
  event_handler = handler;
  uv_async_send(&run_handler);
}

// Function called in node's event loop
static void InvokeHandler(uv_async_t* handle, int status) {
  cout << "lala" << endl;
  EventHandler *handler = (EventHandler*) event_handler;
  InvokeBackInEventLoop(handler);
}


void InitCL (Handle<Object> target) {
  HandleScope scope;
  uv_async_init(uv_default_loop(), &run_handler, InvokeHandler);
  SetWebCL(target, ShakeNodeEventLoop);
}

NODE_MODULE(cl, InitCL)
