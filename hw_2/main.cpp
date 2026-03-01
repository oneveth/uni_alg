//
//  main.cpp
//  hw_2
//
//  Created by Ivan Batrakov on 01/03/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <cmath>

double simpson_rule(double (*f)(double), double a, double b, int n) {
    if (n % 2 == 1) n++; // Делаем n четным
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i += 2)
        sum += 4 * f(a + i * h);

    for (int i = 2; i < n-1; i += 2)
        sum += 2 * f(a + i * h);

    return (h / 3) * sum;
}

double func(double x){
    return (4*(x*x)-8);
}

int main(int argc, const char * argv[]) {
    int counter = 1;
    double nS[] = {0, 2, 6, 8, 10, 50, 100, 1000};
    
    for (double i : nS){
        double result = simpson_rule(func, 2, 7, i);
        std::cout << counter << ". Результат (n=" << i << "): \t" << result << ";" <<std::endl;
        counter++;
    }
    
}
