/**
 * @file    p126.cpp
 * @name    p126样例函数
 * @date    2022-09-27
 */

#include <iostream>
#include <algorithm>
#include <vector>

class Solution {
public:
    Solution(const std::vector<int> &nums, const std::vector<int> &queries) {
        std::vector<int> order_nums(nums);
        std::sort(order_nums.begin(), order_nums.end());
        std::vector<int> sum(nums.size());
        sum[0] = order_nums[0];
        for( int i = 1; i < order_nums.size(); i ++ ) {
            sum[i] = sum[i - 1] + order_nums[i];
        }
        ans.resize(queries.size());
        for( int i = 0; i < queries.size(); i ++ ) {
            ans[i] = std::upper_bound(sum.begin(), sum.end(), queries[i]) - sum.begin();
        }
    }

    void displayAnswere(std::ostream &out) {
        for( int i = 0; i < ans.size(); i ++ ) {
            out << ans[i] << ' ';
        }
        out << std::endl;
    }
private:
    std::vector<int> ans;
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> nums(n);
    std::vector<int> queries(m);
    for( int i = 0; i < n; i ++ ) {
        std::cin >> nums[i];
    }
    for( int i = 0; i < m; i ++ ) {
        std::cin >> queries[i];
    }
    Solution solution(nums, queries);
    solution.displayAnswere(std::cout);
    return 0;
}