#include <iostream>
#include <string>

using namespace std;

class Person
{
    friend class ResponsiblePerson;
    int age;
public:
    Person(int age) : age(age) {}

    int get_age() const { return age; }
    void set_age(int age) { this->age = age; }

    string drink() const { return "drinking"; }
    string drive() const { return "driving"; }
    string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:
    ResponsiblePerson(const Person& person) : person(person) {}
    
    // getter and setter
    int get_age() const { return person.age; }
    void set_age(int age) { person.age = age; }

    // methos
    string drink() const 
    { 
        if (18 > person.age) {
            return m_tooYoung;
        }
        return person.drink();
    }
    
    string drive() const {
        if (16 > person.age) {
            return m_tooYoung;
        }
        return person.drive(); 
    }
    
    string drink_and_drive() const { 
        return "dead"; // override base functionallity 
    }

private:
    Person person;
    std::string m_tooYoung = "too young";
};

int main() {
    Person jens{15};
    ResponsiblePerson jensResp(jens);
    std::cout << "Drive: " << jensResp.drive() << std::endl;
    std::cout << "Drink: " << jensResp.drink() << std::endl;

    Person michelle{ 27 };
    ResponsiblePerson michelleResp(michelle);
    std::cout << "Drive: " << michelleResp.drive() << std::endl;
    std::cout << "Drink: " << michelleResp.drink() << std::endl;
    std::cout << "Drink and drive: " << michelleResp.drink_and_drive() << std::endl;

    return 0;
}