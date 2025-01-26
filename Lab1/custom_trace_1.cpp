#include <iostream>
#include "hash_list.h"

int custom_trace_1()
{
    std::cout << "Running custom trace 1\n";
    
    hash_list list;
    list.insert(1, 1);
    list.insert(2, 2);
    list.insert(3, 3);
    list.insert(3, 33);
    if(list.get_size() != 3) {
        std::cout << "Get Size Failed\n";
        return 1;
    };
    // Call Copy Constructor
    hash_list list_copy(list);
    if(list_copy.get_size() != 3) {
        std::cout << "Get Size Failed\n";
        return 1;
    };
    // Call Assignment Operator
    hash_list third_list = list_copy;
    if(third_list.get_size() != 3) {
        std::cout << "Get Size Failed\n";
        return 1;
    };

    // Test Iterator
    third_list.reset_iter();
    third_list.increment_iter();
    std::optional<std::pair<const int*, float*>> pair = third_list.get_iter_value();
    if(pair.has_value() == false or *(pair.value().first) != 2) {
        std::cout << "Get Iterator Value Failed\n";
        return 1;
    };
    
    return EXIT_SUCCESS; 
}    
