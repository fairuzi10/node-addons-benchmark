#include <nan.h>
#include <unordered_set>
#include "schema.cc"

Nan::Persistent<v8::Function> Set::constructor;

Set::Set() {}

Set::~Set() {}

void Set::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Set").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // // Prototype
  Nan::SetPrototypeMethod(tpl, "add", Add);
  Nan::SetPrototypeMethod(tpl, "delete", Delete);
  Nan::SetPrototypeMethod(tpl, "has", Has);

  // constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("Set").ToLocalChecked(), tpl->GetFunction());
  constructor.Reset(tpl->GetFunction());
}

void Set::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new Set(...)`
    Set* obj = new Set();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `Set(...)`, turn into construct call.
    const int argc = 0;
    v8::Local<v8::Value> argv[argc] = {};
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void Set::Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsInt32()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }
  int value = info[0]->Int32Value();
  Set* obj = ObjectWrap::Unwrap<Set>(info.Holder());
  obj->set_.insert(value);
}

void Set::Delete(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsInt32()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }
  int value = info[0]->Int32Value();
  Set* obj = ObjectWrap::Unwrap<Set>(info.Holder());
  obj->set_.erase(value);
}

void Set::Has(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsInt32()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }
  int value = info[0]->Int32Value();
  Set* obj = ObjectWrap::Unwrap<Set>(info.Holder());
  std::unordered_set<int>::iterator it = obj->set_.find(value);
  bool contains = it != obj->set_.end();

  info.GetReturnValue().Set(Nan::New(contains));
}

void InitAll(v8::Local<v8::Object> exports) { Set::Init(exports); }

NODE_MODULE(addon, InitAll)
