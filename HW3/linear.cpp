//#include <iostream>
//#include <cassert>
//using namespace std;
//
//bool somePredicate(string s)
//{
//    return s.empty();
//}

// !*** DELETE/comment everything above (as stated in specs) + the int main() function
// MAKE SURE TO DELETE countPos BEFORE AND INSIDE THE positionOfMax FUNCTION!!!


// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{   
    // if the number of items is negative, act as if it were zero
    // if the number of items is zero, then it's somePredicate will not return false, so return true
    if (n <= 0)
        return true;

    if (somePredicate(a[n-1])) // (n-1)th position because n represents the number of items we want to consider
        return allTrue(a, n - 1); //check an array with n-1 items

    return false;  // This is not always correct.
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n)
{
    //return -999;  // This is incorrect.
    if(n<= 0)
        return 0;
    if(somePredicate(a[n-1]))
        return 1 + countTrue(a, n - 1);
    else return countTrue(a, n - 1);

}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    if (n <= 0)
        return -1;
    if (somePredicate(a[n - 1]) && firstTrue(a, n - 1) == -1)
        return n - 1;
    return firstTrue(a, n - 1);

    //return -999;  // This is incorrect.
}

// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
// that no strings are to be considered to be in the array, return -1.

//int countPos; // *** delete later
int positionOfMax(const string a[], int n)
{
    
    //return -999;  // This is incorrect.
    if (n <= 0)
        return -1;

    if (n == 1)
        return 0; // base case: returns 0th position if there's only one element

    //countPos = countPos + 1; // *** delete later

    // if the "last" element in the array is greater than the maximum string of the sub-array of strings before
    // then this last element is the greatest, so return its index. Otherwise, return the position of
    // the maximum string of the sub-array of strings before this last element.
    int x = positionOfMax(a, n-1);
    if (a[n - 1] > a[x])
        return n - 1;
    else return x;

    
}


// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)
        return true;

    // if we get here without triggering the above if statement, then n2 != 0, but n1 does
    // so there is nothing to compare the remaining elements of a2
    if (n1 <= 0)  
        return false;

    //countPos = countPos + 1; // *** delete later
    // if the "last" elements of a1 and a2 are the same, "decrease" the size of both arrays
    // otherwise, just "decrease" the size of a1 and leave a2 untouched
    if (a1[n1 - 1] == a2[n2 - 1])
        return contains(a1, n1 - 1, a2, n2 - 1);
    else
        return contains(a1, n1 - 1, a2, n2);


    //return false;  // This is not always correct.
}


//!*** delete / comment out before submitting 

//int main() {
//    string a[] = { "", "", "", "t", "t", "t" };
//    string b[] = { "" };
//    string c[] = { "t" };
//    string d[] = { "t", "", "", "", "t", "t" };
//
//    assert(allTrue(a, 6) == false);
//    assert(allTrue(a, 3) == true);
//    assert(allTrue(b, 1) == true);
//    assert(allTrue(c, 1) == false);
//    assert(allTrue(c, 0) == true);
//    assert(allTrue(c, -1) == true);
//
//    assert(countTrue(d, 2) == 1);
//    assert(countTrue(d, -10) == 0);
//    assert(countTrue(d, 6) == 3);
//    assert(countTrue(b, 0) == 0);
//    assert(countTrue(b, 1) == 1);
//    assert(countTrue(c, 1) == 0);
//
//    assert(firstTrue(a, 6) == 0);
//    assert(firstTrue(a, 3) == 0);
//    assert(firstTrue(b, 1) == 0);
//    assert(firstTrue(b, 0) == -1);
//    assert(firstTrue(c, 1) == -1);
//    assert(firstTrue(d, 6) == 1);
//    assert(firstTrue(d, 1) == -1);
//
//    countPos = 0;
//    assert(positionOfMax(a, 6) == 3 && !(countPos > 6));
//    countPos = 0;
//    assert(positionOfMax(a, 3) == 0 && !(countPos > 3));
//    countPos = 0;
//    assert(positionOfMax(a, 1) == 0 && !(countPos > 1));
//    countPos = 0;
//    assert(positionOfMax(a, 4) == 3 && !(countPos > 4));
//    countPos = 0;
//    assert(positionOfMax(b, 1) == 0 && !(countPos > 1));
//    countPos = 0;
//    assert(positionOfMax(b, 0) == -1 && !(countPos > 0));
//    countPos = 0;
//    assert(positionOfMax(b, -6) == -1);
//    countPos = 0;
//    assert(positionOfMax(c, 1) == 0 && !(countPos > 1));
//    countPos = 0;
//    assert(positionOfMax(d, 6) == 0 && !(countPos > 6));
//    countPos = 0;
//    assert(positionOfMax(d, 4) == 0 && !(countPos > 4));
//
//    string a1[] = { "john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel" };
//    string t1[] = { "sonia", "ketanji", "samuel" };
//    string t2[] = { "sonia", "elena", "elena" };
//    string f1[] = { "sonia", "samuel", "ketanji" };
//    string f2[] = { "sonia", "samuel", "ketanji" };
//
//    countPos = 0;
//    assert(contains(a1, 7, t1, 3) == true && !(countPos > 7));
//    countPos = 0;
//    assert(contains(a1, 7, t2, 3) == true && !(countPos > 7));
//    countPos = 0;
//    assert(contains(a1, 7, f1, 3) == false && !(countPos > 7));
//    countPos = 0;
//    assert(contains(a1, 7, f2, 3) == false && !(countPos > 7));
//
//    countPos = 0;
//    assert(contains(a1, 7, t1, -1) == true && !(countPos > 7));
//    countPos = 0;
//    assert(contains(a1, 0, t1, 3) == false && !(countPos > 0));
//    countPos = 0;
//    assert(contains(a1, 0, t1, 0) == true && !(countPos > 0));
//    countPos = 0;
//    assert(contains(a1, 7, t1, 0) == true && !(countPos > 7));
//    countPos = 0;
//    assert(contains(a1, -1, t1, -1) == true && !(countPos > 7));
//    countPos = 0;
//    assert(contains(a1, 1, t1, 3) == false && !(countPos > 1));
//    assert(contains(b, 1, d, 6) == false);
//
//
//    string a3[] = { "john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel" };
//    string q11[] = { "elena", "ketanji", "samuel" };
//    string q21[] = { "ketanji", "elena", "samuel" };
//
//    countPos = 0;
//    assert(contains(a3, 7, q11, 3) == true && !(countPos > 7));
//    countPos = 0;
//    assert(contains(a3, 7, q21, 3) == true && !(countPos > 7));
//
//
//
//    cout << "Test cases passed!" << endl;
//}
