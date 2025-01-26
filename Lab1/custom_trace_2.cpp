#include <iostream>
#include "hash_list.h"

int custom_trace_2()
{
    std::cout << "Running custom trace 2\n";
    
    hash_list list;
	if(list.get_size() != 0) { return 1; }

    list.insert(1, 1);
	if(list.get_size() != 1) { return 1; }

	// Removing Non Existant List Item
	if(list.remove(2) != false) { return 1; }
    list.insert(2, 2);
	if(list.remove(2) != true) { return 1; }
	if(list.get_size() != 1) { return 1; }

	// Adding 2 Back
    list.insert(2, 4);
	if(list.get_size() != 2) { return 1; }
	if(list.get_value(2) != 4) { return 1; }

	// Removing The Head
	if(list.remove(1) != true) { return 1; }
	if(list.get_size() != 1) { return 1; }

	// Resetting Iterator
	list.reset_iter();
	std::optional<std::pair<const int*, float*>> pair = list.get_iter_value();
	if(*(pair.value().first) != 2) { return 1; }
	if(*(pair.value().second) != 4) { return 1; }

	// Incrementing Iterator To End
	list.increment_iter();
	if(list.iter_at_end() == false) { return 1; }
	if(list.get_iter_value().has_value() == true) { return 1; }

	// Incrementing Null Iterator
	list.increment_iter();
	if(list.iter_at_end() == false) { return 1; }

	// Resetting Iterator
	list.reset_iter();
	if(*(list.get_iter_value().value().first) != 2) { return 1; }
	if(*(list.get_iter_value().value().second) != 4) { return 1; }

	// Creating New Assigned List
	hash_list list_copy = list;
	list_copy.reset_iter();
	if(list_copy.iter_at_end() == true) { return 1; }
	if(list_copy.get_iter_value().has_value() == false) { return 1; }
	if(*(list_copy.get_iter_value().value().first) != 2) { return 1; }
	if(*(list_copy.get_iter_value().value().second) != 4) { return 1; }
	list_copy.increment_iter();
	if(list_copy.iter_at_end() == false) { return 1; }

    return EXIT_SUCCESS; 
}    
