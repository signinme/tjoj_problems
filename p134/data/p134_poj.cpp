/**
 * @file    p134.cpp
 * @name    p134样例程序
 * @date    2022-10-31
*/

#include <iostream>
#include <algorithm>
#include <vector>

class Group {
private:
    struct Edge {
        int x, y, w;
        Edge(int x_, int y_, int w_) : x(x_), y(y_), w(w_) {}
    };

    class SearchSet {
    private:
        int size;
        std::vector<int> list;
    public:
        SearchSet(int n) : size(n), list(n) {
            for( int i = 0; i < n; i ++ )
                list[i] = i;
        }

        int &operator[](int x) {
            return list[findRoot(x)];
        }
    private:
        int findRoot(int x) {
            if( list[x] == x )
                return x; 
            return list[x] = findRoot(list[x]);
        }
    };
    int n, last;
    std::vector<Edge> edges;
    SearchSet ss;

public:
    Group(int n_) : n(n_), last(n_ - 1), ss(n_) {}

    void addEdge(int x, int y, int w) {
        edges.push_back(Edge(x, y, w));
    }

    void connectViliges(int x, int y) {
        if( ss[y] == ss[x] )
            return;
        last --;
        ss[y] = ss[x];
    }
    static bool comp(const Edge &e1, const Edge &e2) {
        return e1.w < e2.w;
    }
    int calculateMinDistance() {
        
        std::sort(edges.begin(), edges.end(), comp);
        
        int ans = 0, pointer = 0;
        while( last > 0 && pointer < edges.size() ) {
            while( pointer < edges.size() && ss[edges[pointer].x] == ss[edges[pointer].y] ) {
                pointer ++;
            }
            ans += edges[pointer].w;
            ss[edges[pointer].x] = ss[edges[pointer].y];
            last --;
            pointer ++;
        }
        return (last == 0 ? ans : -1);
    }
};
int main() {
    int n, m;
    std::cin >> n;
    Group group(n);
    for( int i = 0; i < n; i ++ ) {
        for( int j = 0; j < n; j ++ ) {
            int w;
            std::cin >> w;
            if( i < j ) {
                group.addEdge(i, j, w);
            }
        }
    }
    std::cin >> m;
    while( m -- ) {
        int x, y;
        std::cin >> x >> y;
        group.connectViliges(x - 1, y - 1);
    }
    
    std::cout << group.calculateMinDistance() << std::endl;
    return 0;
}