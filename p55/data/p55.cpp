/**
 * @brief p55样例程序
 * @author 张校
 * @date 2021-10-27
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <climits>
#include <set>
class Picture {
public:
    struct Node {
        int id, earliest, latest;
        std::vector<std::pair<Node*, int>> next;
        std::vector<std::pair<Node*, int>> last;
        Node(const int id_) : id(id_) { earliest = INT_MIN; latest = INT_MAX; }
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
                if( ! i.first->CheckNode(C, S) )
                    return false;
            C.erase(C.find(id));
            S.insert(id);
            return true;
        }
    };

    /**
     * void AddLine(int start, int end)
     * @brief 插入一条边
     * @param int s 开始节点坐标
     * @param int e 结束节点坐标
     * @param int w 边权值
     */
    void AddLine(int s, int e, int w) {
        nodes[s].next.push_back(std::make_pair(&nodes[e], w));
        nodes[e].last.push_back(std::make_pair(&nodes[s], w));
    }
    /**
     * int FindKeyPath()
     * @brief 寻找关键路径
     * @return 关键路径长度
     */
    int FindKeyPath() {
        std::stack<Node *> S;
        for( auto &node : nodes ) {
            if( node.last.empty() ) {
                S.push(&node);
            }
        }
        int max_earliest = INT_MIN;
        while( ! S.empty() ) {
            Node &n = *S.top();
            S.pop();
            max_earliest = std::max(max_earliest, n.earliest);
            for( auto &next : n.next ) {
                if( next.first->earliest < n.earliest + next.second ) {
                    next.first->earliest = n.earliest + next.second;
                    S.push(next.first);
                }
            }
        }
        for( auto &node : nodes ) {
            if( node.next.empty() ) {
                node.latest = max_earliest;
                S.push(&node);
            }
        }
        while( ! S.empty() ) {
            Node &n = *S.top();
            S.pop();
            for( auto &last : n.last ) {
                if( last.first->latest > n.latest - last.second ) {
                    last.first->latest = n.latest - last.second;
                    S.push(last.first);
                }
            }
        }
        return max_earliest - INT_MIN;
    }
    /**
     * void PrintKeyPath(std::ostream &out)
     * @brief 打印关键路径
     */
    void PrintKeyPath(std::ostream &out) {
        for( auto &node : nodes ) {
            for( auto &next : node.next ) {
                if( next.first->earliest == next.first->latest && next.first->earliest == node.earliest + next.second )
                    out << node.id + 1 << "->" << next.first->id + 1 << std::endl;
            }
        }
    }
    /**
     * void FixOrder()
     * @brief 给边排序
     */
    void FixOrder() {
        bool (*comp)(std::pair<Node *, int>p1, std::pair<Node *, int>p2) =
            [](std::pair<Node *, int>p1, std::pair<Node *, int>p2) { return p1.first->id < p2.first->id; };
        for( auto &node : nodes ) {
            std::sort(node.next.begin(), node.next.end(), comp);
            // std::sort(node.last.begin(), node.last.end(), comp);
            // std::reverse(node.next.begin(), node.next.end());
        }
    }
    /**
     * bool Check()
     * @brief 检查是否有环
     * @return 是否有环（flase：有；true：无）
     */
    bool Check() {
        std::set<int> S;
        for( auto &node : nodes ) {
            std::set<int> C;
            if( node.last.empty() && ! node.CheckNode(C, S) )
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
        pic->AddLine(s - 1, e - 1, w);
    }
    pic->FixOrder();
    if( ! pic->Check() ) {
        std::cout << 0 << std::endl;
    }
    else {
        std::cout << pic->FindKeyPath() << std::endl;
        pic->PrintKeyPath(std::cout);
    }
    delete pic;
    return 0;
}