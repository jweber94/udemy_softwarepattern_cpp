#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Document {};

struct IPrinter {
    virtual void print(Document& doc) = 0;
};

struct IScanner {
    virtual void scan(Document& doc) = 0;
};

struct IFax {
    virtual void fax(Document& doc) = 0;
};

struct IPrintScanner : public IPrinter, public IScanner {

};

struct IMachine : public IPrinter, public IScanner, public IFax {
};


// Make the MutliPurposePrinter a decorator around the segragated interfaces
struct MultiPurposePrinter : public IMachine {

    IPrinter& _printer;
    IScanner& _scanner;
    IFax& _fax;

    MultiPurposePrinter(IPrinter& printer, IScanner& scanner, IFax& fax) : 
    _printer(printer),
    _scanner(scanner),
    _fax(fax)
    {}

    void print(Document& doc) override {
        _printer.print(doc);
    }
    void scan(Document& doc) override {
        _scanner.scan(doc);
    }
    void fax(Document& doc) override {
        _fax.fax(doc);
    }
};

struct FaxMachine : public IFax {
    void fax(Document& doc) override {
        std::cout << "OK" << std::endl;
    }
};


int main()
{
    Document myDoc;
    FaxMachine faxer;
    
    faxer.fax(myDoc);   // OK
    //faxer.scan(myDoc);  // Not OK

	return 0;
}