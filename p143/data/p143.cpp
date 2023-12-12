/**
 * @file    p143.cpp
 * @brief   p143样例程序
 * @date    2023-12-12
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

class threeSum {
public:
    threeSum(const std::vector<int> &array) : array_(array), index_(array.size()) {
        std::iota(index_.begin(), index_.end(), 0);
        std::sort(index_.begin(), index_.end(), [this](int x, int y)
                  { return this->array_[x] < this->array_[y]; });
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
    const std::vector<int> &array_;
    std::vector<int> index_;
};

int main() {
    int size;
    std::cin >> size;
    std::vector<int> array(size);
    for (int i = 0; i < size; i ++) {
        std::cin >> array[i];
    }
    threeSum tsum(array);
    auto ans = tsum.solve();
    for (auto &p : ans) {
        std::cout << p[0] << ' ' << p[1] << ' ' << p[2] << std::endl;
    }

    return 0;
}