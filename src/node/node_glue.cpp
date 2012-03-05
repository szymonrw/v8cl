#include "../v8cl.h"
#include <node.h>

void InitCL (v8::Handle<v8::Object> target) {
  v8::HandleScope scope;
  v8cl::SetWebCL(target);
}

NODE_MODULE(cl, InitCL)
