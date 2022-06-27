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
	#include "../../vector/vector.hpp" // include your vector header file
	std::ofstream ofs("testOutput/ft_vector_out.txt");

#endif

int nb = 0;

Test t;

void segfault_handler(int sig) {
	(void)sig;
	t.print<std::string>("SEGFAULT");
	throw std::runtime_error("SEGFAULT");
}

int main() {

	std::signal(SIGSEGV, &segfault_handler);
	ofs << "VECTOR TEST";
	

	clock_t start_test;
	clock_t time_test;
	srand(0);
	start_test = clock();


	// test 1: Default constructor
	t.newTest();
	try {
		ft::vector<int> v;
		t.print<size_t>(v.capacity());
		t.print<size_t>(v.size());
		t.print<bool>(v.empty());
	}
	catch(...) {}

	// test 2: Constructor with size and default value
	t.newTest();
	try {
		ft::vector<MyTestClass> v(10);
		t.print<size_t>(v.capacity());
		t.print<size_t>(v.size());
		t.print<bool>(v.empty());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
	}
	catch(...) {}

	// test 3: Constructor with size and value
	t.newTest();
	try {
		ft::vector<MyTestClass> v(10, MyTestClass(12));
		t.print<size_t>(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
	}
	catch(...) {}

	// test 4: Copy constructor
	t.newTest();
	try {
		ft::vector<MyTestClass> v(10, MyTestClass(22));
		v.reserve(20);
		ft::vector<MyTestClass> v2(v);
		t.print<size_t>(v2.size());
		t.print<size_t>(v2.capacity());
		for (size_t i = 0; i < v2.size(); i++) {
			t.print<MyTestClass>(v2[i]);
		}
	}
	catch(...) {}

	// test 5: Operator=
	t.newTest();
	try {
		ft::vector<MyTestClass> v(10, MyTestClass(32));
		ft::vector<MyTestClass> v2;
		v2 = v;
		t.print<size_t>(v2.size());
		for (size_t i = 0; i < v2.size(); i++) {
			t.print<MyTestClass>(v2[i]);
		}
	}
	catch(...) {}

	// test 6: Constructor with iterator
	t.newTest();
	try {
		ft::vector<MyTestClass> v(10, MyTestClass(42));
		v.reserve(20);
		ft::vector<MyTestClass> v2(v.begin(), v.end());
		t.print<size_t>(v2.size());
		t.print<size_t>(v2.capacity());
		for (size_t i = 0; i < v2.size(); i++) {
			t.print<MyTestClass>(v2[i]);
		}
	}
	catch(...) {}

	// test 7: Reserve
	t.newTest();
	try {
		ft::vector<int> v;
		v.reserve(10);
		t.print<size_t>(v.capacity());
		v.reserve(100);
		t.print<size_t>(v.capacity());
		v.reserve(0);
		t.print<size_t>(v.capacity());
		v.reserve(v.max_size() + 1);
		t.print<size_t>(v.capacity());
	}
	catch(std::length_error) { t.print<std::string>("LENGTH_ERROR"); }
	catch(...) {}

	// test 8: Resize
	t.newTest();
	try {
		ft::vector<int> v;
		v.resize(10);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
		v.resize(0);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		v.resize(11);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
		v.resize(11, 1);
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
		v.resize(99, 42);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
	}
	catch(...) {}

	// test 9: Max_size
	t.newTest();
	try {
		ft::vector<int> v;
		t.print<size_t>(v.max_size());
	}
	catch(...) {}



	// test 10: Push_back
	t.newTest();
	try {
		ft::vector<int> v;
		v.push_back(42);
		t.print<size_t>(v.size());
		t.print<int>(v[0]);
		for (int i = 0; i < 100; i++) {
			v.push_back(i);
			t.print<size_t>(v.size());
			t.print<int>(v[i]);
			t.print<size_t>(v.capacity());

		}
	}
	catch(...) {}

	// test 11: Pop_back
	t.newTest();
	try {
		ft::vector<int> v;
		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		v.pop_back();
		t.print<int>(v[98]);
		int i = v.size() - 1;
		while (!v.empty()) {
			t.print<int>(v[i]);
			v.pop_back();
			t.print<size_t>(v.size());
			--i;
		}
	}
	catch(...) {}

	// test 12: Front
	t.newTest();
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		t.print<int>(v.front());
		int & ref = v.front();
		ref = 42;
		t.print<int>(v.front());
	}
	catch(...) {}

	// test 13: Back
	t.newTest();
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		t.print<int>(v.back());
		int & ref = v.back();
		ref = 42;
		t.print<int>(v.back());
	}
	catch(...) {}

	//test 14: At
	t.newTest();
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		t.print<int>(v.at(5));
		int & ref = v.at(5);
		ref = 42;
		t.print<int>(v.at(5));
		t.print<int>(v.at(99));
	}
	catch(std::out_of_range) { t.print<std::string>("Out of Range Exeception"); }
	catch(...) {}

	// test 15: Clear
	t.newTest();
	try {
		ft::vector<int> v;

		v.clear();
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		v.clear();
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
	}
	catch(...) {}

	// test 16: Assign nb and val
	t.newTest();
	try {
		ft::vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		v.assign(7, 42);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (int i = 0; i < 7; i++) {
			t.print<int>(v[i]);
		}
		v.assign(10, 41);
		for (int i = 0; i < 10; i++) {
			t.print<int>(v[i]);
		}
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		v.assign(23, 11);
		for (int i = 0; i < 23; i++) {
			t.print<int>(v[i]);
		}
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		v.assign(0, 0);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
	}
	catch(...) {}

	// test 17: Assign iterators
	t.newTest();
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
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (int i = 0; i < 20; i++) {
			t.print<int>(v[i]);
		}
		v.assign(v2.begin(), v2.begin() + 5);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (int i = 0; i < 5; i++) {
			t.print<int>(v[i]);
		}
	}
	catch(...) {}

	// test 18: Insert pos and val
	t.newTest();
	try {
		ft::vector<int> v;

		v.insert(v.end(), 42);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (int i = 0; i < 10; i++) {
			t.print<int>(*v.insert(v.end(), i));
		}
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
		v.insert(v.begin(), -42);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		t.print<int>(v[0]);
	}
	catch(...) {}

	// test 19: Insert pos, count and val
	t.newTest();
	try {
		ft::vector<MyTestClass> v(20, MyTestClass(42));

		t.print<size_t>(v.size());
		v.insert(v.end(), 10, MyTestClass(0));
		t.print<size_t>(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		v.insert(v.begin(), 10, MyTestClass(0));
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		v.insert(v.begin() + 5, 10, MyTestClass(12));
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
	}
	catch(...) {}

	// test 20: Insert iterators
	t.newTest();
	try {
		ft::vector<MyTestClass> v;
		ft::vector<MyTestClass> v2;

		t.print<size_t>(v.size());
		for (int i = 0; i < 20; i++) {
			v2.push_back(MyTestClass(i));
		}
		v.insert(v.end(), v2.begin(), v2.end());
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		v.insert(v.begin(), v2.begin() + 5, v2.begin() + 10);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		v.insert(v.begin() + 5, v2.begin(), v2.begin() + 5);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
	}
	catch(...) {}
	// test 21: Erase pos
	t.newTest();
	try {
		ft::vector<MyTestClass> v;
		for (int i = 0; i < 20; i++) {
			v.push_back(MyTestClass(i));
		}
		t.print<size_t>(v.size());
		t.print<MyTestClass>(*v.erase(v.begin()));
		t.print<MyTestClass>(v.front());
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		t.print<MyTestClass>(*v.erase(v.begin() + 5));
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		ft::vector<MyTestClass>::iterator it = v.erase(v.end() - 1);
		if (it != v.end()) {
			t.print<MyTestClass>(*it);
		}
		else
			t.print<std::string>("end()");
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
	}
	catch(...) {}

	// test 22: Erase iterators
	t.newTest();
	try {
		ft::vector<MyTestClass> v;
		for (int i = 0; i < 100; i++) {
			v.push_back(MyTestClass(i));
		}
		t.print<size_t>(v.size());
		t.print<MyTestClass>(*v.erase(v.begin(), v.begin() + 5));
		t.print<MyTestClass>(v.front());
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());

		t.print<MyTestClass>(*v.erase(v.begin() + 5, v.begin() + 10));
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		t.print<MyTestClass>(*v.erase(v.end() - 10, v.end() - 1));
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		t.print<MyTestClass>(*v.erase(v.end() - 1, v.end() - 1));
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
	}
	catch(...) {}

	// test 23: Swap member
	t.newTest();
	try {
		ft::vector<MyTestClass> v2(20, MyTestClass(42));
		ft::vector<MyTestClass> v(70, MyTestClass(21));
		v.swap(v2);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		t.print<size_t>(v2.size());
		t.print<size_t>(v2.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		for (size_t i = 0; i < v2.size(); i++) {
			t.print<MyTestClass>(v2[i]);
		}
	}
	catch(...) {}

	// test 24: Swap non member
	t.newTest();
	try {
		ft::vector<MyTestClass> v2(20, MyTestClass(42));
		ft::vector<MyTestClass> v(70, MyTestClass(21));
		ft::swap(v, v2);
		t.print<size_t>(v.size());
		t.print<size_t>(v.capacity());
		t.print<size_t>(v2.size());
		t.print<size_t>(v2.capacity());
		for (size_t i = 0; i < v.size(); i++) {
			t.print<MyTestClass>(v[i]);
		}
		for (size_t i = 0; i < v2.size(); i++) {
			t.print<MyTestClass>(v2[i]);
		}
	}
	catch(...) {}

	// test 25: < operator | <= operator
	t.newTest();
	try {
		ft::vector<int> v1(20, int(42));
		ft::vector<int> v2(20, int(42));
		t.print<bool>(v1 < v2);
		t.print<bool>(v1 <= v2);
		v2.push_back(int(12));
		t.print<bool>(v1 < v2);
		t.print<bool>(v1 <= v2);
	}
	catch(...) {}

	// test 26: > operator | >= operator
	t.newTest();
	try {
		ft::vector<int> v1(20, int(42));
		ft::vector<int> v2(20, int(42));
		t.print<bool>(v1 > v2);
		t.print<bool>(v1 >= v2);
		v1.push_back(int(12));
		t.print<bool>(v1 > v2);
		t.print<bool>(v1 >= v2);
	}
	catch(...) {}

	// test 27: == operator | != operator
	t.newTest();
	try {
		ft::vector<int> v1(20, int(42));
		ft::vector<int> v2(20, int(42));
		t.print<bool>(v1 == v2);
		t.print<bool>(v1 != v2);
		v1.push_back(int(12));
		t.print<bool>(v1 == v2);
		t.print<bool>(v1 != v2);
	}
	catch(...) {}

	// test 28: get_allocator
	t.newTest();
	try {
		ft::vector<int> v;
		int *p = v.get_allocator().allocate(10);
		for (int i = 0; i < 10; i++) {
			v.get_allocator().construct(p + i, i);
		}
		t.print<std::string>("oui");
		for (int i = 0; i < 10; i++) {
			t.print<int>(p[i]);
			v.get_allocator().destroy(p + i);
		}
		v.get_allocator().deallocate(p, 10);
	}
	catch(...) {}

	// test 29: random access iterator
	t.newTest();
	try {
		ft::vector<int> v;

		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		ft::vector<int>::iterator endo = v.end();
		endo--;
		t.print<int>(*endo);
		endo++;
		for (ft::vector<int>::iterator it = v.begin(); it != endo; it++) {
			t.print<int>(*it);
			*it = *it + 1;
		}
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
		ft::vector<int>::iterator begindo = v.begin();
		t.print<int>(*(begindo + 50));
		t.print<int>(*(endo - 50));
	}
	catch(...) {}

	// Test 30: const_iterator
	t.newTest();
	try {
		ft::vector<int> v;

		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		ft::vector<int>::const_iterator endo = v.end();
		endo--;
		t.print<int>(*endo);
		endo++;
		for (ft::vector<int>::const_iterator it = v.begin(); it != endo; it++) {
			t.print<int>(*it);
		}
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
		ft::vector<int>::const_iterator begindo = v.begin();
		t.print<int>(*(begindo + 50));
		t.print<int>(*(endo - 50));
	}
	catch(...) {}

	// test 31: reverse iterator
	t.newTest();
	try {
		ft::vector<int> v;

		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		ft::vector<int>::reverse_iterator rendo = v.rend();
		rendo--;
		t.print<int>(*rendo);
		rendo++;
		for (ft::vector<int>::reverse_iterator it = v.rbegin(); it != rendo; it++) {
			t.print<int>(*it);
		}
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
		ft::vector<int>::reverse_iterator rbegindo = v.rbegin();
		t.print<int>(*(rbegindo + 50));
		t.print<int>(*(rendo - 50));
	}
	catch(...) {}

	// test 32: const_reverse iterator
	t.newTest();
	try {
		ft::vector<int> v;

		for (int i = 0; i < 100; i++) {
			v.push_back(i);
		}
		ft::vector<int>::const_reverse_iterator rendo = v.rend();
		rendo--;
		t.print<int>(*rendo);
		rendo++;
		for (ft::vector<int>::const_reverse_iterator it = v.rbegin(); it != rendo; it++) {
			t.print<int>(*it);
		}
		for (size_t i = 0; i < v.size(); i++) {
			t.print<int>(v[i]);
		}
		ft::vector<int>::const_reverse_iterator rbegindo = v.rbegin();
		t.print<int>(*(rbegindo + 50));
		t.print<int>(*(rendo - 50));
	}
	catch(...) {}

	time_test = clock() - start_test;
	float time_f;
	time_f = ((float)time_test)/CLOCKS_PER_SEC;
	ofs << std::endl;
  	ofs << "Time: " << time_f << std::endl;
	ofs.close();

	return 0;
}