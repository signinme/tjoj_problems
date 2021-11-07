/**
 * 随机测试数据生成程序
 * @author 张校
 * @date 2021-10-27
 * @brief 使用方法：直接编译运行
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

class Picture {
public:
    struct Node {
        int id, in, out;
        std::vector<Node*> next;
        Node(const int id_) : id(id_) { in = out = 0; }
        ~Node() = default;
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
     * @brief 随机增加一条边使图构成环
     * @param int e 该边的结束坐标
     */
    void AddErrorLine(int e) {
        int step = rand() % 10 + 1;
        int i = e;
        while( step -- && nodes[i].next.size() > 0 )
            i = nodes[i].next[rand() % nodes[i].next.size()]->id;
        AddLine(i, e);
    }
    /**
     * Build(const int n)
     * @brief 构造n个点的无边列表
     * @param int n 节点个数
     */
    void Build(const int n) { for( int i = 0; i < n; i ++ ) nodes.push_back(Node(i)); }
    /**
     * @brief 检查节点是否为结尾节点
     */
    bool IsNotEnd(const int n) { return n >= 0 && n < nodes.size() && nodes[n].out != 0; }
    /**
     * @brief 打印所有边
     */
    void PrintLines(std::ostream &out) {
        bool (*comp)(Node *n1, Node *n2) = [](Node *n1, Node *n2) { return n1->id < n2->id; };
        for( auto node : nodes ) {
            std::sort(node.next.begin(), node.next.end(), comp);
            for( auto i : node.next ) {
                out << node.id + 1 << ' ' << i->id + 1 << ' ' << rand() % 10 + 1 << std::endl;
            }
        }
    }
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
    for( int i = 1; i <= test_num; i ++ )
    {
        std::string file_in = "input" + std::to_string(i) + ".txt";
        std::string file_out = "output" + std::to_string(i) + ".txt";
        std::ofstream fin(file_in), fout(file_out);

        int n, m;
        if( i <= test_num * 0.2 ) {
            n = rand() % 5 + 6;
        }
        else if( i <= test_num * 0.4 ) {
            n = rand() % 10 + 41;
        }
        else {
            // 正解算法的复杂度应该是O(n + m)或O(m)（这里n和m的次数相同）
            n = rand() % 100 + 99900;
        }
        m = n * (rand() % 50 + 150) / 100;

        std::vector<int> chart;
        Shuffle(chart, n);
        Picture *pic = new Picture(n);
        fin << n << ' ' << m + (i % 2) << std::endl;

        while( m -- ) {
            /**
             * 可以看出，这里随机生成的s、e，都有s<=e，即生成的是已经经过拓扑排序的有序图
             * 但为了避免直接在读入时检测s、e就能判断结果，这里使用随机洗牌的序列代替id
             */
            int s = rand() % (n - 1);
            int e = rand() % (n - s - 1) + s + 1;
            pic->AddLine(chart[s], chart[e]);
        }
        // 当结果为0时，生成一条边让图成环
        if( i % 2 ) {
            int e = -1;
            while( !pic->IsNotEnd(e) ) e = rand() % n;
            pic->AddErrorLine(e);
            fout << 0 << std::endl;
        }
        else
            fout << 1 << std::endl;
        pic->PrintLines(fin);
        fin.close();
        fout.close();
        delete pic;
    }
    return 0;
}