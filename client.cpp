#include <arpa/inet.h>
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, calloc, free */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>     /* read, write, close */

#include <fstream>
#include <iostream>
#include <vector>

#include "helpers.h"
#include "iostream"
#include "json.hpp"
#include "requests.h"

using json = nlohmann::json;

#define PORT 8080
#define HOST "34.254.242.81"
#define CONTENT_TYPE "application/json"

#define REGISTER_ROUTE "/api/v1/tema/auth/register"
#define LOGIN_ROUTE "/api/v1/tema/auth/login"
#define LOGOUT_ROUTE "/api/v1/tema/auth/logout"
#define LIBRARY_ACCESS_ROUTE "/api/v1/tema/library/access"
#define LIBRARY_BOOKS_ROUTE "/api/v1/tema/library/books"

#define JSON_INDENT 2

char* register_req();
char* login_req();
char* logout_req(char* token);
char* enter_library_req();
char* get_books_req();
char* get_book_req();
char* add_book_req();
char* delete_book_req();

char* get_token(char* response);
char* send_req(int sockfd, char* message);
bool error_handler(char* response);
void success_handler(char* response, std::string message);
char* get_status_code(char* response);
char* get_data(char* response);

int main(int argc, char* argv[]) {
  char* response = nullptr;
  char* message = nullptr;
  char* token = nullptr;
  int sockfd;

  sockfd = open_connection((char*)HOST, PORT, AF_INET, SOCK_STREAM, 0);

  std::string command;
  while (1) {
    if (message != nullptr || response != NULL) {
      free(message);
    }
    if (response != nullptr || response != NULL) {
      free(response);
    }

    std::cin >> command;
    /*
       REGISTER
    */
    if (command == "register") {
      message = register_req();
      response = send_req(sockfd, message);
      if (error_handler(response))
        continue;
      else
        success_handler(response, "Registration successful");
    }
    /*
       LOGIN
    */
    else if (command == "login") {
      message = login_req();
      response = send_req(sockfd, message);
      if (error_handler(response)) {
        continue;
      } else {
        char* aux = new char[strlen(response) + 1];
        strcpy(aux, response);
        success_handler(response, "Login successful");
        if (token != NULL) {
          token = NULL;
        }
        
        char *mytoken = get_token(aux);
        token = new char[strlen(mytoken) + 1];
        strcpy(token, mytoken);
        delete[] aux;
      }
    }

    /*
       ENTER LIBRARY
    */
    else if (command == "enter_library") {
      // enter_library
    } else if (command == "get_books") {
      // get_books
    } else if (command == "get_book") {
      // get_book
    } else if (command == "add_book") {
      // add_book
    } else if (command == "delete_book") {
      // delete_book
    } else if (command == "logout") {
      message = logout_req(token);
      response = send_req(sockfd, message);
      if (error_handler(response)) continue;
      success_handler(response, "Logout successful");
      if (token != nullptr) {
        delete[] token;
      }
    } else if (command == "exit") {
      break;
    } else {
      printf("Invalid command\n");
    }
  }

  if (token != nullptr || token != NULL) {
    delete[] token;
  }

  close_connection(sockfd);
  return 0;
}

char* enter_library_req(char* token) {
  return compute_get_request((char*)HOST, (char*)LIBRARY_ACCESS_ROUTE, token);
}

char* login_req() {
  json login_data;
  std::string username, password;
  std::cout << "username :" << std::endl;
  std::cin >> username;
  std::cout << "password :" << std::endl;
  std::cin >> password;
  login_data["username"] = username;
  login_data["password"] = password;

  return compute_post_request(
      (char*)HOST, (char*)LOGIN_ROUTE, (char*)CONTENT_TYPE,
      (char*)login_data.dump(JSON_INDENT).c_str(), NULL);
}

char* register_req() {
  json register_data;
  std::string username, password;
  std::cout << "username :" << std::endl;
  std::cin >> username;
  std::cout << "password :" << std::endl;
  std::cin >> password;
  register_data["username"] = username;
  register_data["password"] = password;

  return compute_post_request(
      (char*)HOST, (char*)REGISTER_ROUTE, (char*)CONTENT_TYPE,
      (char*)register_data.dump(JSON_INDENT).c_str(), NULL);
}

char* logout_req(char* token) {
  return compute_get_request((char*)HOST, (char*)LOGOUT_ROUTE, token);
}

char* send_req(int sockfd, char* message) {
  send_to_server(sockfd, message);
  return receive_from_server(sockfd);
}

bool error_handler(char* response) {
  char* aux = new char[strlen(response) + 1];
  strcpy(aux, response);
  char* status_code = get_status_code(aux);

  char* data = get_data(response);

  if (json::accept(data) == false) {
    delete[] data;
    delete[] aux;
    return false;
  }

  json data_j = json::parse(data);

  if (data_j.find("error") != data_j.end()) {
    std::string error = data_j["error"];
    error.erase(std::remove(error.begin(), error.end(), '\"'), error.end());

    std::cout << status_code << " - " << error << std::endl;
    delete[] data;
    delete[] aux;
    return true;
  }
  delete[] data;
  delete[] aux;
  return false;
}

void success_handler(char* response, std::string message) {
  char* status_code = get_status_code(response);

  std::cout << status_code << " - " << message << std::endl;
}

char* get_status_code(char* response) {
  // remove HTTP/1.1
  strtok(response, " ");

  char* status_code = strtok(NULL, "\r\n");
  return status_code;
}

char* get_data(char* response) {
  char* aux = new char[strlen(response) + 1];
  strcpy(aux, response);

  char* data = strstr(aux, "\r\n\r\n");
  data += 4;

  char* new_data = new char[strlen(data) + 1];
  strcpy(new_data, data);

  delete[] aux;
  return new_data;
}

char* get_token(char* response) {
  char* token = strstr(response, "connect.sid=");
  token = strtok(token, ";");
  return token;
}