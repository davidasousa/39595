#include "poly.h"
#include <iostream>

// Assumptions For Polynomial Pair Vectors
// The Vector Will Be Ordered By Ascending Degrees
// EX: 3 + 1x^2 + 0x^2 + 3x^3 ... 

// Helper For Sorting Polynomials By Degree
std::vector<std::pair<power, coeff>>&
sort_degree(std::vector<std::pair<power, coeff>>& poly) {
	// Insertion Sort Based On Power -> Ascending
	for(int idx = 0; idx < poly.size(); idx++) {
		int swap_idx = idx;
		power min_degree = poly[idx].first;

		// Finding Smallest Power Between [Idx, Poly.Size]
		for(int jdx = idx + 1; jdx < poly.size(); jdx++) {
			if(poly[jdx].first < min_degree) { 
				swap_idx = jdx; 
				min_degree = poly[jdx].first;
			}	
		}

		std::pair<power, coeff> temp = poly[idx];
		poly[idx] = poly[swap_idx];
		poly[swap_idx] = temp;
	}
	return poly;
}

// Basic Constructor
polynomial::polynomial() {
	poly.push_back({0, 0});
}

// Constructing Polynomial From Iterator Of Pairs
// Polynomials Always In Ascending Order Form
template <typename Iter>
polynomial::polynomial(Iter begin, Iter end) {
	poly.clear();

	for(auto it = begin; it != end; it++) { 
		poly.push_back(*it); 
	}
	sort_degree(poly);
}

// Creating Polynomial From Another
polynomial::polynomial(const polynomial &other) {
	poly = other.poly;
}

// Printing Function - Const At End Prevents Changing The Class
void polynomial::print() const {
	for(auto it = poly.begin(); it != poly.end(); it++) {
		std::cout << it -> second;
		std::cout << "x^";
		std::cout << it -> first;
		if(it != poly.end() - 1) { std::cout << " + "; }
	}
	std::cout << std::endl;
}

// Polynomial Assignment Operator
polynomial& polynomial::operator=(const polynomial &other) {
	poly = other.poly;
	return *this;	
}

// Sum Two Polynomials
polynomial& polynomial::operator+(const polynomial &other) {
	size_t smaller_degree = std::min(find_degree_of(), other.find_degree_of());
	size_t larger_degree = std::max(find_degree_of(), other.find_degree_of());

	// Assigning The Larger Of The Two Polynomials
	std::vector<std::pair<power, coeff>> larger_poly = 
		find_degree_of() > other.find_degree_of() ? 
		this -> poly : 
		other.poly ;

	// Adding Shared Terms
	for(int idx = 0; idx <= smaller_degree; idx++) {
		poly[idx].second += other.poly[idx].second;	
	}

	// Adding Terms From Larger Polynomial
	for(int idx = find_degree_of(); idx < larger_degree; idx++) {
		poly.push_back(larger_poly[idx]);
	}

	return *this;	
}

// Multiply Two Polynomials
polynomial& polynomial::operator*(const polynomial &other) {
	size_t new_degree = find_degree_of() * other.find_degree_of();
	polynomial new_poly;

	// Can Be Optimized With Whole Row Addition
	for(auto it : poly) {
		for(auto jt : other.poly) {
			std::vector<std::pair<power, coeff>> new_term = {{ 
				it.first + jt.first, 
				it.second * jt.second 
			}};

			new_poly = new_poly + polynomial(new_term.begin(), new_term.end());
			new_poly.print();
		}
	}
	
	*this = new_poly;
	return *this;
}

// Returns The Degree Of The Polynomial
size_t 
polynomial::find_degree_of() const { return poly.size() - 1; }

// Returns Sorted Polynomial
std::vector<std::pair<power, coeff>> 
polynomial::canonical_form() const {
	std::vector<std::pair<power, coeff>> new_poly;
	for(auto it : poly) { new_poly.push_back(it); }
	return new_poly;
}
