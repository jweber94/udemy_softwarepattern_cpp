#include <iostream>
#include <string>
#include <variant>

// classical approach without std::variant and std::visit
struct House {
    ~House() {
        if (type == Type::name)
            house_name_ptr->~basic_string();
    }

    union {
        std::string* house_name_ptr;
        int house_number;
    };

    enum class Type { name, number } type;

    House(const std::string& name, Type t) : type(t) {
        if (t == Type::name)
            house_name_ptr = new (&house_name_storage) std::string(name);
    }

private:
    alignas(std::string) char house_name_storage[sizeof(std::string)];

};

// we need to overload the operator() for all possible types of the std::variant<T...> that could be defined for the variant
struct AddressPrinter {
    /* This is a specialized visitor for the std::variant datatype */
    void operator()(const std::string& house_name) const {
        std::cout << "A house called " << house_name << std::endl;
    }

    void operator()(const int house_number) const {
        std::cout << "A house with the number " << house_number << std::endl;
    }
};

int main() {
    House houseWithName{ "MyHouse", House::Type::name };

    std::variant<std::string, int> house1;
    std::variant<std::string, int> house2;
    house1 = 123;
    house2 = "Montefiore Castle";

    // We want to print the std::variant correctly, but we cannot just use the << operator
    //std::cout << house1 << std::endl;

    AddressPrinter ap;
    std::visit(ap, house1); // arguments are a callable (the visitor) and the std::variant(s) that should be processed by the visitor
    std::visit(ap, house2);

    // Another possability is to define lambda functions for the std::visit as an alternative to a visitor callable
    /*
    std::visit(
        [](auto& arg){
            using T = std::decay_t<decltype(arg)>;
            if constexpr (is_same_v(T, std::string)) {
                std::cout << "A house called " << arg << std::endl;
            }
            else {
                std::cout << "House number " << arg << std::endl;
            }
        },
        house1
    );
    */

    return 0;
}
