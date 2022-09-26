/**
 * @file    p125_dp.cpp
 * @name    p125样例程序（使用动态规划求解）
 * @date    2022-09-25
 */

#include <iostream>
#include <vector>

class Solution {
public:
    Solution(std::string str) : s(str), max_length(0) {}
    ~Solution() {}

    void slove() {
        std::vector<int> dp(s.length());
        for( int i = 0; i < s.length(); i ++ ) {
            if( s[i] == '(' ) {
                continue;
            }

            if( i > 0 && s[i - 1] == '(' ) {
                dp[i] = (i > 1 ? dp[i - 2] : 0) + 2;
            }
            else if( i > 0 && i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(' ) {
                dp[i] = (i - dp[i - 1] - 2 >=0 ? dp[i - dp[i - 1] - 2] : 0) + dp[i - 1] + 2;
            }

            if( dp[i] > max_length ) {
                max_length = dp[i];
                start_index = i - max_length + 1;
            }
        }
    }

    int getMaxLength() { return max_length; }
    int getStartIndex() { return start_index; }
private:
    std::string s;
    int max_length, start_index;
};

int main() {
    std::string str;
    std::cin >> str;

    Solution solution(str);
    solution.slove();
    std::cout << solution.getMaxLength() << ' ' << solution.getStartIndex() << std::endl;
    return 0;
}
