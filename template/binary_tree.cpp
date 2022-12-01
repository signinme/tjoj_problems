/**
 * @file    binary_tree.cpp
 * @name    二叉树模板程序
 * @author  张校
 * @date    2022-10-22
 * @brief   二叉树节点定义、二叉树指令构造、二叉树随机构造模板
*/
#include <iostream>
#include <fstream>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int data;           // 节点元素

    TreeNode *lchild;   // 左孩子节点指针

    TreeNode *rchild;   // 有孩子指针

    TreeNode(int x = 0, TreeNode *left = nullptr, TreeNode *right = nullptr) : data(x), lchild(left), rchild(right) {}
    ~TreeNode() { // 自动析构
        if( lchild != nullptr )
            delete lchild;
        if( rchild != nullptr )
            delete rchild;
    }
};

class BinaryTree {
private:
    TreeNode *root;
public:
    BinaryTree(const std::vector<int> &order) {
        int index = 0;
        root = buildTreeDFS(order, index);
    }

    BinaryTree(int num_nodes) {
        std::vector<int> name_list;
        int index = 0;

        shuffle(name_list, num_nodes);
        root = buildTreeRandomDFS(name_list, index, num_nodes);
    }

    ~BinaryTree() {
        if( root != nullptr )
            delete root;
    }

    TreeNode *getRoot() {
        return root;
    }

    void traversalTreeByOrder(std::vector<int> &list, int order, bool get_null) {
        list.resize(0);
        if( root == nullptr )
            return ;
        traversalTreeByOrderDFS(root, list, order, get_null);
    }
private:
    /**
     * @brief           二叉树指令构造
     * @param   order   构造指令列表
     * @param   index   当前节点序号
     * @return          子树根节点指针
     */
    TreeNode *buildTreeDFS(const std::vector<int> &order, int &index) {
        if( index >= order.size() || order[index] == -1 ) {
            index ++;
            return nullptr;
        }
        // 构造以当前节点为根节点的子树并返回
        return new TreeNode(order[index ++], buildTreeDFS(order, index), buildTreeDFS(order, index));
    }
    /**
     * @brief   二叉树随机构造
    */
    TreeNode *buildTreeRandomDFS(const std::vector<int> &name_list, int &index, int last_node) {
        if( last_node == 0 )
            return nullptr;
        int left_num_nodes = rand() % (last_node);
        return new TreeNode(
            name_list[index ++],
            buildTreeRandomDFS(name_list, index, left_num_nodes),
            buildTreeRandomDFS(name_list, index, last_node - left_num_nodes - 1)
        );
    }
    /**
     * @brief   根据遍历顺序order（0、1、2对应先序、中序、后序）获得二叉树遍历列表或构造指令列表（get_null=1时获取构造指令）
    */
    void traversalTreeByOrderDFS(TreeNode *root, std::vector<int> &list, int order, bool get_null) {
        if( root == nullptr ) {
            if( get_null ) {
                list.push_back(-1);
            }
            return ;
        }
        if( order == 0 ) list.push_back(root->data);
        traversalTreeByOrderDFS(root->lchild, list, order, get_null);
        if( order == 1 ) list.push_back(root->data);
        traversalTreeByOrderDFS(root->rchild, list, order, get_null);
        if( order == 2 ) list.push_back(root->data);
    }
    /**
     * @brief   随机洗牌
     */
    void shuffle(std::vector<int> &list, int size = 0) {
        if( size <= 0 )
            size = list.size();
        else
            list.resize(size);
        
        for( int i = 0; i < size; i ++ )
            list[i] = i;
        for( int i = size - 1; i > 0; i -- ) {
            int j   = rand() % (i + 1);
            int t   = list[i];
            list[i] = list[j];
            list[j] = t;
        }
    }
};

int main() {
    srand((unsigned)time(NULL));
    int x, num_nodes = 0, num_null = 0;
    std::vector<int> order;
    while( cin >> x ) {
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

    // 调用Solution

    return 0;
}