#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Document {};

struct IMachine {
    virtual void print(Document& doc) = 0;
    virtual void scan(Document& doc) = 0;
    virtual void fax(Document& doc) = 0;
};

struct MultiPurposePrinter : public IMachine {

    void print(Document& doc) override {
        std::cout << "OK" << std::endl;
    }
    void scan(Document& doc) override {
        std::cout << "OK" << std::endl;
    }
    void fax(Document& doc) override {
        std::cout << "OK" << std::endl;
    }
};

struct FaxMachine : public IMachine {
    // This breaks the interface segregation principle because we need to implement print and scan even if the FaxMachine does not deliver a valid call for it
    void print(Document& doc) override {
        std::cout << "Not implemented" << std::endl;
    }
    void scan(Document& doc) override {
        std::cout << "Not implemented" << std::endl;
    }
    void fax(Document& doc) override {
        std::cout << "OK" << std::endl;
    }
};


int main()
{
    Document myDoc;
    FaxMachine faxer;
    
    faxer.fax(myDoc);   // OK
    faxer.scan(myDoc);  // Not OK

	return 0;
}