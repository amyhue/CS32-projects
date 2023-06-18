//#include <iostream>
//#include <cmath>
//#include <cassert>
//using namespace std;

//!*** delete above

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then for this value of a2            the function must return
//    "john" "ketanji" "elena"                     1
//    "john" "elena" "samuel"                      2
//    "ketanji" "john" "elena"                     0
//    "sonia" "elena" "samuel"                     3

// int countPos; // ***delete
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
     //return -999;  // This is incorrect.

    if (n2 <= 0)
        return 1;
    if (n1 <= 0)
        return 0;

    //countPos = countPos + 1; // *** delete

    if (a1[n1 - 1] == a2[n2 - 1])
        return countIncludes(a1, n1 - 1, a2, n2) + countIncludes(a1, n1 - 1, a2, n2 - 1);
    else
        return countIncludes(a1, n1 - 1, a2, n2);


}

// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator,
    int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;

    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < separator
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstGreater-1 is not known yet
    //  Every element at position firstGreater or later is > separator

    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    if (n <= 1) return;

    int firstNotLess = 0;
    int firstGreater = 0;

    separate(a, n, a[n - 1], firstNotLess, firstGreater);
    
    // if the last item in the array is the largest element (i.e. firstGreat == n),
    // then begin to order the sub-array before it containing all smaller elements
    if (firstGreater == n)
        order(a, firstNotLess);
    //countPos = countPos + 1; //***delete later
    else order(a, n);

}




//int main() {
//
//    int n1, n2, x;
//
//    string a1[] = { "sonia", "sonia", "elena" };
//    string q11[] = { "sonia", "elena" };
//
//    n1 = 3, n2 = 2; countPos = 0; x = (tgamma(n1 + 1 + 1) / tgamma(n2 + 1) * tgamma(n1 + 1 - n2 + 1));
//    assert(countIncludes(a1, n1, q11, n2) == 2 && !(countPos>x) );
//
//
//    string a[] = { "john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel" };
//    string q1[] = { "john", "ketanji", "elena" };
//    string q2[] = { "john", "elena", "samuel" };
//    string q3[] = { "ketanji", "john", "elena" };
//    string q4[] = { "sonia", "elena", "samuel" };
//
//    n1 = 7, n2 = 3; countPos = 0; x = (tgamma(n1 + 1 + 1) / tgamma(n2 + 1) * tgamma(n1 + 1 - n2 + 1));
//    assert(countIncludes(a, n1, q1, n2) == 1 && !(countPos > x));
//
//    n1 = 7, n2 = 3; countPos = 0; x = (tgamma(n1 + 1 + 1) / tgamma(n2 + 1) * tgamma(n1 + 1 - n2 + 1));
//    assert(countIncludes(a, n1, q2, n2) == 2 && !(countPos > x));
//
//    n1 = 7, n2 = 3; countPos = 0; x = (tgamma(n1 + 1 + 1) / tgamma(n2 + 1) * tgamma(n1 + 1 - n2 + 1));
//    assert(countIncludes(a, n1, q3, n2) == 0 && !(countPos > x));
//
//    n1 = 7, n2 = 3; countPos = 0; x = (tgamma(n1 + 1 + 1) / tgamma(n2 + 1) * tgamma(n1 + 1 - n2 + 1));
//    assert(countIncludes(a, n1, q4, n2) == 3 && !(countPos > x));
//
//
//    string a2[] = { "sonia", "sonia", "elena", "elena" };
//    string t1[] = {"sonia", "elena"};
//
//    n1 = 4; n2 = 2; countPos = 0; x = (tgamma(n1 + 1 + 1) / tgamma(n2 + 1) * tgamma(n1 + 1 - n2 + 1));
//    assert(countIncludes(a2, n1, t1, n2) == 4 && !(countPos > x));
//
//    int actual_size; int o1_size;
//    string o1[] = {"2", "1", "0", "3", "4", "99", "7", "9", "5", "8", "6", ""};
//    actual_size = 12;
//    o1_size = actual_size;
//    order(o1, o1_size);
//    for (int i = 0; i < actual_size; i++)
//        cout << o1[i] << ',';
//    cout << endl;
//
//
//    string o2[] = { "1", "1", "0", "2", "0", "1" };
//    actual_size = 6;
//    o1_size = 6;
//    order(o2, o1_size);
//    for (int i = 0; i < actual_size; i++)
//        cout << o2[i] << ',';
//    cout << endl;
//
//
//    cout << "Trees work" << endl;
//}
