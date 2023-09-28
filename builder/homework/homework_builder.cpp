#include <string>
#include <ostream>
#include <vector>
#include <sstream> // ostringstream
#include <iostream>

using namespace std;

// indentation is 2 spaces
class CodeBuilder;
// single responsability: CodeBlock holds the data and is able to print it in a formated way
class CodeBlock {
private:
    // member
    std::string _classname;
    std::vector<std::pair<std::string, std::string>> _fields; // type, name
    std::size_t _indentation = 1;
    // constructor
    CodeBlock(std::string class_name) : 
    _classname(class_name)
    {}

public:
    // methods
    static CodeBuilder create(const std::string class_name);

    std::string str(const std::size_t indent = 0) const {
        std::ostringstream oss;
        oss << "class " << _classname << "\n{\n"; // line 1 and 2

        for (const auto& field : _fields) {
            oss << std::string(indent * _indentation, ' ') << field.second << " " << field.first << ";\n";
        }

        oss << "};";
        return oss.str();
    }
     
    friend class CodeBuilder;
};


class CodeBuilder
{
private:
    CodeBlock _codeBlock;

public:
    CodeBuilder(const string& class_name) :
        _codeBlock(class_name)
    {}

    CodeBuilder& add_field(const string& name, const string& type)
    {
        _codeBlock._fields.push_back(std::make_pair(name, type));
        return *this; // fluent API
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
    {
        os << obj._codeBlock.str(2);
        return os;
    }
};

// To use CodeBuilder within CodeBlock, the compiler needs to know the complete implementation of CodeBuilder. Therefor we need to externalize the create method implementation from the class definition of CodeBlock further above
CodeBuilder CodeBlock::create(const std::string class_name) {
    return { class_name }; // implicit generation of CodeBuilder via type inference by the compiler
}

int main() {

    auto cb = CodeBuilder{ "Person" }
                .add_field("name", "string")
                .add_field("age", "int");
    std::cout << cb;

    auto carBuilder = CodeBlock::create("Car").add_field("int", "horsepower");


    return 0;
}