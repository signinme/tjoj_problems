/**
 * @name    p5.cpp
 **/

#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> list(n);
    for( auto &i : list )
        std::cin >> i;
    int bias = 0;
    for( int i = 0; i < list.size(); i ++ ) {
        int j = i - 1;
        while( j >= 0 && list[j] != list[i] )
            j --;
        if( j < 0 )
            list[i - bias] = list[i];
        else
            bias ++;
    }
    for( int i = 0; i < list.size() - bias; i ++ )
        std::cout << list[i] << ' ';
    std::cout << std::endl;
    return 0;
}