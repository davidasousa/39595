#include <iostream>
#include <string>

class person {
public:
	void printName();
	void setName();
	person(std::string _name);

private:
	std::string name;
};

person::person(std::string _name) {
	name = _name;
}

void person::printName() {
	std::cout << name << std::endl;
}

class student : public person {
public:
	student(std::string _name, int _gpa);
	void printNameGpa();

private:
	int Gpa;
};

student::student(std::string _name, int _gpa) : person(_name) {
	Gpa = _gpa;
}

void student::printNameGpa() {
	this -> printName();
	std:: cout << Gpa << std::endl;
}

int main(void) {
	person p1 {"David"};
	student s1 {"Dave", 4};
	p1.printName();
	s1.printName();
	s1.printNameGpa();

	return 0;
}
