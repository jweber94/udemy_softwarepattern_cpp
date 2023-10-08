#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Printer {
    static int _id; // static members are a defacto singleton

    public:
        int get_id() const {
            return _id;
        }

        void set_id(int idVal) {
            _id = idVal;
        }
};

int Printer::_id{0};

int main()
{
    Printer p1;
    Printer p2;

    p2.set_id(5); // set works for all printer instances since it is static - this breaks the application code if we are not aware of the monostate
    
    int id2 = p2.get_id();
    int id1 = p1.get_id();

    std::cout << id1 << "; " << id2 << std::endl;
	return 0;
}