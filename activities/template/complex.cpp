#include "complex.h"

complexNumber::complexNumber(float _real, float _im) {
	real = _real;
	im = _im;
}

bool
complexNumber::operator>(const complexNumber& other) {
	float selfMag = (im * im) + (real * real);
	float otherMag = (other.im * other.im) + (other.real * other.real);
	if(selfMag > otherMag) { return true; } else { return false; }
}
