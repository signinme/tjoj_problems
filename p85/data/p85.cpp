/**
 * @name    p85.cpp
 * @brief   p85 样例程序
 * @author  张校
 * @date    2021-12-7
 */

#include <iostream>
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
     * @brief 输入数列
     */
    void Input(std::istream &in) {
        for( int i = 0; i < size_; i ++ )
            in >> list_[i];
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
    while( 1 )
    {
        int n;
        std::cin >> n;
        if( n == 0 )
            break;
        List &L = *(new List(n));
        L.Input(std::cin);
        std::cout << L.Solve() << std::endl;
        delete &L;
    }
    return 0;
}