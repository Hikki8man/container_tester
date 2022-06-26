#include <iostream>
#include <string>
#include <list>
#include <fstream>

#ifdef STD
	#include <stack>
	namespace ft = std;
	std::ofstream ofs("testOutput/std_stack_out.txt");
#else
	#include "../../stack/stack.hpp" // include your stack header file
	std::ofstream ofs("testOutput/ft_stack_out.txt");

#endif


#include "../utils/color.hpp"
#include "../utils/Test.hpp"
int nb = 1;

int main (void) {
	{
		ofs << "STACK TEST" << std::endl;
		ft::stack<int> a;
		// Test 1
		Test<bool>(a.empty(), false);
		// Test 2
		a.push(1);
		Test<bool>(a.empty(), false);
		// Test 3
		Test<int>(a.top(), false);
		// Test 4
		a.pop();
		Test<bool>(a.empty(), false);
		// Test 5
		for (int i = 0; i < 10; ++i) {
			a.push(i);
		}
		 Test<size_t>(a.size(), false);
		// Test 6
		Test<int>(a.top(), false);
		// Test 7
		ft::stack<int> c;
		for (int i = 0; i < 20; ++i) {
			c.push(i + 20);
		}
		a = c;
		Test<size_t>(a.size(), false);
		// Test 8
		Test<int>(a.top(), false);
		// Test 9
		c.pop();
		Test<bool>(a.top() < c.top(), false);
		// Test 10
		Test<bool>(a.top() > c.top(), false);
		// Test 11
		Test<bool>(a.top() == c.top(), false);
		// Test 12
		Test<bool>(a.top() != c.top(),false);
		// Test 13
		Test<bool>(a.top() <= c.top(), false);
		// Test 14
		Test<bool>(a.top() >= c.top(), false);
	}
	{
		ft::stack <std::string, std::list<std::string> > a;

		// Test 15
		Test<bool>(a.empty(), false);
		// Test 16
		a.push("1");
		Test<bool>(a.empty(), false);
		// Test 17
		Test<std::string>(a.top(), false);
		// Test 18
		a.pop();
		Test<bool>(a.empty(), false);
		// Test 19
		for (int i = 0; i < 10; ++i) {
			a.push("string " + std::to_string(i + 1));
		}
		Test<size_t>(a.size(), false);
		// Test 20
		Test<std::string>(a.top(), false);
		// Test 21
		ft::stack<std::string, std::list<std::string> > c;
		for (int i = 0; i < 20; ++i) {
			c.push("string " + std::to_string(i + 1));
		}
		a = c;
		Test<size_t>(a.size(), false);
		// Test 22
		Test<std::string>(a.top(), false);
		// Test 23
		c.pop();
		Test<bool>(a.top() < c.top(), false);
		// Test 24
		Test<bool>(a.top() > c.top(), false);
		// Test 25
		Test<bool>(a.top() == c.top(), false);
		// Test 26
		Test<bool>(a.top() != c.top(), false);
		// Test 27
		Test<bool>(a.top() <= c.top(), false);
		// Test 28
		Test<bool>(a.top() >= c.top(), false);
		// Test 29
		Test<bool>(a < c, false);
		Test<bool>(a <= c);
		Test<bool>(a > c);
		Test<bool>(a >= c);
		Test<bool>(a == c);
		Test<bool>(a != c);
	}
	ofs.close();
}