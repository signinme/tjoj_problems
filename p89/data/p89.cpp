/**
 * @name    p89样例程序
 * @author  张校
 * @date    2021-11-1
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <queue>

class PICTURE {
public:
    struct NODE {
        int id, count;
        std::vector<int> next;
        NODE(int i) : id(i) { count = 0; }
        ~NODE() = default;
    };
    /**
     * @brief 插入一条边
     */
    void InsertLine(int s, int e) { list[s - 1].next.push_back(e - 1); }
    /**
     * @brief 解决小世界现象问题
     */
    void Solve() {
        for( auto &node : list ) {
            bool chart[2000] = {0};
            chart[node.id] = true;
            std::queue<std::pair<int, int>> que;
            que.push(std::make_pair(0, node.id));
            while( ! que.empty() ) {
                node.count ++;
                int count = que.front().first;
                NODE &n = list[que.front().second];
                que.pop();
                for( auto next : n.next ) {
                    if( ! chart[next] ) {
                        chart[next] = true;
                        if( count < 6 )
                            que.push(std::make_pair(count + 1, next));
                    }
                }
            }
        }
    }
    /**
     * @brief 打印结果
     */
    void Print(std::ostream &out) {
        for( const auto &node : list ) {
            out << node.id + 1 << ':' << ' ' << std::fixed << std::setprecision(2) << float(node.count * 100.0 / list.size() + 0.004) << '%' << std::endl;
        }
    }
    PICTURE(const int n) { for( int i = 0; i < n; i ++ ) list.push_back(NODE(i)); }
    ~PICTURE() = default;
private:
    std::vector<NODE> list;
};

int main() {
    int n, m;
    std::cin >> n >> m;
    PICTURE &pic = *(new PICTURE(n));
    while( m -- ) {
        int s, e;
        std::cin >> s >> e;
        pic.InsertLine(s, e);
        pic.InsertLine(e, s);
    }
    pic.Solve();
    pic.Print(std::cout);
    delete &pic;
    return 0;
}