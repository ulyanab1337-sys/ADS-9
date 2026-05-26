// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
public:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        Node(char val) : value(val) {}
    };

    explicit PMTree(const std::vector<char>& symbols);
    ~PMTree() = default;

    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPermByNumber(int number) const;
    std::vector<std::vector<char>> getPerm10() const;
    std::vector<std::vector<char>> getPerm20() const;

private:
    std::shared_ptr<Node> root;
    std::vector<char> originalSymbols;

    void buildTree(std::shared_ptr<Node> node, std::vector<char> remaining);
    void collectPerms(std::shared_ptr<Node> node, std::vector<char>& current,
                      std::vector<std::vector<char>>& result) const;
    bool findPermByNumber(std::shared_ptr<Node> node, std::vector<char>& current,
                          int& counter, int targetNumber,
                          std::vector<char>& result) const;
    static int factorial(int n);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<std::vector<char>> getPerm10(const PMTree& tree);
std::vector<std::vector<char>> getPerm20(const PMTree& tree);

#endif
