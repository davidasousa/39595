#include <iostream>
#include <cassert>

#include "hash_list.h"

// A unit test for a basic constructor
void t_constructor(void){
  hash_list list;

  if(list.get_size() != 0){
    std::cout << "t_constructor: invalid size" << std::endl;
  }
}

/*******
 Unit test to check if insertion into an empty list
 works. More unit tests would be recommended for
 testing insert. Could you think of what other tests one
 might consider?
**********/

void t_insert_empty(void){
  hash_list list;

  list.insert(1, 7.0);
  
  if(list.get_size() != 1){
    std::cout << "t_insert_empty: invalid size" << std::endl;
    return;
  }

  if(!list.get_value(1).has_value()){
    std::cout << "Expected value but says no value" << std::endl;
    return;
  }

  if(!(list.get_value(1).value() == 7.0)){
    std::cout << "Value does not match" << std::endl;
  }

}

void t_check_copy_constructor() {
  hash_list list;

  list.insert(1, 7.0);
  // Unit Test 1 For Copy Constructor
  hash_list list2(list); // Creating New List With The Copy Constructor
  if(!list2.get_value(1).has_value()){
    std::cout << "Expected value but says no value" << std::endl;
    return;
  }

  // Unit Test 2 For Copy Constructor
  if(!(list2.get_value(1).value() == 7.0)) {
	std::cout << "Copied Value Does Not Match" << std::endl;
  }
}

void t_check_assignment_operator() {
  hash_list list;

  list.insert(1, 7.0);
  // Unit Test 1 For Assignment Operator
  hash_list list3 = list; // Creating New List With Assignment Operator
  if(list3.get_size() != 1){
    std::cout << "t_insert_empty: invalid size" << std::endl;
    return;
  }
  
  // Unit Test 2 For Assignment Operator
  if(!list3.get_value(1).has_value()){
    std::cout << "Expected value but says no value" << std::endl;
    return;
  }

  // Unit Test 3 For Assignment Operator
  if(!(list3.get_value(1).value() == 7.0)) {
	std::cout << "Copied Value Does Not Match" << std::endl;
  }
}


int main(int argc, char *argv[])
{
  t_constructor();
  t_insert_empty(); 
  t_check_copy_constructor();
  t_check_assignment_operator();
}
