/**
 * @file    p143_data.cpp
 * @brief   p143随机测试数据生成程序
 * @date    2023-12-12
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ctime>

class threeSum {
public:
    threeSum(int size) : array_(size), index_(size) {
        for (int i = 0; i < size; i ++){
            if (i > 1 && (rand() % 10) < 7) {
                int i1 = rand() % i;
                int i2 = rand() % i;
                while (i1 == i2) {
                    i2 = rand() % i;
                }
                array_[i] = -(array_[i1] + array_[i2]);
            } else {
                array_[i] = static_cast<int>(randUint() % RANGE) - static_cast<int>(1e5);
            }
        }

        std::iota(index_.begin(), index_.end(), 0);
        std::sort(index_.begin(), index_.end(), [this](int x, int y)
                  { return this->array_[x] < this->array_[y]; });
    }

    void printArray(std::ostream &out) {
        out << array_.size() << std::endl;
        out << array_.front();
        for (int i = 1; i < array_.size(); i ++) {
            out << ' ' << array_[i];
        }
        out << std::endl;
    }

    std::vector<std::vector<int>> solve() {
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < array_.size() - 2; ++i) {
            if (i > 0 && array_[index_[i]] == array_[index_[i - 1]]) {
                continue;
            }

            int l = i + 1;
            int r = array_.size() - 1;
            int n1 = array_[index_[i]];
            while (l < r) {
                int n2 = array_[index_[l]];
                int n3 = array_[index_[r]];
                if (n1 + n2 + n3 == 0) {
                    ans.push_back(std::vector<int>{n1, n2, n3});

                    do {
                        --r;
                    } while (l < r && array_[index_[r]] == array_[index_[r + 1]]);
                    do {
                        ++l;
                    } while (l < r && array_[index_[l]] == array_[index_[l - 1]]);
                } else if (n1 + n2 + n3 > 0) {
                    --r;
                } else {
                    ++l;
                }
            }
        }
        return ans;
    }
private:
    const static uint32_t RANGE=static_cast<uint32_t>(2e5);
    uint32_t randUint() {
        return (static_cast<uint32_t>(rand()) << 16) | static_cast<uint32_t>(rand());
    }

    std::vector<int> array_;
    std::vector<int> index_;
};

int main() {
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int size;
        if (index <= test_num * 0.2) {
            size = rand() % 6 + 15;
        } else if (index <= test_num * 0.4) {
            size = rand() % 11 + 90;
        } else {
            size = rand() % 101 + 2900;
        }

        threeSum tsum(size);
        tsum.printArray(fin);
        auto ans = tsum.solve();
        for (auto &p : ans) {
            fout << p[0] << ' ' << p[1] << ' ' << p[2] << std::endl;
        }

        fin.close();
        fout.close();
    }
    return 0;
}