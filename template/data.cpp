/**
 * @file    data.cpp
 * @name    随机测试数据生成程序模板
 * @author  张校
 * @date    2022-10-22
 * @brief   随机测试数据文件输出模板
*/

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        if( index <= test_num * 0.2 ) {

        }
        else if( index <= test_num * 0.4 ) {

        }
        else {

        }

        // 文件输出代码

        fin.close();
        fout.close();
    }
}