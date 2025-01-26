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

	list1 = list2;
	if(list1.get_size() != 2) { return 1; }
	list1.remove(0);
	list1.remove(2);
	if(list1.iter_at_end() == false) { return 1; }
    
    return EXIT_SUCCESS; 
}    
