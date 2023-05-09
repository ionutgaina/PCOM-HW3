#include "body.cpp"
#include "cookie.cpp"
#include "header.cpp"

class Request
{
public:
  char *method;
  Body body = Body();
  Header header = Header();
  Cookie cookie = Cookie();
};