#include "hash_list.h"

template<typename K, typename V>
hash_list<K,V>::hash_list() {
	size = 0;
	head = NULL;
	iter_ptr = head;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

template<typename K, typename V>
void 
hash_list<K,V>::insert(K key, V value) {
	// List Does Not Exist
	if(head == NULL) { 
		head = new node<K,V>{key, value, NULL}; 
		iter_ptr = head; // Ensure Iterator
		size++;
		return;
	}

	// Finding The Node
	node<K,V>* curr = head;
	node<K,V>* prev = NULL;
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
	prev -> next = new node<K,V>{key, value, NULL};
	size++;
	return;
}

template<typename K, typename V>
std::optional<V> 
hash_list<K,V>::get_value(K key) const {
	node<K,V>* curr = head;
	// Iterate Through Nodes Till Either Reach End Or Find Value
	while(curr != NULL && curr -> key != key) { 
		curr = curr -> next; 
	}
	// If Node Was Found
	if(curr != NULL) { 
		return curr -> value; 
	}
	return {};
}

template<typename K, typename V>
bool 
hash_list<K,V>::remove(K key) { 
	node<K,V>* curr = head;
	node<K,V>* prev = NULL;
	
	while(curr != NULL && curr -> key != key) {
		prev = curr;
		curr = curr -> next;
	}

	if(curr == NULL) { // Key Not Found
		return false;
	}

	if(prev == NULL) { // First Node In List
		head = curr -> next;
		iter_ptr = head; // Ensure Iterator Becomes Null
	} else { // [1:n] Node
		prev -> next = curr -> next;	
	}

	size--;
	delete curr;
	return true; 
}

template<typename K, typename V>
size_t 
hash_list<K,V>::get_size() const { return size; }

template<typename K, typename V>
hash_list<K,V>::~hash_list() {
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
template<typename K, typename V>
hash_list<K,V>::hash_list(const hash_list &other) {	 
    // Default Initializations
	size = 0;
	head = NULL;
	iter_ptr = head;
    // Copying The List
    node<K,V>* curr = other.head;
    // Object Itself Is Stack Allocated But All Nodes Are Dynamic
    while(curr != NULL) { 
        this -> insert(curr -> key, curr -> value);
        curr = curr -> next;
    }
}

// Assignment Operator -> LHS Points To RHS With A Shallow Copy
template<typename K, typename V>
hash_list<K,V>&
hash_list<K,V>::operator=(const hash_list &other) { 
	if(this == &other) { return *this; }
	// Deleting Original List
	node<K,V>* curr = head;
	while(curr != NULL) {
		node<K,V>* next = curr -> next;
		remove(curr -> key);
		curr = next;
	}
	// Resetting State
	head = NULL;	
	size = 0;
	// Tranferring Other List -> This
	curr = other.head;
	while(curr != NULL) {
		insert(curr -> key, curr -> value);	
		curr = curr -> next;
	}
	// Setting Iterator
	if(other.iter_ptr == NULL) { 
		iter_ptr = NULL; 
	} else {
		curr = head;
		while(curr -> value != other.iter_ptr -> value) { curr = curr -> next; }
		iter_ptr = curr;
	}

	return *this; 
}

template<typename K, typename V>
void 
hash_list<K,V>::reset_iter() { iter_ptr = head; }

template<typename K, typename V>
void 
hash_list<K,V>::increment_iter() {
    if(iter_ptr == NULL) { return; }
    iter_ptr = iter_ptr -> next;
}

template<typename K, typename V>
std::optional<std::pair<const K*, V*>> 
hash_list<K,V>::get_iter_value() { 
	if(iter_ptr == NULL) { return std::nullopt; }

	std::pair<const K*, V*> pair(
		&(iter_ptr -> key), // Key Address
		&(iter_ptr -> value) // Value Address
	);
  return pair; 
}


template<typename K, typename V>
bool 
hash_list<K,V>::iter_at_end() { 
    if(iter_ptr == NULL) { return true; }
    return false; 
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
