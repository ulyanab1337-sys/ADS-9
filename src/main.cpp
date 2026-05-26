// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

void printPerm(const std::vector<char>& perm) {
    for (char c : perm) std::cout << c;
    std::cout << std::endl;
}

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);
    
    std::cout << "=== Пример ===" << std::endl;
    
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    for (size_t i = 0; i < perms.size(); i++) {
        std::cout << i+1 << ": ";
        printPerm(perms[i]);
    }
    
    std::cout << "\n=== Эксперимент ===" << std::endl;
    
    std::ofstream fout("result/plot_data.txt");
    
    for (int n = 3; n <= 7; n++) {
        std::vector<char> sym;
        for (int i = 0; i < n; i++) sym.push_back('0' + i);
        
        PMTree t(sym);
        
        auto start = std::chrono::high_resolution_clock::now();
        t.getAllPerms();
        auto end = std::chrono::high_resolution_clock::now();
        double timeAll = std::chrono::duration<double>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        t.getPerm10();
        end = std::chrono::high_resolution_clock::now();
        double time10 = std::chrono::duration<double>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        t.getPerm20();
        end = std::chrono::high_resolution_clock::now();
        double time20 = std::chrono::duration<double>(end - start).count();
        
        fout << n << " " << timeAll << " " << time10 << " " << time20 << std::endl;
        std::cout << "n=" << n << ": " << timeAll << "s, " << time10 << "s, " << time20 << "s" << std::endl;
    }
    
    fout.close();
    
    return 0;
}
