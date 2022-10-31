/**
 * @file    p134_data.cpp
 * @name    p134随机测试数据生成程序
 * @date    2022-10-31
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
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
    std::vector<std::vector<int>> edges_matrix;
    SearchSet ss;

public:
    Group(int n_, int max_w) : n(n_), last(n), edges_matrix(n, std::vector<int>(n)), ss(n_) {
        for( int i = 0; i < n; i ++ ) {
            edges_matrix[i][i] = 0;
            for( int j = 0; j < i; j ++ ) {
                edges_matrix[i][j] = rand() % max_w + 1;
                edges_matrix[j][i] = edges_matrix[i][j];
                edges.push_back(Edge(i, j, edges_matrix[i][j]));
            }
        }
    }

    void printEdgesMatrix(std::ostream &out) {
        for( int i = 0; i < n; i ++ ) {
            for( int j = 0; j < n; j ++ ) {
                out << edges_matrix[i][j] << ' ';
            }
            out << std::endl;
        }
    }

    void connectViliges(int x, int y) {
        if( ss[y] == ss[x] )
            return;
        last --;
        ss[y] = ss[x];
    }

    int calculateMinDistance() {
        auto comp = [](const Edge &e1, const Edge &e2) {
            return e1.w < e2.w;
        };
        std::sort(edges.begin(), edges.end(), comp);
        
        int ans = 0, pointer = 0;
        while( last && pointer < edges.size() ) {
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


int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n, max_w, connected_num;
        if( index <= test_num * 0.2 ) {
            n = rand() % 8 + 3;
            max_w = 10;
        }
        else if( index <= test_num * 0.4 ) {
            n = rand() % 11 + 40;
            max_w = 100;
        }
        else {
            n = rand() % 11 + 90;
            max_w = 1000;
        }
        connected_num = rand() % (n / 2);

        Group group(n, max_w);
        fin << n << std::endl;
        group.printEdgesMatrix(fin);
        fin << connected_num << std::endl;
        while( connected_num -- ) {
            int x = rand() % n;
            int y = rand() % n;
            while( y == x ) {
                y = rand() % n;
            }
            fin << x + 1 << ' ' << y + 1 << std::endl;
            group.connectViliges(x, y);
        }
        fout << group.calculateMinDistance() << std::endl;
        // 文件输出代码

        fin.close();
        fout.close();
    }
}