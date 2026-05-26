// Copyright 2022 NNTU-CS
#include "tree.h"

#include <memory>
#include <vector>

PMTree::PMTree(const std::vector<char>& symbols)
    : originalSymbols(symbols) {
    root = std::make_shared<Node>('\0');
    buildTree(root, symbols);
}

void PMTree::buildTree(std::shared_ptr<Node> node,
                       std::vector<char> remaining) {
    if (remaining.empty()) {
        return;
    }

    for (size_t i = 0; i < remaining.size(); i++) {
        char ch = remaining[i];
        auto child = std::make_shared<Node>(ch);
        node->children.push_back(child);

        std::vector<char> newRemaining;
        for (size_t j = 0; j < remaining.size(); j++) {
            if (j != i) {
                newRemaining.push_back(remaining[j]);
            }
        }

        buildTree(child, newRemaining);
    }
}

void PMTree::getAllPermutations(std::shared_ptr<Node> node,
                                std::vector<char>& current,
                                std::vector<std::vector<char>>& result) {
    if (node->children.empty()) {
        result.push_back(current);
        return;
    }

    for (auto& child : node->children) {
        current.push_back(child->value);
        getAllPermutations(child, current, result);
        current.pop_back();
    }
}

int PMTree::getSubtreeSize(std::shared_ptr<Node> node) const {
    if (node->children.empty()) {
        return 1;
    }

    int size = 0;
    for (auto& child : node->children) {
        size += getSubtreeSize(child);
    }
    return size;
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    tree.getAllPermutations(tree.root, current, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<std::vector<char>> allPerms = getAllPerms(tree);
    if (num >= 0 && num < static_cast<int>(allPerms.size())) {
        return allPerms[num];
    }
    return std::vector<char>();
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    auto node = tree.root;
    std::vector<char> remaining = tree.originalSymbols;

    while (node->children.size() > 0) {
        int cumulative = 0;
        for (auto& child : node->children) {
            int subtreeSize = tree.getSubtreeSize(child);
            if (num < cumulative + subtreeSize) {
                result.push_back(child->value);
                node = child;

                for (auto it = remaining.begin(); it != remaining.end();
                     ++it) {
                    if (*it == child->value) {
                        remaining.erase(it);
                        break;
                    }
                }
                break;
            }
            cumulative += subtreeSize;
        }
    }

    return result;
}
