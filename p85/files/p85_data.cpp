/**
 * @name    p85_data.cpp
 * @brief   p85 随机测试数据生成程序
 * @author  张校
 * @date    2021-12-7
 */

#include <iostream>
#include <fstream>
#include <cstring>

class List {
public:
    List(int size) : size_(size) { list_ = new int[size]; key_ = new int[size]; }
    ~List() {
        if( ! list_)
            delete[] list_;
        if( ! key_)
            delete[] key_;
    }

    /**
     * @brief 生成随机序列
     */
    void GenerateRandomList() {
        for( int i = 0; i < size_; i ++ )
            list_[i] = rand() % int(size_ * 1.2) + 1;
    }
    /**
     * @brief 生成顺序序列
     */
    void GenerateOrderList() {
        for( int i = 0; i < size_; i ++ )
            list_[i] = i + 1;
    }
    /**
     * @brief 生成逆序序列
     */
    void GenerateDescList() {
        for( int i = 0; i < size_; i ++ )
            list_[i] = size_ - i + 1;
    }
    /**
     * @brief 打印序列
     */
    void PrintList(std::ofstream &fin) {
        for( int i = 0; i < size_; i ++ )
            fin << list_[i] << ' ';
        fin << std::endl;
    }
    /**
     * @brief 计算逆序数
     */
    int Solve() {
        memcpy(key_, list_, size_ * sizeof(int));
        return MergeSort(list_, key_, 0, size_);
    }
private:
    /**
     * @brief 归并排序
     */
    int MergeSort(int *list, int *key, int l, int r) {
        if( r - l == 1 )
        {
            list[l] = key[l];
            return 0;
        }
        int m = (l + r) / 2;
        int count = MergeSort(key, list, l, m) + MergeSort(key, list, m, r);
        for( int i1 = l, i2 = m, c = l; ; ) {
            if( i1 == m ) {
                while( i2 < r )
                    list[c ++] = key[i2 ++];
                break;
            }
            if( i2 == r ) {
                while( i1 < m )
                    list[c ++] = key[i1 ++];
                break;
            }
            if( key[i1] > key[i2] ) {
                count += m - i1;
                list[c ++] = key[i2 ++];
            }
            else {
                list[c ++] = key[i1 ++];
            }
        }
        return count;
    }
    
    int size_, *list_, *key_;
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

        int m = index * 10;
        while( m -- ) {
            int n;
            if( index <= test_num * 0.2 ) {
                n = rand() % 11 + 10;
            } else if( index <= test_num * 0.4 ) {
                n = rand() % 11 + 90;
            } else if( index <= test_num * 0.6) {
                n = rand() % 101 + 9900;
            } else {
                n = rand() % 1001 + 19000;
            }
            fin << n << std::endl;
            List &L = *(new List(n));
            if( m == 1 )
                L.GenerateDescList();
            else if( m == 0)    
                L.GenerateOrderList();
            else
                L.GenerateRandomList();

            L.PrintList(fin);
            fout << L.Solve() << std::endl;
            delete &L;
        }
        fin << 0 << std::endl;
        fin.close();
        fout.close();
    }
    return 0;
}