#include "Sequence.h"
#include <iostream>


Sequence::Sequence() {

	head = new Node; // head points to a dummy Node object
	head->m_next = head;
	head->m_prev = head;
	//head->m_data = -100;
}

bool Sequence::empty() const{
	if (size() == 0)
		return true;
	else return false;
}

int Sequence::size() const{
	int size_count = 0;
	for (Node* p = head->m_next; p != head; p = p->m_next) {
		size_count++;
	}
	return size_count;
}

int Sequence::insert(int pos, const ItemType& value) {
	if (0 <= pos && pos <= size()) {
		
		// create new node that we will insert into the linked list with m_data = value
		Node* new_node = new Node;
		new_node->m_data = value;

		// iterate throught the list to point to node position we want to insert at
		Node* p = head->m_next;
		for(int node_num = 0; node_num < pos; node_num++) {
			p = p->m_next;
		}
		
		Node* p_tail = p->m_prev;

		//insert new node between node at pos-1 and current node at pos
		p_tail->m_next = new_node;
		new_node->m_prev = p_tail;
		new_node->m_next = p;
		p->m_prev = new_node;


		//std::cerr << "new_node value: " << new_node->m_data << ", position value: " << pos << std::endl;
		return pos;
	}
	else return -1;
}

int Sequence::insert(const ItemType& value) {
	int p = size();

	//traverse linked list to find node values == value
	Node* node_pos = head->m_next;
	for (int node_num = 0; node_num < size(); node_num++) {
		if (value <= node_pos->m_data) {
			p = node_num;
			break;
		}

		node_pos = node_pos->m_next;
	}

	return insert(p, value);
}

bool Sequence::erase(int pos) {
	if (0 <= pos && pos < size()){	

		// get to position of the node we want to erase
		Node* to_delete = head->m_next;
		for (int node_num = 0; node_num < pos; node_num++) {
			to_delete = to_delete->m_next;
		}

		Node* node_before = to_delete->m_prev;
		Node* node_after = to_delete->m_next;

		// link node_before with node_after properly;
		node_before->m_next = to_delete->m_next;
		node_after->m_prev = to_delete->m_prev;

		// delete the node that to_delete points to
		delete to_delete;
		to_delete = NULL;

		return true;
	}

	else return false;
}

int Sequence::remove(const ItemType& value) {
	int erase_counter = 0;
	int pos = 0; // node position

	// traverse linked list to remove all nodes with m_data == value
	for (Node* p = head->m_next; p != head;) {
		if (value == p->m_data) {
			p = p->m_next; // pre-emptively point to the next node because current node will be deleted
						   //and we'll lose the pointer to the next node
			erase(pos);
			erase_counter++;
			pos--;
		}
		else {
			p = p->m_next;
		}
		pos++;
	}
	return erase_counter;
}

bool Sequence::get(int pos, ItemType& value) const {
	if (0 <= pos && pos < size()) {

		//traverse linked list to point to node at position pos
		Node* p = head->m_next;
		for (int node_num = 0; node_num < pos; node_num++) {
			p = p->m_next;
		}

		// store the node's m_data in value
		value = p->m_data;
		return true;
	}

	else return false;
}

bool Sequence::set(int pos, const ItemType& value) {
	if (0 <= pos && pos < size()) {

		//traverse linked list to point to node at position pos
		Node* p = head->m_next;
		for (int node_num = 0; node_num < pos; node_num++) {
			p = p->m_next;
		}

		// set value in the node's m_data
		p->m_data = value;
		return true;
	}

	else return false;
}

int Sequence::find(const ItemType& value) const {
	int p = -1;
	int posCounter = 0;

	// traverse array to find first m_data == value
	for (Node* pos = head->m_next; pos != head; pos = pos->m_next) {
		if (pos->m_data == value) {
			p = posCounter;
			break;
		}
		posCounter++;
	}

	return p;
}

void Sequence::swap(Sequence& other) {
	Node* tempHead = other.head;
	other.head = this->head;
	this->head = tempHead;
}

Sequence::~Sequence() {
	for (Node* p = head->m_next; p != head; /*p = p->m_next*/) {
		Node* to_be_deleted = p;
		p = p->m_next;
		delete to_be_deleted;
		to_be_deleted = NULL;
	}


	delete head;
	head = NULL;
	

}

Sequence::Sequence(const Sequence& other) {
	head = new Node; // head points to a dummy Node object
	head->m_next = head;
	head->m_prev = head;

	int pos = 0;
	//traverse other Sequence and insert a node with corresponding value according to proper position in this
	for (Node* p = other.head->m_next; p != other.head; p = p->m_next) {
		insert(pos, p->m_data);
		pos++;
	}
}

Sequence& Sequence::operator=(const Sequence& rhs) {
	if (this != &rhs)
	{
		Sequence temp(rhs);
		swap(temp);
	}
	return *this;
}

void Sequence::dump() const {
	
	std::cerr << "Sequence next: ";
	
	for (Node* p = head->m_next; p != head; p = p->m_next) {
		std::cerr << p->m_data << ", ";
	}

	std::cerr << std::endl << "Sequence prev: ";
	for (Node* p = head->m_prev; p != head; p = p->m_prev) {
		std::cerr << p->m_data << ", ";
	}
	std::cerr << std::endl;
	std::cerr << "Finished outputting all nodes" << std::endl << std::endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
	int k = -1;

	if (seq2.empty() == true) return -1;

	for (int i = 0; i < seq1.size(); i++) {
		ItemType seq1_value, seq2_value;
		seq1.get(i, seq1_value);
		seq2.get(0, seq2_value);
		if (seq1_value == seq2_value) {
			k = i;

			for (int n = 0; n < seq2.size(); n++) {
				if (i + n >= seq1.size()) // out of seq1 bounds
					return -1;
				seq1.get(i + n, seq1_value);
				seq2.get(n, seq2_value);
				if (seq1_value != seq2_value) { // if a node doesn't match, leave the for loop
					k = -1;
					break;
				}
				
				if (n == seq2.size() - 1) // i.e. if we've reached the end of seq2 and all nodes match up
					return k;

			}

		}
	}

	return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
	
	// store all wanted node datas in a temporary Sequence
	//if result is seq1 or seq2, avoid possibly overwriting previous data before we can obtain
	Sequence temp;

	// first insert seq2 in reverse order into temp 
	for (int i = 0; i < seq2.size(); i++) {
		ItemType seq2_value;
		// stores node value into seq2_value
		seq2.get(i, seq2_value);

		// inserts nodes from seq2 in reverse order (FI;LO kind-of idea)
		temp.insert(0, seq2_value); }

	// now insert seq1 in normal order
	for (int i = 0; i < seq1.size(); i++) {
		ItemType seq1_value;
		// stores node value into seq1_value
		seq1.get(i, seq1_value);

		// inserts all nodes in reverse order (FI;LO kind-of idea)
		temp.insert(0, seq1_value);
	}


	// set result as temp
	result = temp;
}
