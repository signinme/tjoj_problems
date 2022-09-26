/**
 * @name    p91_data.cpp
 * @brief   p91 随机测试数据生成程序
 * @author  张校
 * @date    2021-12-7
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>

class HASH {
public:
    static const int MULT_FACTOR = 37;
    static const int MAX_NAME_LENGTH = 100;
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
     * @brief 生成随机名字
     */
    static std::string RandomName(int length) {
        std::string name;
        for( int i = 0; i < length; i ++ ) {
            if( rand() % 2 )
                name += rand() % 26 + 'A';
            else
                name += rand() % 26 + 'a';
        }
        return name;
    }
private:
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
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());
        int N, P;
        if( index <= test_num * 0.2 ) {
            P = rand() % 11 + 10;
        }
        else if( index <= test_num * 0.4 ) {
            P = rand() % 11 + 190;
        }
        else {
            P = rand() % 101 + 9900;
        }
        if( index % 3 == 0 )
            P = HASH::CalculateNextPrimeNumber(P);
        N = P / 2 + rand() % (int(P * 0.7) + 1) + 1;
        if( index == 1 ) {
            P = 1;
            N = 3;
        }

        fin << N << ' ' << P << std::endl;
        HASH &H = *(new HASH(P));
        while( N -- ) {
            std::string name = HASH::RandomName(1 + rand() % HASH::MAX_NAME_LENGTH);
            fin << name << ' ';
            int index = H.Insert(name);
            if( index == -1 )
                fout << "- ";
            else
                fout << index << ' ';
        }
        fin << std::endl;
        fout << std::endl;
        delete &H;

        fin.close();
        fout.close();
    }
    return 0;
}