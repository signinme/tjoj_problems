/**
 * @file    p127.cpp
 * @name    p127示例程序
 * @date    2022-09-28
 */

#include <iostream>
#include <vector>
#include <set>
#include <queue>

class Matrix {
public:
    Matrix(int k_) : k(k_), rowConditions(k), colConditions(k) {}

    bool slove() {
        std::vector<int> rows(k), cols(k);
        if( ! topologicalSort(k, rowConditions, rows) )
            return false;
        if( ! topologicalSort(k, colConditions, cols) )
            return false;

        matrix.resize(k);
        for( int i = 0; i < k; i ++ )
            matrix[i].resize(k);
        for( int i = 0; i < k; i ++ ) {
            matrix[rows[i]][cols[i]] = i + 1;
        }
        return true;
    }

    void addRowCondition(int x, int y) {
        std::pair<int, int> p(x, y);
        if( rows_set.find(p) == rows_set.end() ) {
            rowConditions[x - 1].push_back(y - 1);
            rows_set.insert(p);
        }
    }
    void addColCondition(int x, int y) {
        std::pair<int, int> p(x, y);
        if( cols_set.find(p) == cols_set.end() ) {
            colConditions[x - 1].push_back(y - 1);
            cols_set.insert(p);
        }
    }

    void displayMatrix(std::ostream &out) {
        if( matrix.size() == 0 )
            return ;
        for( int i = 0; i < k; i ++ ) {
            for( int j = 0; j < k; j ++ ) {
                out << matrix[i][j] << ' ';
            }
            out << std::endl;
        }
    }
    /**
     * @brief   拓扑排序
     */
    static bool topologicalSort(const int k, const std::vector<std::vector<int>> &edges, std::vector<int> &list) {
        std::queue<int> que;
        std::vector<int> chart(k);
        for( int i = 0; i < k; i ++ ) {
            for( auto to : edges[i] ) {
                chart[to] ++;
            }
        }
        for( int i = 0; i < k; i ++ ) {
            if( chart[i] == 0 )
                que.push(i);
        }
        int index = 0;
        while( ! que.empty() ) {
            int p = que.front();
            que.pop();
            list[p] = index ++;
            for( auto to : edges[p] ) {
                chart[to] --;
                if( ! chart[to] )
                    que.push(to);
            }
        }
        return index == k;
    }
private:
    int k;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> rowConditions;
    std::vector<std::vector<int>> colConditions;
    
    std::set<std::pair<int, int>> rows_set;
    std::set<std::pair<int, int>> cols_set;
};

int main() {
    int k, n, m;
    std::cin >> k >> n >> m;
    Matrix matrix(k);
    while( n -- ) {
        int x, y;
        std::cin >> x >> y;
        matrix.addRowCondition(x, y);
    }
    while( m -- ) {
        int x, y;
        std::cin >> x >> y;
        matrix.addColCondition(x, y);
    }
    if( matrix.slove() == false ) {
        std::cout << -1 << std::endl;
    }
    else {
        matrix.displayMatrix(std::cout);
    }
    return 0;
}