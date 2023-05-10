class Body
{
public:
  std::map<std::string, std::string> fields = std::map<std::string, std::string>();

  Body()
  {
  }

  void add_field(std::string key, std::string value)
  {
    this->fields[key] = value;
  };

  void print_body()
  {
    for (auto it = this->fields.begin(); it != this->fields.end(); it++)
    {
      std::cout << it->first << " " << it->second << std::endl;
    }
  };
};