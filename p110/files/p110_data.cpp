/**
 * @name    p110_data.cpp
 * @brief   p110 随机测试数据生成程序
 * @author  张校
 * @date    2021-12-7
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class List {
public:
    /**
     * @brief   初始化时生成一个随机数列
     * @param   size int 数列长度
     * @param   max_num int 数列中最大元素
     */
    List(int size, int max_num) {
        for( int i = 0; i < size; i ++ )
            list_.push_back(rand() % max_num + 1);
        std::sort(list_.begin(), list_.end());
    }
    ~List() = default;
    /**
     * @brief   清空数组
     */
    void Clear() {
        list_.clear();
    }
    /**
     * @brief   在数组尾部插入一个元素
     */
    void PushBack(int elem) {
        list_.push_back(elem);
    }
    /**
     * @brief   寻找元素最后一个出现的下标
     * @return  找到：下标；找不到：-1；
     */
    int UpperBound(int elem) {
        int l = 0, r = list_.size() - 1;
        while( l != r ) {
            int m = (l + r) / 2;
            if( list_[m + 1] <= elem )
                l = m + 1;
            else
                r = m;
        }
        return (list_[r] == elem ? r : -1);
    }
    /**
     * @brief   寻找元素第一个出现的下标
     * @return  找到：下标；找不到：-1；
     */
    int LowerBound(int elem) {
        int l = 0, r = list_.size() - 1;
        while( l != r ) {
            int m = (l + r) / 2;
            if( list_[m] >= elem )
                r = m;
            else
                l = m + 1;
        }
        return (list_[l] == elem ? l : -1);
    }
    /**
     * @brief 在数列中随机取元素
     */
    int RandElem() {
        return list_[rand() % list_.size()];
    }
    /**
     * @brief 打印整个数列
     */
    void PrintList(std::ofstream &fout) {
        for( auto i : list_ ) {
            fout << i << ' ';
        }
        fout << std::endl;
    }
private:
    std::vector<int> list_;
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

        int n, m;
        if( index <= test_num * 0.2 ) {
            n = rand() % 11 + 10;
        }
        else if( index <= test_num * 0.4 ) {
            n = rand() % 101 + 900;
        }
        else {
            n = rand() % 1001 + 99000;
        }
        m = n * (rand() % 501 + 500) / 100;
        fin << n << std::endl;

        if( index == 10 ){
            for( int i = 1; i <= n; i ++ )
                fin << i << ' ';
            fin << std::endl;
            while( m -- ) {
                int elem = rand() % n + 1;
                if( rand() % 2 )
                    fin << "upper " << elem << std::endl;
                else
                    fin << "lower " << elem << std::endl;
                fout << elem - 1 << std::endl;
            }
        }
        else {
            List &L = *(new List(n, n));
            L.PrintList(fin);
            while( m -- ) {
                int elem = rand() % 100 < 25 ? rand() % n + 1 : L.RandElem();
                if( rand() % 2 ) {
                    fin << "upper " << elem << std::endl;
                    fout << L.UpperBound(elem) << std::endl;
                }
                else {
                    fin << "lower " << elem << std::endl;
                    fout << L.LowerBound(elem) << std::endl;
                }
            }
            delete &L;
        }
        
        fin << "done" << std::endl;
        fin.close();
        fout.close();
    }
    return 0;
}