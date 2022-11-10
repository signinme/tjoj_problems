/**
 * @file    p132_data.cpp
 * @brief   p132样例程序
 * @date    2022-10-21
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>

class Graph {
private:
    struct Edge {
        int to, weight;
        Edge(int t, int w) : to(t), weight(w) {}
    };

    int num_nodes;
    std::vector<std::vector<Edge>> edges;
    std::vector<std::vector<int>> min_distance;

     
public:
    Graph(int n, int m, int max_weight) : num_nodes(n), edges(n + 1), min_distance(n + 1) {
        // 随机生成图
        // 先插n - 1条边使图连通
        std::vector<bool> chart(num_nodes, false);
        chart[rand() % num_nodes] = true;
        for( int i = 1; i < n; i ++ ) {
            int x_c = rand() % i + 1;
            int y_c = rand() % (n - i) + 1;
            int x, y, w = rand() % max_weight + 1;
            for(int i = 0; i < num_nodes && (x_c > 0 || y_c > 0); i ++ ) {
                if( chart[i] == true ) x_c --;
                else y_c --;
                if( x_c == 0 ) {
                    x = i;
                    x_c --;
                }
                if( y_c == 0 ) {
                    y = i;
                    y_c --;
                }
            }
            chart[y] = true;
            edges[x + 1].push_back(Edge(y + 1, w));
            edges[y + 1].push_back(Edge(x + 1, w));
        }
        for( int i = n - 1; i < m; i ++ ) {
            int x = rand() % num_nodes + 1;
            int y = rand() % num_nodes + 1;
            while( y == x )
                y = rand() % num_nodes + 1;
            int w = rand() % max_weight + 1;
            edges[x].push_back(Edge(y, w));
            edges[y].push_back(Edge(x, w));
        }
    }
    ~Graph() {}

    void printEdges(std::ostream &out) {
        for( int i = 1; i <= num_nodes; i ++ ) {
            auto comp = [](const Edge &e1, const Edge &e2) {
                return e1.to < e2.to;
            };
            std::sort(edges[i].begin(), edges[i].end(), comp);
            for( auto edge : edges[i] ) {
                if( edge.to > i ) {
                    out << i << ' ' << edge.to << ' ' << edge.weight << std::endl;
                }
            }
        }
    }
    
    /**
     * @brief   访问一个点的单源最短路信息，如果还没求就先求单源最短路
    */
    std::vector<int>& operator[](int index) {
        if( min_distance[index].size() == 0 ) {
            generateTree(index);
        }
        return min_distance[index];
    }

private:
    /**
     * @brief   求点root为源点的单源最短路
     */
    void generateTree(int root) {
        std::vector<int> &md = min_distance[root];
        if( md.size() != 0 ) {
            return ;
        }
        md.resize(num_nodes + 1);

        struct COMP {
            bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
                return p1.first > p2.first;
            }
        };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, COMP> pque;
        pque.push(std::make_pair(0, root));
        for( int i = 1; i <= num_nodes; i ++ ) {
            if( !pque.empty() && pque.top().second != root ) {
                while( !pque.empty() && md[pque.top().second] != 0 ) {
                    pque.pop();
                }
            }
            if( pque.empty() ) {
                break;
            }
            int now = pque.top().second;
            md[now] = pque.top().first;
            pque.pop();

            for( auto edge : edges[now] ) {
                if( md[edge.to] == 0 && edge.to != root ) {
                    pque.push(std::make_pair(md[now] + edge.weight, edge.to));
                }
            }
        }
    }
};

int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n, m, h, r, max_weight;
        if( index <= test_num * 0.2 ) {
            n = rand() % 6 + 5;
            r = rand() % 6 + 5;
            max_weight = 10;
        }
        else if( index <= test_num * 0.4 ) {
            n = rand() % 11 + 90;
            r = rand() % 11 + 90;
            max_weight = 100;
        }
        else {
            n = rand() % 101 + 900;
            r = rand() % 101 + 900;
            max_weight = 100000;
        }
        m = rand() % n + n - 1;
        h = rand() % n + 1;

        Graph graph(n, m, max_weight);
        std::vector<bool> chart(n, false);
        std::vector<int> points(h);
        for( int i = 0; i < h; i ++ ) {
            int k = rand() % n;
            int j = k;
            while( chart[j] == true )
                j = (j + 1) % n;
            chart[j] = true;
            points[i] = j + 1;
        }

        fin << n << ' ' << m << std::endl;
        graph.printEdges(fin);
        fin << h << ' ' << r << std::endl;
        for( int i = 0; i < n; i ++ ) {
            if( chart[i] ) {
                fin << i + 1 << ' ';
            }
        }
        fin << std::endl;
        for( int i = 0; i < r; i ++ ) {
            int x = rand() % n + 1;
            int y = rand() % n + 1;
            fin << x << ' ' << y << std::endl;
            int ans = -1;
            for( auto point : points ) {
                int distance = graph[x][point] + graph[y][point];
                if( ans == -1 || ans > distance ) {
                    ans = distance;
                }
            }
            fout << ans << std::endl;
        }

        fin.close();
        fout.close();
    }
}