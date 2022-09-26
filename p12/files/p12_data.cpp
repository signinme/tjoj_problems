/**
 * @name    p12_data.cpp
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class LIST {
public:
    LIST(int n, int s, int m) : n_(n), s_(s - 1), m_(m) {
        list_.resize(n);
        for( int i = 0; i < n - 1; i ++ )
            list_[i] = i + 1;
        list_[n - 1] = 0;
    }

    void Slove(std::ostream &out) {
        int i = (s_ + n_ - 1) % n_;
        for( int j = n_; j > 1; j -- ) {
            for( int k = 1; k < (m_ - 1) % j + 1; k ++ )
                i = list_[i];
            out << list_[i] + 1 << ' ';
            list_[i] = list_[list_[i]];
        }
        out << i + 1 << std::endl;
    }
private:
    int n_, s_, m_;
    std::vector<int> list_;
};

int main() {
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file);
        std::ofstream fout(output_file);
        
        int n, s, m;
        if( index <= test_num * 0.2 ) {
            n = 10 + rand() % 11;
            m = rand() % n + 1;
        }
        else if( index <= test_num * 0.4 ) {
            n = 90 + rand() % 11;
        }
        else {
            n = 100 + rand() % 9901;
        }
        s = rand() % n + 1;
        m = rand() % n + 1;

        fin << n << ' ' << s << ' ' << m << std::endl;
        LIST L(n, s, m);
        L.Slove(fout);

        fin.close();
        fout.close();
    }
    return 0;
}