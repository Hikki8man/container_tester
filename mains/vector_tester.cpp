#include "../utils/color.hpp"
#include "../utils/Test.hpp"
#include "../utils/MyTestClass.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <csignal>
#include <ctime>
#include <chrono>
#include <sys/time.h>


#ifdef STD
	#include <vector>
	namespace ft = std;
	std::ofstream ofs("testOutput/std_vector_out.txt");
#else
	#include "../../vector.hpp" // include your stack header file
	std::ofstream ofs("testOutput/ft_vector_out.txt");

#endif

int nb = 1;


void segfault_handler(int sig) {
	(void)sig;
	Test<std::string>("SEGFAULT", false);
	throw std::runtime_error("SEGFAULT");
}

int main() {

	std::signal(SIGSEGV, &segfault_handler);
	ofs << "VECTOR TEST";
	

	// struct timeval time_now;
	// gettimeofday(&time_now, NULL);
	// time_t time_start = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);


	// test 1: Default constructor
	try {
		ft::vector<int> v;
		Test<size_t>(v.capacity(), false);
		Test<size_t>(v.size(), true);
		Test<bool>(v.empty(), true);
	}
	catch(...) {}

	// test 2: Constructor with size and default value
	try {
		ft::vector<MyTestClass> v(10);
		Test<size_t>(v.capacity(), false);
		Test<size_t>(v.size(), true);
		Test<bool>(v.empty(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
	}
	catch(...) {}

	// test 3: Constructor with size and value
	try {
		ft::vector<MyTestClass> v(10, MyTestClass(12));
		Test<size_t>(v.size(), false);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
	}
	catch(...) {}

	// test 4: Copy constructor
	try {
		ft::vector<MyTestClass> v(10, MyTestClass(22));
		v.reserve(20);
		ft::vector<MyTestClass> v2(v);
		Test<size_t>(v2.size(), false);
		Test<size_t>(v2.capacity(), true);
		for (size_t i = 0; i < v2.size(); i++) {
			Test<MyTestClass>(v2[i], true);
		}
	}
	catch(...) {}

	// test 5: Operator=
	try {
		ft::vector<MyTestClass> v(10, MyTestClass(32));
		ft::vector<MyTestClass> v2;
		v2 = v;
		Test<size_t>(v2.size(), false);
		for (size_t i = 0; i < v2.size(); i++) {
			Test<MyTestClass>(v2[i], true);
		}
	}
	catch(...) {}

	// test 6: Constructor with iterator
	try {
		ft::vector<MyTestClass> v(10, MyTestClass(42));
		v.reserve(20);
		ft::vector<MyTestClass> v2(v.begin(), v.end());
		Test<size_t>(v2.size(), false);
		Test<size_t>(v2.capacity(), true);
		for (size_t i = 0; i < v2.size(); i++) {
			Test<MyTestClass>(v2[i], true);
		}
	}
	catch(...) {}

	// test 7: Reserve
	try {
		ft::vector<int> v;
		v.reserve(10);
		Test<size_t>(v.capacity(), false);
		v.reserve(100);
		Test<size_t>(v.capacity(), true);
		v.reserve(0);
		Test<size_t>(v.capacity(), true);
		v.reserve(v.max_size() + 1);
		Test<size_t>(v.capacity(), true);
	}
	catch(std::length_error) { Test<std::string>("LENGTH_ERROR", true); }
	catch(...) {}

	// test 8: Resize
	try {
		ft::vector<int> v;
		v.resize(10);
		Test<size_t>(v.size(), false);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
		v.resize(0);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		v.resize(11);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
		v.resize(11, 1);
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
		v.resize(99, 42);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
	}
	catch(...) {}

	// test 9: Max_size
	try {
		ft::vector<int> v;
		Test<size_t>(v.max_size(), false);
		// if (v.max_size() == std::distance(v.begin(), v.end())) { // not sure if this is the correct way to test this
		// 	Test<std::string>("true", false);
		// }
		// else {
		// 	Test<std::string>("false", false);
		// }
	}
	catch(...) {}



	// test 10: Push_back
	try {
		ft::vector<int> v;
		v.push_back(42);
		Test<size_t>(v.size(), false);
		Test<int>(v[0], true);
		for (int i = 0; i < 100; i++) {
			v.push_back(i);
			Test<size_t>(v.size(), true);
			Test<int>(v[i], true);
			Test<size_t>(v.capacity(), true);

		}
	}
	catch(...) {}

	// test 11: Pop_back
	try {
		ft::vector<int> v;
		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		v.pop_back();
		Test<int>(v[98], false);
		int i = v.size() - 1;
		while (!v.empty()) {
			v.pop_back();
			Test<size_t>(v.size(), true);
			Test<int>(v[i], true);
			--i;
		}
	}
	catch(...) {}

	// test 12: Front
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		Test<int>(v.front(), false);
		int & ref = v.front();
		ref = 42;
		Test<int>(v.front(), true);
	}
	catch(...) {}

	// test 13: Back
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		Test<int>(v.back(), false);
		int & ref = v.back();
		ref = 42;
		Test<int>(v.back(), true);
	}
	catch(...) {}

	//test 14: At
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		Test<int>(v.at(5), false);
		int & ref = v.at(5);
		ref = 42;
		Test<int>(v.at(5), true);
		Test<int>(v.at(99), true);
	}
	catch(std::out_of_range) { Test<std::string>("Out of Range Exeception", true); }
	catch(...) {}

	// test 15: Clear
	try {
		ft::vector<int> v;

		v.clear();
		Test<size_t>(v.size(), false);
		Test<size_t>(v.capacity(), true);
		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		v.clear();
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
	}
	catch(...) {}

	// test 16: Assign nb and val
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		v.assign(7, 42);
		Test<size_t>(v.size(), false);
		Test<size_t>(v.capacity(), true);
		for (int i = 0; i < 7; i++) {
			Test<int>(v[i], true);
		}
		v.assign(10, 41);
		for (int i = 0; i < 10; i++) {
			Test<int>(v[i], true);
		}
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		v.assign(23, 11);
		for (int i = 0; i < 23; i++) {
			Test<int>(v[i], true);
		}
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		v.assign(0, 0);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
	}
	catch(...) {}

	// test 17: Assign iterators
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		ft::vector<int> v2;
		for (int i = 0; i < 20; i++) {
			v2.push_back(i + 10);
		}
		v.assign(v2.begin(), v2.end());
		Test<size_t>(v.size(), false);
		Test<size_t>(v.capacity(), true);
		for (int i = 0; i < 20; i++) {
			Test<int>(v[i], true);
		}
		v.assign(v2.begin(), v2.begin() + 5);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (int i = 0; i < 5; i++) {
			Test<int>(v[i], true);
		}
	}
	catch(...) {}

	// test 18: Insert pos and val
	try {
		ft::vector<int> v;

		v.insert(v.end(), 42);
		Test<size_t>(v.size(), false);
		Test<size_t>(v.capacity(), true);
		for (int i = 0; i < 10; i++) {
			Test<int>(*v.insert(v.end(), i), true);
		}
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
		v.insert(v.begin(), -42);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		Test<int>(v[0], true);
	}
	catch(...) {}

	// test 19: Insert pos, count and val
	try {
		ft::vector<MyTestClass> v(20, MyTestClass(42));

		Test<size_t>(v.size(), false);
		v.insert(v.end(), 10, MyTestClass(0));
		Test<size_t>(v.size(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		v.insert(v.begin(), 10, MyTestClass(0));
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		v.insert(v.begin() + 5, 10, MyTestClass(12));
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
	}
	catch(...) {}

	// test 20: Insert iterators
	try {
		ft::vector<MyTestClass> v;
		ft::vector<MyTestClass> v2;

		Test<size_t>(v.size(), false);
		for (int i = 0; i < 20; i++) {
			v2.push_back(MyTestClass(i));
		}
		v.insert(v.end(), v2.begin(), v2.end());
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		v.insert(v.begin(), v2.begin() + 5, v2.begin() + 10);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		v.insert(v.begin() + 5, v2.begin(), v2.begin() + 5);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
	}
	catch(...) {}
	// test 21: Erase pos
	try {
		ft::vector<MyTestClass> v;
		for (int i = 0; i < 20; i++) {
			v.push_back(MyTestClass(i));
		}
		Test<size_t>(v.size(), false);
		Test<MyTestClass>(*v.erase(v.begin()), true);
		Test<MyTestClass>(v.front(), true);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);
		Test<MyTestClass>(*v.erase(v.begin() + 5), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		Test<MyTestClass>(*v.erase(v.end() - 1), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		// Test<MyTestClass>(*v.erase(v.end()), true);
		// for (int i = 0; i < v.size(); i++) {
		// 	Test<MyTestClass>(v[i], true);
		// }
	}
	catch(...) {}

	// test 22: Erase iterators
	try {
		ft::vector<MyTestClass> v;
		for (int i = 0; i < 100; i++) {
			v.push_back(MyTestClass(i));
		}
		Test<size_t>(v.size(), false);
		Test<MyTestClass>(*v.erase(v.begin(), v.begin() + 5), true);
		Test<MyTestClass>(v.front(), true);
		Test<size_t>(v.size(), true);
		Test<size_t>(v.capacity(), true);

		Test<MyTestClass>(*v.erase(v.begin() + 5, v.begin() + 10), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		Test<MyTestClass>(*v.erase(v.end() - 10, v.end() - 1), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		Test<MyTestClass>(*v.erase(v.end() - 1, v.end() - 1), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		// Test<size_t>(v.size(), true);
		// Test<MyTestClass>(*v.erase(v.end(), v.end()- 1), true);
		// Test<size_t>(v.size(), true);
		// Test<size_t>(v.capacity(), true);
	}
	catch(...) {}

	// test 23: Swap member
	try {
		ft::vector<MyTestClass> v2(20, MyTestClass(42));
		ft::vector<MyTestClass> v(70, MyTestClass(21));
		v.swap(v2);
		Test<size_t>(v.size(), false);
		Test<size_t>(v.capacity(), true);
		Test<size_t>(v2.size(), true);
		Test<size_t>(v2.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		for (size_t i = 0; i < v2.size(); i++) {
			Test<MyTestClass>(v2[i], true);
		}
	}
	catch(...) {}

	// test 24: Swap non member
	try {
		ft::vector<MyTestClass> v2(20, MyTestClass(42));
		ft::vector<MyTestClass> v(70, MyTestClass(21));
		ft::swap(v, v2);
		Test<size_t>(v.size(), false);
		Test<size_t>(v.capacity(), true);
		Test<size_t>(v2.size(), true);
		Test<size_t>(v2.capacity(), true);
		for (size_t i = 0; i < v.size(); i++) {
			Test<MyTestClass>(v[i], true);
		}
		for (size_t i = 0; i < v2.size(); i++) {
			Test<MyTestClass>(v2[i], true);
		}
	}
	catch(...) {}

	// test 25: < operator | <= operator
	try {
		ft::vector<int> v1(20, int(42));
		ft::vector<int> v2(20, int(42));
		Test<bool>(v1 < v2, false);
		Test<bool>(v1 <= v2, true);
		v2.push_back(int(12));
		Test<bool>(v1 < v2, true);
		Test<bool>(v1 <= v2, true);
	}
	catch(...) {}

	// test 26: > operator | >= operator
	try {
		ft::vector<int> v1(20, int(42));
		ft::vector<int> v2(20, int(42));
		Test<bool>(v1 > v2, false);
		Test<bool>(v1 >= v2, true);
		v1.push_back(int(12));
		Test<bool>(v1 > v2, true);
		Test<bool>(v1 >= v2, true);
	}
	catch(...) {}

	// test 27: == operator | != operator
	try {
		ft::vector<int> v1(20, int(42));
		ft::vector<int> v2(20, int(42));
		Test<bool>(v1 == v2, false);
		Test<bool>(v1 != v2, true);
		v1.push_back(int(12));
		Test<bool>(v1 == v2, true);
		Test<bool>(v1 != v2, true);
	}
	catch(...) {}

	// test 28: get_allocator
	try {
		ft::vector<int> v;
		int *p = v.get_allocator().allocate(10);
		for (int i = 0; i < 10; i++) {
			v.get_allocator().construct(p + i, i);
		}
		Test<std::string>("oui", false);
		for (int i = 0; i < 10; i++) {
			Test<int>(p[i], true);
			v.get_allocator().destroy(p + i);
		}
		v.get_allocator().deallocate(p, 10);
	}
	catch(...) {}

	// test 29: random access iterator
	try {
		ft::vector<int> v;

		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		ft::vector<int>::iterator endo = v.end();
		endo--;
		Test<int>(*endo, false);
		endo++;
		for (ft::vector<int>::iterator it = v.begin(); it != endo; it++) {
			Test<int>(*it, true);
			*it = *it + 1;
		}
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
		ft::vector<int>::iterator begindo = v.begin();
		Test<int>(*(begindo + 50), true);
		Test<int>(*(endo - 50), true);
	}
	catch(...) {}

	// test 30: const_iterator
	try {
		ft::vector<int> v;

		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		ft::vector<int>::const_iterator endo = v.end();
		endo--;
		Test<int>(*endo, false);
		endo++;
		for (ft::vector<int>::const_iterator it = v.begin(); it != endo; it++) {
			Test<int>(*it, true);
		}
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
		ft::vector<int>::const_iterator begindo = v.begin();
		Test<int>(*(begindo + 50), true);
		Test<int>(*(endo - 50), true);
	}
	catch(...) {}

	// test 31: reverse iterator
	try {
		ft::vector<int> v;

		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		ft::vector<int>::reverse_iterator rendo = v.rend();
		rendo--;
		Test<int>(*rendo, false);
		rendo++;
		for (ft::vector<int>::reverse_iterator it = v.rbegin(); it != rendo; it++) {
			Test<int>(*it, true);
		}
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
		ft::vector<int>::reverse_iterator rbegindo = v.rbegin();
		Test<int>(*(rbegindo + 50), true);
		Test<int>(*(rendo - 50), true);
	}
	catch(...) {}

	// test 32: const_reverse iterator
	try {
		ft::vector<int> v;

		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		ft::vector<int>::const_reverse_iterator rendo = v.rend();
		rendo--;
		Test<int>(*rendo, false);
		rendo++;
		for (ft::vector<int>::const_reverse_iterator it = v.rbegin(); it != rendo; it++) {
			Test<int>(*it, true);
		}
		for (size_t i = 0; i < v.size(); i++) {
			Test<int>(v[i], true);
		}
		ft::vector<int>::const_reverse_iterator rbegindo = v.rbegin();
		Test<int>(*(rbegindo + 50), true);
		Test<int>(*(rendo - 50), true);
	}
	catch(...) {}

	ofs.close();

	// gettimeofday(&time_now, NULL);
	// time_t time_end = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	// std:: cout << "time: " << time_end - time_start << " ms" << std::endl;


	return 0;
}