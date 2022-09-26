/**
 * @name    p5_data.cpp
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

class LIST {
public:
    static const int MAX_N = 100000;
    LIST(const std::vector<int> &list) {
        std::set<int> chart;
        for( auto i : list )
            if( chart.find(i) == chart.end() ) {
                list_.push_back(i);
                chart.insert(i);
            }
    }
    ~LIST() = default;

    void PrintList(std::ostream &out) {
        for( auto i : list_ )
            out << i << ' ';
        out << std::endl;
    }
private:
    std::vector<int> list_;
};

int main() {
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n;
        if( index <= test_num * 0.2 ) {
            n = 10 + rand() % 11;
        }
        else if( index <= test_num * 0.4 ) {
            n = 90 + rand() % 11;
        }
        else if( index <= test_num * 0.6) {
            n = 9000 + rand() % 1001;
        }
        else {
            n = 49000 + rand() % 1001;
        }
        int bias = rand();
        fin << n << std::endl;
        std::vector<int> list(n);
        for( auto &i : list ) {
            i = bias + rand() % std::min(n, 10001);
            fin << i << ' ';
        }
        LIST L(list);
        L.PrintList(fout);

        fin.close();
        fout.close();
    }
}