#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/di.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost;


/* We want a database that exists only once in our application */

// The following class defines the singleton which we implemented to use it in our application/business logic
class SingletonDatabase {
	private:
		// private constructor is only called by the first time, the static get() function is called
		SingletonDatabase() {
			std::cout << "Initializing database" << std::endl;
			std::ifstream ifs("/home/jens/Desktop/udemy/udemy_softwarepattern_cpp/Singleton/Singleton/capitals.txt");
			std::string s, s2;
			while (getline(ifs, s)) { 	// name
				getline(ifs, s2);		// number
				int population = std::stoi(s2);
				_capitals.insert({s, population});
			}
		}
	
		std::map<std::string, int> _capitals;

	public:
		// avoid creating copied of our singleton
		SingletonDatabase(SingletonDatabase const&) = delete;
		void operator=(SingletonDatabase const&) = delete;

		static SingletonDatabase& get() {
			static SingletonDatabase db;
			return db;
		}

		int get_population(const std::string& city) {
			int pop{0};
			try {
				pop = _capitals.at(city);
			} catch (...) {
				std::cerr << "There is no city called " << city << std::endl;
				pop = -1;
			}
			return pop;
		}
};

// this represents our application/business logic
struct SingletonRecordFinder {
	int total_population(std::vector<std::string> cities) {
		int res{0};
		for (auto& city : cities) {
			res += SingletonDatabase::get().get_population(city);
		}
		return res;
	};
};

// Here we want to test our application logic, that uses the singleton under the hood
TEST(SingletonTest, IntegrationTest) {
	// depends on the database
	SingletonRecordFinder rf;
	std::vector<std::string> cities {"Tokyo", "New York"}; // To prepare the test, we need to have knowlage about the database - this is not good unit test practice
	EXPECT_EQ((33200000 + 17800000), rf.total_population(cities)); // We need to have up-to-date values of the database that we have under to hood to have a valid number to test against - maybe the number of (in our example) inhabitants vary over time and this would invalidate the test
	/* The problem with this test is that we depend hardly on the database that is accessed via the singleton. Therefor we have implemented an integration test instead of an unit test for SingletonRecordFinder */
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}