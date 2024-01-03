#include <iostream>
#include <sstream>
#include <string>

// define a generic visitable 
template <typename visitable>
struct Visitor {
	virtual void visit(visitable& obj) = 0;
};

// visitor base class is just a marker interface - needed just for the generic accept method to avoid manually overloading all visitable classes
struct VisitorBase {
	virtual ~VisitorBase() = default;
};


// this is the visitbale base class
struct Expression {
	virtual ~Expression() = default;

	// The main difference between this and the classic approach is that we are able to not implement the accept method within our derived visitable class
	// if we do not do this, we just ignore the visitor if it encounters our derived class
	virtual void accept(VisitorBase& obj) {
		using EV = Visitor<Expression>; // CRTP - check if we can convert the handed over visitor to fit this expression
		if (auto ev = dynamic_cast<EV*>(&obj)) {
			ev->visit(*this); // if this is the case, let it visit this expression/visitable
		}
	}
};

struct DoubleExpression : public Expression {
	double value;
	DoubleExpression(double val) : value(val) {}
	virtual void accept(VisitorBase& obj) { // get a visitor
		using DEV = Visitor<DoubleExpression>; 
		if (auto ev = dynamic_cast<DEV*>(&obj)) { // check wheather the visitor can visit our type
			ev->visit(*this); // if this is the case, let it visit this expression/visitable
		}
	}
};

struct AdditionExpression : public Expression {
	Expression* left;
	Expression* right;
	AdditionExpression(Expression* left, Expression* right) :
		left(left), right(right) 
	{}
	
	~AdditionExpression() {
		delete left;
		delete right;
	}
	
	virtual void accept(VisitorBase& obj) { // get a visitor
		using AEV = Visitor<AdditionExpression>;
		if (auto ev = dynamic_cast<AEV*>(&obj)) { // check wheather the visitor can visit our type
			ev->visit(*this); // if this is the case, let it visit this expression/visitable
		}
	}
};

struct SubtractionExpression : public Expression {
	Expression* left;
	Expression* right;
	SubtractionExpression(Expression* left, Expression* right) :
		left(left), right(right)
	{}

	~SubtractionExpression() {
		delete left;
		delete right;
	}

	virtual void accept(VisitorBase& obj) { // get a visitor
		using AEV = Visitor<SubtractionExpression>;
		if (auto ev = dynamic_cast<AEV*>(&obj)) { // check wheather the visitor can visit our type
			ev->visit(*this); // if this is the case, let it visit this expression/visitable
		}
	}
};

struct ExpressionPrinter :	public VisitorBase,
							public Visitor<DoubleExpression>, // by outcommenting this line, we can disable visítables for specific visitors without breaking the compilation
							public Visitor<AdditionExpression>
{
	void visit(AdditionExpression& obj) override {
		oss << "( ";
		obj.left->accept(*this); // since we are a VisitorBase (due to inheriting from this marker interface), we just can handover this
		oss << " + ";
		obj.right->accept(*this);
		oss << " )";
	}

	void visit(DoubleExpression& obj) override {
		oss << obj.value;
	}

	std::string str() const {
		return oss.str();
	}

private:
	std::ostringstream oss{""};
};

int main() {
	auto e = // (1 + ( 2 - 4 ))
		new AdditionExpression(
			new DoubleExpression{ 10 },
			new AdditionExpression(
				new DoubleExpression(2),
				new DoubleExpression(5)
			)
		);

	ExpressionPrinter ep;
	ep.visit(*e);
	std::cout << ep.str() << std::endl;
	return 0;
}