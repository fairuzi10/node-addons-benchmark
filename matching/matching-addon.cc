#include <nan.h>
#include <string>

int countOccurrence(std::string str, std::string pattern) {
    int n = str.length();
    int m = pattern.length();

    if (n < m) {
        return 0;
    }

    long long base = 37;
    long long mod = 10000000000037;
    long long hashPattern = 0;
    for (int i = 0; i < m; i++) {
        hashPattern = (hashPattern*base + pattern[i]-'a'+1) % mod;
    }

    long long hashStr = 0;
    long long baseLast = 1;
    for (int i = 0; i < m; i++) {
        hashStr = (hashStr*base + str[i]-'a'+1) % mod;
        if (i < m-1) {
            baseLast = (baseLast*base) % mod;
        }
    }

    int ret = 0;
    if (hashStr == hashPattern) {
        ret++;
    }
    for (int i = m; i < n; i++) {
        // removing the last character
        hashStr = (hashStr - (str[i-m]-'a'+1)*baseLast) % mod;
        if (hashStr < 0) {
            hashStr += mod;
        }
        hashStr = (hashStr*base + str[i]-'a'+1) % mod;
        if (hashStr == hashPattern) {
            ret++;
        }
    }
    return ret;
}

void CountOccurrence(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsString() || !info[1]->IsString()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  std::string str = *Nan::Utf8String(info[0]);
  std::string pattern = *Nan::Utf8String(info[1]);
  v8::Local<v8::Int32> result = Nan::New(countOccurrence(str, pattern));

  info.GetReturnValue().Set(result);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("countOccurrence").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(CountOccurrence)->GetFunction());
}

NODE_MODULE(addon, Init)