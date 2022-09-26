/**
 * @name    p91.cpp
 * @brief   p91 样例程序
 * @author  张校
 * @date    2021-12-7
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <string>

class HASH {
public:
    static const int MULT_FACTOR = 37;
    HASH(int size) : size_(CalculateNextPrimeNumber(size)), list_(size_) {}
    ~HASH() {}

    /**
     * @brief   插入一个元素
     * @return  若插入成功，返回下标；否则返回-1
     */
    int Insert(const std::string &str) {
        int count = Hash(str);
        for( int i = 0; i <= size_; i ++ ) {
            int index = ((count + Square((i + 1) / 2 % size_) * (i % 2 ? 1 : -1)) % size_ + size_) % size_;
            if( list_[index] == "" ) {
                list_[index] = str;
                return index;
            }
        }
        return -1;
    };
private:
    /**
     * @brief 计算第一个不小于P的素数
     */
    static int CalculateNextPrimeNumber(const int P) {
        if( P <= 2 )
            return 2;
        bool *chart = new bool[P];
        memset(chart, 0, sizeof(bool) * P);
        int count = 0;
        while( count * 2 + 3 < P || chart[count] ) {
            if( ! chart[count] )
                for( int i = count; i < P; i += count * 2 + 3 )
                    chart[i] = true;
            count ++;
        }
        delete[] chart;
        if( count == P )
            return -1;
        return count * 2 + 3;
    }
    /**
     * @brief 计算平方
     */
    static int Square(int n) {
        return (n * n);
    }
    /**
     * @brief 计算hash值
     */
    int Hash(const std::string &str) const {
        int count = 0;
        for( int i = 0; i < str.length(); i ++ )
            count = (count * MULT_FACTOR + str[i]) % size_;
        return count;
    }
    
    int size_;
    std::vector<std::string> list_;
};

int main()
{
    int N, P;
    std::cin >> N >> P;
    HASH &H = *(new HASH(P));
    while( N -- ) {
        std::string name;
        std::cin >> name;
        int index = H.Insert(name);
        if( index == -1 )
            std::cout <<"- ";
        else
            std::cout << index << ' ';
    }
    std::cout << std::endl;
    delete &H;
    return 0;
}