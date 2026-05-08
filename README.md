# C Multi-Threaded HTTP server

A static, multithreaded HTTP server written in C

This server handles multiple client connections concurrently and serves HTTP responses. It is primarily intended for learning / local usage.

---

## Features

- Multi-threaded request handling (concurrent clients)
- HTTP/1.1 compatible request parsing 
- Logging of requests and errors (requests are only logged in debug mode)

---

## Requirements

- Linux/MacOS (POSIX threads are used)
- C compiler (GCC and Clang are both supported)
- Make and CMake

---

## Build and Run
```bash
mkdir build && cd build
cmake .. -DCMAKE_C_COMPILER=clang -DDEBUG_MODE=ON # Change the flags as needed
make
./build/http_server
