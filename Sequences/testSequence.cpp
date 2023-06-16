#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

//int main()

#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    assert(s.insert(0, "lavash") == 0);
    assert(s.insert(0, "tortilla") == 0);
    assert(s.size() == 2);
    ItemType x = "injera";
    assert(s.get(0, x) && x == "tortilla");
    assert(s.get(1, x) && x == "lavash");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

//int main() {
//	//test size, empty, insert, default constructor
//	Sequence s1; // default constructor
//	Sequence s2;
//	Sequence s3;
//	ItemType x = 0;
//	ItemType y = 0;
//
//	assert(s1.size() == 0 && s1.empty() == true); // tests empty sequence has size 0 and is empty
//	assert(s1.insert(-100, 100) == -1); // cannot insert at negative position value
//	assert(s1.insert(1, 100) == -1); // cannot insert at a position value greater than the sequence's size
//
//	assert(s1.insert(0, 100) == 0); // can insert at position 0
//	assert(s1.empty() == false && s1.size() == 1); // checks that the sequence is no longer empty and has increased in size by 1
//	assert(s1.insert(1, 200) == 1); // can now insert at pos = 1 because 1 is not greater than sequence size
//	assert(s1.insert(0, 50) == 0 && s1.size() > 2); // can insert at pos == 0 without overwriting the value originally at pos
//	assert(s1.insert(2, 150) == 2); // can insert when pos is an int between 0 and size()
//	assert(s1.insert(s1.size(), 250) == 4); // can insert when pos == size()
//	assert(s1.insert(1, 50) == 1); // can insert at pos 1
//	assert(s1.size() == 6); // checks the size
//	// Sequence s1 from 0 to size() should be (comma for reading clarity): 50, 50, 100, 150, 200, 250
//
//	// ;-;
//	// test single-parameter insert
//	assert(s2.insert(100) == 0 && s2.size() == 1); // inserts at pos = 0 and size() increases by 1
//	assert(s2.insert(200) == 1); // inserts at pos = 1 because no value is smaller than 100
//	assert(s2.insert(50) == 0); // inserts at pos = 0 because it's the smallest location where 50 <= value (50 < 100)
//	assert(s2.insert(150) == 2); // inserts at pos = 2 because it's the smallest location where 150 <= value (150 < 200 but 150 > 100)
//	assert(s2.insert(250) == 4); // inserts at pos = 4 because no value is smaller than 250
//	assert(s2.insert(50) == 0); // inserts at pos = 0 because it's the smallest location where 50 <= value (50 = 50)
//	assert(s2.size() == 6); // checks the size
//	//Sequence s2 from 0 to size() should be: 50, 50, 100, 150, 200, 250
//
//	// ;-;
//	//test get() - we'll test s1
//	//s1: 50, 50, 100, 150, 200, 250
//	assert(s1.get(-1, x) == false && x == 0); // cannot get values at pos <0
//	assert(s1.get(6, x) == false && x == 0); // cannot get value at pos = size()
//	assert(s1.get(7, x) == false && x == 0); // cannot get value at pos > size()
//
//	// checks we can get values when 0 <= position < size() and get values at positions we're expecting
//	// tests that the double-parameter insert() function worked as expected
//	assert(s1.get(0, x) && x == 50);
//	assert(s1.get(1, x) && x == 50);
//	assert(s1.get(2, x) && x == 100);
//	assert(s1.get(3, x) && x == 150);
//	assert(s1.get(4, x) && x == 200);
//	assert(s1.get(5, x) && x == 250);
//
//	// ;-;
//	// tests that the single-parameter insert() worked as expected
//	assert(s2.get(0, x) && x == 50);
//	assert(s2.get(1, x) && x == 50);
//	assert(s2.get(2, x) && x == 100);
//	assert(s2.get(3, x) && x == 150);
//	assert(s2.get(4, x) && x == 200);
//	assert(s2.get(5, x) && x == 250);
//
//	// ;-;
//	// test erase()
//	//we'll work with the s2 Sequence (size = 6)
//	// s2: 50, 50, 100, 150, 200, 250
//	assert(s2.erase(-1) == false && s2.erase(6) == false && s2.erase(7) == false); // cannot erase from values that are < 0 or >= size()
//	assert(s2.erase(1) == true); // can erase at pos between 0 and size() (not-inclusive)
//	// s2 (size = 5): 50, 100, 150, 200, 250
//
//	// make sure we can erase() start and end of a sequence
//	assert(s2.erase(4) == true); //Erased end of s2 -- s2 is now: 50, 100, 150, 200
//	assert(s2.erase(0)); //Erased start of s2 -- s2 is now: 100, 150, 200
//
//	assert(s3.erase(0) == false); // can't erase on a empty Sequence
//
//	//;-;
//	// test remove() - we'll work with the s1 Sequence
//	s1.insert(5, 50); // remove(5)) should later remove all values of 50, even if they aren't all clustered at the start of the sequence
//	assert(s1.remove(50) == 3 && s1.size() == 4); // should remove all values of 50
//
//	// Check that s1 is now: 100, 150, 200, 250
//	assert(s1.get(0, y) && y == 100);
//	assert(s1.get(1, y) && y == 150);
//	assert(s1.get(2, y) && y == 200);
//	assert(s1.get(3, y) && y == 250);
//
//	//;-;
//	// test set() - we'll work with the s1 Sequence
//	// check that cannot replace item at position pos if pos < 0 or pos >= size()
//	assert(s1.set(-1, 300) == false && s1.set(4, 300) == false && s1.set(5, 300) == false);
//
//	//check that s1 has not been modified after failed set()
//	assert(s1.size() == 4);
//	assert(s1.get(0, y) && y == 100);
//	assert(s1.get(1, y) && y == 150);
//	assert(s1.get(2, y) && y == 200);
//	assert(s1.get(3, y) && y == 250);
//
//	assert(s1.set(0, 300) == true && s1.get(0, y) && y == 300); // can modified start of the sequence
//	assert(s1.set(3, 300) == true && s1.get(3, y) && y == 300); // can modified end of the sequence
//	assert(s1.set(1, 300) == true && s1.get(1, y) && y == 300); // can modified middle of the sequence
//	assert(s1.get(2, y) && y == 200); //check that set() did not modify any other nodes
//
//	// change s1 back to what it was before we modified it with set()
//	s1.set(0, 100); s1.set(3, 250); s1.set(1, 150);
//
//	assert(s1.get(0, y) && y == 100);
//	assert(s1.get(1, y) && y == 150);
//	assert(s1.get(2, y) && y == 200);
//	assert(s1.get(3, y) && y == 250);
//
//	//;-;
//	// test find() - we'll use s1
//	assert(s1.find(50) == -1); // there's no 50 in s1
//	assert(s1.find(250) == 3); // 250 is located at position 3
//	assert(s1.insert(4, 250) == 4); assert(s1.find(250) == 3); // although there are two 250s, find() returns the smallest possible position value
//	s1.erase(250);
//
//	//;-;
//	// test copy constructor
//	Sequence copy_s1(s1); // copies s1
//	assert(copy_s1.size() == s1.size()); //checks their size is the same
//	// loop through the node to make sure the corresponding values are the same
//	for (int i = 0; i < copy_s1.size(); i++) {
//		ItemType s1_val, copy_s1_val;
//		s1.get(i, s1_val); copy_s1.get(i, copy_s1_val);
//		assert(s1_val == copy_s1_val);
//	}
//
//	//;-;
//	//test swap() - we'll swap s1 and s1 first; since s4 is a copy of s1, we'll compared a swapped s1 with s4
//	s1.swap(s1);
//	assert(copy_s1.size() == s1.size()); //checks their size is the same
//	// checks that swap() did not modify s1
//	for (int i = 0; i < s1.size(); i++) {
//		ItemType s1_val, copy_s1_val;
//		s1.get(i, s1_val); copy_s1.get(i, copy_s1_val);
//		assert(s1_val == copy_s1_val);
//	}
//
//	// Now, we'll test swap() with s1 and s2
//	Sequence copy_s2(s2); // create a copy of s2
//	assert(copy_s2.size() == s2.size()); //checks their size is the same
//
//	s1.swap(s2); // s1 and s2 swaps
//
//	// checks that swap() swapped s1 and s2 (we compare with copy_s2 and copy_s1 respectively)
//	//checks s2 is now s1
//	for (int i = 0; i < s1.size(); i++) {
//		ItemType s1_val, copy_s2_val;
//		s1.get(i, s1_val); copy_s2.get(i, copy_s2_val);
//		assert(s1_val == copy_s2_val);
//	}
//
//	//checks s1 is now s2
//	for (int i = 0; i < s2.size(); i++) {
//		ItemType s2_val, copy_s1_val;
//		s2.get(i, s2_val); copy_s1.get(i, copy_s1_val);
//		assert(s2_val == copy_s1_val);
//	}
//
//
//	//;-;
//	// test operator=
//
//	// check that we can assign a Sequence itself
//	s1 = s1;
//	for (int i = 0; i < s1.size(); i++) {
//		ItemType s1_val, copy_s2_val;
//		s1.get(i, s1_val); copy_s2.get(i, copy_s2_val);
//		assert(s1_val == copy_s2_val);
//	}
//
//	//check that we can assign an uninitialized Sequence
//	Sequence copy_s1_1 = copy_s1;
//	for (int i = 0; i < copy_s1_1.size(); i++) {
//		ItemType copy_s1_1_val, copy_s1_val;
//		copy_s1_1.get(i, copy_s1_1_val); copy_s1.get(i, copy_s1_val);
//		assert(copy_s1_1_val == copy_s1_val);
//	}
//
//	// check that we can assign to an initialized Sequence (of different size) and overwrite previous data
//	copy_s1 = copy_s2;
//	for (int i = 0; i < copy_s1.size(); i++) {
//		ItemType copy_s1_val, copy_s2_val;
//		copy_s1.get(i, copy_s1_val); copy_s2.get(i, copy_s2_val);
//		assert(copy_s1_val == copy_s2_val);
//	}
//
//
//	//;-;
//	// test subsequence()
//
//	Sequence seq1; seq1.insert(10); seq1.insert(20); seq1.insert(30);
//	//seq1: 10, 20, 30
//
//	Sequence seq2 = s1; seq2.insert(0, 150); seq2.insert(1, 100); seq2.insert(2, 200);
//	//seq2: 150, 100, 200, 100, 150, 200
//	Sequence seq3 = s1; seq3.insert(0, 50); seq3.insert(4, 70);
//	seq3.insert(5, 100); seq3.insert(6, 150); seq3.insert(200);
//	//seq3: 50, 100, 150, 200, 70, 100, 150, 200
//
//	assert(subsequence(s3, s1) == -1); // cannot find subsequence from an empty sequence
//	assert(subsequence(s1, s3) == -1); // cannot find subsequence with an empty sequence
//	assert(subsequence(s1, seq1) == -1); // seq1 is not a subsequence of s1
//	assert(subsequence(s2, s1) == 0); // s2 is a subsequence of s1 starting at position 0
//	assert(subsequence(seq2, s1) == 3); // s2's items must be listed in order in s1 to count as a subsequence
//	assert(subsequence(seq3, s1) == 1); // returns the smallest position where the subsequence occurs
//
//	//;-;
//	//test concatReverse()
//	Sequence result1;
//	Sequence result2;
//
//	concatReverse(s3, result1, result2); // if both sequences are empty, the result sequence should also be empty
//	assert(s3.size() == 0 && result1.size() == 0 && result2.size() == 0);
//
//	// if the first sequence is empty, the result sequence should only contain items from
//	// the non-empty sequence (i.e. second)
//	concatReverse(s1, s3, result1);
//	assert(s1.size() != 0 && s3.size() == 0 && result1.size() == s1.size());
//	for (int i = 0; i < s1.size(); i++) {
//		ItemType s1_val, result1_val;
//		s1.get(i, s1_val); result1.get(result1.size() - 1 - i, result1_val);
//		assert(s1_val == result1_val);
//	}
//
//	// if the second sequence is empty, the result sequence should only contain items from
//	// the non-empty sequence (i.e. first)
//	concatReverse(s3, s1, result2);
//	assert(s3.size() == 0 && s1.size() != 0 && result2.size() == s1.size());
//	for (int i = 0; i < s1.size(); i++) {
//		ItemType s1_val, result2_val;
//		s1.get(i, s1_val); result2.get(result2.size() - 1 - i, result2_val);
//		assert(s1_val == result2_val);
//	}
//
//	// if result and seq1 (and/or seq 2) refer to the same sequence, the function should
//	// return a sequence that is not impacted by the aliasing. We should see the same
//	// sequence as if result and seq1/seq2 were not referring to the same sequence.
//	copy_s1 = s1;
//	concatReverse(s1, s2, copy_s1); // copy_s1 and s1 do not refer to the same sequence
//	concatReverse(s1, s2, s1); // s1 and s1 refer to the same sequence - s1 has now been modified
//	// copy_s1 and s1 objects should be identical (i.e. copies of each other) if concatReverse is implemented correctly
//	assert(s1.size() == copy_s1.size());
//	for (int i = 0; i < s1.size(); i++) {
//		ItemType s1_val, copy_s1_val;
//		s1.get(i, s1_val); copy_s1.get(i, copy_s1_val);
//		assert(s1_val == copy_s1_val);
//	}
//
//	copy_s2 = s2;
//	concatReverse(s1, s2, copy_s2); // copy_s2 and s2 do not refer to the same sequence
//	concatReverse(s1, s2, s2); // s2 and s2 refer to the same sequence - s2 has now been modified
//	// copy_s2 and s2 objects should be identical (i.e. copies of each other) if concatReverse is implemented correctly
//	assert(s2.size() == copy_s2.size());
//	for (int i = 0; i < s2.size(); i++) {
//		ItemType s2_val, copy_s2_val;
//		s2.get(i, s2_val); copy_s2.get(i, copy_s2_val);
//		assert(s2_val == copy_s2_val);
//	}
//
//	copy_s1 = s1;
//	copy_s1_1 = s1;
//	concatReverse(s1, copy_s1_1, copy_s1); // s1, copy_s1_1, copy_s1 do not refer to the same sequence
//	concatReverse(s1, s1, s1); // s1 all refer to the same sequence - s1 has now been modified
//	// copy_s1 and s1 objects should be identical (i.e. copies of each other) if concatReverse is implemented correctly
//	assert(s1.size() == copy_s1.size());
//	for (int i = 0; i < s1.size(); i++) {
//		ItemType s1_val, copy_s1_val;
//		s1.get(i, s1_val); copy_s1.get(i, copy_s1_val);
//		assert(s1_val == copy_s1_val);
//	}
//
//	//;-; test destructor
//	//s1.~Sequence();
//	//s2.~Sequence();
//	//s3.~Sequence();
//
//	cout << "Test cases have passed!" << endl;
//
//}
