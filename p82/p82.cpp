/**
 * @brief p82样例程序
 * @author 张校
 * @date 2021-10-25
 * 可以参考37题样例程序
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

        void PrintByMode(std::ostream &out, const int mode)
        {
            if( mode == 1 ) out << c;
            if( l ) l->PrintByMode(out, mode);
            if( mode == 2 ) out << c;
            if( r ) r->PrintByMode(out, mode);
            if( mode == 3 ) out << c;
        }
    };

    TheTree() { root = NULL; }
    ~TheTree() { Clear(); }
    void Clear() { if( root ) delete root; root = NULL; }

    void BuildTree(std::istream &in)
    {
        Clear();
        int n;
        in >> n;
        std::stack<Node*> S;
        bool left = false;
        Node *pointer;
        // while( true )
        while( n )
        {
            char c;
            std::string ope;
            in >> ope;
            if( root == NULL ) {
                in >> c;
                root = new Node(c);
                pointer = root;
                left = true;
                n --;
            }
            else if( ope == "pop" )
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
                in >> c;
                S.push(pointer);
                pointer = pointer->InsertChild(c, left);
                if( left == false )
                    S.pop();
                left = true;
                n --;
            }
        }
    }

    void PrintByMode(std::ostream &out, const int mode) { root->PrintByMode(out , mode); out << std::endl; }
private:
    Node *root;
};

int main()
{
    TheTree *tree = new TheTree();
    tree->BuildTree(std::cin);
    tree->PrintByMode(std::cout, 3);
    delete tree;
}