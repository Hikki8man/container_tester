#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <fstream>

extern std::ofstream ofs;
extern int nb;

template <typename T>
class Test {
	public:
		Test(T a, bool sameTest) {
			if (sameTest == false) {
				ofs << std::endl;
				ofs << "Test " << nb << ": " << a;
				nb++;
			}
			else
				ofs << " " << a;
		}
};

#endif // TEST_HPP