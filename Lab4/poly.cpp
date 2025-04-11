#include "poly.h"
#include <iostream>

#define ZERO_CONST std::pair<power, coeff>{0, 0}

// Assumptions For Polynomial Pair Vectors
// The Vector Will Be Ordered By Ascending Degrees
// EX: 3 + 1x^2 + 0x^2 + 3x^3 ... 

// Helper For Sorting Polynomials By Degree
std::vector<std::pair<power, coeff>>&
sort_degree(std::vector<std::pair<power, coeff>>& poly) {
	// Insertion Sort Based On Power -> Ascending
	for(int idx = 0; idx < poly.size(); idx++) {
		int swap_idx = idx;
		power max_degree = poly[idx].first;

		// Finding Smallest Power Between [Idx, Poly.Size]
		for(int jdx = idx + 1; jdx < poly.size(); jdx++) {
			if(poly[jdx].first > max_degree) { 
				swap_idx = jdx; 
				max_degree = poly[jdx].first;
			}	
		}

		std::pair<power, coeff> temp = poly[idx];
		poly[idx] = poly[swap_idx];
		poly[swap_idx] = temp;
	}
	return poly;
}

// Helper For Merging Like Terms && Removing 0 Coeff Terms
std::vector<std::pair<power, coeff>>&
merge_poly(std::vector<std::pair<power, coeff>>& poly) {
	for(auto it = poly.begin(); it != poly.end() - 1;) { // Removing 0 Coeff Terms
		if(it -> second == 0) {
			poly.erase(it);
			continue;
		} else if (it -> first == (it + 1) -> first) { // Merging Like Terms
			it -> second += (it + 1) -> second;
			poly.erase(it + 1);
		}
		it++;
	}
	return poly;
}

// Basic Constructor
polynomial::polynomial() {
	poly.clear();
	poly.push_back({0, 0});
}

// Constructing Polynomial From Iterator Of Pairs
// Polynomials Always In Ascending Order Form
template <typename Iter>
polynomial::polynomial(Iter begin, Iter end) {
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

// Sum Two Polynomials // Was A Ref Being Returned
polynomial polynomial::operator+(const polynomial &other) const {
	// Assigning The Larger Of The Two Polynomials
	std::vector<std::pair<power, coeff>> sum;

	auto self_it = poly.begin();
	auto other_it = other.poly.begin();

	while(self_it != poly.end() && other_it != other.poly.end()) {
		/*
		std::cout << self_it -> first << self_it -> second;
		std::cout << " ";
		std::cout << other_it -> first << other_it -> second;
		std::cout << std::endl;
		*/

		// Adding Shared Terms
		if(self_it -> first == other_it -> first) {
			if(self_it -> second + other_it -> second != 0) {
				sum.push_back({self_it -> first, self_it -> second + other_it -> second});
			}
			self_it++; other_it++;
		} else if(self_it -> first < other_it -> first) {
			sum.push_back(*other_it);
			other_it++;
		} else if(self_it -> first > other_it -> first) {
			sum.push_back(*self_it);
			self_it++;
		}
	}

	while(self_it != poly.end()) { sum.push_back(*self_it++); }
	while(other_it != other.poly.end()) { sum.push_back(*other_it++); }
	
	return polynomial(sum.begin(), sum.end());
}

polynomial 
polynomial::operator+(const int& other) const {
	std::vector<std::pair<power, coeff>> new_poly = poly;
	new_poly.back().second = new_poly.back().second + other;
	return polynomial(new_poly.begin(), new_poly.end());
}

polynomial 
operator+(const int& other, const polynomial& poly) { return poly + other; }

// Multiply Two Polynomials
polynomial 
polynomial::operator*(const polynomial &other) const {
	polynomial product;

	for(auto it : poly) {
		for(auto jt : other.poly) {
			std::pair<power, coeff> term = { 
				it.first + jt.first, 
				it.second * jt.second
			};

			std::vector<std::pair<coeff, power>> term_vec = { term };
			if(term.second != 0) { 
				product = product + polynomial(term_vec.begin(), term_vec.end());
			}
		}
	}
	
	// Remove Lingering 0x^0
	if(product.poly.back() == ZERO_CONST) { product.poly.pop_back(); }
	// Return Empty Polynomial As 0x^0
	if(product.poly.size() == 0) { return polynomial{}; } 
	else { return product; }
}

polynomial 
polynomial::operator*(const int& other) const {
	std::vector<std::pair<power, coeff>> new_poly;
	for(auto it : poly) { new_poly.push_back({it.first, it.second * other}); }
	return polynomial(new_poly.begin(), new_poly.end());
}

polynomial 
operator*(const int& other, const polynomial& poly) { return poly * other; }

// Polynomial Modulus
polynomial 
polynomial::operator%(const polynomial &other) const {
	polynomial remainder(*this);
	
	while(remainder.find_degree_of() >= find_degree_of()) {
		// Finding Leading Terms
		std::pair<power, coeff> lead_dividend = remainder.poly.front();
		std::pair<power, coeff> lead_divisor = other.poly.front();

		// Divide Leading Terms
		std::vector<std::pair<power, coeff>> quotient = {{
			lead_dividend.first - lead_divisor.first,
			lead_dividend.second / lead_divisor.second
		}};
		polynomial quotient_poly(quotient.begin(), quotient.end());

		// Multiply By Divisor - Quotient * Divisor
		polynomial quotient_divisor = quotient_poly * other;

		// Subtract Divident By Quotient 
		remainder = remainder + (-1 * quotient_divisor);
	}

	// Repeat Steps One More Time
	// Finding Leading Terms
	std::pair<power, coeff> lead_dividend = remainder.poly.front();
	std::pair<power, coeff> lead_divisor = other.poly.front();

	// Divide Leading Terms
	std::vector<std::pair<power, coeff>> quotient = {{
		lead_dividend.first - lead_divisor.first,
		lead_dividend.second / lead_divisor.second
	}};
	polynomial quotient_poly(quotient.begin(), quotient.end());

	// Multiply By Divisor - Quotient * Divisor
	polynomial quotient_divisor = quotient_poly * other;
	// Subtract Divident By Quotient 
	(-1 * quotient_divisor).print();
	remainder = remainder + (-1 * quotient_divisor);

	return remainder;
}

// Returns The Degree Of The Polynomial
size_t 
polynomial::find_degree_of() const { return poly.size() - 1; }

// Returns Sorted Polynomial
std::vector<std::pair<power, coeff>> 
polynomial::canonical_form() const {
	std::vector<std::pair<power, coeff>> new_poly = poly;
	return merge_poly(sort_degree(new_poly));
}
