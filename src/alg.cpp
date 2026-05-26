// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "tree.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

int PMTree::factorial(int n) {
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

PMTree::PMTree(const std::vector<char>& symbols) : originalSymbols(symbols) {
    if (symbols.empty()) {
        root = nullptr;
        return;
    }
    std::vector<char> sorted = symbols;
    std::sort(sorted.begin(), sorted.end());
    root = std::make_shared<Node>('\0');
    for (char c : sorted) {
        auto child = std::make_shared<Node>(c);
        root->children.push_back(child);
        std::vector<char> remaining;
        for (char rem : sorted) if (rem != c) remaining.push_back(rem);
        buildTree(child, remaining);
    }
}

void PMTree::buildTree(std::shared_ptr<Node> node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    std::sort(remaining.begin(), remaining.end());
    for (size_t i = 0; i < remaining.size(); ++i) {
        auto child = std::make_shared<Node>(remaining[i]);
        node->children.push_back(child);
        std::vector<char> newRemaining;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (j != i) newRemaining.push_back(remaining[j]);
        }
        buildTree(child, newRemaining);
    }
}

void PMTree::collectPerms(std::shared_ptr<Node> node, std::vector<char>& current,
                          std::vector<std::vector<char>>& result) const {
    if (!node) return;
    if (node->value != '\0') current.push_back(node->value);
    if (node->children.empty() && node->value != '\0') {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            collectPerms(child, current, result);
        }
    }
    if (node->value != '\0') current.pop_back();
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    if (root) {
        for (const auto& child : root->children) {
            collectPerms(child, current, result);
        }
    }
    return result;
}

bool PMTree::findPermByNumber(std::shared_ptr<Node> node, std::vector<char>& current,
                              int& counter, int targetNumber,
                              std::vector<char>& result) const {
    if (!node) return false;
    if (node->value != '\0') current.push_back(node->value);
    if (node->children.empty() && node->value != '\0') {
        counter++;
        if (counter == targetNumber) {
            result = current;
            current.pop_back();
            return true;
        }
    } else {
        for (const auto& child : node->children) {
            if (findPermByNumber(child, current, counter, targetNumber, result)) {
                if (node->value != '\0') current.pop_back();
                return true;
            }
        }
    }
    if (node->value != '\0') current.pop_back();
    return false;
}

std::vector<char> PMTree::getPermByNumber(int number) const {
    if (number <= 0) return {};
    int total = factorial(static_cast<int>(originalSymbols.size()));
    if (number > total) return {};
    std::vector<char> current;
    std::vector<char> result;
    int counter = 0;
    for (const auto& child : root->children) {
        if (findPermByNumber(child, current, counter, number, result)) {
            return result;
        }
    }
    return {};
}

std::vector<std::vector<char>> PMTree::getPerm10() const {
    auto all = getAllPerms();
    std::vector<std::vector<char>> result;
    for (size_t i = 0; i < std::min<size_t>(10, all.size()); ++i) {
        result.push_back(all[i]);
    }
    return result;
}

std::vector<std::vector<char>> PMTree::getPerm20() const {
    auto all = getAllPerms();
    std::vector<std::vector<char>> result;
    for (size_t i = 0; i < std::min<size_t>(20, all.size()); ++i) {
        result.push_back(all[i]);
    }
    return result;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<std::vector<char>> getPerm10(const PMTree& tree) {
    return tree.getPerm10();
}

std::vector<std::vector<char>> getPerm20(const PMTree& tree) {
    return tree.getPerm20();
}
