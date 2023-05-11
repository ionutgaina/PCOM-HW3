#include "../utils/json.hpp"
#include "../utils/requests.h"
#include "body.cpp"
#include "cookie.cpp"
#include "header.cpp"

using json = nlohmann::json;

class Request {
 public:
  std::string method;
  std::string host;
  std::string path;
  Header headers = Header();
  Cookie cookies = Cookie();
  Body body = Body();

  Request(){};

  Request(std::string host) { this->host = host; };

  Request(std::string host, std::string method, std::string path) {
    this->host = host;
    this->method = method;
    this->path = path;
  };

  std::string create_request() {
    json j_body = get_json(this->body.fields);

    json j_body_int = get_json(this->body.fields_int);

    for (json::iterator it = j_body_int.begin(); it != j_body_int.end(); ++it) {
      j_body[it.key()] = it.value();
    }

    std::string body_data = j_body.dump(JSON_ALIGN);

    std::cout << body_data << std::endl;

    std::string request = this->method + " " + this->path + " HTTP/1.1\r\n";
    request += "Host: " + this->host + "\r\n";
    if (this->method == POST) {
      request += "Content-Type: application/json\r\n";
      request += "Content-Length: " + std::to_string(body_data.size()) + "\r\n";
    }

    if (this->headers.fields.size() > 0) {
      request += this->headers.get_headers();
    }

    if (this->cookies.fields.size() > 0) {
      request += "Cookie: " + this->cookies.get_cookies() + "\r\n";
    }

    request += "\r\n";

    if (this->method == POST) {
      request += body_data;
    }
    return request;
  };

  bool is_valid() {
    return this->method.length() > 0 && this->host.length() > 0 &&
           this->path.length() > 0;
  }

 private:
  json get_json(std::map<std::string, std::string> data) {
    json j_map(data);
    return j_map;
  };

  json get_json(std::map<std::string, int> data) {
    json j_map(data);
    return j_map;
  };
};