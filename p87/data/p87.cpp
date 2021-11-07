/**
 * @name    p87样例程序
 * @author  张校
 * @date    2021.11.3
 */
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <climits>

class PICTURE{
public:
    struct NODE;
    typedef std::priority_queue<std::pair<int, NODE *>, std::vector<std::pair<int, NODE*>>, std::greater<std::pair<int, NODE*>>> PRIQUEUE;
    struct NODE {
        int id, min_distance;
        std::vector<std::pair<NODE*,int>> next;
        /**
         * inline void WriteMinDistance(std::set<NODE*> &S, PRIQUEUE &que)
         * @brief 更新一个点所有下级节点的最短距离
         */
        inline void WriteMinDistance(std::set<NODE*> &S, PRIQUEUE &que) {
            for( auto n : next ) {
                if( n.first->min_distance > min_distance + n.second && S.find(n.first) == S.end() ) {
                    n.first->min_distance = min_distance + n.second; // 这里可有可无，如果没有可能会有更多无意义点进入优先队列
                    que.emplace(std::make_pair(min_distance + n.second, n.first));
                }
            }
        }
        NODE(int id_) : id(id_) { min_distance = INT_MAX; }
        ~NODE() = default;
    };
    PICTURE(int size) {
        for( int i = 0; i < size; i ++ )
            list.push_back(NODE(i));
    };
    /**
     * @brief 插入一条边
     */
    void InsertLine(int s, int e, int w) {
        list[s].next.push_back(std::make_pair(&list[e], w));
    }
    /**
     * @brief 解决单源最短路问题
     */
    void Solve(int start) {
        std::set<NODE *> S; // 查重表
        PRIQUEUE que;       // 优先队列
        list[start].min_distance = 0;
        que.emplace(std::make_pair(0, &list[start]));
        while( S.size() < list.size() && ! que.empty() ) {
            int min_dist = que.top().first;
            NODE *select = que.top().second;
            que.pop();
            if( S.find(select) != S.end() )
                continue;
            S.insert(select);
            select->WriteMinDistance(S, que);
        } 
    }
    /**
     * @brief 打印执行Solve后打印结果
     */
    void PrintMinDistance(std::ostream &out) {
        for( const auto i : list )
            out << i.min_distance << ' ';
        out << std::endl;
    }
private:
    std::vector<NODE> list;
};

int main() {
    int n, m, start;
    std::cin >> n >> m >> start;
    PICTURE *pic = new PICTURE(n);
    while( m -- ) {
        int s, e, w;
        std::cin >> s >> e >> w;
        pic->InsertLine(s - 1, e - 1, w);
        pic->InsertLine(e - 1, s - 1, w);
    }
    pic->Solve(start - 1);
    pic->PrintMinDistance(std::cout);
    delete pic;
    return 0;
}