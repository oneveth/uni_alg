//
//  main.cpp
//  main4
//
//  Created by Ivan Batrakov on 14/06/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

int swans_greed(int x, int k, std::vector<int> arr){
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    
    int output = 0;
    
    for (int i = 0; i < k; ++i) {
        if (x == 0) break;
        
        int banknote = arr[i];
        if (banknote <= x) {
            int count = x / banknote;
            output += count;
            x %= banknote;
        }
    }
    
    if (x == 0) {
        return output;
    }
    else {
        std::cout << "не вышло: "; return -1;
    }
    
}


int main(){
    std::cout << "1. " << swans_greed(130, 4, {10, 3, 40, 1}) << std::endl;
    std::cout << "2. " << swans_greed(100, 2, {7, 5}) << std::endl;
    std::cout << "3. " << swans_greed(1, 1, {1}) << std::endl;
    return 0;
}
