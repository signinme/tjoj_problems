/**
 * @file    p131.cpp
 * @name    p131样例程序
 * @author  张校
 * @date    2022-10-22
*/
#include <iostream>
#include <vector>

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

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution {
public:
    std::vector<int> postorderTraversal(TreeNode* root) {
        //这里填写你的代码
        std::vector<int> ans;
        postorderTraversalDFS(root, ans);
        return ans;
    }
private:
    void postorderTraversalDFS(TreeNode* root, std::vector<int> &list) {
        if( root == nullptr )
            return ;
        if( root->lchild != nullptr )
            postorderTraversalDFS(root->lchild, list);
        if( root->rchild != nullptr )
            postorderTraversalDFS(root->rchild, list);
        list.push_back(root->data);
    }
};
/********************************/
/*     以下是你需要提交的代码     */
/********************************/

class BinaryTree {
private:
    TreeNode *root;
public:
    BinaryTree(const std::vector<int> &order) {
        int index = 0;
        root = buildTreeDFS(order, index);
    }
    ~BinaryTree() {
        if( root != nullptr )
            delete root;
    }
    TreeNode *getRoot() {
        return root;
    }
private:
    TreeNode *buildTreeDFS(const std::vector<int> &order, int &index) {
        if( index >= order.size() || order[index] == -1 ) {
            index ++;
            return nullptr;
        }
        return new TreeNode(order[index ++], buildTreeDFS(order, index), buildTreeDFS(order, index));
    }
};

int main() {
    int x, num_nodes = 0, num_null = 0;
    std::vector<int> order;
    while( std::cin >> x ) {
        order.push_back(x);
        if( x == -1 ) {
            num_null ++;
            if( num_null == num_nodes + 1) {
                break;
            }
        }
        else {
            num_nodes ++;
        }
    }
    BinaryTree bt(order); // 构造二叉树
    Solution solution;
    std::vector<int> ans(solution.postorderTraversal(bt.getRoot())); // 调用Solution::postorderTraversal
    for( int i = 0; i < ans.size(); i ++ ) { // 打印结果
        std::cout << ans[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}