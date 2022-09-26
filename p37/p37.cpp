/**
 * @brief p37样例程序
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
        
        void PrintString(std::ostream &out)
        {
            out << c;
            if( l ) l->PrintString(out);
            if( r ) r->PrintString(out);
        }
        void ShowByLayer(std::ostream &out, int layer)
        {
            if( r ) r->ShowByLayer(out, layer + 1);
            for( int i = 0; i < layer; i ++ )
                out << "     ";
            out << c << std::endl;
            if( l ) l->ShowByLayer(out, layer + 1);
        }

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
    void PrintByLayer(std::ostream &out)
    {
        std::queue<Node *> Q;
        Q.push(root);
        while( ! Q.empty() )
        {
            Node *pointer = Q.front();
            if( pointer != NULL )
            {
                out << pointer->c;
               
                Q.push(pointer->l);
                Q.push(pointer->r);
            }
            Q.pop();
        }
        out << std::endl;
    }
    void ShowByLayer(std::ostream &out) { root->ShowByLayer(out, 0); }
private:
    Node *root;
};

int main()
{
    std::string t;
    TheTree *tree = new TheTree();
    std::cin >> t;
    tree->BuildTree(t);
    tree->PrintByMode(std::cout, 1);
    tree->PrintByMode(std::cout, 2);
    tree->PrintByMode(std::cout, 3);
    tree->PrintByLayer(std::cout);
    tree->ShowByLayer(std::cout);
    delete tree;
}