/**
 * @brief p49样例程序
 * @author 张校
 * @date 2021-10-26
 */
#include <iostream>
#include <string>
#include <queue>
#include <stack>

class TheTree {
public:
    struct Node {
        char c;
        Node *l, *r;
        Node(const char c_, Node *l_ = NULL, Node *r_ = NULL) : c(c_), l(l_), r(r_) {}
        ~Node() {Clear();}
        void Clear() { if( l ) delete l; if( r ) delete r; }
        Node *InsertChild(const char c_, const bool left_child) { if( left_child ) return l = new Node(c_); return r = new Node(c_); }

        /**
         * @brief 按模式打印
         * @param int mode 打印模式
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
         * @brief 找到并打印所有等于指定字符的元素的前驱、后继节点和对应的tag
         *        这里没有建立线索树，但遍历方法和建立线索树的方法一直
         */
        void PrintNode(std::ostream &out, const char C, char &last_char, bool &last_ltag, bool &print_now, bool &find, std::string &buff)
        {
            if( l ) l->PrintNode(out, C, last_char, last_ltag,print_now, find, buff);
            if( print_now ) {
                out << "succ is " << c << (r == NULL) << std::endl;
                out << buff << std::endl;
                print_now = false;
            }
            if( c == C ) {
                find = true;
                print_now = true;
                
                if( last_char == '\0' ) {
                    buff = "prev is NULL";
                }
                else {
                    buff = "prev is " + std::string(1, last_char) + std::to_string(last_ltag);
                }
            }
            last_char = c;
            last_ltag = l == NULL;
            if( r ) r->PrintNode(out, C, last_char, last_ltag, print_now, find, buff);
        }
    };

    TheTree() { root = NULL; }
    ~TheTree() { Clear(); }
    void Clear() { if( root ) delete root; root = NULL; }

    /**
     * @brief 根据输入创建一颗二叉树
     */
    void BuildTree(std::string tree)
    {
        Clear();
        std::stack<Node*> S;
        bool left = false;
        Node *pointer;
        for( std::string::iterator i = tree.begin(); i != tree.end(); i ++ )
        {
            if( *i == '\r' )
                break;
            if( root == NULL ) {
                root = new Node(*i);
                pointer = root;
                left = true;
            }
            else if(*i == '#')
            {
                if( left == true )
                    left = false;
                else {
                    if( S.empty() )
                        break;
                    pointer = S.top();
                    S.pop();
                }
            }
            else
            {
                S.push(pointer);
                pointer = pointer->InsertChild(*i, left);
                if( left == false )
                    S.pop();
                left = true;
            }
        }
    }

    void PrintByMode(std::ostream &out, const int mode) { root->PrintByMode(out , mode); out << std::endl; }
    /**
     * @brief 打印前驱、后继节点和tag
     */
    void PrintNode(std::ostream &out, const char c) {
        char last = '\0';
        bool print_now = false, find = false, last_ltag = false;
        std::string buff;
        root->PrintNode(out, c, last, last_ltag, print_now, find, buff);
        if( print_now == true )
        {
            out << "succ is NULL" << std::endl;
            out << buff << std::endl;
        }
        if( find == false )
            out << "Not found" << std::endl;
    }
private:
    Node *root;
};

int main()
{
    std::string t;
    TheTree *tree = new TheTree();
    std::cin >> t;
    tree->BuildTree(t);
    tree->PrintByMode(std::cout, 2);
    char c;
    std::cin >> c;
    tree->PrintNode(std::cout, c);
    delete tree;
}