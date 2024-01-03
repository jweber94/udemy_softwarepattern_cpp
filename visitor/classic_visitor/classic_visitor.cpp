#include <iostream>
#include <string>
#include <sstream>

/* visitor implementation via interface and derivered class as differenciation for a concern */
struct DoubleExpression;
struct AdditionExpression;
struct SubtractionExpression;

struct ExpressionVisitor {
	// here we define all possible overloads - this is needed for the compile time dispatching, see the comment of the visit() method within DoubleExpression
	virtual void visit(DoubleExpression* de) = 0;
	virtual void visit(AdditionExpression* de) = 0;
	virtual void visit(SubtractionExpression* de) = 0;
};

struct ExpressionPrinter : public ExpressionVisitor {
	std::ostringstream oss;

	std::string str() const { return oss.str(); }

	void visit(DoubleExpression* de) override;
	void visit(AdditionExpression* ae) override;
	void visit(SubtractionExpression* ae) override;
};

struct ExpressionEvaluator : public ExpressionVisitor {
	double result{ 0 };

	void visit(DoubleExpression* de) override;
	void visit(AdditionExpression* ae) override;
	void visit(SubtractionExpression* ae) override;
};

/* actual datastructure */
struct Expression {
	virtual ~Expression() = default;
	virtual void accept(ExpressionVisitor* visitor) = 0; // see the comment within DoubleExpression for details
};

struct DoubleExpression : public Expression {
	double value;
	DoubleExpression(double val) : value(val) {}

	void accept(ExpressionVisitor* visitor) override {
		visitor->visit(this); // this code needs to be in all derived classes of Expression - this is the workaround of our dispatching, since the this pointer has the derived classes type associated with it, which would not be the case if we implement this method within the Expression base class
	}
};

struct AdditionExpression : public Expression {
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

	void accept(ExpressionVisitor* visitor) override {
		visitor->visit(this);
	}
};

struct SubtractionExpression : public Expression {
	Expression* left;
	Expression* right;

	SubtractionExpression(Expression* left, Expression* right) :
		left(left),
		right(right)
	{}

	~SubtractionExpression() {
		delete left;
		delete right;
	}

	void accept(ExpressionVisitor* visitor) override {
		visitor->visit(this);
	}
};

/* We need to have the definitions (all methods etc, not just the forward declaration of the class) to implement the visit methods with the derived class specific Expression properties. Therefor we need to put them after the expression definitions and not right inside or after the ExpressionPrinter visitor definition */
void ExpressionPrinter::visit(DoubleExpression* de) {
	oss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression* ae) {
	bool need_braces = dynamic_cast<SubtractionExpression*>(ae->right); // we have a subexpression at the right side of the minus sign
	ae->left->accept(this);
	oss << " + ";
	if (need_braces) {
		oss << "( ";
	}
	ae->right->accept(this);
	if (need_braces) {
		oss << " )";
	}
}

void ExpressionPrinter::visit(SubtractionExpression* se) {
	bool need_braces = dynamic_cast<SubtractionExpression*>(se->right); // we have a subexpression at the right side of the minus sign
	if (need_braces) {
		oss << "( ";
	}
	se->left->accept(this);
	oss << " - ";
	se->right->accept(this);
	if (need_braces) {
		oss << " )";
	}
}

void ExpressionEvaluator::visit(DoubleExpression* de) {
	result += de->value;
}

void ExpressionEvaluator::visit(AdditionExpression* ae) {
	if (auto l = dynamic_cast<DoubleExpression*>(ae->left)) {
		result += l->value;
	}
	else {
		ae->left->accept(this);
	}

	if (auto r = dynamic_cast<DoubleExpression*>(ae->right)) {
		result += r->value;
	}
	else {
		ae->right->accept(this);
	}
}

void ExpressionEvaluator::visit(SubtractionExpression* se) {
	if (auto l = dynamic_cast<DoubleExpression*>(se->left)) {
		result += l->value;
	}
	else {
		se->left->accept(this);
	}

	if (auto r = dynamic_cast<DoubleExpression*>(se->right)) {
		result -= r->value;
	}
	else {
		se->right->accept(this);
	}
}

int main() {
	auto e = // (1 + ( 2 - 4 ))
		new AdditionExpression(
			new DoubleExpression{10},
			new SubtractionExpression(
				new DoubleExpression(2),
				new DoubleExpression(5)
			)
		);
	
	ExpressionPrinter ep;
	ep.visit(e);
	std::cout << ep.str() << std::endl;

	ExpressionEvaluator ev;
	ev.visit(e);
	std::cout << "Result is " << ev.result << std::endl;

	return 0;
}