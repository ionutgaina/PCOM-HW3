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

#include "classes/request.cpp"

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

    sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

    /*
        REGISTER
    */

    Request register_request = Request(HOST, POST, REGISTER_ROUTE);

    register_request.body.add_field("username", "test");
    register_request.body.add_field("password", "test");

    std::string request_string = register_request.create_request();
    std::cout << request_string << std::endl;

    send_to_server(sockfd, request_string.c_str());
    response = receive_from_server(sockfd);
    printf("%s\n", response);
    // Ex 4: GET weather data from OpenWeather API
    // Ex 5: POST weather data for verification to main server
    // Ex 6: Logout from main server

    // BONUS: make the main server return "Already logged in!"

    // free the allocated data at the end!
    close_connection(sockfd);

    return 0;
}
