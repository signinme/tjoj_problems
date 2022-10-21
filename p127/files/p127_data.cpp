/**
 * @file    p127_data.cpp
 * @name    p127随机测试数据生成程序
 * @date    2022-09-28
 */

#include <iostream>
#include <fstream>
#include <vector>

class Matrix {
public:
    Matrix(int k_) : k(k_), rowNumbers(k), colNumbers(k) {
        shuffle(k, rowConditions);
        shuffle(k, colConditions);
        for( int i = 0; i < k; i ++ ) {
            rowNumbers[rowConditions[i]] = i;
            colNumbers[colConditions[i]] = i;
        }
        matrix.resize(k);
        for( int i = 0; i < k; i ++ )
            matrix[i].resize(k);
        for( int i = 0; i < k; i ++ )
            matrix[rowConditions[i]][colConditions[i]] = i + 1;
    }

    void getGoodRowsSet(std::vector<std::pair<int,int>> &rows, int n) {
        // 插入描述唯一矩阵的必要边
        for( int i = 0; i < k - 1; i ++ )
            rows.push_back(std::make_pair(rowNumbers[i] + 1, rowNumbers[i + 1] + 1));
        // 插入一些合法的随机边
        for( int i = 0; i < n - k + 1; i ++ ) {
            int x = rand() % (k - 1);
            int y = x + rand() % (k - x - 1) + 1;
            rows.push_back(std::make_pair(rowNumbers[x] + 1, rowNumbers[y] + 1));
        }
    }
    void getBadRowsSet(std::vector<std::pair<int, int>> &rows, int n) {
        // 先获取一个合法的边集合
        int bad_edges = rand() % 10 + 1;
        getGoodRowsSet(rows, n - bad_edges);
        // 再插入一些非法边
        for( int i = 0; i < bad_edges; i ++ ) {
            int x = rand() % (k - 1) + 1;
            int y = rand() % (x);
            rows.push_back(std::make_pair(rowNumbers[x] + 1, rowNumbers[y] + 1));
        }
    }
    void getGoodColsSet(std::vector<std::pair<int,int>> &cols, int m) {
        // 插入描述唯一矩阵的必要边
        for( int i = 0; i < k - 1; i ++ )
            cols.push_back(std::make_pair(colNumbers[i] + 1, colNumbers[i + 1] + 1));
        // 插入一些合法的随机边
        for( int i = 0; i < m - k + 1; i ++ ) {
            int x = rand() % (k - 1);
            int y = x + rand() % (k - x - 1) + 1;
            cols.push_back(std::make_pair(colNumbers[x] + 1, colNumbers[y] + 1));
        }
    }
    void getBadColsSet(std::vector<std::pair<int, int>> &cols, int m) {
        // 先获取一个合法的边集合
        int bad_edges = rand() % 10 + 1;
        getGoodColsSet(cols, m - bad_edges);
        // 再插入一些非法边
        for( int i = 0; i < bad_edges; i ++ ) {
            int x = rand() % (k - 1) + 1;
            int y = rand() % (x);
            cols.push_back(std::make_pair(colNumbers[x] + 1, colNumbers[y] + 1));
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

    static void shuffle(int n, std::vector<int> &list) {
        list.resize(n);
        for( int i = 0; i < n; i ++ )
            list[i] = i;
        for( int i = 0; i < n - 1; i ++ ) {
            int t = rand() % (n - i);
            if( t == 0 )
                continue;
            int tmp = list[i];
            list[i] = list[i + t];
            list[i + t] = tmp;
        }
    }
private:
    int k;
    std::vector<int> rowConditions;
    std::vector<int> colConditions;
    std::vector<int> rowNumbers;
    std::vector<int> colNumbers;
    std::vector<std::vector<int>> matrix;
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
        
        int k, n, m;
        if( index <= test_num * 0.2 ) {
            k = 5 + rand() % 6;
            n = 15 + rand() % 6;
            m = 15 + rand() % 6;
        }
        else if( index <= test_num * 0.4 ) {
            k = 90 + rand() % 11;
            n = 900 + rand() % 101;
            m = 900 + rand() % 101;
        }
        else {
            k = 400;
            n = 9000 + rand() % 1001;
            m = 9000 + rand() % 1001;
        }
        fin << k << ' ' << n << ' ' << m << std::endl;
        Matrix matrix(k);
        std::vector<std::pair<int, int>> rows;
        std::vector<std::pair<int, int>> cols;
        std::vector<int> rows_index;
        std::vector<int> cols_index;
        Matrix::shuffle(n, rows_index);
        Matrix::shuffle(m, cols_index);
        if( index % 2 == 1 ) {
            matrix.getGoodRowsSet(rows, n);
            matrix.getGoodColsSet(cols, m);
            matrix.displayMatrix(fout);
        }
        else {
            switch(rand() % 3) {
            case 0:
                matrix.getBadRowsSet(rows, n);
                matrix.getBadColsSet(cols, m);
                break;
            case 1:
                matrix.getGoodRowsSet(rows, n);
                matrix.getBadColsSet(cols, m);
                break;
            case 3:
            default:
                matrix.getBadRowsSet(rows, n);
                matrix.getGoodColsSet(cols, m);
            }
            fout << -1 << std::endl;
        }
        for( int i = 0; i < n; i ++ ) {
            fin << rows[rows_index[i]].first << ' ' << rows[rows_index[i]].second << std::endl;
        }
        for( int i = 0; i < m; i ++ ) {
            fin << cols[cols_index[i]].first << ' ' << cols[cols_index[i]].second << std::endl;
        }
        /*for( int i = 0; i < n; i ++ ) {
            fin << rows[i].first << ' ' << rows[i].second << std::endl;
        }
        for( int i = 0; i < m; i ++ ) {
            fin << cols[i].first << ' ' << cols[i].second << std::endl;
        }
        */
        fin.close();
        fout.close();
    }
    return 0;
}