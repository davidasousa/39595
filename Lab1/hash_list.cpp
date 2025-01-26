#include "hash_list.h"

hash_list::hash_list() {
	size = 0;
	head = NULL;
	iter_ptr = head;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void 
hash_list::insert(int key, float value) {
	// List Does Not Exist
	if(head == NULL) { 
		head = new node{key, value, NULL}; 
		size++;
		return;
	}

	// Finding The Node
	node* curr = head;
	node* prev = NULL;
	while(curr != NULL) {
		// Found Key Replace Value
		if(curr -> key == key) {
			curr -> value = value;
			return;
		}
		prev = curr;
		curr = curr -> next;
	}

	// Key Not Found
	prev -> next = new node{key, value, NULL};
	size++;
	return;
}

std::optional<float> 
hash_list::get_value(int key) const {
	std::optional<float> node_value;
	node* curr = head;

	// Iterate Through Nodes Till Either Reach End Or Find Value
	while(curr != NULL && curr -> key != key) { 
		curr = curr -> next; 
	}
	// If Node Was Found
	if(curr != NULL) { 
		node_value = curr -> value; 
	}
	return node_value; 
}

bool 
hash_list::remove(int key) { 
	node* curr = head;
	node* prev = NULL;
	
	while(curr != NULL && curr -> key != key) {
		prev = curr;
		curr = curr -> next;
	}

	if(curr == NULL) { // Key Not Found
		return false;
	}

	if(prev == NULL) { // First Node In List
		head = curr -> next;
	} else { // [1:n] Node
		prev -> next = curr -> next;	
	}

	size--;
	delete curr;
	return true; 
}

size_t 
hash_list::get_size() const { return size; }

hash_list::~hash_list() {
	while(head != NULL) {
		remove(head -> key);
	}
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

// Copy Constructor
hash_list::hash_list(const hash_list &other) {	 
    // Default Initializations
	size = 0;
	head = NULL;
	iter_ptr = head;
    // Copying The List
    node* curr = other.head;
    // Object Itself Is Stack Allocated But All Nodes Are Dynamic
    while(curr != NULL) { 
        this -> insert(curr -> key, curr -> value);
        curr = curr -> next;
    }
}

// Assignment Operator -> LHS Points To RHS With A Shallow Copy
hash_list &hash_list::operator=(const hash_list &other) { 
	// Deleting Original List
	node* curr = this -> head;
	while(curr != NULL) {
		node* next = curr -> next;
		this -> remove(curr -> key);
		curr = next;
	}

	// Resetting State
	this -> head = NULL;	
	this -> iter_ptr = other.iter_ptr;
	this -> size = 0;

	// Tranferring Other List -> This
	curr = other.head;
	while(curr != NULL) {
		this -> insert(curr -> key, curr -> value);	
		curr = curr -> next;
	}

	return *this; 
}

void hash_list::reset_iter() {
    if(this -> head == NULL) {
        this -> iter_ptr = NULL;
    } else {
        this -> iter_ptr = this -> head;
    }
}


void hash_list::increment_iter() {
    if(this -> iter_ptr == NULL) { return; }

    if(this -> iter_ptr -> next == NULL) {
        this -> iter_ptr = NULL;
    } else {
        this -> iter_ptr = this -> iter_ptr -> next;
    }
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { 
	if(this -> iter_ptr == NULL) {
		return std::nullopt;
	}

	std::pair<const int*, float*> pair(
		&(this -> iter_ptr -> key), // Key Address
		&(this -> iter_ptr -> value) // Value Address
	);
    return pair; 
}


bool hash_list::iter_at_end() { 
    if(this -> iter_ptr == NULL) { return true; }
    return false; 
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
