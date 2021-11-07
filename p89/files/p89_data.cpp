/**
 * @name    p89随机测试数据生成程序
 * @author  张校
 * @date    2021-11-1
 * @brief   使用方式：直接编译运行
 */
#include <iostream>
#include <fstream>
#include <algorithm>
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
    void InsertLine(int s, int e) { list[s].next.push_back(e); }
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
     * @brief 对边排序用于输出
     */
    void FixOrder() {
        for( auto &i : list ) {
            std::sort(i.next.begin(), i.next.end());
        }
    }
    /**
     * @brief 打印所有边
     */
    void PrintLines(std::ostream &out) {
        for( auto &i : list ) {
            for( std::vector<int>::iterator it = i.next.begin(); it != i.next.end(); it ++ )
            {
                if( *it > i.id)
                    out << i.id + 1 << ' ' << *it + 1 << std::endl;
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
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试数据个数
    for( int i = 1; i <= test_num; i ++ ) {
        std::string inputfile = "input" + std::to_string(i) + ".txt";
        std::string outputfile = "output" + std::to_string(i) + ".txt";
        std::ofstream fin(inputfile.c_str());
        std::ofstream fout(outputfile.c_str());
        int n, m;
        if( i <= test_num * 0.2 ) {
            n = rand() % 5 + 16;
            m = n * (rand() % 200 + 100) / 100;
        } else if ( i <= test_num * 0.4 ) {
            n = rand() % 10 + 91;
            m = n * (rand() % 200 + 100) / 100;
        } else if( i <= test_num * 0.9 ) {
            n = rand() % 50 + 1951;
            m = n * (rand() % 200 + 100) / 100;
        } else {
            n = rand() % 50 + 1951;
            m = n * (rand() % 3200 + 100) / 100;
        }
        fin << n << ' ' << m << std::endl;
        PICTURE &pic = *(new PICTURE(n));
        for( int j = 0; j < n; j ++ ) {
            int s, e;
            s = j;
            e = rand() % n;
            // fin << s + 1 << ' ' << e + 1 << std::endl;
            pic.InsertLine(s, e);
            pic.InsertLine(e, s);
        }
        for( int j = n; j < m; j ++ ) {
            int s, e;
            s = rand() % n;
            e = rand() % n;
            // fin << s + 1 << ' ' << e + 1 << std::endl;
            pic.InsertLine(s, e);
            pic.InsertLine(e, s);
        }
        pic.FixOrder();

        pic.PrintLines(fin);
        pic.Solve();
        pic.Print(fout);
        fin.close();
        fout.close();
        delete &pic;
    }
    return 0;
}