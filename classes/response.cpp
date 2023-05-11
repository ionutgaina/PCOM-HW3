#include <iostream>
#include <string>

#include "../utils/json.hpp"

using json = nlohmann::json;

class Response {
 public:
  std::string response;

  Response() { this->response = ""; }

  Response(std::string response) { this->response = response; }

  std::string get_body() {
    return this->response.substr(this->response.find("\r\n\r\n") + 4);
  }

  std::string get_status_code() {
    std::string status = response.substr(response.find(' ') + 1);
    return status.substr(0, status.find('\r'));
  }

  std::string get_token() {
    std::size_t start = response.find("connect.sid=");
    if (start == std::string::npos) {
      return "";
    }
    std::string token = response.substr(start);
    std::size_t end = token.find(';');
    if (end == std::string::npos) {
      return "";
    }
    return token.substr(0, end);
  }

  void print_result() {
    std::string body = this->get_body();
    std::string status_code = this->get_status_code();

    if (json::accept(body)) {
      json body_j = json::parse(body);
      if (body_j["error"] != NULL) {
        std::string error = body_j["error"];
        error.erase(std::remove(error.begin(), error.end(), '\"'), error.end());
        std::cout << status_code << " - " << error << std::endl;
        return;
      }
    }
    std::cout << status_code << std::endl;
  }
};