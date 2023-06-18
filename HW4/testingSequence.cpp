#include "Sequence.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void test()
{
	Sequence<int> si;
	assert(si.empty());
	assert(si.size() == 0);
	assert(si.insert(0, 20) == 0);
	assert(si.insert(10) == 0);
	assert(si.find(20) == 1);
	assert(si.remove(10) == 1);
	int i;
	assert(si.get(0, i));
	assert(si.set(0, 30));
	assert(si.erase(0));
	Sequence<int> si2(si);
	si2.swap(si);
	si2 = si;
	assert(subsequence(si, si) == -1);
	concatReverse(si, si2, si);

	Sequence<string> ss;
	assert(ss.empty());
	assert(ss.size() == 0);
	assert(ss.insert(0, "Hello") == 0);
	assert(ss.insert("Goodbye") == 0);
	assert(ss.find("Hello") == 1);
	assert(ss.remove("Goodbye") == 1);
	string s;
	assert(ss.get(0, s));
	assert(ss.set(0, "Aloha"));
	assert(ss.erase(0));
	Sequence<string> ss2(ss);
	ss2.swap(ss);
	ss2 = ss;
	assert(subsequence(ss, ss2) == -1);
	concatReverse(ss, ss2, ss);
}

//int main()
//{
//	test();
//	cout << "Passed all tests" << endl;
//}

//#include "Sequence.h"  // class template from problem 2

//class Coord
//{
//public:
//	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//	Coord() : m_r(0), m_c(0) {}
//	double r() const { return m_r; }
//	double c() const { return m_c; }
//private:
//	double m_r;
//	double m_c;
//};
//
//int main()
//{
//	Sequence<int> si;
//	si.insert(50);               // OK
//	Sequence<Coord> sc;
//	sc.insert(0, Coord(50, 20));  // OK
//	sc.insert(Coord(40, 10));     // error!
//}
