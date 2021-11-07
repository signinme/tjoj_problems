/**
 * p81随机测试数据生成程序
 * @author 张校
 * @date 2021-10-26
 * @brief 使用方法：直接编译运行
 */
#include <iostream>
#include <fstream>
#include <vector>

class Tree {
public:
    static const int MAX_NODES_NUM = 10000;
    static const int NODES_NUM_MOD = 52;
    static const char *CharList;
    struct Node {
        char name;
        int l, r;
        Node() { l = r = -1; }
        ~Node() {}
        friend std::ostream &operator <<(std::ostream &, const Node &);
    };

    Tree() { size = 0; list = NULL; }
    Tree(int n) { size = n; list = new Node[n]; }
    ~Tree() { Clear(); }
    void Clear() { if( list ) delete[] list; list = NULL; size = 0; }

    /**
     * @brief 构造一颗二叉树
     */
    int BuildTree(int n) {
        Clear();
        list = new Node[n];
        std::vector<int> L;
        Tree::Shuffle(L, n);
        root = L[size ++];
        return deepth = BuildTreeDFS(root, n - 1, L);
    }
    /**
     * @brief 随机交换节点/节点名字
     *        交换节点名字是异构，交换节点是同构
     */
    void RandomSwapNode() { RandomSwapNodeDFS(root); }
    void RandomSwapName() {
        if( ! RandomSwapNameDFS(root) ) { // 保证至少有一个节点孩子名字被交换
            int i = rand() % size;
            while( ! SwapName(i) ) i = rand() % size;
        }
    }
    /**
     * @brief 获取根节点索引、获取树节点个数、获取树深度
     */
    int Root() const { return root; }
    int Size() const { return size; }
    int Deepth() const { return deepth; }
    /**
     * @brief 随机洗牌
     */
    static void Shuffle(std::vector<int>& vec, int n)
    {
        for( int i = 0; i < n; i ++ )
            vec.push_back(i);
        for( int i = 0; i < n; i ++ )
        {
            //保证每次第i位的值不会涉及到第i位以前
            int index = i + (rand() % (n - i));
            std::swap(vec[index], vec[i]);
        }
    }

    friend std::ostream &operator <<(std::ostream &out, const Tree &t);
private:
    int size, root, deepth;
    Node *list;
    /**
     * @brief 用DFS随机生成树中节点
     * @param int i 当前节点指针
     * @param int n 当前节点的所有晚辈节点数量
     * @return 当前节点作为根节点的子树深度
     */
    int BuildTreeDFS(int i, int n, const std::vector<int> L) {
        list[i].name = CharList[rand() % NODES_NUM_MOD];
        int ld = 0, rd = 0;
        if( n == 0 ) { // 无孩子
            list[i].l = list[i].r = -1;
        }
        else if( n == 1 || rand() % 100 <= 10) { // 一个孩子
            if( rand() % 2 == 0 ) { // 只有左孩子
                list[i].l = L[size ++];
                ld = BuildTreeDFS(list[i].l, n - 1, L);
                list[i].r = -1;
            }
            else { // 只有右孩子
                list[i].r = L[size ++];
                ld = BuildTreeDFS(list[i].r, n - 1, L);
                list[i].l = -1;
            }
        }
        else { // 两个孩子
            int left_child = rand() % (n - 1);
            list[i].l = L[size ++];
            ld = BuildTreeDFS(list[i].l, left_child, L);
            list[i].r = L[size ++];
            rd = BuildTreeDFS(list[i].r, n - left_child - 2, L);
        }
        return std::max(ld, rd) + 1;
    }
    /**
     * @brief 随机交换当前节点的左右孩子
     */
    void RandomSwapNodeDFS(int i) {
        if( i == -1 )
            return ;
        if( rand() % 2 == 0 )
        {
            list[i].l = list[i].l + list[i].r;
            list[i].r = list[i].l - list[i].r;
            list[i].l = list[i].l - list[i].r;
        }
        RandomSwapNodeDFS(list[i].l);
        RandomSwapNodeDFS(list[i].r);
    }
    /**
     * @brief 随机交换当前节点左右孩子名字
     * @return 以当前节点为根的子树中是否有节点交换过孩子名字
     */
    bool RandomSwapNameDFS(int i) {
        if( list[i].l == -1 || list[i].r == -1 )
            return false;
        if( rand() % 2 == 0 ) {
            SwapName(i);
            RandomSwapNameDFS(list[i].l);
            RandomSwapNameDFS(list[i].r);
            return list[list[i].l].l != -1 || list[list[i].l].r != -1 || list[list[i].r].l != -1 || list[list[i].r].r != -1;
        }
        else
            return RandomSwapNameDFS(list[i].l) | RandomSwapNameDFS(list[i].r);
    }
    /**
     * @brief 交换当前节点左右孩子名字
     */
    bool SwapName(int i) {
        if( list[i].l == -1 || list[i].r == -1 )
            return false;
        char name            = list[list[i].r].name;
        list[list[i].r].name = list[list[i].l].name;
        list[list[i].l].name = name;
        return true;
    }
};
const char * Tree::CharList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::ostream &operator <<(std::ostream &out, const Tree::Node &node) {
    out << node.name << ' ';
    if( node.l == -1 )
        out << '-';
    else
        out << node.l;
    out << ' ';
    if( node.r == -1 )
        out << '-';
    else
        out << node.r;
    return out;
}

std::ostream &operator <<(std::ostream &out, const Tree &t) {
    for( int i = 0; i < t.Size(); i ++ )
        out << t.list[i] << std::endl;
    return out;
}

int main()
{
    srand((unsigned) time(NULL));
    int test_num = 10; // 测试点个数
    for( int i = 1; i <= test_num; i ++ )
    {
        std::string file_in = "input" + std::to_string(i) + ".txt";
        std::string file_out = "output" + std::to_string(i) + ".txt";
        std::ofstream fin(file_in), fout(file_out);
        int n1, n2; // 测试数据规模
        if( i <= test_num * 0.2 ) {
            n1 = 10;
            n2 = 10;
        }
        else if( i <= test_num * 0.4 ) {
            n1 = 100;
            n2 = 100;
        }
        else {
            n1 = Tree::MAX_NODES_NUM;
            n2 = Tree::MAX_NODES_NUM;
            if( i <= test_num * 0.5 ) {
                n1 += (rand() % 100) - 50;
                n2 += (rand() % 100) - 50;
            }
        }

        Tree *tree;
        tree = new Tree();
        tree->BuildTree(n1);
        fin << n1 << std::endl;
        fin << *tree;
        if( n1 == n2 )
        {
            if( i % 2 == 0 ) // Yes
            {
                fout << "Yes" << std::endl;
                fout << tree->Deepth() << std::endl;
                tree->RandomSwapNode();
                fin << n2 << std::endl;
                fin << *tree;
                fout << tree->Deepth() << std::endl;
            }
            else // No
            {
                fout << "No" << std::endl;
                fout << tree->Deepth() << std::endl;
                tree->RandomSwapName();
                fin << n2 << std::endl;
                fin << *tree << std::endl;
                fout << tree->Deepth() << std::endl;
            }
        }
        else // No
        {
            fout << "No" << std::endl;
            fout << tree->Deepth() << std::endl;
            tree->BuildTree(n2);
            fin << n2 << std::endl;
            fin << *tree;
            fout << tree->Deepth() << std::endl;
        }
        fin.close();
        fout.close();
        delete tree;
    }
    return 0;
}