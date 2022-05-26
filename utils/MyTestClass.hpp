#ifndef MY_TEST_CLASS_HPP
# define MY_TEST_CLASS_HPP

#include <iostream>

class MyTestClass {
	public:
		MyTestClass() : n(17) {};
		MyTestClass(int nb) : n(nb) {};
		MyTestClass(const MyTestClass& other) : n(other.n) {};
		MyTestClass& operator=(const MyTestClass& other) {
			n = other.n;
			return *this;
		}
		~MyTestClass() {};
	
		int n;
};

std::ostream & operator<<(std::ostream & ofs, const MyTestClass& c) {
	ofs << c.n;
	return ofs;
}

#endif