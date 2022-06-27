#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <fstream>

extern std::ofstream ofs;
extern int nb;

class Test {
	public:
		explicit Test() {}

		template<typename Type>
		void print(const Type& t) {
			ofs << t << " ";
		}

		static void newTest() {
			++nb;
			ofs << std::endl;
			ofs << "Test " << nb << ": ";
		}
	};

#endif // TEST_HPP