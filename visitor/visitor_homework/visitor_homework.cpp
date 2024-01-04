#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// forward declaration for the ExpressionVisitor
struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor
{
    virtual void accept(Value& valPtr) = 0;
    virtual void accept(AdditionExpression& valPtr) = 0;
    virtual void accept(MultiplicationExpression& valPtr) = 0;
};

struct Expression
{
    virtual void visit(ExpressionVisitor& ev) = 0;
};

struct Value : Expression
{
    int value;

    Value(int value) : value(value) {}
    
    void visit(ExpressionVisitor& ev) override {
        ev.accept(*this); // the derived classes this pointer contains type information about the derived class, so we need to overload the visit method within all derived classes, even if the code is everywhere the same
    }
};

struct AdditionExpression : Expression
{
    Expression& lhs, & rhs;

    AdditionExpression(Expression& lhs, Expression& rhs) : lhs(lhs), rhs(rhs) {}

    void visit(ExpressionVisitor& ev) override {
        ev.accept(*this);
    }
};

struct MultiplicationExpression : Expression
{
    Expression& lhs, & rhs;

    MultiplicationExpression(Expression& lhs, Expression& rhs)
        : lhs(lhs), rhs(rhs) {}

    void visit(ExpressionVisitor& ev) override {
        ev.accept(*this);
    }
};

struct ExpressionPrinter : ExpressionVisitor
{
    std::ostringstream oss;

    void accept(Value& valPtr) override {
        oss << valPtr.value;
    }

    void accept(AdditionExpression& valPtr) override {
        oss << "(";
        valPtr.lhs.visit(*this);
        oss << "+";
        valPtr.rhs.visit(*this);
        oss << ")";
    }

    void accept(MultiplicationExpression& valPtr) override {
        valPtr.lhs.visit(*this);
        oss << "*";
        valPtr.rhs.visit(*this);
    }

    std::string str() const { return oss.str(); }
};

int main() {
    Value v2{ 2 };
    Value v3{ 3 };
    AdditionExpression simple{ v2,v3 };
    ExpressionPrinter ep;
    ep.accept(simple);
    std::cout << "Expected: (2+3) - got: " << ep.str() << std::endl;

    return 0;
}