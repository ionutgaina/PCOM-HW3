#include "requests.h"

#include <arpa/inet.h>
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h>
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>     /* read, write, close */

#include "helpers.h"

char *compute_get_request(char *host, char *url, char *token) {
  char *message = (char *)calloc(BUFLEN, sizeof(char));
  char *line = (char *)calloc(LINELEN, sizeof(char));

  // Step 1: write the method name, URL, request params (if any) and protocol
  // type
  sprintf(line, "GET %s HTTP/1.1", url);
  compute_message(message, line);

  sprintf(line, "Host: %s", host);
  compute_message(message, line);

  printf("Token: %s\n", token);
  if (token != NULL) {
    sprintf(line, "Authorization: Bearer %s", token);
    compute_message(message, line);
  }
  // Step 4: add final new line
  compute_message(message, "");
  memset(line, 0, LINELEN);
  free(line);

  printf("Message: %s\n", message);
  return message;
}

char *compute_post_request(char *host, char *url, char *content_type,
                           char *body_data, char *token) {
  char *message = (char *)calloc(BUFLEN, sizeof(char));
  char *line = (char *)calloc(LINELEN, sizeof(char));

  sprintf(line, "POST %s HTTP/1.1", url);
  compute_message(message, line);

  sprintf(line, "Host: %s", host);
  compute_message(message, line);

  if (content_type != NULL) {
    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);
    sprintf(line, "Content-Length: %ld", strlen(body_data));
    compute_message(message, line);
  }

  if (token != NULL) {
    sprintf(line, "Authorization: Bearer %s", token);
    compute_message(message, line);
  }

  compute_message(message, "");

  strcat(message, body_data);

  memset(line, 0, LINELEN);
  free(line);
  return message;
}
