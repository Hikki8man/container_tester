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

Test t;

int main (void) {

	clock_t start_test;
	clock_t time_test;
	srand(0);
	start_test = clock();

	{
		ofs << "STACK TEST" << std::endl;
		ft::stack<int> a;
		// Test 1
		t.newTest();
		t.print<bool>(a.empty());
		// Test 2
		t.newTest();
		a.push(1);
		t.print<bool>(a.empty());
		// Test 3
		t.newTest();
		t.print<int>(a.top());
		// Test 4
		t.newTest();
		a.pop();
		t.print<bool>(a.empty());
		// Test 5
		t.newTest();
		for (int i = 0; i < 10; ++i) {
			a.push(i);
		}
		 t.print<size_t>(a.size());
		// Test 6
		t.newTest();
		t.print<int>(a.top());
		// Test 7
		t.newTest();
		ft::stack<int> c;
		for (int i = 0; i < 20; ++i) {
			c.push(i + 20);
		}
		a = c;
		t.print<size_t>(a.size());
		// Test 8
		t.newTest();
		t.print<int>(a.top());
		// Test 9
		t.newTest();
		c.pop();
		t.print<bool>(a.top() < c.top());
		// Test 10
		t.newTest();
		t.print<bool>(a.top() > c.top());
		// Test 11
		t.newTest();
		t.print<bool>(a.top() == c.top());
		// Test 12
		t.newTest();
		t.print<bool>(a.top() != c.top());
		// Test 13
		t.newTest();
		t.print<bool>(a.top() <= c.top());
		// Test 14
		t.newTest();
		t.print<bool>(a.top() >= c.top());
	}
	{
		ft::stack <std::string, std::list<std::string> > a;

		// Test 15
		t.newTest();
		t.print<bool>(a.empty());
		// Test 16
		t.newTest();
		a.push("1");
		t.print<bool>(a.empty());
		// Test 17
		t.newTest();
		t.print<std::string>(a.top());
		// Test 18
		t.newTest();
		a.pop();
		t.print<bool>(a.empty());
		// Test 19
		t.newTest();
		for (int i = 0; i < 10; ++i) {
			a.push("string " + std::to_string(i + 1));
		}
		t.print<size_t>(a.size());
		// Test 20
		t.newTest();
		t.print<std::string>(a.top());
		// Test 21
		t.newTest();
		ft::stack<std::string, std::list<std::string> > c;
		for (int i = 0; i < 20; ++i) {
			c.push("string " + std::to_string(i + 1));
		}
		a = c;
		t.print<size_t>(a.size());
		// Test 22
		t.newTest();
		t.print<std::string>(a.top());
		// Test 23
		t.newTest();
		c.pop();
		t.print<bool>(a.top() < c.top());
		// Test 24
		t.newTest();
		t.print<bool>(a.top() > c.top());
		// Test 25
		t.newTest();
		t.print<bool>(a.top() == c.top());
		// Test 26
		t.newTest();
		t.print<bool>(a.top() != c.top());
		// Test 27
		t.newTest();
		t.print<bool>(a.top() <= c.top());
		// Test 28
		t.newTest();
		t.print<bool>(a.top() >= c.top());
		// Test 29
		t.newTest();
		t.print<bool>(a < c);
		t.print<bool>(a <= c);
		t.print<bool>(a > c);
		t.print<bool>(a >= c);
		t.print<bool>(a == c);
		t.print<bool>(a != c);
		// Test 30
		t.newTest();
		for (int i = 0; i < 10000; ++i) { // need time to test
			a.push("string " + std::to_string(i + 1));
		}
	}
	time_test = clock() - start_test;
	float time_f;
	time_f = ((float)time_test)/CLOCKS_PER_SEC;
  	ofs << std::endl;
  	ofs << "Time: " << time_f << std::endl;

	ofs.close();
}