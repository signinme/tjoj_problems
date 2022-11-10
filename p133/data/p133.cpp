#include <iostream>
#include <vector>

class Solution {
private:
    struct Node {
        std::vector<std::pair<int, int>> from;
        std::vector<std::pair<int, int>> to;
        bool result;
        int confirmations, checks;
        Node() : confirmations(1), checks(0) {} 
    };
    std::vector<Node> chart;
    std::vector<int> sorting_results;
public:
    int topologicalSorting(int n) {
        sorting_results.resize(n);
        std::queue<int> que;
        for( int i = 0; i < n; i ++ ) {
            if( chart[i].checks == 0 )
            que.push(i);
        }
        
        for( int i = 0; i < n; i ++ ) {
            if( que.empty() )
                return i;
            int index = que.front();
            que.pop();
            sorting_result[i] = index;
            if( index == 0 )
                return i + 1;
            for( auto &to : chart[index].to ) {
                if( chart[index].result != chart[to.second] ) { // 状态已经被确定
                    chart[to.first].confirmations = 0;
                    chart[to.first].checks = 0;
                }
                else {
                    chart[to.first].checks --;
                    if( chart[index].confirmations == 0 )
                        chart[to.first].confirmations --;
                }
                if( chart[to.first].checks == 0 )
                    que.push(to.first);
            }
        }
        return 0;
    }

    void getAssumptions(std::vector<int> &assumptions) {
        std::queue<std::pair<int, bool;>> que;
        que.push(std::pair<int, int>(0, true));
        while( !que.empty() ) {
            std::pair<int, bool> assumption = que.front();
            que.pop();
            for( auto from : chart[assumption.first].from ) {
                if( chart[from.first].confirmations != 0 ) {
                    if( assumption.second == chart[assumption.first].result ) {
                        que.push(std::pair<int, bool>(from.first, from.second));
                    }
                    else {
                        que.push(std::pair<int, bool>(from.first, !from.second));
                    }
                }
            }
        }
    }
    std::vector<std::vector<int>> Solve(int n, std::vector<std::vector<int>> &evidences, std::vector<std::vector<int>> &reasonings) {
        chart.resize(n);
        for( auto &evidence : evidences ) {
            chart[evidence[0]].result = evidence[1];
            chart[evidence[0]].confirmations = 0;
        }
        for( auto &reasoning : reasonings ) {
            chart[reasoning[0]].result = reasoning[1];
            chart[reasoning[0]].confirmations = chart[reasoning[0]].checks = reasioning.size() / 2 - 1;
            for( int i = 2; i < reasoning.size(); i += 2) {
                chart[reasoning[0]].from.push_back(std::pair<int, int>(reasoning[i], reasoning[i + 1]));
                chart[reasoning[i]].to.push_back(std::pair<int, int>(reasoning[0], reasoning[i + 1]));
            }
        }

        std::vector<std::vector<int>> ans(3);
        int index = topologicalSorting(n);
        if( index == 0 || sorting_results[index - 1] != 0 ) {
            ans[0][0] = 3;
        }
        else {
            if( chart[0].confirmations != 0 ) {
                ans[0][0] = 2;
                getAssumptions(ans[1]);
            }
            else {
                if( chart[0].result == true )
                    ans[0][0] = 0;
                else
                    ans[0][0] = 1;
            }
            ans[2].resize(index);
            for( int i = 0; i < index; i ++ )
                ans[2][i] = sort_result[i];
        }
    }

    bool checkAnswer(const std::vector<std::vector<int>> &ans) {

    }

};