#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <map>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum class Importance {
    primary,
    secondary,
    tertiary
};

template<typename T, typename Key = std::string> // Key is an optional template argument. If not specified further, it will used as a std::string
class Multiton {
    public:
        static std::shared_ptr<T> get(const Key& key) {
            /*
                In this example we check if a key was already called on the multiton
                and if not we add it to the multitons static memory.
                We initialize the static members defacto on the fly
            */
            if (
                const auto it = _instances.find(key); 
                it != _instances.end()
               ) 
            {
                return it->second;
            } else {
                std::shared_ptr<T> new_instance = std::make_shared<T>();
                _instances.insert{key, new_instance};
                return new_instance;
            }
        }
    
    protected:
        Multiton() = default;
        virtual ~Multiton() = default;

    private:
        static std::map<Key, std::shared_ptr<T>> _instances;
};

// initialize the static map for the multiton
template<typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::_instances;

// The Printer should not have any arguments to create a Multiton of it in our case here
class Printer {
    public:
        Printer() {
            _totalInstanceCount++;
            std::cout << "A total of " << Printer::_totalInstanceCount << " printer instances are created so far" << std::endl;

        }
    private:
        static int _totalInstanceCount;
};
int Printer::_totalInstanceCount{0};

int main()
{
    typedef Multiton<Printer, Importance> mt; // only a typedef to have shorter access to the multiton

    std::shared_ptr<Printer> main = mt::get(Importance::primary);   // init case of get
    std::shared_ptr<Printer> aux1 = mt::get(Importance::secondary); // init case of get
    std::shared_ptr<Printer> aux2 = mt::get(Importance::secondary); // return case of get

    // since we work with shared_ptr we can change the properties of the printer and access them later on via the multiton

	return 0;
}