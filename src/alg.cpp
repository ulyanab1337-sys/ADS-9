// Copyright 2022 NNTU-CS
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>

#include "tree.h"

namespace {

int64_t computeFactorial(int n) {
    int64_t output = 1;

    for (int i = 2; i <= n; ++i)
        output *= i;

    return output;
}

void traverseAll(NodeItem* ptr,
                 std::vector<char>* buffer,
                 std::vector<std::vector<char>>* storage) {
    if (ptr->symbol != '\0')
        buffer->push_back(ptr->symbol);

    if (ptr->branches.empty()) {
        if (!buffer->empty())
            storage->push_back(*buffer);
    } else {
        for (auto branch : ptr->branches)
            traverseAll(branch, buffer, storage);
    }

    if (ptr->symbol != '\0')
        buffer->pop_back();
}

}  // namespace

std::vector<std::vector<char>> getAllPerms(PermutationTree& tree) {
    std::vector<std::vector<char>> storage;
    std::vector<char> buffer;

    traverseAll(tree.fetchRoot(), &buffer, &storage);

    return storage;
}

std::vector<char> getPerm1(PermutationTree& tree, int position) {
    std::vector<std::vector<char>> allVariants = getAllPerms(tree);

    if (position < 1 || position > static_cast<int>(allVariants.size()))
        return {};

    return allVariants[position - 1];
}

std::vector<char> getPerm2(PermutationTree& tree, int position) {
    int64_t totalCombinations = computeFactorial(tree.fetchSize());

    if (position < 1 || position > totalCombinations)
        return {};

    std::vector<char> output;

    NodeItem* current = tree.fetchRoot();

    int remaining = tree.fetchSize();
    int64_t idx = position - 1;

    while (!current->branches.empty()) {
        int64_t groupSize = computeFactorial(remaining - 1);

        int chosen = static_cast<int>(idx / groupSize);

        idx %= groupSize;

        current = current->branches[chosen];

        output.push_back(current->symbol);

        --remaining;
    }

    return output;
}
