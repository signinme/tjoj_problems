/**
 * @name   p55 随机测试数据生成程序
 * @author 张校
 * @date   2021-10-27
 * @brief  使用方法：直接编译运行
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stack>
#include <climits>

class Picture {
public:
    struct Node {
        int id, earliest, latest;
        std::vector<std::pair<Node*, int>> next;
        std::vector<std::pair<Node*, int>> last;
        Node(const int id_) : id(id_) { earliest = INT_MIN; latest = INT_MAX; }
        ~Node() = default;
    };
    /**
     * @brief 检查节点是否为结尾节点
     */
    bool IsNotEnd(const int n) { return n >= 0 && n < nodes.size() && nodes[n].next.empty(); }
    /**
     * @brief 随机增加一条边使图构成环
     * @param int e 该边的结束坐标
     */
    void AddErrorLine(int e) {
        int step = rand() % 10 + 1;
        int i = e;
        while( step -- && nodes[i].next.size() > 0 )
            i = nodes[i].next[rand() % nodes[i].next.size()].first->id;
        AddLine(i, e, rand() % 100 + 1);
    }
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
     * @brief 打印所有边
     */
    void PrintLines(std::ostream &out) {
        for( auto node : nodes ) {
            for( auto &next : node.next ) {
                out << node.id + 1 << ' ' << next.first->id + 1 << ' ' << next.second << std::endl;
            }
        }
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

void Shuffle(std::vector<int>& vec, int n)
{
    for( int i = 0; i < n; i ++ )
        vec.push_back(i);
    for( int i = 0; i < n; i ++ )
    {
        //保证每次第i位的值不会涉及到第i位以前
        int index = i + (rand() % (n - i));
        std::swap(vec[index], vec[i]);
    }
}

int main()
{
    srand((unsigned) time(NULL));
    int test_num = 10; // 测试点个数
    for( int i = 1; i <= test_num; i ++ ) {
        std::string file_in = "input" + std::to_string(i) + ".txt";
        std::string file_out = "output" + std::to_string(i) + ".txt";
        std::ofstream fin(file_in), fout(file_out);
        
        int n, m;
        if( i <= test_num * 0.2 ) {
            n = rand() % 5 + 6;
        }
        else if( i <= test_num * 0.4) {
            n = rand() % 10 + 91;
        }
        else {
            n = rand() % 100 + 99900;
        }
        m = n * (rand() % 50 + 151) / 100;

        std::vector<int> chart;
        Shuffle(chart, n);
        fin << n << ' ' << m + (i == 7) << std::endl;
        Picture *pic = new Picture(n);
        while( m -- ) {
            /**
             * 可以看出，这里随机生成的s、e，都有s<=e，即生成的是已经经过拓扑排序的有序图
             * 但为了避免直接在读入时检测s、e就能判断结果，这里使用随机洗牌的序列代替id
             */
            int s = rand() % (n - 1);
            int e = rand() % (n - s - 1) + s + 1;
            pic->AddLine(chart[s], chart[e], rand() % 100 + 1);
        }
        if( i == 7 ) {
            int e = -1;
            while( !pic->IsNotEnd(e) ) e = rand() % n;
            pic->AddErrorLine(e);
        }
        pic->FixOrder();
        pic->PrintLines(fin);
        
        if( i == 7 ) {
            fout << 0 << std::endl;
        }
        else {
            fout << pic->FindKeyPath() << std::endl;
            pic->PrintKeyPath(fout);
        }
        delete pic;
        fin.close();
        fout.close();
    }
    return 0;
}