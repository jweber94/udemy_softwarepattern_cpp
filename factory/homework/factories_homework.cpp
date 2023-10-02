#include <string>
using namespace std;

struct Person
{
  friend class PersonFactory;

  int id;
  string name;

private:
    Person(const int id, const std::string name) :
    id(id),
    name(name)
    {}
};

class PersonFactory
{
public:
  static Person create_person(const string& name)
  {
    static int _creationCounter = 0;
    auto ret = Person(_creationCounter, name);
    _creationCounter++;
    return ret;
  }
};

int main()
{
    Person testPerson = PersonFactory::create_person("Jens");
	return 0;
}