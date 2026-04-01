//
//  sortings.hpp
//  hw_3
//
//  Created by Ivan Batrakov on 02/04/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#ifndef sortings_hpp
#define sortings_hpp

#include <stdio.h>
#include <vector>

void comb_sort(std::vector<int>&);

void Shell_sort(std::vector<int>&);

int partition(std::vector<int>&, int, int);

void quick_sort(std::vector<int>&, int, int);

#endif /* sortings_hpp */
