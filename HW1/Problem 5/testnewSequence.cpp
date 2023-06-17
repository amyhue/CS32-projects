#include "newSequence.h"
#include "RainfallList.h"

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence a(10);   // a can hold at most 10 items
    Sequence b(5);      // b can hold at most 5 itembs
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 30;

    //Sequence f(-10);

    cout << endl << ";-;" << endl << endl;

    b.dump();
    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v + k) != -1);

    b.dump();

    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);
    b.dump();

    cout << endl << ";-;" << endl << endl;
    a.dump();
    b.dump();
    cout << endl << ";-; operator=" << endl << endl;

    b.dump();
    Sequence d;
    d.dump();

    d = b;
    cout << endl << ";-; testing operator=" << endl << endl;
    d.dump();
    b.dump();

    d.insert(5);
    d.dump();
    b.dump();

    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    assert(a.insert(1, 100) == -1);
    assert(a.insert(0, 100) == 0);
    cout << endl << ";-; prep for swap" << endl << endl;
    a.dump();
    b.dump();
    cout << endl << ";-; swapping=" << endl << endl;
    a.swap(b);
    cout << endl << ";-; swapped=" << endl << endl;
    a.dump();
    b.dump();

    a.insert(100);
    a.dump();
    b.dump();

    b.swap(a);
    cout << "swapped" << endl;
    a.dump();
    b.dump();

    a.swap(b);
    cout << "swapped again" << endl;
    a.dump();
    b.dump();


    cout << endl << ";-;" << endl << endl;


    assert(a.insert(v) == -1 && b.insert(v) != -1);
    a.dump();
    b.dump();

    cout << endl << ";-;" << endl << endl;

    RainfallList rain;

    assert(rain.size() == 0);
    assert(rain.add(-1) == false && rain.size() == 0);
    assert(rain.add(401) == false && rain.size() == 0);

    /*rain.dump();*/

    assert(rain.add(100) == true && rain.size() == 1);
    /*rain.dump();*/

    rain.add(-150);
    /*rain.dump();*/
    assert(rain.add(150) == true && rain.size() == 2);
    assert(rain.add(150) == true && rain.size() == 3);
    assert(rain.add(150) == true && rain.size() == 4);


    assert(rain.add(150) == true && rain.size() == 5);
    assert(rain.add(140) == true && rain.size() == 6);
    assert(rain.add(160) == true && rain.size() == 7);

    assert(rain.remove(170) == false && rain.size() == 7);
    assert(rain.remove(150) == true && rain.size() == 6);

    assert(rain.minimum() == 100);
    assert(rain.maximum() == 160);

    rain.remove(160);
    assert(rain.maximum() == 150);

    cout << "Tests have passed!" << endl;

    cout << "Passed all tests" << endl;

    /*a.~Sequence();
    b.~Sequence();
    c.~Sequence();
    d.~Sequence();*/

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

    cout << endl << ";-; swapping" << endl << endl;

    s2.swap(s);
    s.dump();
    s2.dump();

 
    cout << "Tests have passed!" << endl;
    cout << "Passed all tests" << endl;
}
