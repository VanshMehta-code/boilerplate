#pragma once
#include <atomic>
#include <future>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <curl/curl.h>

struct Response {
  int status;
  std::string content;
  Response(int status, std::string content) : status(status), content(content) {}
};

struct Data {
  std::string url;
  std::vector<std::string> header;
  std::string json;
  int waitTime; 
  Data (std::string url, std::vector<std::string> header, nlohmann::json json, int waitTime):url(url), header(header), waitTime(waitTime) {
    this->json = json.dump();
  }
  Data (std::string url, std::vector<std::string> header, int waitTime): url(url), header(header ), waitTime(waitTime) {}
};

class Client {
  static size_t write_func (void *ptr, size_t size, size_t nmemb, void *userData){
  std::string *buf = (std::string*)userData;
  buf->append((char*)ptr,size*nmemb);
  return size * nmemb;
}
  public:
  Response get (Data data);
  Response post (Data data);
};

class AsyncClient {
  public:
  std::future<Response> get (Data data);
  std::future<Response> post (Data data); 
};

class Async {
  int size = 1;
  std::atomic<int> curr = 0;
  public:
  AsyncClient client;
  bool handle ();
  void initSemaphore (int handleRequest);
  std::future<bool> semaphore();
  std::future<void> sleep (int second);
};