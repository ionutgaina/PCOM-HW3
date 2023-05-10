#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>  /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <unistd.h> /* read, write, close */
#include <vector>
#include <fstream>

#include "iostream"

#include "json.hpp"

#include "helpers.h"
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

char *register_req();
char *login_req();
char *logout_req();
char *enter_library_req();
char *get_books_req();
char *get_book_req();
char *add_book_req();
char *delete_book_req();

int main(int argc, char *argv[])
{
    char *response;
    char *message;
    int sockfd;

    sockfd = open_connection((char *)HOST, PORT, AF_INET, SOCK_STREAM, 0);

    std::string command;
    while (1)
    {
        std::cin >> command;
        if (command == "register")
        {
            // register
        }
        else if (command == "login")
        {
            // login
        }
        else if (command == "enter_library")
        {
            // enter_library
        }
        else if (command == "get_books")
        {
            // get_books
        }
        else if (command == "get_book")
        {
            // get_book
        }
        else if (command == "add_book")
        {
            // add_book
        }
        else if (command == "delete_book")
        {
            // delete_book
        }
        else if (command == "logout")
        {
            // logout
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            printf("Invalid command\n");
        }

        message = register_req();
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        printf("%s\n", response);
    }

    return 0;
}

char *register_req()
{
    json register_data;
    std::string username, password;
    std::cout << "username :" << std::endl;
    std::cin >> username;
    std::cout << "password :" << std::endl;
    std::cin >> password;
    register_data["username"] = username;
    register_data["password"] = password;

    return compute_post_request((char *)HOST, (char *)REGISTER_ROUTE, (char *)CONTENT_TYPE, (char *)register_data.dump(JSON_INDENT).c_str(), NULL);
}

char *login_req()
{
    json login_data;
    std::string username, password;
    std::cout << "username :" << std::endl;
    std::cin >> username;
    std::cout << "password :" << std::endl;
    std::cin >> password;
    login_data["username"] = username;
    login_data["password"] = password;

    return compute_post_request((char *)HOST, (char *)LOGIN_ROUTE, (char *)CONTENT_TYPE, (char *)login_data.dump(JSON_INDENT).c_str(), NULL);
}