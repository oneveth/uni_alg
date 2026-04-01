//
//  input_output.cpp
//  hw_3
//
//  Created by Ivan Batrakov on 02/04/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <stdio.h>
#include "sortings.hpp"
#include <iostream>
#include <random>
#include <algorithm>

int main(){
    std::vector<int> values {  5, 10, 15, 20 };
    
    for (int i : values){
        std::cout << "// " << i << std::endl;
        std::vector<int> temp_vector(i);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(1, 100);
        
        std::generate(temp_vector.begin(), temp_vector.end(), [&]() {
            return distrib(gen);
        });
        
        
        std::vector<int> comb_sort_vector = temp_vector;
        std::vector<int> Shell_vector = temp_vector;
        std::vector<int> quick_sort_vector = temp_vector;
        
        comb_sort(comb_sort_vector);
        Shell_sort(Shell_vector);
        quick_sort(quick_sort_vector, 0, static_cast<int>(quick_sort_vector.size() - 1));
        
        std::cout << "comb_sort: " << std::endl;
        for (int i : comb_sort_vector){
            std::cout << i << ", ";
        }
        std::cout << std::endl;
        
        std::cout << "Shell_sort: " << std::endl;
        for (int i : Shell_vector){
            std::cout << i << ", ";
        }
        std::cout << std::endl;
        
        std::cout << "quick_sort: " << std::endl;
        for (int i : quick_sort_vector){
            std::cout << i << ", ";
        }
        std::cout << std::endl;
        
        std::cout << std::endl << "_______________________________________"<< std::endl;
    }
    
    return 0;
}
