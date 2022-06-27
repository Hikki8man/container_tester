#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <fstream>

extern std::ofstream ofs;

class Test {
	public:
		explicit Test() : nb(0) {}

		template<typename Type>
		void print(const Type& t) {
			ofs << t << " ";
		}

		void newTest() {
			++nb;
			ofs << std::endl;
			ofs << "Test " << nb << ": ";
		}
		protected:
			int nb;
	};

#endif // TEST_HPP