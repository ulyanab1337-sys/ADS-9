// Copyright 2022 NNTU-CS
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>

#include "tree.h"

namespace {

int64_t factCalc(int n) {
    int64_t res = 1;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

void recursiveWalk(PMNode* curNode,
                   std::vector<char>* tmp,
                   std::vector<std::vector<char>>* out) {
    if (curNode->value != '\0')
        tmp->push_back(curNode->value);

    if (curNode->children.empty()) {
        if (!tmp->empty())
            out->push_back(*tmp);
    } else {
        for (auto nxt : curNode->children)
            recursiveWalk(nxt, tmp, out);
    }

    if (curNode->value != '\0')
        tmp->pop_back();
}

}  // namespace

std::vector<std::vector<char>> getAllPerms(PMTree& tr) {
    std::vector<std::vector<char>> out;
    std::vector<char> tmp;
    recursiveWalk(tr.getRoot(), &tmp, &out);
    return out;
}

std::vector<char> getPerm1(PMTree& tr, int pos) {
    std::vector<std::vector<char>> all = getAllPerms(tr);
    if (pos < 1 || pos > static_cast<int>(all.size()))
        return {};
    return all[pos - 1];
}

std::vector<char> getPerm2(PMTree& tr, int pos) {
    int64_t total = factCalc(tr.getSize());
    if (pos < 1 || pos > total)
        return {};

    std::vector<char> res;
    PMNode* cur = tr.getRoot();
    int left = tr.getSize();
    int64_t idx = pos - 1;

    while (!cur->children.empty()) {
        int64_t sz = factCalc(left - 1);
        int sel = static_cast<int>(idx / sz);
        idx %= sz;
        cur = cur->children[sel];
        res.push_back(cur->value);
        --left;
    }

    return res;
}
