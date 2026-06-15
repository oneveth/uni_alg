//
//  main.cpp
//  main5
//
//  Created by Ivan Batrakov on 14/06/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <vector>

class NO_ex5 {
private:
    int n, k;
    std::vector<std::vector<int>> graph_matrix;
    std::vector<int> colour;
    
    bool checker(int v, int c) {
        for (int i = 0; i < n; i++) {
            if (graph_matrix[v][i] == 1 && colour[i] == c) {
                return false;
            }
        }
        return true;
    }
    
    bool solver(int v) {
        if (v == n) return true;

        for (int c = 1; c <= k; c++) {
            if (checker(v, c)) {
                colour[v] = c;
                if (solver(v + 1)) {
                    return true;
                }
                colour[v] = 0;
            }
        }
        return false;
    }
    
public:
    NO_ex5(int n_vertexes, int k_colours)
    : n(n_vertexes), k(k_colours), graph_matrix(n, std::vector<int>(n)), colour(n, 0) {}
    
    void nine_k_in_one(){
        for (int i = 0; i < n; i++) {
            std::string row;
            std::cin >> row;
            for (int j = 0; j < n; j++) {
                graph_matrix[i][j] = row[j] - '0';
            }
        }

        if (solver(0)) {
            std::cout << "\nYES\n";
            for (int i = 0; i < n; i++) {
                std::cout << colour[i] << (i == n - 1 ? "" : " ");
            }
            std::cout << "\n";
        } else {
            std::cout << "\nNO\n";
        }
    }
    
};

int main(){

    int n, k;
    std::cout << ": "; std::cin >> n >> k;

    NO_ex5 spinner(n, k);
    spinner.nine_k_in_one();
    
    return 0;
}
