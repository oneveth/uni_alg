//
//  sortings.cpp
//  hw_3
//
//  Created by Ivan Batrakov on 02/04/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include "sortings.hpp"

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
