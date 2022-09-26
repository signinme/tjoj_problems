/**
 * @name   p107样例程序
 * @author 张校
 * @date   2021-10-28
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>

class Picture {
public:
    enum SEARCH_TYPE {dfs, bfs};
    typedef std::vector<int>              GROUP_TYPE;
    typedef std::vector<std::vector<int>> GROUP_SET;
    /**
     * @brief 查找
     */
    void Search(SEARCH_TYPE type, GROUP_SET &groups) {
        std::set<int> S;
        for( int i = 0; i < size; i ++ )
            if( S.find(i) == S.end() )
            {
                groups.push_back(GROUP_TYPE());
                if( type == SEARCH_TYPE::dfs )
                    SearchByDfs(i, S, groups.back());
                else
                    SearchByBfs(i, S, groups.back());
            }
    }
    /**
     * @brief 插入一条边
     */
    void InsertLine(int s, int t) { map[s].push_back(t); }
    void FixOrder() {
        for( auto &i : map ) {
            // std::sort(i.begin(), i.end());
            std::reverse(i.begin(), i.end());
        }
    }
    /**
     * @brief 打印组和组中元素
     */
    static void PrintGroupSet(std::ostream &out, GROUP_SET &groups) {
        for( auto &group : groups ) {
            out << '{' << group.front();
            for( GROUP_TYPE::iterator i = group.begin() + 1; i != group.end(); i ++ )
                out << ' ' << *i;
            out << '}';
        }
        out << std::endl;
    }
    void Clear() { map.clear(); }
    Picture(const int n) : size(n) { for( int i = 0; i < n; i ++ ) map.push_back(std::vector<int>()); }
    ~Picture() { Clear(); }
private:
    int size;
    std::vector<std::vector<int>> map;
    /**
     * @brief 使用BFS搜索
     */
    void SearchByBfs(int start, std::set<int> &S, GROUP_TYPE &G) {
        std::queue<int> Q;
        Q.push(start);
        while( ! Q.empty() ) {
            int now = Q.front();
            Q.pop();
            if( S.find(now) != S.end() )
                continue;
            S.insert(now);
            G.push_back(now);
            for( auto i : map[now] )
                Q.push(i);
        }
    }
    /**
     * @brief 使用DFS搜索
     */
    void SearchByDfs(int now, std::set<int> &S, GROUP_TYPE &G) {
        if( S.find(now) != S.end() )
            return ;
        S.insert(now);
        G.push_back(now);
        for( auto i : map[now] )
            SearchByDfs(i, S, G);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Picture *pic = new Picture(n);
    while( m -- ){
        int s, e;
        std::cin >> s >> e;
        pic->InsertLine(s, e);
        pic->InsertLine(e, s);
    }
    // pic->FixOrder();
    Picture::GROUP_SET groupdfs, groupbfs;
    pic->Search(Picture::SEARCH_TYPE::dfs, groupdfs);
    pic->Search(Picture::SEARCH_TYPE::bfs, groupbfs);
    Picture::PrintGroupSet(std::cout, groupdfs);
    Picture::PrintGroupSet(std::cout, groupbfs);

    delete pic;
    return 0;
}