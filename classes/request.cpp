#include "../utils/requests.h"
#include "body.cpp"
#include "cookie.cpp"
#include "header.cpp"

class Request {
 public:
  std::string method;
  std::string host;
  std::string path;
  std::string token;
  Header headers = Header();
  Cookie cookies = Cookie();
  Body body = Body();

  Request(){};

  Request(std::string host) { this->host = host; };

  Request(std::string host, std::string method, std::string path,
          std::string token = "") {
    this->host = host;
    this->method = method;
    this->path = path;
    this->token = token;
  };

  std::string create_request() {
    json j_body = get_json(this->body.fields);
    std::string body_data = j_body.dump(JSON_ALIGN);

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
};