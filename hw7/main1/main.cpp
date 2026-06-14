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

class TreeNode{
public:
    
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    TreeNode(int val = 0, std::unique_ptr<TreeNode> left = nullptr, std::unique_ptr<TreeNode> right = nullptr)
        : val(val), left(std::move(left)), right(std::move(right)) {}
    
};

int turn_on_the_bright_lights(const std::unique_ptr<TreeNode>& node){
    if (!node) {
        return INT_MIN;
    }
    
    int left_max = turn_on_the_bright_lights(node->left);
    int right_max = turn_on_the_bright_lights(node->right);
    
    return std::max({node->val, left_max, right_max});
}


int main(int argc, const char * argv[]) {
    auto root = std::make_unique<TreeNode>(1,
            std::make_unique<TreeNode>(3,
    std::make_unique<TreeNode>(8,
std::make_unique<TreeNode>(14),
    std::make_unique<TreeNode>(15) ),
        std::make_unique<TreeNode>(10,
                            nullptr,
            std::make_unique<TreeNode>(3) ) ),
                                                        std::make_unique<TreeNode>(5,
                                                    std::make_unique<TreeNode>(2),
                                                            std::make_unique<TreeNode>(6,
                                                        std::make_unique<TreeNode>(0),
                                                                std::make_unique<TreeNode>(1) ) ) );
    
    
    std::cout << turn_on_the_bright_lights(root) << std::endl;
    return 0;
}
