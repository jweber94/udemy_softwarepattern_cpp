#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <boost/lexical_cast.hpp>

// tokenize the numbers and arithmetic expressions
struct Token {
	enum Type{integer, plus, minus, lparentesis, rparentesis} type;
	std::string text; // raw text of the token (without its associated interpretation)

	Token(Type type, const std::string& text) :
		type(type),
		text(text)
	{}

	// be able to print the token easily
	friend std::ostream& operator<<(std::ostream& os, const Token& token) {
		os << "'" << token.text << "'" << std::endl;
		return os;
	}
};

// lexer
std::vector<Token> lex(const std::string& input) {
	std::vector<Token> result;
	for (int i = 0; i < input.size(); i++) {
		switch (input.at(i)) {
		case '+':
			result.push_back(Token{ Token::Type::plus, "+" });
			break;
		case '-':
			result.push_back(Token{ Token::Type::minus, "-" });
			break;
		case '(':
			result.push_back(Token{ Token::Type::lparentesis, "(" });
			break;
		case ')':
			result.push_back(Token{ Token::Type::rparentesis, ")" });
			break;
		default: // assume we only feed integers within our string - under this assumtion, if no arithmetic operation is handed over, then it must be an integer
			std::ostringstream buffer;
			buffer << input.at(i); // take the first number of our integer
			for (int j = i + 1; j < input.size(); j++) { // check the length of the integer and add them to the buffer
				if (std::isdigit(input.at(j))) {
					buffer << input.at(j);
					i++; // do not process the integer that we added to the buffer a second time from the outter for loop (i based)
				}
				else {
					result.push_back(Token{Token::Type::integer, buffer.str()});
					break; // stop the j based integer search for loop
				}
			}
		}
	}
	return result;
}

// parser
struct Element {
	virtual int eval() const = 0; // the evaluation should not modify the element
};

struct Integer : public Element {
	int value;
	Integer (int value) : value(value) {}

	int eval() const override {
		return value;
	}
};

struct BinaryOperation : public Element {
	enum Type {addition, subtraction} type;
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

// actual parsing step - we want to convert our complete tokenized expression into a single integer element. Therefore we need to return here just one single element which we can evaluate to an int
std::shared_ptr<Element> parse(const std::vector<Token>& tokens) {
	/*
		We assume that we can not process nested brackets to make the example not too complicated
	*/
	auto result = std::make_unique<BinaryOperation>();
	bool have_lhs{ false };
	std::shared_ptr<Integer> integer;
	int value;
	for (int i = 0; i < tokens.size(); i++) {
		auto& token = tokens.at(i); // we need the reference here in order to modify the token within the tokens vector
		switch (token.type) {
		case Token::Type::integer:
			// create an integer
			value = boost::lexical_cast<int>(token.text);
			integer = std::make_shared<Integer>(value);
			// add the integer to the binary operation that should deliver us the result at the end
			if (!have_lhs) {
				result->lhs = integer;
				have_lhs = true;
			}
			else {
				result->rhs = integer;
			}
			break;
		case Token::Type::plus:
			result->type = BinaryOperation::Type::addition;
			break;
		case Token::Type::minus:
			result->type = BinaryOperation::Type::subtraction;
			break;
		case Token::Type::lparentesis:
			int j = i; // get the currently parsed token as our index j that describes the left parentesis
			// determine the index where the lparent is closed by the right parent
			for (; j < tokens.size(); ++j) {
				if (tokens.at(j).type == Token::Type::rparentesis) { // stop the bracket processing at the right parenthesis
					break;
				}
			}
			// get the parenthesized subexpression and parse it to a binary expression element which we can evaluate if we want to
			std::vector<Token> subexpression(&tokens.at(i + 1), &tokens.at(j));
			auto element = parse(subexpression);
			if (!have_lhs) {
				result->lhs = element;
				have_lhs = true;
			}
			else {
				result->rhs = element;
			}
			i = j;
			break;
		// We do not need to have a special handling for the right parentesis since this is only the termination condition for the subexpression of the lparentesis case
		//case Token::Type::rparentesis:
		//	break;
		}
	}
	return result;
}

int main() {
	std::string input{"(13-4)-(12+1)"};
	// verify lexer
	auto tokens = lex(input);
	for (auto& token : tokens) {
		std::cout << token << " ";
	}
	std::cout << std::endl;

	// verify parser
	std::shared_ptr<Element> calcResult;
	try { // try catch block is needed since the lexical_cast<> can throw if we receive an unconvertable character to our targeted datatype
		calcResult = parse(tokens);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Our final result is: " << calcResult->eval() << std::endl;
	return 0;
}