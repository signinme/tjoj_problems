/**
 * @file    p128.cpp
 * @name    p128样例程序
 * @date    2022-09-30
 */

#include <iostream>
#include <vector>

class Tree{
public:
    struct Node {
        int val, left, right;
    };

    Tree(int n, const std::vector<std::pair<int, int>> &list) {
        nodes.resize(list.size());
        for( int i = 0; i < list.size(); i ++ ) {
            nodes[i].val = i;
            nodes[i].left = list[i].first;
            nodes[i].right = list[i].second;
        }
    }

    int slove(int start) {
        int to_start, longest;
        dfs(0, start, to_start, longest);
        return longest;
    }
private:
    std::vector<Node> nodes;

    void dfs(int index, int start, int &to_start, int &longest) {
        if( index == -1 ) {
            to_start = -1;
            longest = 0;
        }
        int l_to_start = -1, l_longest = 0, r_to_start = -1, r_longest = 0;
        if( nodes[index].left != -1) {
            dfs(nodes[index].left, start, l_to_start, l_longest);
        }
        if( nodes[index].right != -1 ) {
            dfs(nodes[index].right, start, r_to_start, r_longest);
        }

        if( start == nodes[index].val ) {
            to_start = 1;
            longest = std::max(l_longest, r_longest);
        }
        else if( l_to_start != -1 ) {
            to_start = l_to_start + 1;
            longest = std::max(l_longest, l_to_start + r_longest);
        }
        else if( r_to_start != -1 ) {
            to_start = r_to_start + 1;
            longest = std::max(r_longest, r_to_start + l_longest);
        }
        else {
            to_start = -1;
            longest = std::max(l_longest, r_longest) + 1;
        }
    }
};

int main() {
    int n, start;
    std::cin >> n >> start;
    std::vector<std::pair<int, int>> list(n);
    for( int i = 0; i < n; i ++ ) {
        std::cin >> list[i].first >> list[i].second;
    }
    Tree tree(n, list);
    std::cout << tree.slove(start) << std::endl;
    return 0;
}