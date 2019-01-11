class Set : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit Set();
  ~Set();
  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Add(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Delete(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Has(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
  std::unordered_set<int> set_;
};
