// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<char> symbols = {'A', 'B', 'C'};
    PMTree tree(symbols);
    
    std::vector<std::vector<char>> allPerms = getAllPerms(tree);
    
    std::cout << "All permutations:" << std::endl;
    for (size_t i = 0; i < allPerms.size(); i++) {
        std::cout << i << ": ";
        for (char c : allPerms[i]) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nPermutation at index 1: ";
    std::vector<char> perm1 = getPerm1(tree, 1);
    for (char c : perm1) {
        std::cout << c;
    }
    std::cout << std::endl;
    
    std::cout << "Permutation at index 2 (optimized): ";
    std::vector<char> perm2 = getPerm2(tree, 2);
    for (char c : perm2) {
        std::cout << c;
    }
    std::cout << std::endl;
    
    return 0;
}
