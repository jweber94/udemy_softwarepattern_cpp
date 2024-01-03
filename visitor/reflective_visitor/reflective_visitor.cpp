#include <iostream>
#include <string>
#include <sstream>

struct Expression {
	virtual ~Expression() = default;
};

struct DoubleExpression : public Expression {
	double value;
	DoubleExpression(double val) : value(val) {}
};

struct AdditionExpression : public Expression {
	// We want to define a datastructure which represents 1 + 2 + 3
	//        +
	//       / \
	//		1	+
	//		   / \
	//		  2   3
	// So we need our left and right members (we have kinda like a binary tree here) as Expressions, so we can either have a DoubleExpression or a AdditionExpression/SubtractionExpression
	Expression* left;
	Expression* right;

	AdditionExpression(Expression* left, Expression* right) :
		left(left),
		right(right)
	{}

	~AdditionExpression() {
		delete left;
		delete right;
	}
};


struct ExpressionPrinter{
	std::ostringstream oss;

	std::string str() const {
		return oss.str();
	}

	void print(Expression* e) {
		// we do a downcast of the base class Expression to the specific derived classes
			// https://en.cppreference.com/w/cpp/language/dynamic_cast - caution: this has a high runtime cost
		if (auto de = dynamic_cast<DoubleExpression*>(e)) { // dynamic_cast delivers a nullptr if we can not cast the base class into the derived class which is specified within the template argument
			oss << de->value;
		}
		else if (auto ae = dynamic_cast<AdditionExpression*>(e)) {
			oss << "( ";
			print(ae->left);
			oss << " + ";
			print(ae->right);
			oss << " )";
		}
		else {
			// this is a problem with the reflective approach: If we miss a downcast/add a new expression but forget to add the print functionallity here, we might encounter problems/unexpected behaviour at runtime and we break the open-close principle
			std::cout << "CAUTION: Unknown expression was handed over to the print method of the ExpressionPrinter" << std::endl;
		}
	}


	/*
	// does not work since the compiler does the dispatching of the methods at compile time
	void print(DoubleExpression* de, std::ostringstream& oss) const {
		oss << de->value;
	}

	void print(AdditionExpression* ae, std::ostringstream& oss) const {
		oss << "( ";
		print(ae->left, oss); // this will not work, since we do not know of what type ae->left is. We only know that it can be called via the Expression base class pointer, but to dispatch the correct print method, we do not know which print method needs to be called, since we need to know them at complile time
		oss << " + ";
		print(ae->right, oss);
		oss << " )";
	}
	*/
};

int main() {
	Expression* e = // (1 + ( 2 + 4 ))
		new AdditionExpression(
			new DoubleExpression{1},
			new AdditionExpression(
				new DoubleExpression(2),
				new DoubleExpression(4)
			)
		);
	
	ExpressionPrinter exprPrinter;
	exprPrinter.print(e);
	std::cout << exprPrinter.str() << std::endl;

	return 0;
}