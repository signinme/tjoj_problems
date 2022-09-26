/**
 * @brief p81样例程序
 * @author 张校
 * @date 2021-10-26
 */
#include <iostream>
#include <string>
#include <cstring>

class Tree {
public:
    struct Node {
        char name;
        int l, r, p;
        Node() { p = l = r = -1; }
        ~Node() {}

        friend std::istream &operator >>(std::istream &, Node &);
        friend std::ostream &operator <<(std::ostream &, const Node &);
    };

    Tree() { size = 0; list = NULL; }
    Tree(int n) { size = n; list = new Node[n]; }
    ~Tree() { Clear(); }
    void Clear() { if( list ) delete[] list; list = NULL; size = 0; }

    /**
     * @brief 输入一颗树
     */
    int InputTree(std::istream &in) {
        for( int i = 0; i < size; i ++ ) {
            in >> list[i];
            if( list[i].r >= 0 )
                list[list[i].r].p = i;
            if( list[i].l >= 0 )
                list[list[i].l].p = i;
        }
        return root = FindRoot();
    }

    /**
     * @brief 获取根节点索引、获取树节点个数、获取树深度
     */
    int Root() const { return root; }
    int Size() const { return size; }
    int Deepth() const { return DeepthDFS(root); }
    /**
     * bool CompareTree(const Tree &t1, const Tree &t2)
     * @brief 比较两颗树是否同构
     */
    static bool CompareTree(const Tree &t1, const Tree &t2) {
        if( t1.Size() != t2.Size() )
            return false;
        return CompareTreeDFS(t1, t2, t1.Root(), t2.Root());
    }

    friend std::ostream &operator <<(std::ostream &out, const Tree &t);
private:
    int size, root;
    Node *list;
    /**
     * @brief 找根节点
     *        通过从任意节点(这里用索引0节点)不断寻找其父母节点实现
     * @return 根节点坐标（-1表示错误）
     *         注意，本函数不一定能确定树是否正确
     */
    int FindRoot()
    {
        bool *bo = new bool[size];
        memset(bo, 0, sizeof(bool) * size);
        int i = 0;
        while( list[i].p != -1 && ! bo[list[i].p] ) {
            i = list[i].p;
            bo[i] = true;
        }
        delete[] bo;
        return list[i].p == -1 ? i : -1;
    }
    /**
     * @brief 用DFS确定树深度
     */
    int DeepthDFS(int i) const {
        if( i == -1 )
            return 0;
        int dl = DeepthDFS(list[i].l);
        int dr = DeepthDFS(list[i].r);
        return std::max(dl, dr) + 1;
    }
    /**
     * @brief 用DFS比较两棵树是否同构
     */
    static bool CompareTreeDFS(const Tree &t1, const Tree &t2, int i1, int i2) {
        if( i1 == -1 || i2 == -1 )
            return i1 == i2;
        if( t1.list[i1].name != t2.list[i2].name )
            return false;
        return ((CompareTreeDFS(t1, t2, t1.list[i1].l, t2.list[i2].l) && CompareTreeDFS(t1, t2, t1.list[i1].r, t2.list[i2].r)) ||
        (CompareTreeDFS(t1, t2, t1.list[i1].l, t2.list[i2].r) && CompareTreeDFS(t1, t2, t1.list[i1].r, t2.list[i2].l)));
    }
};
/**
 * @brief 将字符串转化为数字
 */
int StringToInteger(std::string s)
{
    int n = 0;
    for( std::string::iterator i = s.begin(); i != s.end(); i ++ ) {
        if( *i == '-' ) return -1;
        if( *i >= '0' && *i <= '9' )
            n = n * 10 + *i - '0';
    }
    return n;
}
std::istream &operator >>(std::istream &in, Tree::Node &node) {
    std::string s1, s2;
    in >> node.name >> s1 >> s2;
    node.l = StringToInteger(s1);
    node.r = StringToInteger(s2);
    return in;
}
std::ostream &operator <<(std::ostream &out, const Tree::Node &node) {
    out << node.name << ' ' << node.l << ' ' << node.r;
    return out;
}
std::ostream &operator <<(std::ostream &out, const Tree &t) {
    for( int i = 0; i < t.Size(); i ++ )
        out << t.list[i] << std::endl;
    return out;
}

int main()
{
    int n1, n2;
    Tree *t1, *t2;
    std::cin >> n1;
    t1 = new Tree(n1);
    t1->InputTree(std::cin);
    std::cin >> n2;
    t2 = new Tree(n2);
    t2->InputTree(std::cin);
    std::cout << (Tree::CompareTree(*t1, *t2) ? "Yes" : "No") << std::endl;
    std::cout << t1->Deepth() << std::endl;
    std::cout << t2->Deepth() << std::endl;
    delete t1;
    delete t2;
    return 0;
}