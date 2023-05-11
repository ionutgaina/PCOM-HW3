#include <map>
class Body {
 public:
  std::map<std::string, std::string> fields =
      std::map<std::string, std::string>();
  std::map<std::string, int> fields_int = std::map<std::string, int>();

  Body(){};

  void add_field(std::string key, std::string value) {
    this->fields[key] = value;
  };

  void add_field(std::string key, int value) { this->fields_int[key] = value; };
};