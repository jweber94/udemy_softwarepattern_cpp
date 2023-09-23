#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;


struct Journal { // struct: everything is public by default
	// members
	std::string _title;
	std::vector<std::string> _entries;

	// constructor
	Journal (const std::string& title) : _title(title) {}

	// methods
	void add_entry(const std::string& entry) {
		static int count = 1;
		_entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
	}

	/*
	void save(const std::string& filename) {
		// works but we break the single responsability principle by adding another "persistance" functionallity to the journal which should only implement basic journal functionallity
		// problem with this approach: We need to implement overloaded functions for everything that we want to be able to safe for all journal, books, ... if we have multiple classes that should be safed
		std::ofstream ofs(filename);
		for (auto& it : _entries)
		{
			ofs << it << std::endl;
		}
	}
	*/

};


// better: separation of concerns --> implement a persistance manager which is agostic to the type how we should persist its handed over data
struct PersistanceManager {
	
	
	PersistanceManager() {

	}

	static void save(const Journal& j, const std::string& filename) {
		std::ofstream ofs(filename);
		for (auto& it : j._entries) {
			ofs << it << std::endl;
		}
	}

};

int main()
{

	Journal myJournal("FooBar");

	myJournal.add_entry("Testing");
	myJournal.add_entry("Works");

	// myJournal.save();
	PersistanceManager pm;
	pm.save(myJournal, "out.txt");

	getchar(); // halt program before termination in order to have the output under windows visable in cmd
	return 0;
}
