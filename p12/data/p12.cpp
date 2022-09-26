/**
 * @name    p12.cpp
 */

#include <iostream>
#include <vector>

class LIST {
public:
    LIST(int n, int s, int m) : n_(n), s_(s - 1), m_(m) {
        list_.resize(n);
        for( int i = 0; i < n - 1; i ++ )
            list_[i] = i + 1;
        list_[n - 1] = 0;
    }

    void Slove(std::ostream &out) {
        int i = (s_ + n_ - 1) % n_;
        for( int j = n_; j > 1; j -- ) {
            for( int k = 1; k < (m_ - 1) % j + 1; k ++ )
                i = list_[i];
            out << list_[i] + 1 << ' ';
            list_[i] = list_[list_[i]];
        }
        out << i + 1 << std::endl;
    }
private:
    int n_, s_, m_;
    std::vector<int> list_;
};

int main() {
    int n, s, m;
    std::cin >> n >> s >> m;
    LIST L(n, s, m);
    L.Slove(std::cout);
    return 0;
}