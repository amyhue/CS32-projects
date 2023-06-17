#include "Sequence.h"
#include <iostream> // allowed in the header?

using namespace std;


Sequence::Sequence() {
	m_size = 0;
}


bool Sequence::empty() const {
	if (size() == 0)
		return true;
	else
		return false;
}


int Sequence::size() const {
	return m_size;
}


int Sequence::insert(int pos, const ItemType& value) {

	// make sure there's room in the sequence to add an additional vlaue
	//if size() is not less than DEFAULT_MAX_ITEMS, then there is no room at all to add a new value
	
	if (0 <= pos && pos <= size() && size() < DEFAULT_MAX_ITEMS) {
		
		// shift items from pos and those following to one position greater than before
		for (int i = size(); i > pos; i--)
			m_arr[i] = m_arr[i -1];

		m_arr[pos] = value;
		m_size += 1; // size of the sequence increases by 1 when we insert a value
		return pos;
	}
	else return -1;
}


int Sequence::insert(const ItemType& value) {
	int p = size();

	//Find first p (i.e. smallest p) integer such that parameter value is less than or equal to any value in Sequence's object
	//at position p

	for (int i = 0; i < size(); i++) {
		if (value <= m_arr[i]) {
			p = i;
			break;
		}
	}

	return insert(p, value);
}


bool Sequence::erase(int pos) {
	if (0 <= pos && pos < size()){

		// Shift elements one to the left
		for (int i = pos; i < size() - 1; i++){
			m_arr[i] = m_arr[i + 1];
		}
		m_size = m_size - 1; // "Shrink" the Sequence size
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
	Sequence temp = other;

	other.m_size = this->m_size;
	for (int i = 0; i < other.m_size; i++) {
		other.m_arr[i] = this->m_arr[i];
	}

	this->m_size = temp.m_size;
	for (int i = 0; i < this->m_size; i++) {
		this->m_arr[i] = temp.m_arr[i];
	}
}

void Sequence::dump() const {
	cerr << "Sequence size: " << m_size<< endl;
	for(int i  = 0; i < m_size; i++)
		cerr << m_arr[i] << ", ";
	cerr << endl << endl;
}
