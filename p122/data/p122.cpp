/**
 * @name    p122.cpp
 * @brief   p122示例代码
 * @date    2022-04-17
 */
#include <iostream>
#include <string>

class TREE {
public:
    struct NODE {
        char item_;
        NODE *left_, *right_;
        NODE(char item, NODE *left = NULL, NODE *right = NULL) :
            item_(item), left_(left), right_(right) {}
        ~NODE() {
            if( left_ )
                delete left_;
            if( right_ )
                delete right_;
        }
        void PrintNode(std::ostream &out) {
            if( left_ )
                left_->PrintNode(out);
            if( right_ )
                right_->PrintNode(out);
            out << item_;
        }
    };

    TREE(const std::string &P, const std::string &M) {
        error_ = false;
        root_ = Construct(P, M, 0, 0, P.length());
        if( error_ && root_ ) {
            delete root_;
            root_ = NULL;
        }
    }
    ~TREE() {
        if( root_ )
            delete root_;
    }
    void PrintTree(std::ostream &out) {
        if( ! root_ )
            return ;
        root_->PrintNode(out);
        out << std::endl;
    }
    bool IsError() {
        return error_;
    }
private:
    NODE *root_;
    bool error_;
    NODE *Construct(const std::string &P, const std::string &M, int i, int j, int length) {
        if( length == 0 )
            return NULL;
        if( length == 1 ) {
            if( P[i] == M[j] )
                return new NODE(P[i], NULL, NULL);
            error_ = true;
            return NULL;
        }
        int l = 0;
        while( l < length && M[j + l] != P[i] )
            l ++;
        if( l == length ) {
            error_ = true;
            return NULL;
        }
        return new NODE(P[i], Construct(P, M, i + 1, j, l), Construct(P, M, i + 1 + l, j + 1 + l, length - l - 1));
    }
};

int main() {
    std::string F, M;
    while( std::cin >> F >> M ) {
        TREE t(F, M);
        if( t.IsError() )
            std::cout << "Error" << std::endl;
        else
            t.PrintTree(std::cout);
    }
    return 0;
}