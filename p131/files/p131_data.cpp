/**
 * @file    p131_data.cpp
 * @name    p131随机测试数据生成程序
 * @author  张校
 * @date    2022-10-22
*/
#include <iostream>
#include <fstream>
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
     * @brief   二叉树指令构造
     */
    TreeNode *buildTreeDFS(const std::vector<int> &order, int &index) {
        if( index >= order.size() || order[index] == -1 ) {
            index ++;
            return nullptr;
        }
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
            n = rand() % 101 + 99900;
        }

        // 文件输出代码
        BinaryTree bt(n);
        std::vector<int> order;
        std::vector<int> ans;
        bt.traversalTreeByOrder(order, 0, true);
        bt.traversalTreeByOrder(ans, 2, false);

        for( int i = 0; i < order.size(); i ++ )
            fin << order[i] << ' ';
        fin << std::endl;

        for( int i = 0; i < ans.size(); i ++ )
            fout << ans[i] << ' ';
        fout << std::endl;

        fin.close();
        fout.close();
    }
}