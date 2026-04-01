//
//  tests.cpp
//  hw_3
//
//  Created by Ivan Batrakov on 02/04/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "catch2/catch_amalgamated.hpp"
#include "../sortings.hpp"
#include <vector>

TEST_CASE("sortings", "[default]"){
    
    std::vector<int> empty_vector = {};
    std::vector<int> single_element_vector = {1};
    std::vector<int> sorted_vector = {1, 2, 3, 4, 5};
    std::vector<int> duplicates_containing_vector = {3, 1, 2, 3, 1, 2};
    std::vector<int> pseudo_random_vector = {7, -2, 0, 15, 4, 1};
    
    
    SECTION("comb_sort"){
        comb_sort(empty_vector);
        comb_sort(single_element_vector);
        comb_sort(sorted_vector);
        comb_sort(duplicates_containing_vector);
        comb_sort(pseudo_random_vector);
        
        CHECK( std::is_sorted( empty_vector.begin(), empty_vector.end() ) );
        CHECK( std::is_sorted( single_element_vector.begin(), single_element_vector.end() ) );
        CHECK( std::is_sorted( sorted_vector.begin(), sorted_vector.end() ) );
        CHECK( std::is_sorted( single_element_vector.begin(), single_element_vector.end() ) );
        CHECK( std::is_sorted( duplicates_containing_vector.begin(), duplicates_containing_vector.end() ) );
        CHECK( std::is_sorted( pseudo_random_vector.begin(), pseudo_random_vector.end() ) );
    }
    
    
    SECTION("Shell_sort"){
        Shell_sort(empty_vector);
        Shell_sort(single_element_vector);
        Shell_sort(sorted_vector);
        Shell_sort(duplicates_containing_vector);
        Shell_sort(pseudo_random_vector);
        
        CHECK( std::is_sorted( empty_vector.begin(), empty_vector.end() ) );
        CHECK( std::is_sorted( single_element_vector.begin(), single_element_vector.end() ) );
        CHECK( std::is_sorted( sorted_vector.begin(), sorted_vector.end() ) );
        CHECK( std::is_sorted( single_element_vector.begin(), single_element_vector.end() ) );
        CHECK( std::is_sorted( duplicates_containing_vector.begin(), duplicates_containing_vector.end() ) );
        CHECK( std::is_sorted( pseudo_random_vector.begin(), pseudo_random_vector.end() ) );
    }
    
    
    SECTION("quick_sort"){
        quick_sort(empty_vector, 0, static_cast<int>(empty_vector.size() - 1));
        quick_sort(single_element_vector, 0, static_cast<int>(single_element_vector.size() - 1));
        quick_sort(sorted_vector, 0, static_cast<int>(sorted_vector.size() - 1));
        quick_sort(duplicates_containing_vector, 0, static_cast<int>(duplicates_containing_vector.size() - 1));
        quick_sort(pseudo_random_vector, 0, static_cast<int>(pseudo_random_vector.size() - 1));
        
        CHECK( std::is_sorted( empty_vector.begin(), empty_vector.end() ) );
        CHECK( std::is_sorted( single_element_vector.begin(), single_element_vector.end() ) );
        CHECK( std::is_sorted( sorted_vector.begin(), sorted_vector.end() ) );
        CHECK( std::is_sorted( single_element_vector.begin(), single_element_vector.end() ) );
        CHECK( std::is_sorted( duplicates_containing_vector.begin(), duplicates_containing_vector.end() ) );
        CHECK( std::is_sorted( pseudo_random_vector.begin(), pseudo_random_vector.end() ) );
    }
    
}

