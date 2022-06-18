#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <csignal>

#ifdef STD
	#include <map>
	namespace ft = std;
	std::ofstream ofs("testOutput/std_map_out.txt");
#else
	#include "../..//map.hpp" // include your stack header file
	std::ofstream ofs("testOutput/ft_map_out.txt");

#endif

#include "../utils/color.hpp"
#include "../utils/Test.hpp"

int nb = 1;

void segfault_handler(int sig) {
	(void)sig;
	Test<std::string>("SEGFAULT", false);
	throw std::runtime_error("SEGFAULT");
}

int main() {
	std::signal(SIGSEGV, &segfault_handler);

	ofs << "MAP TEST";
	ft::map<std::string, int>	test;

	try {
		test.insert(ft::pair<std::string, int>("m", 1));
		test.insert(ft::pair<std::string, int>("f", 2));
		test.insert(ft::pair<std::string, int>("c", 4));
		test.insert(ft::pair<std::string, int>("d", 4));
		test.insert(ft::pair<std::string, int>("e", 4));
		test.insert(ft::pair<std::string, int>("u", 4));
		test.insert(ft::pair<std::string, int>("p", 4));
		test.insert(ft::pair<std::string, int>("l", 4));
		test.insert(ft::pair<std::string, int>("a", 4));
		test.insert(ft::pair<std::string, int>("g", 4));
		test.insert(ft::pair<std::string, int>("n", 4));
		test.insert(ft::pair<std::string, int>("o", 4));
		test.insert(ft::pair<std::string, int>("q", 4));
		test.insert(ft::pair<std::string, int>("r", 4));
		test.insert(ft::pair<std::string, int>("s", 4));
	} catch (...) {}

	// Test 1 - find
	try {
		// Find dans une map vide
		ft::map<std::string, int>::iterator it = test.find("a");
		Test<std::string>(it != test.end() ? "it != test.end()" : "it == test.end()", false);

		// Find un element qui existe
		ft::map<std::string, int>::iterator it2 = test.find("a");
		Test<std::string>(it2 != test.end() ? "it2 != test.end()" : "it2 == test.end()", true);

		// Find un element qui existe pas
		ft::map<std::string, int>::iterator it3 = test.find("z");
		Test<std::string>(it3 != test.end() ? "it3 != test.end()" : "it3 == test.end()", true);
	} catch(...) {}

	// Test 2 - capacity
	try {
		// size
		Test<int>(test.size(), false);

		// empty
		Test<bool>(test.empty(), true);

		// max_size
		Test<int>(test.max_size(), true);
	} catch (...) {}

	// // Test 3 - upper / lower bound

	// try {
	// 	// upper_bound
	// 	ft::map<std::string, int>::iterator it = test.upper_bound("a");
	// 	Test<std::string>((*it).first, false);

	// 	// lower_bound
	// 	ft::map<std::string, int>::iterator it2 = test.lower_bound("a");
	// 	Test<std::string>((*it2).first, true);
	// } catch (...) {}

	// Test 3 - insert

	try {
		ft::map<int, char>m;


	}
	catch (...) {}
}