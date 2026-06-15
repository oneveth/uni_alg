//
//  main.cpp
//  main1
//
//  Created by Ivan Batrakov on 14/06/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <memory>
#include <algorithm>
#include <climits>
#include <utility>
#include <vector>

std::pair<int,int> recursive(const std::vector<int>& arr, int l, int r){
    if (l == r) {
        return {arr[l], arr[l]};
    }
    
    if (r == l + 1) {
        if (arr[l] < arr[r]) {
            return {arr[l], arr[r]};
        }
        else {
            return {arr[r], arr[l]};
        }
    }

    int m = l + (r - l) / 2;

    auto [left_min, left_max] = recursive(arr, l, m);
    auto [right_min, right_max] = recursive(arr, m + 1, r);

    return {std::min(left_min, right_min), std::max(left_max, right_max)};
}

std::pair<int,int> min_max_whatever(const std::vector<int>& arr){
    return recursive(arr, 0, arr.size() - 1);
}

int main(){
    
    std::vector<int> arr = {5, 7, 2, 4, 9, 6};

    auto [min_val, max_val] = min_max_whatever(arr);

    std::cout << "The minimum array element is " << min_val << std::endl;
    std::cout << "The maximum array element is " << max_val << std::endl;
    
    return 0;
}
