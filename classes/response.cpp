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

  std::string get_session_cookie() {
    std::size_t start = response.find("connect.sid=") + 12;
    if (start == std::string::npos) {
      return "";
    }
    std::string session_cookie = response.substr(start);
    std::size_t end = session_cookie.find(';');
    if (end == std::string::npos) {
      return "";
    }
    return session_cookie.substr(0, end);
  }

  std::string get_token() {
    std::string body = this->get_body();
    if (json::accept(body)) {
      json body_j = json::parse(body);
      if (body_j["token"].is_null() == false) {
        std::string token = body_j["token"];
        token.erase(std::remove(token.begin(), token.end(), '\"'), token.end());
        return token;
      }
    }
    return "";
  }

  void print_result() {
    std::string body = this->get_body();
    std::string status_code = this->get_status_code();

    if (json::accept(body)) {
      json body_j = json::parse(body);
      if (body_j["error"].is_null() == false) {
        std::string error = body_j["error"];
        error.erase(std::remove(error.begin(), error.end(), '\"'), error.end());
        std::cout << status_code << " - " << error << std::endl;
        return;
      }
    }
    std::cout << status_code << std::endl;
  }
};