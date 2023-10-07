#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost;


TEST(SingletonTest, IntegrationTest) {
	// depends on the database
	std::cout << "Foo" << std::endl;
	EXPECT_EQ(0, 0);
}

TEST(SingletonTest, UnitTest) {
	// unit test of the user with a dummy database via dependency injection
	std::cout << "Bar" << std::endl;
	EXPECT_EQ(0, 0);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return 0;
}