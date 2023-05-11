#include <iostream>
#include <string>
#include <unordered_map>

#include "../utils/constants.h"
#include "request.cpp"

class Command {
 private:
  enum class CommandType {
    REGISTER,
    LOGIN,
    LOGOUT,
    ENTER_LIBRARY,
    GET_BOOKS,
    GET_BOOK,
    ADD_BOOK,
    DELETE_BOOK,
  };

  const std::unordered_map<std::string, CommandType> commands = {
      {"register", CommandType::REGISTER},
      {"login", CommandType::LOGIN},
      {"logout", CommandType::LOGOUT},
      {"enter_library", CommandType::ENTER_LIBRARY},
      {"get_books", CommandType::GET_BOOKS},
      {"get_book", CommandType::GET_BOOK},
      {"add_book", CommandType::ADD_BOOK},
      {"delete_book", CommandType::DELETE_BOOK}};

 public:
  CommandType command_type;
  Request request;

  Command(std::string command, std::string *session_cookie,
          std::string *token) {
    std::string copy_session_cookie, copy_token;
    if (session_cookie != NULL) {
      copy_session_cookie = *session_cookie;
    }

    if (token != NULL) {
      copy_token = *token;
    }

    auto it = this->commands.find(command);
    if (it == this->commands.end()) {
      std::cout << "Invalid command" << std::endl;
      return;
    }
    CommandType command_type = it->second;
    switch (command_type) {
      case CommandType::REGISTER:
        this->request = Request(HOST, POST, REGISTER_ROUTE);
        break;
      case CommandType::LOGIN:
        this->request = Request(HOST, POST, LOGIN_ROUTE);
        break;
      case CommandType::LOGOUT:
        this->request = Request(HOST, GET, LOGOUT_ROUTE);
        session_cookie = NULL;
        token = NULL;
        break;
      case CommandType::ENTER_LIBRARY:
        this->request = Request(HOST, GET, LIBRARY_ACCESS_ROUTE);
        break;
      case CommandType::GET_BOOKS:
        this->request = Request(HOST, GET, LIBRARY_BOOKS_ROUTE);
        break;
      case CommandType::GET_BOOK:
        this->request = Request(HOST, GET, LIBRARY_BOOKS_ROUTE);
        break;
      case CommandType::ADD_BOOK:
        this->request = Request(HOST, POST, LIBRARY_BOOKS_ROUTE);
        break;
      case CommandType::DELETE_BOOK:
        this->request = Request(HOST, DELETE, LIBRARY_BOOKS_ROUTE);
        break;
    }
    this->command_type = command_type;

    if (copy_session_cookie.length() > 0) {
      this->request.cookies.add_field("connect.sid", copy_session_cookie);
    }

    if (copy_token.length() > 0) {
      this->request.headers.add_field("Authorization", "Bearer " + copy_token);
    }
  };

  std::string create_request() {
    switch (this->command_type) {
      case CommandType::REGISTER:
        return this->register_req();
        break;
      case CommandType::LOGIN:
        return this->login_req();
        break;
      case CommandType::LOGOUT:
        return this->logout_req();
        break;
      case CommandType::ENTER_LIBRARY:
        return this->enter_library_req();
        break;
      case CommandType::GET_BOOKS:
        return this->get_books_req();
        break;
        // case CommandType::GET_BOOK:
        //   return this->get_book_req();
        //   break;
      case CommandType::ADD_BOOK:
        return this->add_book_req();
        break;
        // case CommandType::DELETE_BOOK:
        //   return this->delete_book_req();
        //   break;

      default:
        break;
    }
    return "";
  }

 private:
  std::string register_req() {
    std::string username, password;
    std::cout << "username :" << std::endl;
    std::getline(std::cin, username);
    if (!this->validate_input("username", username, false, true, true))
      return "";
    std::cout << "password :" << std::endl;
    std::getline(std::cin, password);
    if (!this->validate_input("password", password, false, true, true))
      return "";

    this->request.body.add_field("username", username);
    this->request.body.add_field("password", password);

    return this->request.create_request();
  };

  std::string login_req() {
    std::string username, password;
    std::cout << "username :" << std::endl;
    std::getline(std::cin, username);
    if (!this->validate_input("username", username, false, true, true))
      return "";
    std::cout << "password :" << std::endl;
    std::getline(std::cin, password);
    if (!this->validate_input("password", password, false, true, true))
      return "";

    this->request.body.add_field("username", username);
    this->request.body.add_field("password", password);

    return this->request.create_request();
  }

  std::string logout_req() { return this->request.create_request(); }

  std::string enter_library_req() { return this->request.create_request(); }

  std::string get_books_req() { return this->request.create_request(); }

  std::string add_book_req() {
    // ignore the newline character
    std::string title, author, genre, publisher, page_count;
    std::cout << "title :" << std::endl;
    std::getline(std::cin, title);
    if (!this->validate_input("title", title, false, true, true)) return "";
    std::cout << "author :" << std::endl;
    std::getline(std::cin, author);
    if (!this->validate_input("author", author, false, true, true)) return "";
    std::cout << "genre :" << std::endl;
    std::getline(std::cin, genre);
    if (!this->validate_input("genre", genre, false, true, true)) return "";
    std::cout << "publisher :" << std::endl;
    std::getline(std::cin, publisher);
    if (!this->validate_input("publisher", publisher, false, true, true))
      return "";
    std::cout << "page_count :" << std::endl;
    std::getline(std::cin, page_count);
    if (!this->validate_input("page_count", page_count, true, true, true))
      return "";

    int page_count_int = std::stoi(page_count);

    this->request.body.add_field("title", title);
    this->request.body.add_field("author", author);
    this->request.body.add_field("genre", genre);
    this->request.body.add_field("publisher", publisher);
    this->request.body.add_field("page_count", page_count_int);

    return this->request.create_request();
  }

  bool isNumber(std::string input) {
    if (input.length() == 0) {
      return false;
    }
    for (char c : input) {
      if (!std::isdigit(c)) {
        return false;
      }
    }
    return true;
  }

  bool validate_input(std::string field, std::string input, bool isNumber,
                      bool isEmpty, bool noSpaces) {
    if (isNumber && this->isNumber(input)) {
      std::cout << field << " must be a number" << std::endl;
      return false;
    }

    if (!isEmpty && input.length() == 0) {
      std::cout << field << " cannot be empty" << std::endl;
      return false;
    }

    if (noSpaces && input.find(" ") != std::string::npos) {
      std::cout << field << " cannot contain spaces" << std::endl;
      return false;
    }

    return true;
  }
};