#include "v8cl.h"

namespace v8cl {

  void DisposeOpenCLObject (Persistent<Value> value, void* release) {
    if (release && value->IsObject()) {
      Local<Object> object = value->ToObject();
      if (object->InternalFieldCount()) {
        void *ptr = object->GetPointerFromInternalField(0);

        int32_t (CALL *clRelease) (void* smth);
        *(void**) &clRelease = release;

        clRelease(ptr); // Returned value is omitted. Check when debugging.
      }
    }

    value.Dispose();
    value.Clear();
  }

  // Callback stuff for SetEventCallback
  void FireEvent (void* event, int32_t type, void* data) {
    if (data) {
      EventHandler* handler = (EventHandler*) data;
      if (handler->events.shake) {
        handler->type = type;
        handler->events.shake(handler->implHandle);
      }
    }
  }

  void HandleEvent (EventHandler* handler) {
    if (handler->f->IsFunction()) {
      Persistent<Function> f = Persistent<Function>::Cast<Value>(handler->f);
      Handle<Value> args[3];
      args[0] = handler->event;
      args[1] = Int32::New(handler->type);
      args[2] = Local<Value>::New(handler->data);
      f->Call(f, 3, args);
      f.Clear();
    }

    handler->f.Dispose();
    handler->f.Clear();
    handler->data.Dispose();
    handler->data.Clear();
    handler->event.Dispose();
    handler->event.Clear();
    delete handler;
  }
}
