# cpp-boilerplate

A collection of C++ boilerplates that make systems-level coding feel as clean as Python. Each boilerplate is a standalone starting point for a specific domain — HTTP clients, ML inference, CUDA, and servers.

---

## Philosophy

C++ gives you full control but at the cost of boilerplate. This repo fixes that by giving you pre-wired, production-aware starting points so you spend time on logic, not setup.

---

## Boilerplates

### ✅ HTTP Client (`/http-client`)
> Status: Done

Sync and async HTTP client built on libcurl + nlohmann/json. Feels like using `httpx` in Python.

**Features**
- Sync `GET` / `POST` via `Client`
- Async `GET` / `POST` via `AsyncClient` (`std::async`)
- Semaphore for concurrency control
- JSON body serialization via nlohmann/json
- Header and timeout support per request

**Dependencies**
- `libcurl`
- `nlohmann/json`

**Quick start**
```cpp
std::vector<std::string> headers = {
    "Content-Type: application/json",
    "Authorization: Bearer my_token"
};

// Sync GET
Data req("https://api.example.com/data", headers, 10);
std::string res = Client::get(req);

// Async POST
nlohmann::json payload = {{"prompt", "hello"}, {"model", "gpt-4"}};
Data req2("https://api.example.com/chat", headers, payload, 30);
auto future = AsyncClient().post(req2);
std::string res2 = future.get();
```

---

### 🔲 ML Models (`/ml`)
> Status: Planned

Run inference on ONNX / TensorFlow Lite / llama.cpp models with a clean API. Feels like using `transformers` or `torch` in Python.

**Planned features**
- Model loader abstraction (ONNX Runtime, llama.cpp)
- Tokenizer helpers
- Batched inference
- Async inference calls

**Planned dependencies**
- `onnxruntime`
- `llama.cpp`

---

### 🔲 CUDA / GPU (`/cuda`)
> Status: Planned

GPU compute boilerplate with memory management helpers and kernel launcher wrappers. Feels like writing `numba` or `cupy` but in C++.

**Planned features**
- Device/host memory RAII wrappers
- Kernel launch helpers with error checking
- cuBLAS / cuDNN setup
- Multi-GPU support

**Planned dependencies**
- CUDA Toolkit
- cuBLAS
- cuDNN

---

### 🔲 Server (`/server`)
> Status: Planned

HTTP server boilerplate with routing, middleware, and JSON request/response handling. Feels like `FastAPI` in Python.

**Planned features**
- Route registration (`GET`, `POST`, `PUT`, `DELETE`)
- JSON body parsing
- Middleware chain
- Async request handling

**Planned dependencies**
- `cpp-httplib` or `crow`
- `nlohmann/json`

---

## Project Structure

```
cpp-boilerplate/
├── http-client/
│   ├── src/
│   │   └── main.cpp
│   ├── lib/
│   │   ├── client.cpp
│   │   └── client.h
│   ├── include/
│   └── CMakeLists.txt
├── ml/
├── cuda/
├── server/
└── README.md
```

---

## Building (per boilerplate)

```bash
cd http-client
cmake -B build
cmake --build build
./build/boilerplate
```

CMake is configured to auto-detect all `.cpp` files in `src/` and `lib/` — just drop your files in and rebuild.

---

## Requirements

- C++17 or later
- CMake 3.20+
- Per-boilerplate dependencies listed above
