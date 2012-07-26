#ifndef _CALLBACKS_H
#define _CALLBACKS_H

#include "v8cl.h"

namespace v8cl {
  void DisposeOpenCLObject (Persistent<Value> value, void* f);

  // Callback stuff for SetEventCallback
  void FireEvent (void* event, int32_t type, void* data);
  void HandleEvent (EventHandler* handler);
}

#endif
