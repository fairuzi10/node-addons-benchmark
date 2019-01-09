#include <nan.h>
#include <iostream>
#include <vector>
typedef std::vector<std::vector<long long>> mat;
const int MOD = 1000000007;

// multiply matrix a and b, both having size nxn
mat multiply(mat a, mat b) {
    int n = a.size();
    mat result;
    for (int i = 0; i < n; i++) {
        result.push_back(std::vector<long long>());
        for (int j = 0; j < n; j++) {
            result[i].push_back(0);
            for (int k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + a[i][k]*b[k][j]) % MOD;
            }
        }
    }
    return result;
}

mat power(mat m, long long p) {
    if (p == 1) {
        return m;
    } else if (p % 2 == 1) {
        mat temp = power(m, p-1);
        return multiply(temp, m);
    } else {
        mat temp = power(m, p/2);
        return multiply(temp, temp);
    }
}

void Power(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsArray() || !info[1]->IsInt32()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  v8::Local<v8::Array> arg0 = v8::Local<v8::Array>::Cast(info[0]);

  int N = arg0->Length();
  mat v;
  for (int i = 0; i < N; i++) {
    v8::Local<v8::Array> row = v8::Local<v8::Array>::Cast(arg0->Get(i));
    v.push_back(std::vector<long long>());
    for (int j = 0; j < N; j++) {
      v8::Local<v8::Int32> el = v8::Local<v8::Int32>::Cast(row->Get(j));
      v[i].push_back(el->Value());
    }
  }

  int p = info[1]->ToInt32()->Value();
  mat result = power(v, p);

  v8::Local<v8::Array> ret = Nan::New<v8::Array>(N);
  for (int i = 0; i < N; i++) {
    v8::Local<v8::Array> row = Nan::New<v8::Array>(N);
    for (int j = 0; j < N; j++) {
      row->Set(j, Nan::New((int)result[i][j]));
    }
    ret->Set(i, row);
  }

  info.GetReturnValue().Set(ret);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("power").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Power)->GetFunction());
}

NODE_MODULE(addon, Init)
