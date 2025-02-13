#include "hash_map.h"

template<typename K, typename V>
size_t
hash_func(K key, int modulus) { 
	std::hash<K> _hash;
	return _hash(key) % modulus;
}

// Hashmap Constructor
template<typename K, typename V>
hash_map<K,V>::hash_map(size_t capacity, float upper_load_factor, float lower_load_factor) {
	_capacity = capacity;
	_upper_load_factor = upper_load_factor;
	_lower_load_factor = lower_load_factor;	
	_size = 0;
	_head = new hash_list<K,V>[capacity];

	for(size_t idx = 0; idx < capacity; idx++) { 
		_head[idx] = hash_list<K,V>(); 
	}
}

template<typename K, typename V>
hash_map<K,V>::~hash_map() {
	delete[] _head;
}

template<typename K, typename V>
hash_map<K,V>::hash_map(const hash_map& other) {
	_capacity = other._capacity;
	_upper_load_factor = other._upper_load_factor;
	_lower_load_factor = other._lower_load_factor;
	_size = other._size;
	_head = new hash_list[other._capacity];

	for(size_t idx = 0; idx < other._capacity; idx++) { 
		_head[idx] = hash_list(other._head[idx]);
	}
}

template<typename K, typename V>
hash_map<K,V>& 
hash_map<K,V>::operator=(const hash_map& other) {
	// Self Assignment
	if(this == &other) { return *this; }
	// Clean Up Old Memory
	for(size_t idx = 0; idx < _capacity; idx++) {
		_head[idx].~hash_list();
	}
	delete[] _head;

	_capacity = other._capacity;
	_upper_load_factor = other._upper_load_factor;
	_lower_load_factor = other._lower_load_factor;
	_size = other._size;
	_head = new hash_list[other._capacity];

	for(size_t idx = 0; idx < other._capacity; idx++) { 
		_head[idx] = hash_list(other._head[idx]);
	}	
	return *this;
}

template<typename K, typename V>
void 
hash_map<K,V>::insert(K key, V value) {
	// If The Hash List Does Not Yet Have This Key Increase Size
	if(!(_head[hash_func(key, _capacity)].get_value(key).has_value())) {
		_size++;
	}
	_head[hash_func(key, _capacity)].insert(key, value);	
}

template<typename K, typename V>
std::optional<V> 
hash_map<K,V>::get_value(K key) const {
	return _head[hash_func(key, _capacity)].get_value(key);
}

template<typename K, typename V>
bool 
hash_map<K,V>::remove(K key) {
	if(_head[hash_func(key, _capacity)].remove(key)) {
		_size--;
		return true;
	} else {
		return false;
	}
}

template<typename K, typename V>
size_t 
hash_map<K,V>::get_size() const { return _size; }

template<typename K, typename V>
size_t 
hash_map<K,V>::get_capacity() const { return _capacity; }

template<typename K, typename V>
void 
hash_map<K,V>::get_all_keys(K* keys) {
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

template<typename K, typename V>
void 
hash_map<K,V>::get_bucket_sizes(size_t* buckets) {
	for(size_t idx = 0; idx < _capacity; idx++) {
		buckets[idx] = _head[idx].get_size();
	}
}
