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

char *compute_get_request(const char *host, const char *url, char *cookies,
                          const char *token) {
  char *message = (char *)calloc(BUFLEN, sizeof(char));
  char *line = (char *)calloc(LINELEN, sizeof(char));

  sprintf(line, "GET %s HTTP/1.1", url);

  compute_message(message, line);

  sprintf(line, "Host: %s", host);
  compute_message(message, line);

  if (token != NULL) {
    sprintf(line, "Authorization: Bearer %s", token);
    compute_message(message, line);
  }

  if (cookies != NULL) {
    sprintf(line, "Cookie: %s", cookies);
    compute_message(message, line);
  }

  compute_message(message, "");

  memset(line, 0, LINELEN);
  free(line);
  return message;
}

char *compute_post_request(const char *host, const char *url,
                           char *content_type, const char *body_data,
                           char *cookies, char *data, const char *token) {
  char *message = (char *)calloc(BUFLEN, sizeof(char));
  char *line = (char *)calloc(LINELEN, sizeof(char));

  sprintf(line, "POST %s HTTP/1.1", url);
  compute_message(message, line);

  sprintf(line, "Host: %s", host);
  compute_message(message, line);

  /*
      HEADER
  */
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

  /*
      COOKIES
  */
  if (cookies != NULL) {
    sprintf(line, "Cookie: %s", cookies);
    compute_message(message, line);
  }

  /*
      DATA
  */
  compute_message(message, "");

  sprintf(line, "%s", body_data);
  compute_message(message, line);

  memset(line, 0, LINELEN);
  free(line);
  return message;
}

char *compute_delete_request(const char *host, const char *url, char *cookies,
                             const char *token) {
  char *message = (char *)calloc(BUFLEN, sizeof(char));
  char *line = (char *)calloc(LINELEN, sizeof(char));

  sprintf(line, "DELETE %s HTTP/1.1", url);

  compute_message(message, line);

  sprintf(line, "Host: %s", host);
  compute_message(message, line);

  if (token != NULL) {
    sprintf(line, "Authorization: Bearer %s", token);
    compute_message(message, line);
  }

  if (cookies != NULL) {
    sprintf(line, "Cookie: %s", cookies);
    compute_message(message, line);
  }

  memset(line, 0, LINELEN);
  compute_message(message, "");

  free(line);
  return message;
}