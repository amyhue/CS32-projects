#include "RainfallList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
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
}
