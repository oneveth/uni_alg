//
//  main.cpp
//  hw_7
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


class NyanEx1{
private:
    
    int max_sum;
    
    int post_order_trav(const std::unique_ptr<TreeNode>& node) {
        if (!node) {
            return 0;
        }

        int left_subnode = std::max(post_order_trav(node->left), 0);
        int right_subnode = std::max(post_order_trav(node->right), 0);

        int current_path_sum = node->val + left_subnode + right_subnode;

        max_sum = std::max(max_sum, current_path_sum);

        return node->val + std::max(left_subnode, right_subnode);
    }
    
public:
    int max_path(const std::unique_ptr<TreeNode>& root){
        max_sum = INT_MIN;
        post_order_trav(root);
        return max_sum;
    }
    
};


int main(int argc, const char * argv[]) {
    
    NyanEx1 ex1;
    
    // no.1;
    auto tree1 = std::make_unique<TreeNode>(1,
            std::make_unique<TreeNode>(1),      std::make_unique<TreeNode>(2) );
    
    //
    std::cout << ex1.max_path(tree1) << std::endl << std::endl;
    
    std::cout << "/////////////////" << std::endl << std::endl;
    
    // no.2;
    auto tree2 = std::make_unique<TreeNode>(-5,
            std::make_unique<TreeNode>(1),      std::make_unique<TreeNode>(7,
                            std::make_unique<TreeNode>(2),      std::make_unique<TreeNode>(3)) );
    //
    std::cout << ex1.max_path(tree2) << std::endl << std::endl;
    
    std::cout << "/////////////////" << std::endl << std::endl;
    
    // no.3;
    auto tree3 = std::make_unique<TreeNode>(-3,
            std::make_unique<TreeNode>(-1),     std::make_unique<TreeNode>(-2) );
    //
    std::cout << ex1.max_path(tree3) << std::endl << std::endl;
    
    return 0;
}
