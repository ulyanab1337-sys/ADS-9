// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct PMNode {
    char value;
    std::vector<PMNode*> children;

    explicit PMNode(char val = '\0') : value(val) {}
};

class PMTree {
 public:
    explicit PMTree(const std::vector<char>& data) {
        size_ = static_cast<int>(data.size());
        root_ = new PMNode();
        buildTree(root_, data);
    }

    ~PMTree() {
        deleteTree(root_);
    }

    PMNode* getRoot() const {
        return root_;
    }

    int getSize() const {
        return size_;
    }

 private:
    PMNode* root_;
    int size_;

    void buildTree(PMNode* node,
                   const std::vector<char>& available) {
        if (available.empty())
            return;

        for (size_t i = 0; i < available.size(); ++i) {
            PMNode* child = new PMNode(available[i]);

            node->children.push_back(child);

            std::vector<char> next = available;

            next.erase(next.begin() + i);

            buildTree(child, next);
        }
    }

    void deleteTree(PMNode* node) {
        if (node == nullptr)
            return;

        for (auto child : node->children)
            deleteTree(child);

        delete node;
    }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);

std::vector<char> getPerm1(PMTree& tree, int num);

std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
