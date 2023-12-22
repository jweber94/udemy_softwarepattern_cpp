#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <memory>

// lexing utilities
struct Token {
    enum Type {integer, variable, plus, minus} type;
    std::string rawData;
    bool valid{ true };

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << "type: " << token.type << ", data: " << token.rawData << ", valid: " << token.valid;
        return os;
    }
};

std::vector<Token> lex(const std::string& inputString) {
    std::vector<Token> result;
    for (int i = 0; i < inputString.size(); i++) {
        switch (inputString.at(i)) {
        case '+':
            result.push_back(Token{Token::Type::plus, "+", true});
            break;
        case '-':
            result.push_back(Token{ Token::Type::minus, "-", true });
            break;
        default:
            // TODO: encapsulate this into a separate function with modus operandi for the type (integer or variable)
            if (std::isdigit(inputString.at(i))) { // integer
                std::stringstream buffer{};
                buffer << inputString.at(i);
                if ((i + 1) == inputString.size()) { // edge case: end of the inputString will not enter the for loop
                    result.push_back(Token{ Token::Type::integer, buffer.str(), true });
                }

                // get integer in its full length
                for (int j = i + 1; j < inputString.size(); j++) {
                    if (std::isdigit(inputString.at(j))) {
                        buffer << inputString.at(j);
                        if ((j + 1) == inputString.size()) {
                            result.push_back(Token{ Token::Type::integer, buffer.str(), true });
                            i = j;
                            break;
                        }
                    }
                    else {
                        result.push_back(Token{Token::Type::integer, buffer.str(), true});
                        i = j - 1; // update parent for loop
                        break; // stop the inner for loop
                    }
                }
            }
            else { // variable
                // we have encountered a variable
                std::stringstream buffer{};
                buffer << inputString.at(i);
                if ((i + 1) == inputString.size()) { // edge case: end of the inputString will not enter the for loop
                    result.push_back(Token{ Token::Type::variable, buffer.str(), true });
                }

                // if our variable has more then one letter, it is invalid
                for (int j = i + 1; j < inputString.size(); j++) {
                    if (!std::isdigit(inputString.at(j)) && (inputString.at(j) != '+') && (inputString.at(j) != '-')) {
                        buffer << inputString.at(j);
                        if ((j + 1) == inputString.size()) {
                            result.push_back(Token{ Token::Type::variable, buffer.str(), false });
                            i = j;
                            break;
                        }
                    }
                    else {
                        bool validVar = (buffer.str().size() > 1);
                        result.push_back(Token{ Token::Type::variable, buffer.str(), validVar });
                        i = j - 1; // update parent for loop
                        break; // stop the inner for loop
                    }
                }
            }
        }
    }
    return result;
}

// parsing utilities
struct Element {
    virtual int eval() const = 0; // the evaluation should not modify the element
};

struct Integer : public Element {
    int value;
    Integer(int value) : value(value) {}

    int eval() const override {
        return value;
    }
};

struct BinaryOperation : public Element {
    enum Type { addition, subtraction } type;
    std::shared_ptr<Element> lhs, rhs;

    int eval() const override {
        // get the values from the binary operation sides as int value (since we can only process integers)
        auto left = lhs->eval();
        auto right = rhs->eval();
        // calculate based on the operation that is associated with this element
        if (type == Type::addition) {
            return left + right;
        }
        else {
            return left - right;
        }
    }
};

struct ExpressionProcessor
{
    friend class Variable;
    std::map<char, int> variables;

    int calculate(const std::string& expression)
    {
        // misc
        int tmpValue{ -1 };
        auto result = std::make_shared<BinaryOperation>();
        int tmpResult = { 0 };
        bool have_lhs{ false };
        bool have_rhs{ false };
        std::shared_ptr<Integer> integer;

        // tokenize
        std::vector<Token> tokenizedExpression = lex(expression);
        
        // parse
        for (auto& token : tokenizedExpression) {
            if (have_rhs) {
                tmpResult = result->eval();
                result->lhs = std::make_shared<Integer>(tmpResult); // set evaluated value to the left hand side
                result->rhs = nullptr; // and invalidate the righthandside to be able to assign it with the next token
                have_rhs = false;
            }
            
            switch (token.type) {
            case Token::Type::integer:
                tmpValue = std::stoi(token.rawData);
                integer = std::make_shared<Integer>(tmpValue);
                // add the integer to the binary operation that should deliver us the result at the end
                if (!have_lhs) {
                    result->lhs = integer;
                    have_lhs = true;
                }
                else {
                    result->rhs = integer;
                    have_rhs = true;
                }
                break;
            case Token::Type::variable:
                if (!token.valid) { // if our received expression contains an invalid token, we always return 0 as our result
                    std::cerr << "Invalid variable with more then one letter detected" << std::endl;
                    return 0;
                }
                assert(token.rawData.size() == 1); // if a variable token is valid it can only have a size of 1 which is the requirement for the conversion from std::string to char
                if (variables.find(token.rawData[0]) == variables.end()) {
                    std::cerr << "Undefined variable detected" << std::endl;
                    return 0;
                }

                tmpValue = variables.at(token.rawData[0]);
                integer = std::make_shared<Integer>(tmpValue);
                // add the integer to the binary operation that should deliver us the result at the end
                if (!have_lhs) {
                    result->lhs = integer;
                    have_lhs = true;
                }
                else {
                    result->rhs = integer;
                    have_rhs = true;
                }
                break;
            case Token::Type::plus:
                result->type = BinaryOperation::Type::addition;
                break;
            case Token::Type::minus:
                result->type = BinaryOperation::Type::subtraction;
                break;
            }
        }
        return result->eval();
    }
};

int main() {
    ExpressionProcessor processor;

    std::string input1{ "1+2+3" };
    std::string input2{ "1+2+xy" };
    std::string input3{ "10-2-x" };

    /*
    std::cout << "Testing the lexer" << std::endl;
    auto testResult = lex(input3);
    for (auto& it : testResult) {
        std::cout << it << std::endl;
    }
    */

    std::cout << "Expect 6: " << processor.calculate(input1) << std::endl;
    std::cout << "Expect 0: " << processor.calculate(input2) << std::endl;

    processor.variables.insert({'x', 3}); // add a variable to the processor
    std::cout << "Expect 5: " << processor.calculate(input3) << std::endl;

    return 0;
}