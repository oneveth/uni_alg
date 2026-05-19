//
//  main.cpp
//  hw_4
//
//  Created by Ivan Batrakov on 19/05/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>

std::vector<int> quicksort(const std::vector<int>& arr, int num_threads) {
    
    size_t N = arr.size();  // Фиксируем N — длину массива...
                            //
    if (N <= 1) {           // ...если массив большой, то происходит Параллельная обработка подмассивов.
        return arr;
    }

    int pivot = arr[arr.size() / 2];
    std::vector<int> left, right, equals;   // equals создаётся для хранения элементов, равных pivot...
                                            //
    for (int i = 0; i < arr.size(); ++i) {  //
        if (arr[i] < pivot) {               //
            left.push_back(arr[i]);         //
        } else if (arr[i] > pivot) {        //
            right.push_back(arr[i]);        //
        }                                   //
        else{                               //
            equals.push_back(arr[i]);       //
        }                                   //
    }                                       //
                                            //
    if (left.empty() || right.empty()) {    //
        return equals;                      // ...именно equals возвращается, если не вышло
                                            // првести разделение на left и right из-за
                                            // равнозначности элементов (на всякий случай).
    }
    
    std::vector<int> sorted_left;                                   // массивы для разультатов сортировки.
    std::vector<int> sorted_right;                                  //
                                                                    //
    int threads_for_left = num_threads / 2;                         // распределение потоков между левой и правой частью.
    int threads_for_right = num_threads - threads_for_left - 1;
    
    
    std::thread left_thread;                                                    // в новых потоках (если их создание возможно)
                                                                                // запустится левая часть...
    if (threads_for_left > 0) {                                                 //
        left_thread = std::thread(                                              //
                        [&](){sorted_left = quicksort(left, threads_for_left);} //
                                  );                                            //
    } else {                                                                    //
        sorted_left = quicksort(left, 0);                                       //
    }                                                                           //
                                                                                //
    sorted_right = quicksort(right, threads_for_right);                         // ...правая сортируется в текущем.

    if (left_thread.joinable()) {
        left_thread.join();
    }
    
    
    std::vector<int> result;
    result.reserve(sorted_left.size() + equals.size() + sorted_right.size());

    result.insert(result.end(), sorted_left.begin(), sorted_left.end());
    result.insert(result.end(), equals.begin(), equals.end());
    result.insert(result.end(), sorted_right.begin(), sorted_right.end());

   return result;
}

int main() {
    std::vector<int> values {   100,    1000,   10000,
                                20000,  30000,  40000,
                                50000                   };
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (auto& i : values){
        std::vector<int> temp_vector(i);
        
        std::uniform_int_distribution<int> distrib(0, i);
        
        std::generate(temp_vector.begin(), temp_vector.end(), [&]() {
            return distrib(gen);
        });
        
        auto start = std::chrono::steady_clock::now();
        std::vector<int> qs4 = quicksort(temp_vector, 4);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << i << std::endl;
        std::cout << "4 потока: " << duration.count() << " мс" << std::endl;
        
        auto start1 = std::chrono::steady_clock::now();
        std::vector<int> qs2 = quicksort(temp_vector, 2);
        auto end1 = std::chrono::steady_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
        std::cout << "2 потока: " << duration1.count() << " мс" << std::endl;
        std::cout << "_______________________________________"<< std::endl;
    }
    return 0;
}
