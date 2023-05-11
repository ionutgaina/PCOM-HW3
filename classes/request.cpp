#include "body.cpp"
#include "cookie.cpp"
#include "header.cpp"

class Request
{
public:
    std::string method;
    std::string host;
    std::string path;
    Cookie cookies = Cookie();
    Header headers = Header();
    Body body = Body();

    Request(){};

    Request(std::string host)
    {
        this->host = host;
    };

    Request(std::string host, std::string method, std::string path, std::string parameter = "")
    {
        this->host = host;
        this->method = method;
        this->path = path;
        if (parameter != "")
        {
            this->path += "/" + parameter;
        }
    };

    std::string create_request()
    {
        std::string body = get_json(this->body.fields).dump(2);

        std::string request = "";
        request += this->method + " " + this->path + " " + "HTTP/1.1" + "\r\n";
        request += "Host: " + this->host + "\r\n";

        if (body.length() > 0)
        {
            request += "Content-Type: application/json\r\n";
            request += "Content-Length: " + std::to_string(body.length()) + "\r\n";
        }

        if (this->headers.fields.size() > 0)
        {
            for (auto it = this->headers.fields.begin(); it != this->headers.fields.end(); it++)
            {
                request += it->first + ": " + it->second + "\r\n";
            }
        }

        if (this->cookies.fields.size() > 0)
        {
            request += "Cookie: ";
            for (auto it = this->cookies.fields.begin(); it != this->cookies.fields.end(); it++)
            {
                request += it->first + "=" + it->second + "; ";
            }
            request += "\r\n";
        }

        request += "\r\n";

        if (this->method == "POST")
        {
            request += body;
        }
        return request;
    };

private:
    json get_json(std::map<std::string, std::string> data)
    {
        json j_map(data);
        return j_map;
    };
};