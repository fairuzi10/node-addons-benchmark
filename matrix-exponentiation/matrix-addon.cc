#include <nan.h>
#include <iostream>
#include <vector>
typedef std::vector<std::vector<long long>> mat;
const int MOD = 10000019;

// multiply matrix a and b, both having size nxn, in O(N^3)
mat multiply(mat A, mat B) {
  int n = A.size();
  mat result;
  for (int i = 0; i < n; i++) {
    result.push_back(std::vector<long long>());
    for (int j = 0; j < n; j++) {
      result[i].push_back(0);
      for (int k = 0; k < n; k++) {
        result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
      }
    }
  }
  return result;
}

// return M^p in O(N^3*log(p))
mat power(mat M, long long p) {
  if (p == 1) {
    return M;
  } else if (p % 2 == 1) {
    mat temp = power(M, p - 1);
    return multiply(temp, M);
  } else {
    mat temp = power(M, p / 2);
    return multiply(temp, temp);
  }
}

mat localValueToMat(v8::Local<v8::Value> v) {
  v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(v);

  int N = array->Length();
  mat ret;
  for (int i = 0; i < N; i++) {
    v8::Local<v8::Array> row = v8::Local<v8::Array>::Cast(array->Get(i));
    ret.push_back(std::vector<long long>());
    for (int j = 0; j < N; j++) {
      v8::Local<v8::Int32> el = v8::Local<v8::Int32>::Cast(row->Get(j));
      ret[i].push_back(el->Value());
    }
  }
  return ret;
}

v8::Local<v8::Array> matToLocalArray(mat V) {
  int N = V.size();
  v8::Local<v8::Array> ret = Nan::New<v8::Array>(N);
  for (int i = 0; i < N; i++) {
    v8::Local<v8::Array> row = Nan::New<v8::Array>(N);
    for (int j = 0; j < N; j++) {
      row->Set(j, Nan::New((int)V[i][j]));
    }
    ret->Set(i, row);
  }
  return ret;
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

  mat v = localValueToMat(info[0]);
  int p = info[1]->ToInt32()->Value();
  mat result = power(v, p);

  info.GetReturnValue().Set(matToLocalArray(result));
}

void Multiply(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsArray() || !info[1]->IsArray()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  mat A = localValueToMat(info[0]);
  mat B = localValueToMat(info[1]);
  mat result = multiply(A, B);
  info.GetReturnValue().Set(matToLocalArray(result));
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("power").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Power)->GetFunction());
  exports->Set(Nan::New("multiply").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Multiply)->GetFunction());
}

NODE_MODULE(addon, Init)
