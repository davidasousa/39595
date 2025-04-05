#include "poly.h"
#include <iostream>

// Basic Constructor
polynomial::polynomial() {
	poly_vec.push_back(std::pair(0, 0));
}

// Constructing Polynomial From Iterator Of Pairs
template <typename Iter>
polynomial::polynomial(Iter begin, Iter end) {
	poly_vec.clear();
	for(auto it = begin; it != end; it++) {
		poly_vec.push_back(*begin);
	}
}

// Creating Polynomial From Another
polynomial::polynomial(const polynomial &other) {
	poly_vec = other.poly_vec;
}

// Printing Function - Const At End Prevents Changing The Class
void polynomial::print() const {
	for(auto term : poly_vec) {
		std::cout << term.first << " ^";
		std::cout << term.second << " + ";
	}
	std::cout << std::endl;
}

// Polynomial Assignment Operator
polynomial& polynomial::operator=(const polynomial &other) {
	poly_vec = other.poly_vec;
	return *this;	
}

// Sum Two Polynomials
polynomial& polynomial::operator+(const polynomial &other) {
	size_t self_degree = find_degree_of();
	size_t other_degree = other.find_degree_of();
	int idx = 0;

	// Adding Shared Terms
	while(idx < std::min(self_degree, other_degree)) {
		poly_vec[idx].first += other.poly_vec[idx].first;	
	}

	// Adding Larger Polynomial Terms From The Other
	while(idx < other_degree) {
		poly_vec.push_back(other.poly_vec[idx]);	
	}

	return *this;	
}

// Returns The Degree Of The Polynomial
size_t polynomial::find_degree_of() const {
	size_t max_degree = 0;
	for(auto term : poly_vec) {
		max_degree = std::max(max_degree, term.second);
	}
	return max_degree;
}
