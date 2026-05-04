#include <chrono>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/multi.h>
#include <future>
#include <thread>
#include "client.h" 



Response Client::get (Data data){
  CURL *curl = curl_easy_init();
  std::string response;
  long status;
  struct curl_slist *list = NULL;
  for (auto h: data.header) {
    list= curl_slist_append(list, h.c_str());
  }

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
  curl_easy_setopt(curl, CURLOPT_URL, data.url.c_str());
  curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, write_func);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA , &response);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
  curl_slist_free_all(list);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return Response((int)status, response);
}

Response Client::post (Data data){
  CURL *curl = curl_easy_init();

  std::string response;
  long status;
  struct curl_slist *list = NULL;
  for (auto h : data.header) {
    list = curl_slist_append(list, h.c_str());
  }

  curl_easy_setopt(curl, CURLOPT_URL, data.url.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS ,data.json.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, long(data.json.size()));
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  curl_easy_setopt(curl,CURLOPT_TIMEOUT_MS , data.waitTime * 1000);
  curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &status);

  curl_slist_free_all(list);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return Response(int(status), response);
}

std::future<Response> AsyncClient::get (Data data) {
  Client client;
  return std::async(std::launch::async, [client,data] () mutable{
    return client.get(data);
  });
}

std::future<Response> AsyncClient::post (Data data) {
  Client client;
  return std::async(std::launch::async, [client, data] () mutable{
    return client.post(data);
  });
}


bool Async::handle() {
  if (curr < size) {
    return true;
  } else {
    return false;
  }
}

void Async::initSemaphore(int handleRequest) {
  size = handleRequest;
}

std::future<bool> Async::semaphore() {
  return std::async(std::launch::async, [&] () {
    curr++;
    int i = 1;
    while (!handle()) {
      sleep(2 * i);
    }
    curr--;
    return true;
  });
}

std::future<void> Async::sleep (int second) {
  return std::async(std::launch::async, [&] () {
    std::this_thread::sleep_for(std::chrono::seconds(second));
  });
}