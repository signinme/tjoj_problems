/**
 * @file    p126_data.cpp
 * @name    p126随机测试数据生成程序
 * @date    2022-09-27
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class Solution {
public:
    static const int MAX_NUM = 1000000;
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
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= 10; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file);
        std::ofstream fout(output_file);

        int n, m, max_num;
        if( index <= test_num * 0.2 ) {
            n = 5 + rand() % 6;
            m = 5 + rand() % 6;
            max_num = Solution::MAX_NUM * 0.0001;
        }
        else if( index <= test_num * 0.4 ) {
            n = 50 + rand() % 51;
            m = 50 + rand() % 51;
            max_num = Solution::MAX_NUM * 0.01;
        }
        else {
            n = 1000;
            m = 1000;
            max_num = Solution::MAX_NUM;
        }
        std::vector<int> nums(n);
        std::vector<int> queries(m);

        fin << n << ' ' << m << std::endl;
        for( int i = 0; i < n; i ++ ) {
            nums[i] = rand() % max_num + 1;
            fin << nums[i] << ' ';
        }
        fin << std::endl;
        for( int i = 0; i < m; i ++ ) {
            queries[i] = rand() % max_num + 1;
            fin << queries[i] << ' ';
        }
        fin << std::endl;
        
        Solution solution(nums, queries);
        solution.displayAnswere(fout);

        fin.close();
        fout.close();
    }
    return 0;
}