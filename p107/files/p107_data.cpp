/**
 * @name   p107随机测试数据生成程序
 * @author 张校
 * @date   2021-10-28
 * @brief  使用方法：直接编译运行
 */
#include <iostream>
#include <fstream>
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
    void FixOrderSort() { for( auto &i : map ) std::sort(i.begin(), i.end()); }
    void FixOrderReverse() { for( auto &i : map ) std::reverse(i.begin(), i.end()); }
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
    /**
     * @brief 打印边
     */
    void PrineLine(std::ostream &out) {
        for( int i = 0; i < size; i ++ )
            for( auto j : map[i])
                if( j > i )
                    out << i << ' ' << j << std::endl;
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
    int test_num = 10; // 测试点个数
    for( int i = 1; i <= test_num; i ++ ) {
        std::string file_in = "input" + std::to_string(i) + ".txt";
        std::string file_out = "output" + std::to_string(i) + ".txt";
        std::ofstream fin(file_in), fout(file_out);

        int n, m;
        if( i <= test_num * 0.2 ) {
            n = rand() % 5 + 11;
        }
        else if( i <= test_num * 0.4 ) {
            n = rand() % 10 + 91;
        }
        else {
            n = rand() % 100 + 900;
        }
        m = n * (rand() % 100 + 51) / 100;

        fin << n << ' ' << m << std::endl;

        Picture *pic = new Picture(n);
        while( m -- ){
            int s = rand() % n;
            int e;
            while((e = rand() % n) == s);
            pic->InsertLine(s, e);
            pic->InsertLine(e, s);
        }
        pic->FixOrderSort();
        pic->PrineLine(fin);
        // pic->FixOrderReverse();
        Picture::GROUP_SET groupdfs, groupbfs;
        pic->Search(Picture::SEARCH_TYPE::dfs, groupdfs);
        pic->Search(Picture::SEARCH_TYPE::bfs, groupbfs);
        Picture::PrintGroupSet(fout, groupdfs);
        Picture::PrintGroupSet(fout, groupbfs);

        fin.close();
        fout.close();
        delete pic;
    }
    return 0;
}