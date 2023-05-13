class Header {
 public:
  std::map<std::string, std::string> fields =
      std::map<std::string, std::string>();

  Header() {}

  void add_field(std::string key, std::string value) {
    this->fields[key] = value;
  };

  std::string get_headers() {
    std::string headers = "";
    for (auto it = this->fields.begin(); it != this->fields.end(); it++) {
      headers += it->first + ": " + it->second + "\r\n";
    }
    return headers;
  };
};