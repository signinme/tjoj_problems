/**
 * @name    p87随机测试数据生成程序
 * @author  张校
 * @date    2021.11.5
 * @brief   使用方法：直接编译运行
 */
#include <iostream>
#include <fstream>
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
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int i = 1; i <= test_num; i ++ ) {
        std::string inputfile = "input" + std::to_string(i) + ".txt";
        std::string outputfile = "output" + std::to_string(i) + ".txt";
        std::ofstream fin(inputfile.c_str());
        std::ofstream fout(outputfile.c_str());
        int n, m, start;
        if( i <= test_num * 0.2 ) {
            n = rand() % 5 + 6;
        } else if( i <= test_num * 0.4 ) {
            n = rand() % 10 + 91;
        } else if( i <= test_num * 0.8 ) {
            n = rand() % 100 + 900;
        }else {
            n = rand() % 100 + 99901;
        }
        m = n * (rand() % 100 + 200) / 100;
        start = rand() % n;

        fin << n << ' ' << m << ' ' << start + 1 << std::endl;
        PICTURE *pic = new PICTURE(n);
        for( int j = 0; j < n; j ++ ) {
            int s, e, w;
            s = j;
            e = rand() % n;
            w = rand() % 1000 + 1;
            fin << s + 1 << ' ' << e + 1 << ' ' << w << std::endl;
            pic->InsertLine(s, e, w);
            pic->InsertLine(e, s, w);
        }
        for( int j = n; j < m; j ++ ) {
            int s, e, w;
            s = rand() % n;
            e = rand() % n;
            w = rand() % 1000 + 1;
            fin << s + 1 << ' ' << e + 1 << ' ' << w << std::endl;
            pic->InsertLine(s, e, w);
            pic->InsertLine(e, s, w);
        }
        pic->Solve(start);
        pic->PrintMinDistance(fout);
        fin.close();
        fout.close();
        delete pic;
    }
    return 0;
}