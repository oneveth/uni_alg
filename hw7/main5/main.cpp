//
//  main.cpp
//  main5
//
//  Created by Ivan Batrakov on 14/06/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <iostream>
#include <memory>
#include <algorithm>
#include <climits>

class TreeNode{
public:
    
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    TreeNode(int val = 0, std::unique_ptr<TreeNode> left = nullptr, std::unique_ptr<TreeNode> right = nullptr)
        : val(val), left(std::move(left)), right(std::move(right)) {}
    
};


class VU_Ex4{
private:
    int dfs(const std::unique_ptr<TreeNode>& node, int current_sum){
        if (!node) {
            return 0;
        }
        
        current_sum = current_sum * 10 + node->val;

        if (!node->left && !node->right) {
            return current_sum;
        }

        return dfs(node->left, current_sum) + dfs(node->right, current_sum);
    }
    
public:
    int summer(const std::unique_ptr<TreeNode>& root){
        return dfs(root, 0);
    }
    
};


int main(int argc, const char * argv[]) {
    
    VU_Ex4 ex4;
    
    // no.1;
    auto tree1 = std::make_unique<TreeNode>(1,
            std::make_unique<TreeNode>(3),      std::make_unique<TreeNode>(5) );
    
    //
    std::cout << ex4.summer(tree1) << std::endl << std::endl;
    
    std::cout << "/////////////////" << std::endl << std::endl;
    
    // no.2;
    auto tree2 = std::make_unique<TreeNode>(1,
    std::make_unique<TreeNode>(2),      std::make_unique<TreeNode>(3,
                    std::make_unique<TreeNode>(2),      std::make_unique<TreeNode>(1)) );
    
    //
    std::cout << ex4.summer(tree2) << std::endl << std::endl;
    
    std::cout << "/////////////////" << std::endl << std::endl;
    
    return 0;
}
