/**
 * @file    header.cpp
 * @name    header文件
 * @author  张校
 * @date    2022-10-22
 * @brief   程序拼接header文件
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int data;

    TreeNode *lchild;

    TreeNode *rchild;

    TreeNode(int x = 0, TreeNode *left = nullptr, TreeNode *right = nullptr) : data(x), lchild(left), rchild(right) {}
    ~TreeNode() { // 自动析构
        if( lchild != nullptr )
            delete lchild;
        if( rchild != nullptr )
            delete rchild;
    }
};
