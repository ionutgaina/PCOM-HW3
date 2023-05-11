#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <vector>
#include <fstream>


#include "utils/helpers.h"
#include "utils/json.hpp"

using json = nlohmann::json;

#include "classes/command.cpp"

#define PORT 8080
#define HOST "34.254.242.81"
#define POST "POST"
#define GET "GET"

#define REGISTER_ROUTE "/api/v1/tema/auth/register"
#define LOGIN_ROUTE "/api/v1/tema/auth/login"
#define LOGOUT_ROUTE "/api/v1/tema/auth/logout"
#define LIBRARY_ACCESS_ROUTE "/api/v1/tema/library/access"
#define LIBRARY_BOOKS_ROUTE "/api/v1/tema/library/books"


int main(int argc, char *argv[])
{
    char *response;
    int sockfd;


    while(1) {
      sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

      std::string cmd;
      std::cin >> cmd;

      Command cmd = Command(cmd, NULL);

      std::string request_string;

      send_to_server(sockfd, request_string.c_str());
      close_connection(sockfd);
    }
    response = receive_from_server(sockfd);
    

    // free the allocated data at the end!

    return 0;
}
