/**
 * @brief p49随机测试数据生成程序
 * @author 张校
 * @date 2021-10-26
 */
#include <iostream>
#include <fstream>
#include <string>

class TheTree {
public:
    
    struct Node {
        static const char *CharList;
        static const int MAX_NODES_NUM = 100000;
        static const int NODES_NUM_MOD = 52; // 一共52个英文字母作为名字
        static char ban_char; // 禁止符，用于生成Not find的结果
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
         * void PrintString(std::ostream &out)
         * @brief 打印作为输入的字符串
         */
        void PrintString(std::ostream &out)
        {
            out << c;
            if( l ) l->PrintString(out);
            else out << '#';
            if( r ) r->PrintString(out);
            else out << '#';
        }
        /**
         * @brief 找到并打印所有等于指定字符的元素的前驱、后继节点和对应的tag
         *        这里没有建立线索树，但遍历方法和建立线索树的方法一致
         *        为什么要使用buff?因为打印succ在prev之前，而只有遍历到后继节点才能打印，所以要存起来
         *        如果现打印prev就不需要
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
        /**
         * void GenarateNode(const int n)
         * @brief 生成树的节点
         * @param int n 当前子树所有孩子包含的节点个数（不包括自己）
         */
        void GenarateNode(const int n)
        {
            if( n > 0 )
            {
                if( n == 1 || rand() % 100 < 10 )
                {
                    if( rand() % 2 == 0 )
                    {
                        l = new Node(GenarateName());
                        l->GenarateNode(n - 1);
                    }
                    else
                    {
                        r = new Node(GenarateName());
                        r->GenarateNode(n - 1);
                    }
                }
                else
                {
                    int left_children = rand() % (n - 1);
                    l = new Node(GenarateName());
                    l->GenarateNode(left_children);
                    r = new Node(GenarateName());
                    r->GenarateNode(n - left_children - 2);
                }
            }
        }
        /**
         * @brief 生成一个不包含禁止符的名字
         */
        static char GenarateName() {
            char c;
            while( (c = CharList[rand() % NODES_NUM_MOD]) == ban_char ) ;
            return c;
        }
    };

    TheTree() { root = NULL; }
    ~TheTree() { Clear(); }
    void Clear() { if( root ) delete root; root = NULL; }

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

    /**
     * @brief 创建一颗二叉树
     */
    void GenarateTree(int n) {
        Clear();
        root = new Node(Node::GenarateName());
        root->GenarateNode(n - 1);
    }
    /**
     * @brief 将二叉树转化成输入用的先序字符串并输出
     */
    void PrintString(std::ostream &out) { root->PrintString(out); out << std::endl; }

    /**
     * 两个find函数
     * @brief 分别找到头和尾
     *        第5个测试点和以后，因为有大量重复字符，这个步骤也可以省去
     */
    char FindHead() {
        if( ! root ) return 0;
        Node *pointer = root;
        while( pointer->l ) pointer = pointer->l;
        return pointer->c;
    }
    char FindTail() {
        if( ! root ) return 0;
        Node *pointer = root;
        while( pointer->r ) pointer = pointer->r;
        return pointer->c;
    }
private:
    Node *root;   
};
const char * TheTree::Node::CharList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char TheTree::Node::ban_char = '\0';
int main()
{
    int test_num = 10; // 测试点个数
    for( int i = 1; i <= test_num; i ++ )
    {
        TheTree::Node::ban_char = TheTree::Node::GenarateName();
        std::string file_in = "input" + std::to_string(i) + ".txt";
        std::string file_out = "output" + std::to_string(i) + ".txt";
        std::ofstream fin(file_in), fout(file_out);

        int n, ope = rand() % 100;
        if( i <= test_num * 0.2 ) {
            n = 10;
        }
        else if( i <= test_num * 0.4 ) {
            n = 100;
        }
        else {
            n = TheTree::Node::MAX_NODES_NUM;
        }

        TheTree *tree = new TheTree();
        tree->GenarateTree(n);
        tree->PrintString(fin);
        tree->PrintByMode(fout, 2);

        char c;
        if( ope <= 15 )
            c = TheTree::Node::ban_char;
        else if( ope <= 50 )
            c = TheTree::Node::GenarateName();
        else if( ope <= 75 )
            c = tree->FindHead();
        else
            c = tree->FindTail();
        fin << c << std::endl;
        tree->PrintNode(fout, c);
        delete tree;
        fin.close();
        fout.close();
    }
    return 0;
}
