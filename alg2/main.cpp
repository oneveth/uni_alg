//
//  main.cpp
//  alg2
//
//  Created by Ivan Batrakov on 15/02/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <queue>

template <typename Func, typename... Args> auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Начинаем отсчет времени
    auto result = func(std::forward<Args>(args)...);  // Выполняем переданную функцию с аргументами
    auto end_time = std::chrono::high_resolution_clock::now();  // Останавливаем отсчет времени

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);  // Вычисляем продолжительность в миллисекундах
    return std::make_pair(result, duration.count());  // Возвращаем результат и время выполнения
}
 

std::queue<int> queue_extended_with_zeroes_generator(std::queue<int> given_queue, int extension_size){
    
    for (int i=0; i!=extension_size; i++){
        given_queue.push(0);
    }
    
    return given_queue;
};

/*
int main(int argc, const char * argv[]) {
    
    unsigned int size[10] = {10, 50000, 100000, 250000, 500000, 1000000, 5000000, 10000000, 25000000, 50000000};
    
    int iter = 1;
    
    for (unsigned int i : size){
        std::queue<int> test;
        auto [result, execution_time] = measure_execution_time(queue_extended_with_zeroes_generator, test, i);
        std::cout << iter << ". Время выполнения: " << execution_time << " мс.\n\n";
        iter++;
    }
    
    return 0;
}
*/

