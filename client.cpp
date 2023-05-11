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

#include "utils/helpers.h"
#include "utils/constants.h"
#include "utils/json.hpp"

using json = nlohmann::json;

#include "classes/command.cpp"

char *parse_string(std::string my_string);

int main(int argc, char *argv[])
{
    char *response;
    std::string token;
    int sockfd;


    while (1)
    {
        std::string command;
        std::cin >> command;
        if (command == "exit")
        {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        Command cmd = Command(command, &token);

        if (!cmd.request.is_valid())
        {
            continue;
        }

        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

        std::string request_string = cmd.create_request();
        std::cout << request_string << std::endl;
        send_to_server(sockfd, request_string.c_str());

        response = receive_from_server(sockfd);
        if (response != NULL || response != nullptr) {
          free(response);
        }
        close_connection(sockfd);
    }

    // // free the allocated data at the end!
    token.clear();

    return 0;
}