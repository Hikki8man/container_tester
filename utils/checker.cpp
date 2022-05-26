#include <iostream>
#include <string>
#include <fstream>
#include "color.hpp"

int main (int ac, char **av) {
	if (ac != 4) {
		std::cout << "Usage: " << av[0] << " container to test" << " <file ft> <file std>" << std::endl;
		return (1);
	}
	std::ifstream f1(av[2]);
	std::ifstream f2(av[3]);
	bool failed = false;

	if (!f1.is_open() || !f2.is_open()) {
		std::cout << "Error: could not open file" << std::endl;
		return (1);
	}
	std::string s1, s2;
	int i = 0;
	std::cout << FG_YELLOW << av[1] << " test:" << std::endl;
	while (getline(f1, s1)) {
		getline(f2, s2);
		if (i == 0) {
			++i;
			continue;
		}
		if (s1 != s2) {
			if (s1.find("SEGFAULT") != std::string::npos)
				std::cout << FG_RED << i << ": " << "SIGSEGV ";
			else
				std::cout << FG_RED << i << ": " << "FAIL ";
			failed = true;
		}
		else {
			if (s1.find("SEGFAULT") != std::string::npos)
				std::cout << FG_GREEN << i << ": " << "SIGSEGV ";
			else
				std::cout << FG_GREEN << i << ": OK ";
		}
		++i;
	}
	std::cout << std::endl;
	if (failed) {
		std::cout << FG_RED << "TEST FAILED !!" << FG_WHITE << std::string(" check \"diff_") +  av[1] + ".txt\"" << std::endl;
		system(std::string("diff " + std::string(av[2]) + " " + std::string(av[3]) + " >> diff/diff_" + av[1] + ".txt").c_str());

	}
	else
		std::cout << FG_GREEN << "TEST PASSED !" << std::endl;
	
	std::cout << RESET_ALL;

	return (0);
}