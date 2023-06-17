#include "newSequence.h"
#include <iostream>

using namespace std;


Sequence::Sequence() {
	
	m_max_size = DEFAULT_MAX_ITEMS;
	m_size = 0;

	m_arr = new ItemType[m_max_size];
}

Sequence::Sequence(int size) {
	
	if(size <0) {
		cerr << "Cannot create a Sequence that can hold " << size << " items." << endl;
		exit(1);
	}
	else {
	m_max_size = size;
	m_size = 0;
	m_arr = new ItemType[m_max_size];
	}
	
}


Sequence::Sequence(const Sequence& other)
	:m_max_size(other.m_max_size), m_size(other.m_size)
{	
	m_arr = new ItemType[m_max_size];

	//copy contents of other
	for (int i = 0; i < m_size; i++) {
		*(m_arr + i) = *(other.m_arr + i);
	}
}

Sequence::~Sequence() {
	
	delete [] m_arr;
	m_arr = NULL;
}


Sequence& Sequence::operator=(const Sequence& rhs) {
	if (this != &rhs) {
		Sequence temp(rhs);
		swap(temp);
	}
	
	return *this;
}


// Return true if the sequence is empty, otherwise false.
bool Sequence::empty() const {
	if (size() == 0)
		return true;
	else
		return false;
}

// Return the number of items in the sequence.
int Sequence::size() const {
	return m_size;
}


int Sequence::insert(int pos, const ItemType& value) {

	// make sure there's room in the sequence to add an additional vlaue
	//if size() is not less than m_max_size, then there is no room at all to add a new value

	if (0 <= pos && pos <= size() && size() < m_max_size) {

		// shift items from pos and those following to one position greater than before
		for (int i = size(); i > pos; i--)
			m_arr[i] = m_arr[i - 1];

		m_arr[pos] = value;
		m_size += 1; // size of the sequence increases by 1 when we insert a value
		return pos;
	}
	else return -1;
}


int Sequence::insert(const ItemType& value) {
	int p = size();

	for (int i = 0; i < size(); i++) {
		if (value <= m_arr[i]) {
			p = i;
			break;
		}
	}

	return insert(p, value);
}

bool Sequence::erase(int pos) {
	if (0 <= pos && pos < size()) {

		// !***WHAT TO DO FOR m_arr[m_size()-1]?
		//***delete last element or set it to NULL?
		for (int i = pos; i < size() - 1; i++) {
			m_arr[i] = m_arr[i + 1];
		}
		m_size = m_size - 1;
		return true;
	}
	else return false;
}


int Sequence::remove(const ItemType& value) {

	int eraseCounter = 0;
	for (int i = 0; i < size(); i++) {
		if (value == m_arr[i]) {
			erase(i);
			eraseCounter++;
			i--; // because all values will shift "down" and we don't want to skip a value
		}
	}
	return eraseCounter;
}


bool Sequence::get(int pos, ItemType& value) const {
	if (0 <= pos && pos < size()) {
		value = m_arr[pos];
		return true;
	}
	else return false;
}


bool Sequence::set(int pos, const ItemType& value) {

	if (0 <= pos && pos < size()) {
		m_arr[pos] = value;
		return true;
	}
	return false;
}


int Sequence::find(const ItemType& value) const {
	int p = -1;

	for (int i = 0; i < size(); i++) {
		if (value == m_arr[i]) {
			p = i;
			break;
		}
	}

	return p;
}


void Sequence::swap(Sequence& other) {
	Sequence temp(other);
	
	/*for (int i = 0; i < temp.m_size; i++)
		cerr << temp.m_arr[i] << ", ";
	cerr << endl << temp.m_arr << endl;

	cerr << endl;
	for (int i = 0; i < other.m_size; i++)
		cerr << endl << other.m_arr[i] << ", ";
	cerr << endl << other.m_arr << endl;

	cerr << "-------------" << endl;*/

	other.~Sequence();
	other.m_max_size = this->m_max_size;
	other.m_size = this->m_size;
	other.m_arr = new ItemType[this->m_max_size];
	for (int i = 0; i < other.m_size; i++) {
		*(other.m_arr + i) = *(this->m_arr + i);
	}


	this->~Sequence();
	this->m_max_size = temp.m_max_size;
	this->m_size = temp.m_size;
	this->m_arr = new ItemType[temp.m_max_size];
	for (int i = 0; i < this->m_size; i++) {
		*(this->m_arr + i) = *(temp.m_arr + i);
	}
	/*other.~Sequence();
	other.m_max_size = this->m_max_size;
	other.m_size = this->m_size;
	other.m_arr = this->m_arr;

	this->~Sequence();
	this->m_max_size = temp.m_max_size;
	this->m_size = temp.m_size;
	this->m_arr = temp.m_arr;*/

	// Why heap error?

	
	/*for (int i = 0; i < temp.m_size; i++)
		cerr << temp.m_arr[i] << ", ";
	cerr << endl<< temp.m_arr <<endl;

	cerr << endl;
	for (int i = 0; i < other.m_size; i++)
		cerr << endl << other.m_arr[i] << ", ";
	cerr << endl << other.m_arr<<endl;

	cerr << endl;
	for (int i = 0; i < this->m_size; i++)
		cerr << this->m_arr[i] << ", ";
	cerr << endl << this ->m_arr<< endl;*/
	

	

}

void Sequence::dump() const {
	cerr << "Sequence size: " << m_size << endl;
	for (int i = 0; i < m_size /*+ 5*/; i++)
		cerr << m_arr[i] << ", ";
	cerr << endl << endl;
}
