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
	#include "../..//map.hpp" // include your map header file
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

void basic_map(ft::map<int, char>& map) {
	try {
		map.insert(ft::make_pair(8, 'a'));
		map.insert(ft::make_pair(10, 'b'));
		map.insert(ft::make_pair(3, 'c'));
		map.insert(ft::make_pair(1, 'd'));
		map.insert(ft::make_pair(6, 'e'));
		map.insert(ft::make_pair(4, 'f'));
		map.insert(ft::make_pair(7, 'g'));
		map.insert(ft::make_pair(14, 'h'));
		map.insert(ft::make_pair(13, 'i'));
	}
	catch(...) {}

	/*
				8
		       / \
	          3   10
			 / \	 \
			1   6	  14
		   	   / \	  /
		      4   7  13

	*/
}

int main() {
	typedef ft::map<int, char>::iterator iterator;
	typedef ft::map<int, char>::const_iterator const_iterator;

	std::signal(SIGSEGV, &segfault_handler);

	srand(time(NULL));

	ofs << "MAP TEST";

	// Test 1 - Constructors
	try {
		ft::map<int, char> m;
		Test<size_t>(m.size());
		Test<bool>(m.empty(), false);

		basic_map(m);
		// By copy
		ft::map<int, char> m2(m);
		for (const_iterator it = m.begin(); it != m.end(); ++it) {
			Test<int>(it->first);
		}
		// By range iterator
		ft::map<int, char> m3(m2.begin(), m2.end());
		for (const_iterator it = m.begin(); it != m.end(); ++it) {
			Test<int>(it->first);
		}
	} catch(...) {}

	// Test 2 - capacity
	try {
		ft::map<int, char> m;

		basic_map(m);
		// size
		Test<size_t>(m.size(), false);

		// empty
		Test<bool>(m.empty(), true);

		// max_size
		Test<size_t>(m.max_size(), true);
	} catch (...) {}

	// Test 3 - insert single element
	try {
		ft::map<int, char>m;

		m.insert(ft::make_pair(1, 'a'));

		ft::pair<iterator, bool> p = m.insert(ft::make_pair(1, 'a'));
		Test<int>(p.first->first, false);
		Test<char>(p.first->second, true);
		Test<bool>(p.second, true);
		Test<size_t>(m.size(), true);
		Test<bool>(m.empty(), true);

		// inserting a new element with a key that already exists
		ft::pair<iterator, bool> p2 = m.insert(ft::make_pair(1, 'b'));

		Test<bool>(p2 != p, true);
		Test<bool>(p2.second, true);
		Test<size_t>(m.size(), true);

		for (int i = 0; i < 50; i++) {
			m.insert(ft::make_pair(rand() % 10000, 'b'));
		}
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first, true);
		}
	}
	catch (...) {}

	// Test 4 - insert elements with hint
	try {
		ft::map<int, char>m;
		basic_map(m);
		iterator it = m.insert(m.begin(), ft::make_pair(0, 'a'));
		Test<int>(it->first, false);
		Test<bool>(it != m.begin(), true);
		it = m.insert(m.end(), ft::make_pair(100, 'a'));
		Test<bool>(it != m.end(), true);
		m.insert(m.end(), ft::make_pair(2, 'a'));
		for (it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first, true);
		}
		Test<size_t>(m.size(), true);
	}
	catch (...) {}

	// Test 5 - insert elements with iterators
	try {
		ft::map<int, char>m;
		basic_map(m);
		ft::map<int, char>m2;
		for (int i = 0; i < 50; i++) {
			m2.insert(ft::make_pair(rand() % 10000, 'b'));
		}
		m.insert(m2.begin(), m2.end());
		Test<size_t>(m.size(), false);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first, true);
		}
	}
	catch (...) {}

	// Test 6 - find
	try {
		ft::map<int, char>m;
		iterator it = m.find(1);
		Test<bool>(it == m.end(), false);
		basic_map(m);
		it = m.find(8);
		Test<bool>(m.empty());
		if (it != m.end()) { Test<int>(it->first); }
		else { Test<std::string>("not found"); }
		it = m.find(100);
		if (it != m.end()) { Test<int>(it->first); }
		else { Test<std::string>("not found"); }
		it = m.find(2);
		if (it != m.end()) { Test<int>(it->first); }
		else { Test<std::string>("not found"); }
		it = m.find(11);
		if (it != m.end()) { Test<int>(it->first); }
		else { Test<std::string>("not found"); }
		const_iterator cit = m.find(4);
		if (cit != m.end()) { Test<int>(cit->first); }
		else { Test<std::string>("not found"); }
	}
	catch (...) {}

	// Test 7 - erase - Key
	try {
		ft::map<int, char>m;
		size_t e = m.erase(117);
		Test<size_t>(e, false);
		basic_map(m);
		m.insert(ft::make_pair(12, 'a'));
		// erase a node with no childrens
		size_t s = m.erase(12);
		Test<size_t>(s, true);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase a node with one child - left
		m.erase(14);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase a node with one child - right
		m.insert(ft::make_pair(0, 'a'));
		m.erase(0);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase a node with two childrens
		m.erase(6);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase a root
		m.erase(8);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase key that doesn't exist
		ft::map<int, char> m2;
		basic_map(m2);
		size_t r = m.erase(100);
		Test<size_t>(r, true); // pq ca marche pas sans true ?
		m.erase(11);
		m.erase(12);
		m.erase(2);
		m.erase(0);
		for (iterator it = m2.begin(); it != m2.end(); it++) {
			Test<int>(it->first);
		}
	}
	catch (...) {}

	// Test 8 - erase - iterator
	try {
		ft::map<int, char>m;
		basic_map(m);
		m.insert(ft::make_pair(12, 'a'));
		// erase a node with no childrens
		iterator it = m.find(12);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase a node with one child - left
		it = m.find(14);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase a node with one child - right
		m.insert(ft::make_pair(0, 'a'));
		it = m.find(0);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase a node with two childrens
		it = m.find(6);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase a root
		it = m.find(8);
		m.erase(it);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		// erase all
		for (iterator it = m.begin(); it != m.end(); it = m.begin()) {
			m.erase(it);
		}
		Test<bool>(m.empty());
		Test<size_t>(m.size());

	}
	catch (...) {}

	// Test 9 - erase - range
	try {
		ft::map<int, char>m;
		basic_map(m);
		m.erase(m.begin(), m.end());
		Test<size_t>(m.size(), false);
		Test<bool>(m.empty());
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		basic_map(m);
		iterator it = m.find(4);
		iterator ite = m.find(13);
		m.erase(it, ite);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
	}
	catch (...) {}

	// Test 10 - clear
	try {
		ft::map<int, char>m;
		m.clear();
		basic_map(m);
		m.clear();
		Test<size_t>(m.size(), false);
		Test<bool>(m.empty());
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
	}
	catch (...) {}

	// Test 11 - swap
	try {
		ft::map<int, char>m;
		basic_map(m);
		ft::map<int, char>m2;
		for (int i = 0; i < 40; i++) {
			m2.insert(ft::make_pair(rand(), 'a'));
		}
		m.swap(m2);
		Test<size_t>(m.size(), false);
		Test<size_t>(m2.size());
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		for (iterator it = m2.begin(); it != m2.end(); it++) {
			Test<int>(it->first);
		}

		// swap non member
		ft::swap(m, m2);
		for (iterator it = m.begin(); it != m.end(); it++) {
			Test<int>(it->first);
		}
		for (iterator it = m2.begin(); it != m2.end(); it++) {
			Test<int>(it->first);
		}
	}
	catch (...) {}

	// Test 12 - count
	try {
		ft::map<int, char>m;
		Test<size_t>(m.count(0), false);
		basic_map(m);
		Test<size_t>(m.count(4));
		Test<size_t>(m.count(5));
		Test<size_t>(m.count(100));
		Test<size_t>(m.count(0));
	}
	catch (...) {}

	// Test 13 - lower_bound
	try {
		ft::map<int, char>m;
		iterator it = m.lower_bound(0);
		Test<bool>(it == m.end(), false);
		basic_map(m);
		it = m.lower_bound(0);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.lower_bound(4);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.lower_bound(5);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.lower_bound(9);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.lower_bound(13);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.lower_bound(14);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.lower_bound(100);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }

		const_iterator cit = m.lower_bound(0);
		if (cit != m.end()) { Test<int>(cit->first); } else { Test<std::string>("it == end"); }
		cit = m.lower_bound(4);
		if (cit != m.end()) { Test<int>(cit->first); } else { Test<std::string>("it == end"); }
	}
	catch (...) {}

	// Test 14 - upper_bound
	try {
		ft::map<int, char>m;
		iterator it = m.upper_bound(0);
		Test<bool>(it == m.end(), false);
		basic_map(m);
		it = m.upper_bound(0);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.upper_bound(4);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.upper_bound(5);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.upper_bound(9);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.upper_bound(13);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.upper_bound(14);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }
		it = m.upper_bound(100);
		if (it != m.end()) { Test<int>(it->first); } else { Test<std::string>("it == end"); }

		const_iterator cit = m.upper_bound(0);
		if (cit != m.end()) { Test<int>(cit->first); } else { Test<std::string>("it == end"); }
		cit = m.upper_bound(4);
		if (cit != m.end()) { Test<int>(cit->first); } else { Test<std::string>("it == end"); }
	}
	catch (...) {}

	// Test 15 - equal_range
	try {
		ft::map<int, char>m;
		basic_map(m);
		ft::pair<iterator, iterator> p = m.equal_range(4);
		Test<int>(p.first->first, false);
		Test<int>(p.second->first);
		p = m.equal_range(8);
		Test<int>(p.first->first);
		Test<int>(p.second->first);
		p = m.equal_range(14);
		if (p.first != m.end())
			Test<int>(p.first->first);
		else
			Test<std::string>("p.first == m.end()");
		if (p.second != m.end())
			Test<int>(p.first->first);
		else
			Test<std::string>("p.second == m.end()");
		p = m.equal_range(100);
		if (p.first != m.end())
			Test<int>(p.first->first);
		else
			Test<std::string>("p.first == m.end()");
		if (p.second != m.end())
			Test<int>(p.first->first);
		else
			Test<std::string>("p.second == m.end()");
		p = m.equal_range(0);
		if (p.first != m.end())
			Test<int>(p.first->first);
		else
			Test<std::string>("p.first == m.end()");
		if (p.second != m.end())
			Test<int>(p.first->first);
		else
			Test<std::string>("p.second == m.end()");

		ft::pair<const_iterator, const_iterator> e = m.equal_range(4);
		Test<int>(e.first->first);
		Test<int>(e.second->first);
	}
	catch (...) {}

	// Test 16 - Operator[]
	try {
		ft::map<int, char>m;
		char &a = m[12];
		m.size();
		Test<int>(m.begin()->first, false);
		a = 'g';
		Test<char>(m.begin()->second);
		m[1];
		m[0];
		m[124];
		m[0];
		Test<size_t>(m.size());
		for (iterator it = m.begin(); it != m.end(); ++it) {
			Test<int>(it->first);
		}
	}
	catch(...) {}

	// Test 17 - At
	try {
		ft::map<int, char>m;
		basic_map(m);
		char& c = m.at(13);
		c = 'v';
		for (iterator it = m.begin(); it != m.end(); ++it) {
			Test<char>(m.at(it->first));
		}
		m.at(12);
	}
	catch (std::out_of_range) { Test<std::string>("Out of Range Exeception"); }
	catch(...) {}

	// Test 18 - Compare operator
	try {
		ft::map<int, char> m;
		basic_map(m);
		ft::map<int, char> m2(m);

		Test<bool>(m == m2, false);
		Test<bool>(m != m2);
		m.insert(ft::make_pair(1, 'w'));
		Test<bool>(m < m2);
		Test<bool>(m <= m2);
		Test<bool>(m > m2);
		Test<bool>(m >= m2);

	}
	catch (...) {}

	// Test 19 - Iterator
	try {
		ft::map<int, char>m;
		basic_map(m);
		iterator it = m.begin();
		it->second = 'q';
		Test<char>(it->second, false);
		
		// Reverse
		for (ft::map<int, char>::reverse_iterator rit = m.rbegin(); rit != m.rend(); ++rit) {
			Test<int>(rit->first);
			rit->second = 'e';
		}
		for (ft::map<int, char>::const_reverse_iterator rit = m.rbegin(); rit != m.rend(); ++rit) {
			Test<int>(rit->second);
		}
	}
	catch(...) {}

	// Test 20 - THICC MAP
	try {
		ft::map<int, char>m;

		for (int i = 0; i <= 1000000; ++i) {
			m.insert(ft::make_pair(i, 'a'));
		}
		iterator it = m.find(1000000);
		if (it != m.end()) { Test<int>(it->first, false); }
		else { Test<std::string>("Not found"); }

		it = m.upper_bound(2000000);
		if (it != m.end()) { Test<int>(it->first, false); }
		else { Test<std::string>("Not found"); }

		Test<size_t>(m.size());
		m.clear();
		Test<bool>(m.empty());
	}
	catch(...) {}

	ofs.close();

	return 0;
}