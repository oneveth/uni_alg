//
//  main.cpp
//  hw_3
//
//  Created by Ivan Batrakov on 01/04/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

void comb_sort(std::vector<int> &vector){
    size_t n = vector.size();
    
    unsigned long int step = n - 1;
    
    while (step > 1){
        step /= 1.3;
        
        int i = 0;
        
        while ( (i + step) < n ){
            if ( vector[i] > vector[i+step] ){
                std::swap(vector[i], vector[i+step]);
            }
            i += 1;
        }
    }
}


void Shell_sort(std::vector<int> &vector){
    
    size_t n = vector.size();
    unsigned long int step = n/2;
    
    while (step > 0){
        
        for(unsigned long int i = step; i < n; i++){
            
            int temp = vector[i];
            unsigned long int j = i;
            
            while ( (j >= step) && (vector[j-step] > temp) ){
                vector[j] = vector[j-step];
                j -= step;
            }
            vector[j] = temp;
            
        }
        step /= 2;
        
    }
}


int partition(std::vector<int> &vector, int low, int high){
    int pivot = vector[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++){
        if(vector[j] < pivot){
            i++;
            std::swap(vector[i], vector[j]);
        }
    }
    std::swap(vector[i+1], vector[high]);
    
    return i+1;
}


void quick_sort(std::vector<int> &vector, int low, int high){
    if(low < high){
        int pi = partition(vector, low, high);
        
        quick_sort(vector, low, pi - 1);
        quick_sort(vector, pi + 1, high);
    }
}


int main(int argc, const char * argv[]) {
    
    std::vector<int> values {   100000, 200000, 300000,
                                400000, 500000, 600000,
                                700000, 800000, 900000,
                                1000000 };
    
    for (int i : values){
        std::cout << "// " << i << std::endl;
        std::vector<int> temp_vector(i);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(0, i);
        
        std::generate(temp_vector.begin(), temp_vector.end(), [&]() {
            return distrib(gen);
        });
        
        
        std::vector<int> comb_sort_vector = temp_vector;
        std::vector<int> Shell_vector = temp_vector;
        std::vector<int> quick_sort_vector = temp_vector;
        
        
        auto start1 = std::chrono::steady_clock::now();
        comb_sort(comb_sort_vector);
        auto end1 = std::chrono::steady_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
        std::cout << "comb_sort: " << duration1.count() << " мс" << std::endl;
        
        
        auto start2 = std::chrono::steady_clock::now();
        Shell_sort(Shell_vector);
        auto end2 = std::chrono::steady_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
        std::cout << "Shell_sort: " << duration2.count() << " мс" << std::endl;
        
        
        auto start3 = std::chrono::steady_clock::now();
        quick_sort(quick_sort_vector, 0, static_cast<int>(quick_sort_vector.size() - 1));
        auto end3 = std::chrono::steady_clock::now();
        auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
        std::cout << "quick_sort: " << duration3.count() << " мс" << std::endl;
        
        std::cout << "_______________________________________"<< std::endl;
    }
    
    return 0;
}
