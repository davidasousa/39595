#include <iostream>
#include "hash_list.h"

int custom_trace_3()
{
    std::cout << "Running custom trace 3\n";
    
    hash_list list1;
	list1.insert(0,10);
	list1.insert(1,20);
	list1.insert(2,30);
	list1.insert(3,40);
	if(*(list1.get_iter_value().value().second) != 10) { return 1; }
	list1.increment_iter();
	if(*(list1.get_iter_value().value().second) != 20) { return 1; }

    hash_list list2;
	list2.insert(0,15);
	list2.insert(2,25);

	// Assign List 1 To Be List 2
	list1 = list2;
	if(list1.get_size() != 2) { return 1; }
	list1.remove(0);
	if(*(list1.get_iter_value().value().second) != 25) { return 1; }
	list1.remove(2);
	if(list1.iter_at_end() == false) { return 1; }

	// List 1 Completely Empty
	if(list2.get_size() != 2) { return 1; }

	// Copy Constructor On List 2 -> 3
	hash_list list3(list2);
	if(list3.get_size() != 2) { return 1; }
	if(list3.remove(1) != false) { return 1; }

    return EXIT_SUCCESS; 
}    
