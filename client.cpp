#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

#include "./body.cpp"

#define HOST "34.254.242.81"
#define PORT 8080

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;
    
    sockfd = open_connection(HOST, 8080, AF_INET, SOCK_STREAM, 0);
        
    // // Ex 1.1: GET dummy from main server
    // message = compute_get_request(HOST, "/api/v1/dummy", NULL, NULL, 0);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);

    // // Ex 1.2: POST dummy and print response from main server
    // char *body_data_fields[2];
    // body_data_fields[0] = calloc(LINELEN, sizeof(char));
    // body_data_fields[1] = calloc(LINELEN, sizeof(char));
    // strcpy(body_data_fields[0], "username=student");
    // strcpy(body_data_fields[1], "password=student");

    // message = compute_post_request(HOST, "/api/v1/dummy", "application/x-www-form-urlencoded", body_data_fields, 2, NULL, 0);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // // printf("%s\n", response);

    /*
        REGISTER
    */

    char route = char("/api/v1/tema/auth/register");


    message = compute_post_request(HOST, &route , "application/json", body_data_fields, 2, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    // printf("%s\n", response);
    // // Ex 3: GET weather key from main server

    message = compute_get_request(HOST, "/api/v1/weather/key", NULL, NULL, 0);
    send_to_server(sockfd, message);
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
