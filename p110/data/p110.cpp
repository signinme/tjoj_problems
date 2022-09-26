/**
 * @name    p110.cpp
 * @brief   p110样例程序
 * @author  张校
 * @date    2021-12-7
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

class List {
public:
    List() = default;
    ~List() {}
    /**
     * @brief   清空数组
     */
    void Clear() {
        list_.clear();
    }
    /**
     * @brief   在数组尾部插入一个元素
     */
    void PushBack(int elem) {
        list_.push_back(elem);
    }
    /**
     * @brief   寻找元素最后一个出现的下标
     * @return  找到：下标；找不到：-1；
     */
    int UpperBound(int elem) {
        int l = 0, r = list_.size() - 1;
        while( l != r && list_[l] >= elem && list_[r] <= elem ) {
            int m = (l + r) / 2;
            if( list_[m + 1] <= elem )
                l = m + 1;
            else
                r = m;
        }
        r = (list_[r] == elem ? r : -1);
        return r;
    }
    /**
     * @brief   寻找元素第一个出现的下标
     * @return  找到：下标；找不到：-1；
     */
    int LowerBound(int elem) {
        int l = 0, r = list_.size() - 1;
        while( l != r && list_[l] >= elem && list_[r] <= elem ) {
            int m = (l + r) / 2;
            if( list_[m] >= elem )
                r = m;
            else
                l = m + 1;
        }
        l = (list_[l] == elem ? l : -1);
        return l;
    }
private:
    std::vector<int> list_;
};

int main()
{
    int n;
    List &L = *(new List());
    std::cin >> n;
    while( n -- ) {
        int elem;
        std::cin >> elem;
        L.PushBack(elem);
    }
    while( 1 ) {
        std::string ope;
        std::cin >> ope;
        if( ope == "done" )
            break;
        
        int elem;
        std::cin >> elem;
        if( ope == "upper" )
            std::cout << L.UpperBound(elem) << std::endl;
        if( ope == "lower" )
            std::cout << L.LowerBound(elem) << std::endl;
    }
    delete &L;
    return 0;
}