#include "hash_map.h"

int 
abs(int val) { return val < 0 ? -val : val; }

int 
hash_func(int key, int modulus) { return abs(key) % modulus; }

// Hashmap Constructor
hash_map::hash_map(size_t capacity) {
	_size = 0;
	_capacity = capacity;
	_head = new hash_list[capacity];
	// Setting Empty Hash Lists
	for(size_t idx = 0; idx < capacity; idx++) { 
		_head[idx] = hash_list(); 
	}
}

hash_map::~hash_map() {
	delete[] _head;
}

hash_map::hash_map(const hash_map& other) {
	_size = other._size;
	_capacity = other._capacity;
	_head = new hash_list[other._capacity];
	for(size_t idx = 0; idx < other._capacity; idx++) { 
		_head[idx] = hash_list(other._head[idx]);
	}
}

hash_map& 
hash_map::operator=(const hash_map& other) {
	// Self Assignment Check
	if(this == &other) { return *this; }

	for(size_t idx = 0; idx < _capacity; idx++) {
		_head[idx].~hash_list();
	}
	delete[] _head;

	_size = other._size;
	_capacity = other._capacity;
	_head = new hash_list[other._capacity];
	for(size_t idx = 0; idx < other._capacity; idx++) { 
		_head[idx] = hash_list(other._head[idx]);
	}	
	return *this;
}

void 
hash_map::insert(int key, float value) {
	// If The Hash List Does Not Yet Have This Key Increase Size
	if(!(_head[hash_func(key, _capacity)].get_value(key).has_value())) {
		_size++;
	}
	_head[hash_func(key, _capacity)].insert(key, value);	
}

std::optional<float> 
hash_map::get_value(int key) const {
	return _head[hash_func(key, _capacity)].get_value(key);
}

bool 
hash_map::remove(int key) {
	if(_head[hash_func(key, _capacity)].remove(key)) {
		_size--;
		return true;
	} else {
		return false;
	}
}

size_t 
hash_map::get_size() const { return _size; }

size_t 
hash_map::get_capacity() const { return _capacity; }

void 
hash_map::get_all_keys(int* keys) {
	int arrpos = 0;
	for(size_t idx = 0; idx < _capacity; idx++) {
		hash_list current_list = _head[idx];
		current_list.reset_iter();

		while(!(current_list.iter_at_end())) {
			keys[arrpos++] = *(current_list.get_iter_value().value().first);
			current_list.increment_iter();
		}
	}
}

void 
hash_map::get_bucket_sizes(size_t* buckets) {
	for(size_t idx = 0; idx < _capacity; idx++) {
		buckets[idx] = _head[idx].get_size();
	}
}
