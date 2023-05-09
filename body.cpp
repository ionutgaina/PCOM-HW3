class Body
{
public:
  int nr_fields;
  char **fields;

  Body()
  {
    this->nr_fields = 0;
  }
  Body(int nr_fields, char **fields)
  {
    this->nr_fields = nr_fields;
    this->fields = fields;
  };

  void free_body()
  {
    for (int i = 0; i < nr_fields; i++)
    {
      delete (fields[i]);
    }
    delete (fields);
  };

  void add_field(char *field)
  {
    this->fields = new char *[this->nr_fields + 1];
    this->fields[this->nr_fields] = field;
    this->nr_fields++;
  };
};