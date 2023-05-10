#include <unordered_map>
#include "request.cpp"

class Command
{
private:
  enum class CommandType
  {
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

  Command(std::string command, std::string *token)
  {
    std::string copy_token;
    if (token != NULL)
    {
      copy_token = *token;
    }

    auto it = this->commands.find(command);
    if (it == this->commands.end())
    {
      std::cout << "Invalid command" << std::endl;
      return;
    }
    CommandType command_type = it->second;
    switch (command_type)
    {
    case CommandType::REGISTER:
      this->request = Request(HOST, POST, REGISTER_ROUTE);
      break;
    case CommandType::LOGIN:
      this->request = Request(HOST, POST, LOGIN_ROUTE);
      break;
    case CommandType::LOGOUT:
      this->request = Request(HOST, GET, LOGOUT_ROUTE);
      token->clear();
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

    if (copy_token.length() > 0)
    {
      this->request.headers.add_field("Authorization", "Bearer " + copy_token);
    }
  };

  std::string create_request()
  {
    switch (this->command_type)
    {
    case CommandType::REGISTER:
      return this->register_req();
      break;
    case CommandType::LOGIN:
      return this->login_req();
      break;
    case CommandType::LOGOUT:
      return this->logout_req();
      break;
      // case CommandType::ENTER_LIBRARY:
      //   return this->enter_library_req();
      //   break;
      // case CommandType::GET_BOOKS:
      //   return this->get_books_req();
      //   break;
      // case CommandType::GET_BOOK:
      //   return this->get_book_req();
      //   break;
      // case CommandType::ADD_BOOK:
      //   return this->add_book_req();
      //   break;
      // case CommandType::DELETE_BOOK:
      //   return this->delete_book_req();
      //   break;

    default:
      break;
    }
    return "";
  }

private:
  std::string register_req()
  {
    std::string username, password;
    std::cout << "username :" << std::endl;
    std::cin >> username;
    std::cout << "password :" << std::endl;
    std::cin >> password;

    this->request.body.add_field("username", username);
    this->request.body.add_field("password", password);

    return this->request.create_request();
  };

  std::string login_req()
  {
    std::string username, password;
    std::cout << "username :" << std::endl;
    std::cin >> username;
    std::cout << "password :" << std::endl;
    std::cin >> password;

    this->request.body.add_field("username", username);
    this->request.body.add_field("password", password);

    return this->request.create_request();
  }

  std::string logout_req()
  {
    return this->request.create_request();
  }
};