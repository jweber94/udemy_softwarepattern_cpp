#include <iostream>
#include <string>
#include <sstream>

struct Expression {
	virtual ~Expression() = default;
	virtual void print(std::ostringstream& oss) = 0;
};

struct DoubleExpression : public Expression {
	double value;
	DoubleExpression(double val) : value(val) {}

	void print(std::ostringstream& oss) override {
		oss << value;
	}
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

	void print(std::ostringstream& oss) override {
		oss << "( ";
		left->print(oss);
		oss << " + ";
		right->print(oss);
		oss << " )";
	}
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
	std::ostringstream oss;
	e->print(oss);
	std::cout << "Equation is: " << oss.str() << std::endl;

	return 0;
}