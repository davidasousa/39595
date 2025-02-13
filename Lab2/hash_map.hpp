#include "hash_map.h"

template<typename K>
size_t
_hash(K key) { 
	std::hash<K> _hash;
	return _hash(key);
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
	_head = new hash_list<K,V>[other._capacity];

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
	_head = new hash_list<K,V>[other._capacity];

	for(size_t idx = 0; idx < other._capacity; idx++) { 
		_head[idx] = hash_list(other._head[idx]);
	}	
	return *this;
}

// Resize The Capacity & Clean Up Old Memory
template<typename K, typename V>
void
hash_map<K,V>::resize_hash_map(size_t new_capacity) {
	// Get All Old Keys & Values
	K* keyArr = new K[_size];
	V* valArr = new V[_size];	
	get_all_keys(keyArr);
	get_all_values(valArr);

	// Clean Up All Old Memory
	for(size_t idx = 0; idx < _capacity; idx++) {
		_head[idx].~hash_list();
	}
	delete[] _head;
	
	// Set New Capacity
	_capacity = new_capacity;	

	// Create New Hash Lists
	_head = new hash_list<K,V>[_capacity];
	for(size_t idx = 0; idx < _capacity; idx++) { 
		_head[idx] = hash_list<K,V>(); 
	}	

	size_t fixed_size = _size; // Prevent Insert Changing
	_size = 0;

	// Add Keys & Values
	for(size_t idx = 0; idx < fixed_size; idx++) {
		insert(keyArr[idx], valArr[idx]);
	}	
	
	delete[] keyArr;
	delete[] valArr;
}

template<typename K, typename V>
void 
hash_map<K,V>::insert(K key, V value) {
	// If The Hash List Does Not Yet Have This Key Increase Size
	if(!(_head[_hash(key) % _capacity].get_value(key).has_value())) {
		_size++;
	}
	_head[_hash(key) % _capacity].insert(key, value);	

	// Checking For Load Balance Increase Rehashing
	if(_size > _upper_load_factor * _capacity) {
		if(_capacity < _capacities[2] && _capacity >= _capacities[1]) { 
			resize_hash_map(_capacities[2]); 
		}
		if(_capacity < _capacities[1] && _capacity >= _capacities[0]) { 
			resize_hash_map(_capacities[1]); 
		}
	}
}

template<typename K, typename V>
std::optional<V> 
hash_map<K,V>::get_value(K key) const {
	return _head[_hash(key) % _capacity].get_value(key);
}

template<typename K, typename V>
bool 
hash_map<K,V>::remove(K key) {
	if(_head[_hash(key) % _capacity].remove(key)) {
		_size--;

		// Load Balance Decrease Rehashing 
		if(_size < _lower_load_factor * _capacity) {
			if(_capacity > _capacities[0] && _capacity <= _capacities[1]) { 
				resize_hash_map(_capacities[0]); 
			}
			if(_capacity > _capacities[1] && _capacity <= _capacities[2]) { 
				resize_hash_map(_capacities[1]); 
			}
		}
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
hash_map<K,V>::get_all_values(V* values) {
	int arrpos = 0;
	for(size_t idx = 0; idx < _capacity; idx++) {
		hash_list current_list = _head[idx];
		current_list.reset_iter();

		while(!(current_list.iter_at_end())) {
			values[arrpos++] = *(current_list.get_iter_value().value().second);
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

template<typename K, typename V>
void 
hash_map<K,V>::get_all_sorted_keys(K *keys) {
	get_all_keys(keys);
	// Selection Sort
	for(size_t i = 0; i < _size; i++) {
		K minVal = keys[i];
		size_t minIdx = i;
		for(size_t j = i + 1; j < _size; j++) {
			if(minVal > keys[j]) {
				minVal = keys[j];
				minIdx = j;
			}
		}
		K temp = keys[i];
		keys[i] = minVal;
		keys[minIdx] = temp;
	}
}
