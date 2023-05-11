class Cookie {
 public:
  std::map<std::string, std::string> fields =
      std::map<std::string, std::string>();

  Cookie() {}

  void add_field(std::string key, std::string value) {
    this->fields[key] = value;
  };

  std::string get_cookies() {
    std::string cookies = "";
    for (auto it = this->fields.begin(); it != this->fields.end(); it++) {
      cookies += it->first + "=" + it->second + "; ";
    }
    return cookies;
  };

  void print_cookie() {
    for (auto it = this->fields.begin(); it != this->fields.end(); it++) {
      std::cout << it->first << " " << it->second << std::endl;
    }
  };
};