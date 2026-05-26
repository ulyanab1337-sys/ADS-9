// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct NodeItem {
    char symbol;
    std::vector<NodeItem*> branches;

    explicit NodeItem(char ch = '\0') : symbol(ch) {}
};

class PermutationTree {
 public:
    explicit PermutationTree(const std::vector<char>& elements) {
        totalCount = static_cast<int>(elements.size());
        origin = new NodeItem();
        constructTree(origin, elements);
    }

    ~PermutationTree() {
        eraseTree(origin);
    }

    NodeItem* fetchRoot() const {
        return origin;
    }

    int fetchSize() const {
        return totalCount;
    }

 private:
    NodeItem* origin;
    int totalCount;

    void constructTree(NodeItem* current,
                       const std::vector<char>& remaining) {
        if (remaining.empty())
            return;

        for (size_t idx = 0; idx < remaining.size(); ++idx) {
            NodeItem* newNode = new NodeItem(remaining[idx]);

            current->branches.push_back(newNode);

            std::vector<char> rest = remaining;

            rest.erase(rest.begin() + idx);

            constructTree(newNode, rest);
        }
    }

    void eraseTree(NodeItem* current) {
        if (current == nullptr)
            return;

        for (auto child : current->branches)
            eraseTree(child);

        delete current;
    }
};

std::vector<std::vector<char>> getAllPerms(PermutationTree& tree);

std::vector<char> getPerm1(PermutationTree& tree, int index);

std::vector<char> getPerm2(PermutationTree& tree, int index);

#endif  // INCLUDE_TREE_H_
