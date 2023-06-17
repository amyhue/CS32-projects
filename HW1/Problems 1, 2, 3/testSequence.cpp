#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{

    /*Sequence s;
    s.insert(0, "a");
    s.insert(1, "b");
    s.insert(2, "e");
    s.insert(3, "b");
    s.insert(4, "c");
    assert(s.remove("b") == 2);
    assert(s.size() == 3);
    string x;
    assert(s.get(0, x) && x == "a");
    assert(s.get(1, x) && x == "e");
    assert(s.get(2, x) && x == "c");*/

    /*Sequence s1;
    s1.insert(0, "paratha");
    s1.insert(0, "focaccia");
    Sequence s2;
    s2.insert(0, "roti");
    s1.swap(s2);
    assert(s1.size() == 1 && s1.find("roti") == 0 && s2.size() == 2 &&
        s2.find("focaccia") == 0 && s2.find("paratha") == 1);*/

    /*Sequence s;
    s.insert(0, "dosa");
    s.insert(1, "pita");
    s.insert(2, "");
    s.insert(3, "matzo");
    assert(s.find("") == 2);
    s.remove("dosa");
    assert(s.size() == 3 && s.find("pita") == 0 && s.find("") == 1 &&
        s.find("matzo") == 2);*/


    Sequence s;
    assert(s.empty());
    s.dump();
    assert(s.find(42) == -1);
    s.dump();
    assert(s.insert(42) == 0);
    s.dump();
    assert(s.size() == 1 && s.find(42) == 0);
    s.dump();
    s.insert(42);

    Sequence s2;
    assert(s2.insert(1, 50) == -1);
    s2.dump();
    assert(s2.insert(0, 50) == 0);
    s2.dump();
    assert(s2.insert(40) == 0);
    s2.dump();
    assert(s2.insert(50) == 1);
    s2.dump();
    assert(s2.insert(100) == 3);
    s2.dump();
    s2.insert(101);
    s2.insert(102);
    s2.insert(90);
    assert(s2.size() == 7);
    s2.dump();
    //assert(s2.insert(103) == -1); // if DEFAULT_MAX_ITEMS = 7
    cerr << ";-;" << endl;
    assert(s2.erase(100) == false);
    s2.dump();
    assert(s2.erase(3) == true && s2.size() == 6); // erases 90
    s2.dump();
    assert(s2.remove(500) == 0 && s2.size() == 6);
    s2.dump();
    assert(s2.remove(50) == 2 && s2.size() == 4);
    s2.dump();

    cout << endl << ";-; initial" << endl;
    s.dump();
    s2.dump();

    cout << endl<< ";-; swapping" << endl <<endl;

    s2.swap(s);
    s.dump();
    s2.dump();



    cout << "Passed all tests" << endl;
}
