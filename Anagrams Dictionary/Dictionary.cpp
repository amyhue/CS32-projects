// Dictionary.cpp

// Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl(int maxBuckets);
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
private:
    //list<string> m_words; 
    int m_buckets;
    vector<list<list<string>>> m_words;
    // for the list of anagrams of a word, the string in the first index is the key. We'll never compare
    // it to the word we want to insert or delete. This way, if the key has the same lette arrangement as 
    // a word we want to insert we won't accidentally think the word already exists in the list of anagrams.
    // Similarly, if we want to delete the anagram with the same letter arrangement as the key, we won't lose it.
};

DictionaryImpl::DictionaryImpl(int maxBuckets/* = 50000*/) : m_words(maxBuckets){
    m_buckets = maxBuckets;
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);

    if (!word.empty()) {
        string key = word;
        sort(key.begin(), key.end());

        // the hashValue corresponds to the bucket (aka the vector index)
        hash<string> hashVal;
        int hashValue = hashVal(key) % m_buckets;


        // first we check whether this key exists already in the given bucket - if it doesn't, we'll add it.
        // If it does exist, we'll want to stop traversing the list and add the anagram and the word to the list (since
        // duplicates are allowed)

        list<list<string>>::iterator it = m_words[hashValue].begin();
        for (it = m_words[hashValue].begin(); it != m_words[hashValue].end(); it++) {
            if (it->front() == key) {

                // if duplicate words were not allowed
                //for (list<string>::iterator newIt = it->begin(); newIt != it->end(); newIt++) {
                //    if (newIt == it->begin()) continue; // the beginning element in the list is the key
                //    if (*newIt == word) return;
                //}

                // We now can add word to the end of the list.
                it->push_back(word);
                return;
            }
        }

        // at this point, the key doesn't exist in the given bucket. We'll create an anagram list and 
        // add the key and also the word we want to insert to this anagram list. The anagram list will
        // then be added to the bucket.
        list<string> newAnagramList;
        newAnagramList.push_back(key);
        newAnagramList.push_back(word);
        m_words[hashValue].push_back(newAnagramList);
        
    }

}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    string key = letters;
    sort(key.begin(), key.end());
    hash<string> hashVal;
    int hashValue = hashVal(key) % m_buckets;

    list<list<string>>::const_iterator it = m_words[hashValue].begin();

    for (it = m_words[hashValue].begin(); it != m_words[hashValue].end(); it++) {
        if (it->front() == key) {

            for (list<string>::const_iterator newIt = it->begin(); newIt != it->end(); newIt++) {
                if (newIt == it->begin()) continue; // the beginning element in the list is the key
                callback(*newIt);
            }
            return;
        }
    }

}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}



// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p + 1; q <= last && *q > *(p - 1); q++)
            ;
        swap(*(p - 1), *(q - 1));
    }
    for (; p < last; p++, last--)
        swap(*p, *last);
}






//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
