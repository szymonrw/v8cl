#include "v8cl.h"

namespace v8cl {

  void DisposeOpenCLObject (Persistent<Value> value, void* f) {
    if (f && value->IsObject()) {
      Local<Object> object = value->ToObject();
      if (object->InternalFieldCount()) {
        int32_t (CALL *release) (void* smth);
        *(void**) &release = f;
        void *ptr = object->GetPointerFromInternalField(0);

        int32_t error = release(ptr);
      }
    }

    value.Dispose();
    value.Clear();
  }

  // Callback stuff for SetEventCallback
  void InvokedByOpenCL (void* event, int32_t type, void* data) {
    if (data) {
      EventHandler* handler = (EventHandler*) data;
      if (handler->events.shake) {
        handler->type = type;
        handler->events.shake(handler->impl_handle);
      }
    } else {
      // TODO: what here?
      //cout << "bad" << endl;
    }
  }

  void InvokeBackInEventLoop (EventHandler* handler) {
    if (handler->f->IsFunction()) {
      Persistent<Function> f = Persistent<Function>::Cast<Value>(handler->f);
      Handle<Value> args[3];
      args[0] = handler->event;//External::Wrap(handler->event);
      args[1] = Int32::New(handler->type);
      args[2] = Local<Value>::New(handler->data);
      f->Call(f, 3, args);
      f.Dispose();
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
