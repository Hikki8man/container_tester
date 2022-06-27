#include <iostream>
#include <string>

#include <fstream>
#include <csignal>
#include <ctime>

#ifdef STD
	#include <map>
	namespace ft = std;
	std::ofstream ofs("testOutput/std_map_out.txt");
#else
	#include "../../map/map.hpp" // include your map header file
	std::ofstream ofs("testOutput/ft_map_out.txt");

#endif

#include "../utils/color.hpp"
#include "../utils/Test.hpp"

Test t;

void segfault_handler(int sig) {
	(void)sig;
	t.print<std::string>("SEGFAULT");
	throw std::runtime_error("SEGFAULT");
}

template<class _Tp>
	struct sup
	{
		bool operator()(const _Tp& __x, const _Tp& __y) const
      	{ return __x > __y; }
	};

void basic_map(ft::map<int, char>& map) {
	try {
		map.insert(ft::make_pair(8, 'a'));
		map.insert(ft::make_pair(3, 'c'));
		map.insert(ft::make_pair(1, 'd'));
		map.insert(ft::make_pair(6, 'e'));
		map.insert(ft::make_pair(4, 'f'));
		map.insert(ft::make_pair(7, 'g'));
		map.insert(ft::make_pair(13, 'i'));
		map.insert(ft::make_pair(10, 'b'));
		map.insert(ft::make_pair(14, 'h'));
	}
	catch(...) {}

	/*
				8
		       /  \
	          3     13
			 / \    / \
			1   6 10	14
		   	   / \	
		      4   7 

	*/
}

int main() {
	typedef ft::map<int, char>::iterator iterator;
	typedef ft::map<int, char>::const_iterator const_iterator;

	std::signal(SIGSEGV, &segfault_handler);

	clock_t start_test;
	clock_t time_test;
	srand(124);
	start_test = clock();


	ofs << "MAP TEST";

	// Test 1 - Constructors
	t.newTest();
	try {
		ft::map<int, char> m;
		t.print<bool>(m.empty());
		t.print<size_t>(m.size());

		basic_map(m);
		// By copy
		ft::map<int, char> m2(m);
		for (const_iterator it = m.begin(); it != m.end(); ++it) {
			t.print<int>(it->first);
		}
		// By range iterator
		ft::map<int, char> m3(m2.begin(), m2.end());
		for (const_iterator it = m.begin(); it != m.end(); ++it) {
			t.print<int>(it->first);
		}
	} catch(...) {}

	// Test 2 - capacity
	t.newTest();
	try {
		ft::map<int, char> m;

		basic_map(m);
		// size
		t.print<size_t>(m.size());

		// empty
		t.print<bool>(m.empty());

		// max_size
		t.print<size_t>(m.max_size());
	} catch (...) {}

	// Test 3 - insert single element
	t.newTest();
	try {
		ft::map<int, char>m;

		m.insert(ft::make_pair(1, 'a'));

		ft::pair<iterator, bool> p = m.insert(ft::make_pair(1, 'a'));
		t.print<int>(p.first->first);
		t.print<char>(p.first->second);
		t.print<bool>(p.second);
		t.print<size_t>(m.size());
		t.print<bool>(m.empty());

		// inserting a new element with a key that already exists
		ft::pair<iterator, bool> p2 = m.insert(ft::make_pair(1, 'b'));

		t.print<bool>(p2 != p);
		t.print<bool>(p2.second);
		t.print<size_t>(m.size());

		for (int i = 1; i < 50; i++) {
			if (i % 2)
				m.insert(ft::make_pair(i + 10, 'b'));
			else
				m.insert(ft::make_pair(i - 10, 'b'));
		}
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
	}
	catch (...) {}

	// Test 4 - insert elements with hint
	t.newTest();
	try {
		ft::map<int, char> m;
		iterator it;
		it = m.insert(m.begin(), ft::make_pair(15, 'a'));
		t.print<int>(it->first);
		m.clear();
		for (it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		basic_map(m);
		it = m.insert(m.begin(), ft::make_pair(15, 'a'));
		t.print<int>(it->first);
		t.print<bool>(it != m.begin());
		it = m.insert(m.end(), ft::make_pair(100, 'a'));
		t.print<bool>(it != m.end());
		m.insert(m.end(), ft::make_pair(2, 'a'));
		m.insert(m.find(14), ft::make_pair(0, 'd'));
		m.insert(m.find(3), ft::make_pair(13, 'd'));
		m.insert(m.find(3), ft::make_pair(13, 'd'));
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		t.print<size_t>(m.size());
	}
	catch (...) {}

	// Test 5 - insert elements with iterators
	t.newTest();
	try {
		ft::map<int, char>m;
		basic_map(m);
		ft::map<int, char>m2;
		for (int i = 1; i < 50; i++) {
			if (i % 2)
				m2.insert(ft::make_pair(i + 10, 'b'));
			else
				m2.insert(ft::make_pair(i - 10, 'b'));
		}
		m.insert(m2.begin(), m2.end());
		t.print<size_t>(m.size());
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
	}
	catch (...) {}

	// Test 6 - find
	t.newTest();
	try {
		ft::map<int, char>m;
		iterator it = m.find(1);
		t.print<bool>(it == m.end());
		basic_map(m);
		it = m.find(8);
		t.print<bool>(m.empty());
		if (it != m.end()) { t.print<int>(it->first); }
		else { t.print<std::string>("not found"); }
		it = m.find(100);
		if (it != m.end()) { t.print<int>(it->first); }
		else { t.print<std::string>("not found"); }
		it = m.find(2);
		if (it != m.end()) { t.print<int>(it->first); }
		else { t.print<std::string>("not found"); }
		it = m.find(11);
		if (it != m.end()) { t.print<int>(it->first); }
		else { t.print<std::string>("not found"); }
		const_iterator cit = m.find(4);
		if (cit != m.end()) { t.print<int>(cit->first); }
		else { t.print<std::string>("not found"); }
	}
	catch (...) {}

	// Test 7 - erase - Key
	t.newTest();
	try {
		ft::map<int, char>m;
		t.print<size_t>(m.erase(117));
		basic_map(m);
		m.insert(ft::make_pair(12, 'a'));
		// erase a node with no childrens
		t.print<size_t>(m.erase(12));
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase a node with one child - left
		m.erase(14);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase a node with one child - right
		m.insert(ft::make_pair(0, 'a'));
		m.erase(0);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase a node with two childrens
		m.erase(6);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase a root
		m.erase(8);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase key that doesn't exist
		ft::map<int, char> m2;
		t.print<size_t>( m.erase(100));
		m.erase(11);
		m.erase(12);
		m.erase(2);
		m.erase(0);
		for (iterator it = m2.begin(); it != m2.end(); it++) {
			t.print<int>(it->first);
		}
	}
	catch (...) {}

	// Test 8 - erase - iterator
	t.newTest();
	try {
		ft::map<int, char> m;
		basic_map(m);
		// erase a node with no childrens
		iterator it = m.find(1);
		t.print<int>(it->first);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase a node with one child - left
		m.insert(ft::make_pair(2, 'a'));
		m.insert(ft::make_pair(1, 'a'));
		it = m.find(2);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase a node with one child - right
		m.insert(ft::make_pair(2, 'a'));
		it = m.find(1);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase a node with two childrens
		it = m.find(6);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase a root
		it = m.find(8);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		// erase all
		for (iterator it = m.begin(); it != m.end(); it = m.begin()) {
			m.erase(it);
		}
		t.print<bool>(m.empty());
		t.print<size_t>(m.size());

	}
	catch (...) {}

	// Test 9 - erase - range
	t.newTest();
	try {
		ft::map<int, char>m;
		basic_map(m);
		m.erase(m.begin(), m.end());
		t.print<size_t>(m.size());
		t.print<bool>(m.empty());
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		basic_map(m);
		iterator it = m.find(4);
		iterator ite = m.find(13);
		m.erase(it, ite);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
	}
	catch (...) {}

	// Test 10 - clear
	t.newTest();
	try {
		ft::map<int, char>m;
		m.clear();
		basic_map(m);
		m.clear();
		t.print<size_t>(m.size());
		t.print<bool>(m.empty());
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
	}
	catch (...) {}

	// Test 11 - swap
	t.newTest();
	try {
		ft::map<int, char>m;
		basic_map(m);
		ft::map<int, char>m2;
		for (int i = 0; i < 40; i++) {
			m2.insert(ft::make_pair(i, 'a'));
		}
		m.swap(m2);
		t.print<size_t>(m.size());
		t.print<size_t>(m2.size());
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		for (iterator it = m2.begin(); it != m2.end(); it++) {
			t.print<int>(it->first);
		}

		// swap non member
		ft::swap(m, m2);
		for (iterator it = m.begin(); it != m.end(); it++) {
			t.print<int>(it->first);
		}
		for (iterator it = m2.begin(); it != m2.end(); it++) {
			t.print<int>(it->first);
		}
	}
	catch (...) {}

	// Test 12 - count
	t.newTest();
	try {
		ft::map<int, char>m;
		t.print<size_t>(m.count(0));
		basic_map(m);
		t.print<size_t>(m.count(4));
		t.print<size_t>(m.count(5));
		t.print<size_t>(m.count(100));
		t.print<size_t>(m.count(0));
	}
	catch (...) {}

	// Test 13 - lower_bound
	t.newTest();
	try {
		ft::map<int, char>m;
		iterator it = m.lower_bound(0);
		t.print<bool>(it == m.end());

		basic_map(m);
		it = m.lower_bound(0);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.lower_bound(4);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.lower_bound(5);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.lower_bound(9);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.lower_bound(13);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.lower_bound(14);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.lower_bound(100);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }

		const_iterator cit = m.lower_bound(0);
		if (cit != m.end()) { t.print<int>(cit->first); } else { t.print<std::string>("it == end"); }
		cit = m.lower_bound(4);
		if (cit != m.end()) { t.print<int>(cit->first); } else { t.print<std::string>("it == end"); }

		for (int i = 0; i < 10000; i++) {
			m.insert(ft::make_pair(rand(), 'a'));
		}
		for (int i = 0; i < 10000; i++) {
			it = m.lower_bound(rand());
			if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		}
	}
	catch (...) {}

	// Test 14 - upper_bound
	t.newTest();
	try {
		ft::map<int, char>m;
		iterator it = m.upper_bound(0);
		t.print<bool>(it == m.end());
		basic_map(m);
		it = m.upper_bound(0);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.upper_bound(4);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.upper_bound(5);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.upper_bound(9);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.upper_bound(13);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.upper_bound(14);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		it = m.upper_bound(100);
		if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }

		const_iterator cit = m.upper_bound(0);
		if (cit != m.end()) { t.print<int>(cit->first); } else { t.print<std::string>("it == end"); }
		cit = m.upper_bound(4);
		if (cit != m.end()) { t.print<int>(cit->first); } else { t.print<std::string>("it == end"); }

		for (int i = 0; i < 10000; i++) {
			m.insert(ft::make_pair(rand(), 'a'));
		}
		for (int i = 0; i < 10000; i++) {
			it = m.upper_bound(rand());
			if (it != m.end()) { t.print<int>(it->first); } else { t.print<std::string>("it == end"); }
		}
	}
	catch (...) {}

	// Test 15 - equal_range
	t.newTest();
	try {
		ft::map<int, char>m;
		basic_map(m);
		ft::pair<iterator, iterator> p = m.equal_range(4);
		t.print<int>(p.first->first);
		t.print<int>(p.second->first);
		p = m.equal_range(8);
		t.print<int>(p.first->first);
		t.print<int>(p.second->first);
		p = m.equal_range(14);
		if (p.first != m.end())
			t.print<int>(p.first->first);
		else
			t.print<std::string>("p.first == m.end()");
		if (p.second != m.end())
			t.print<int>(p.first->first);
		else
			t.print<std::string>("p.second == m.end()");
		p = m.equal_range(100);
		if (p.first != m.end())
			t.print<int>(p.first->first);
		else
			t.print<std::string>("p.first == m.end()");
		if (p.second != m.end())
			t.print<int>(p.first->first);
		else
			t.print<std::string>("p.second == m.end()");
		p = m.equal_range(0);
		if (p.first != m.end())
			t.print<int>(p.first->first);
		else
			t.print<std::string>("p.first == m.end()");
		if (p.second != m.end())
			t.print<int>(p.first->first);
		else
			t.print<std::string>("p.second == m.end()");

		ft::pair<const_iterator, const_iterator> e = m.equal_range(4);
		t.print<int>(e.first->first);
		t.print<int>(e.second->first);
	}
	catch (...) {}

	// Test 16 - Operator[]
	t.newTest();
	try {
		ft::map<int, char>m;
		t.print<size_t>(m.size());
		m[12] = 'g';
		t.print<int>(m.begin()->first);
		t.print<char>(m.begin()->second);
		t.print<size_t>(m.size());

		ft::map<int, int> m2;
		int sum = 0;
		for (int i = 0; i < 10000; i++) {
			int r = rand();
			sum += m2[r];
		}
		t.print<int>(int(sum));
	}
	catch(...) {}

	// Test 17 - At
	t.newTest();
	try {
		ft::map<int, char>m;
		basic_map(m);
		t.print<char>(m.at(13));
		m.at(13) = 'y';
		for (iterator it = m.begin(); it != m.end(); ++it) {
			t.print<char>(m.at(it->first));
		}
		m.at(12);
	}
	catch (std::out_of_range& e) { t.print<std::string>("Out of Range Exeception"); }
	catch(...) {}

	// Test 18 - Compare operator
	t.newTest();
	try {
		ft::map<int, char, sup<int> > m;
		m.insert(ft::make_pair(8, 'a'));
		m.insert(ft::make_pair(10, 'b'));
		m.insert(ft::make_pair(3, 'c'));
		m.insert(ft::make_pair(1, 'd'));
		m.insert(ft::make_pair(6, 'e'));
		m.insert(ft::make_pair(4, 'f'));
		m.insert(ft::make_pair(7, 'g'));
		m.insert(ft::make_pair(14, 'h'));
		m.insert(ft::make_pair(13, 'i'));

		ft::map<int, char, sup<int> > m2(m);

		t.print<bool>(m == m2);
		t.print<bool>(m != m2);
		m.insert(ft::make_pair(1, 'w'));
		t.print<bool>(m < m2);
		t.print<bool>(m <= m2);
		t.print<bool>(m > m2);
		t.print<bool>(m >= m2);

	}
	catch (...) {}

	// Test 19 - Iterator
	t.newTest();
	try {
		ft::map<int, char>m;
		basic_map(m);
		iterator it = m.begin();
		it->second = 'q';
		t.print<char>(it->second);
		
		// Reverse
		for (ft::map<int, char>::reverse_iterator rit = m.rbegin(); rit != m.rend(); ++rit) {
			t.print<int>(rit->first);
			rit->second = 'e';
		}
		for (ft::map<int, char>::const_reverse_iterator rit = m.rbegin(); rit != m.rend(); ++rit) {
			t.print<int>(rit->second);
		}
	}
	catch(...) {}

	// Test 20 - THICC MAP
	t.newTest();
	try {
		ft::map<int, char>m;
		t.print<bool>(m.empty());
		for (int i = 0; i <= 1000000; ++i) {
			m.insert(ft::make_pair(i, 'a'));
		}
		iterator it = m.find(1000000);
		if (it != m.end()) { t.print<int>(it->first); }
		else { t.print<std::string>("Not found"); }

		m.find(500000);

		it = m.upper_bound(2000000);
		if (it != m.end()) { t.print<int>(it->first); }
		else { t.print<std::string>("Not found"); }

		t.print<size_t>(m.size());

		
		for (int i = 0; i <= 1500; ++i) {
			int r = rand();
			m.lower_bound(r);
		}
		m.clear();
		t.print<bool>(m.empty());
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