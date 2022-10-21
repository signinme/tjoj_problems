/**
 * @file    p128_data.cpp
 * @name    p128随机测试数据生成程序
 * @date    2022-09-30
 */

#include <iostream>
#include <fstream>
#include <vector>

class Tree{
public:
    struct Node {
        int val, left, right;
    };

    Tree(int n) {
        nodes.resize(n);
        int index = 0;
        buildTreeDFS(index, n);
    }

    int slove(int start) {
        int to_start, longest;
        dfs(0, start, to_start, longest);
        return longest;
    }
    
    void displayTree(std::ostream &out) {
        for( int i = 0; i < nodes.size(); i ++ ) {
            out << nodes[i].left << ' ' << nodes[i].right << std::endl;
        }
    }
private:
    std::vector<Node> nodes;

    void buildTreeDFS(int &index, int n) {
        int now = index;
        nodes[now].val = now;
        if( n == 1 ) {
            nodes[now].left = -1;
            nodes[now].right = -1;
            return ;
        }
        int left_children;
        if( n > 10 ) { // 为了生成深度较深的二叉树
            switch(rand() % 3) {
            case 0:
                left_children = rand() % (n - 1);
            case 1:
                left_children = rand() % 10;
            case 2:
                left_children = rand() % 10 + n - 10;
            }
        }
        else {
            left_children = rand() % (n - 1);
        }
        if( left_children > 0 ) {
            nodes[now].left = ++ index;
            buildTreeDFS(index, left_children);
        }
        else {
            nodes[now].left = -1;
        }
        if( n - left_children - 1 > 0 ) {
            nodes[now].right = ++ index;
            buildTreeDFS(index, n - left_children - 1);
        }
        else {
            nodes[now].right = -1;
        }
    }

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

int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n;
        if( index <= test_num * 0.2 ) {
            n = rand() % 6 + 5;
        }
        else if( index <= test_num * 0.4 ) {
            n = rand() % 101 + 900;
        }
        else {
            n = rand() % 1001 + 99000;
        }
        Tree tree(n);
        int start = rand() % n;
        fin << n << ' ' << start << std::endl;
        tree.displayTree(fin);
        fout << tree.slove(start) << std::endl;

        fin.close();
        fout.close();
    }
}