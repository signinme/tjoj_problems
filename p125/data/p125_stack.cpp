/**
 * @file    p125_stack.cpp
 * @name    p125样例程序（使用栈求解）
 * @date    2022-09-25
 */

#include <iostream>
#include <vector>
#include <stack>

class Solution {
public:
    Solution(std::string str) : s(str), max_length(0) {}
    ~Solution() {}

    void slove() {
        std::stack<int> st;
        int head = -1;
        for( int i = 0; i < s.size(); i ++ ) {
            if( s[i] == '(' ) {
                st.push(i);
            }
            else {
                if( st.empty() ) {
                    head = i;
                }
                else {
                    st.pop();
                    if( st.empty() ) {
                        if( max_length < i - head ) {
                            max_length = i - head;
                            start_index = head + 1;
                        }
                    }
                    else {
                        if( max_length < i - st.top() ) {
                            max_length = i - st.top();
                            start_index = st.top() + 1;
                        }
                    }
                }
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