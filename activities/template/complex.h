class complexNumber {
public:
	float real;
	float im;

	complexNumber(float _real, float _im); // Constructor
	bool operator>(const complexNumber& other);
};
