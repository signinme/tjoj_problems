/**
 * p44 队列的应用 随机测试数据生成程序
 * @author 张校
 * @date 2021-10-12
 * @brief   直接编译运行，生成随机10个测试数据
            本程序用深度优先搜索实现
 */

#include <iostream>
#include <fstream>
using namespace std;

class Soluction
{
public:
    Soluction() {}
private:
    bool dfs(bool *map, const int row, const int col, int loc)
    {
        if( map[loc] != true )
            return false;
        map[loc] = false;
        bool bo = false;

        int x = loc / col, y = loc % col, dir = 0;
        if( x > 0 )
        {
            bo |= dfs(map, row, col, loc - col);
            dir ++;
        }
        if( x < row - 1 )
        {
            bo |= dfs(map, row, col, loc + col);
            dir ++;
        }
        if( y > 0 )
        {
            bo |= dfs(map, row, col, loc - 1);
            dir ++;
        }
        if( y < col - 1 )
        {
            bo |= dfs(map, row, col, loc + 1);
            dir ++;
        }
        bo |= dir == 4;
        return bo;
    }
public:
    int soluction(bool *map, int row, int col)
    {
        int ans = 0;
        for( int i = 0; i < row * col; i ++ )
            if( map[i] == 1 && dfs(map, row, col, i) == true )
                ans ++;
        return ans;
    }
};


int main()
{
    char file_in[25], file_out[25];
    int test_num = 10; // 测试数据个数
    srand((unsigned int) time(NULL));
    Soluction s;
    for( int i = 1; i <= test_num; i ++ )
    {
        int row, col;
        if( i <= test_num  * 0.2 ) // 20% 的数据
        {
            row = rand() % 6 + 5;
            col = rand() % 6 + 5;
        }
        else if( i <= test_num * 0.4 ) // 40% 的数据
        {
            row = rand() % 26 + 75;
            col = rand() % 26 + 75;
        }
        else
        {
            row = rand() % 51 + 950;
            col = rand() % 51 + 950;
        }

        bool *map = new bool[row * col];
        for( int i = 0; i < row * col; i ++ )
        {
            map[i] = ((rand() % 100) <= 40);
        }
        
        sprintf(file_in, "input%d.txt", i);
        ofstream fin(file_in, ios::out);
        fin << row << ' ' << col << endl;
        for( int i = 0; i < row; i ++ )
        {
            fin << map[i * col + 0] ? '1' : '0';
            for( int j = 1; j < col; j ++ )
                fin << ' ' << map[i * col + j] ? '1' : '0';
            fin << endl;
        }
        fin.close();

        int ans = s.soluction(map, row, col);
        delete[] map;
        
        sprintf(file_out, "output%d.txt", i);
        ofstream fout(file_out, ios::out);
        fout << ans << endl;
        fout.close();
    }
    return 0;
}