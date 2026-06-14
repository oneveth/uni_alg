//
//  main.cpp
//  main4
//
//  Created by Ivan Batrakov on 14/06/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <vector>

long long ex2(int n){
    
    if (n > 20) {
        std::cout << n << " больше 20: ";
        return -1;
    }
    
    std::vector<long long> arr(n + 1, 0);
    
    arr[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            arr[i] += arr[j - 1] * arr[j - i];
        }
    }

    return arr[n];
}


int main(){
    std::cout << ex2(2) << std::endl;
    
    std::cout << ex2(3) << std::endl;
    
    std::cout << ex2(4) << std::endl;
    
    std::cout << ex2(20) << std::endl;
    
    std::cout << ex2(21) << std::endl;
    
    return 0;
}
