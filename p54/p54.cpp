/**
 * @brief p54样例程序
 * @author 张校
 * @date 2021-10-27
 */

#include <iostream>
#include <vector>
#include <set>

class Picture {
public:
    struct Node {
        int id, in, out;
        std::vector<Node*> next;
        Node(const int id_) : id(id_) { in = out = 0; }
        ~Node() = default;
        /**
         * bool CheckNode(std::set<int> &C, std::set<int> &S)
         * @brief 使用DFS检查是否有环
         * @param set C 该点是否在栈中
         * @param set S 该点是否检查过
         * @return 是否存在环（false：有；true：无）
         */
        bool CheckNode(std::set<int> &C, std::set<int> &S) {
            if( S.find(id) != S.end() )
                return true;
            if( C.find(id) != C.end() )
                return false;
            C.insert(id);
            for( auto i : next )
                if( ! i->CheckNode(C, S) )
                    return false;
            C.erase(C.find(id));
            S.insert(id);
            return true;
        }
    };

    /**
     * void AddLine(int start, int end)
     * @brief 插入一条边
     * @param int start 开始节点坐标
     * @param int end 结束节点坐标
     */
    void AddLine(int start, int end) {
        nodes[start].next.push_back(&nodes[end]);
        nodes[start].out ++;
        nodes[end].in ++;
    }
    /**
     * bool Check()
     * @brief 检查是否有环
     * @return 是否有环（flase：有；true：无）
     */
    bool Check() {
        std::set<int> S;
        for( auto node : nodes ) {
            std::set<int> C;
            if( node.in == 0 && ! node.CheckNode(C, S) )
                return false;
        }
        return !S.empty();
    }
    /**
     * Build(const int n)
     * @brief 构造n个点的无边列表
     * @param int n 节点个数
     */
    void Build(const int n) { for( int i = 0; i < n; i ++ ) nodes.push_back(Node(i)); }
    void Clear() { nodes.clear(); }
    Picture() = default;
    Picture(const int n) { Build(n); }
    ~Picture() = default;
private:
    std::vector<Node> nodes;
};
int main()
{
    int n, m;
    std::cin >> n >> m;
    Picture *pic = new Picture(n);
    while( m -- ) {
        int s, e, w;
        std::cin >> s >> e >> w;
        pic->AddLine(s - 1, e - 1);
    }
    std::cout << pic->Check() << std::endl;
    delete pic;
    return 0;
}