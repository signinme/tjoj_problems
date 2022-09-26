/**
 * p82 随机测试数据生成程序
 * @author 张校
 * @date 2021-10-25
 * @brief 使用方法：直接编译运行
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

class TheTree {
public:
    struct Node {
        static const char *CharList;
        static const int MAX_NODES_NUM;
        static const int NODES_NUM_MOD;
        char c;
        Node *l, *r;
        Node(const char c_, Node *l_ = NULL, Node *r_ = NULL) : c(c_), l(l_), r(r_) {}
        ~Node() {Clear();}
        void Clear() { if( l ) delete l; if( r ) delete r; }
        Node *InsertChild(const char c_, const bool left_child) { if( left_child ) return l = new Node(c_); return r = new Node(c_); }
        
        /**
         * void PrintString(std::ostream &out)
         * @brief 打印作为输入的字符串
         */
        void PrintString(std::ostream &out)
        {
            out << "push " << c << std::endl;
            if( l ) l->PrintString(out);
            // else out << "pop" << std::endl;
            out << "pop" << std::endl;
            if( r ) r->PrintString(out);
            // else out << "pop" << std::endl;
        }

        /**
         * void PrintByMode(std::ostream &out, const int mode)
         * @brief 按模式打印
         * @param int mode 模式（1：前序；2：中序；3：后续）
         */
        void PrintByMode(std::ostream &out, const int mode)
        {
            if( mode == 1 ) out << c;
            if( l ) l->PrintByMode(out, mode);
            if( mode == 2 ) out << c;
            if( r ) r->PrintByMode(out, mode);
            if( mode == 3 ) out << c;
        }

        /**
         * void GenarateNode(const int n)
         * @brief 生成树的节点
         * @param int n 当前子树所有孩子包含的节点个数（不包括自己）
         */
        void GenarateNode(const int n, int &size)
        {
            if( n > 0 )
            {
                if( n == 1 || rand() % 100 < 10 )
                {
                    if( rand() % 2 == 0 )
                    {
                        // l = new Node(Node::CharList[rand() % NODES_NUM_MOD]);
                        l = new Node(Node::CharList[size ++]);
                        l->GenarateNode(n - 1, size);
                    }
                    else
                    {
                        // r = new Node(CharList[rand() % NODES_NUM_MOD]);
                        r = new Node(CharList[size ++]);
                        r->GenarateNode(n - 1, size);
                    }
                }
                else
                {
                    int left_children = rand() % (n - 1);
                    // l = new Node(CharList[rand() % NODES_NUM_MOD]);
                    l = new Node(CharList[size ++]);
                    l->GenarateNode(left_children, size);
                    // r = new Node(CharList[rand() % NODES_NUM_MOD]);
                    r = new Node(CharList[size ++]);
                    r->GenarateNode(n - left_children - 2, size);
                }
            }
        }
    };

    TheTree() { root = NULL; size = 0; }
    ~TheTree() { Clear(); }
    void Clear() { if( root ) delete root; root = NULL; size = 0; }

    /**
     * @brief 按模式打印
     */
    void PrintByMode(std::ostream &out, const int mode) { root->PrintByMode(out , mode); out << std::endl; }
    void GenarateTree(int n)
    {
        Clear();
        // root = new Node(Node::CharList[rand() % Node::NODES_NUM_MOD]);
        root = new Node(Node::CharList[size ++]);
        root->GenarateNode(n - 1, size);
    }
    
    void PrintString(std::ostream &out) { root->PrintString(out); out << std::endl; }
private:
    Node *root;
    int size;
};

const char * TheTree::Node::CharList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`1234567890-=~!@#$%^&*()_+[]{}\\|;:\'\",.<>/?";
const int TheTree::Node::MAX_NODES_NUM = 84;
const int TheTree::Node::NODES_NUM_MOD = 84;
int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10;
    for( int i = 1; i <= test_num; i ++ )
    {
        std::string inputfile = "input" + std::to_string(i) + ".txt";
        std::string outputfile = "output" + std::to_string(i) + ".txt";
        std::ofstream fin(inputfile.c_str());
        std::ofstream fout(outputfile.c_str());

        int nodes;
        if( i <= test_num * 0.2 )
            nodes = 10;
        else if( i <= test_num * 0.4 )
            nodes = 20;
        else
            nodes = TheTree::Node::MAX_NODES_NUM;
        
        TheTree *tree = new TheTree();
        fin << nodes << std::endl;
        tree->GenarateTree(nodes);
        tree->PrintString(fin);
        tree->PrintByMode(fout, 3);
        delete tree;
    }
    
}