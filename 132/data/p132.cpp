/**
 * @file    p132.cpp
 * @brief   p132样例程序
 * @date    2022-10-21
*/

#include <iostream>
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
    Graph(int n) : num_nodes(n), edges(n + 1), min_distance(n + 1) {}
    ~Graph() {}

    void addEdge(int x, int y, int weight) {
        edges[x].push_back(Edge(y, weight));
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

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n);
    while( m -- ) {
        int x, y, w;
        std::cin >> x >> y >> w;
        graph.addEdge(x, y, w);
        graph.addEdge(y, x, w);
    }

    int h, r;
    std::cin >> h >> r;
    std::vector<int> points(h);
    for( auto &point : points ) {
        std::cin >> point;
    }

    for( int i = 0; i < r; i ++ ) {
        int x, y, ans = -1;
        std::cin >> x >> y;
        for( auto point : points ) {
            int distance = graph[x][point] + graph[y][point];
            if( ans == -1 || ans > distance ) {
                ans = distance;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}