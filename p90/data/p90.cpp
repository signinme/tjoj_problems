#include <iostream>
using namespace std;

class SORTTREE {
public:
    struct NODE {
        NODE *left_, *right_, *parent_;
        int elem_, count_, height_;
        NODE(int elem, NODE *parent) : elem_(elem), parent_(parent) {
            left_ = NULL;
            right_ = NULL;
            count_ = 1;
            height_ = 0;
        }
        ~NODE() {
            if( left_ )
                delete left_;
            if( right_ )
                delete right_;
        }

        int Balance() {
            return - (left_ ? left_->height_ : 0) + (right_ ? right_->height_ : 0);
        }
        void UpdateHeight() {
            height_ =  std::max((left_ ? left_->height_ : 0), (right_ ? right_->height_ : 0));
        }
    };

    SORTTREE() { root_ = NULL; }
    ~SORTTREE() { delete root_; }

    void Insert(int elem) {
        if( ! root_ ) {
            root_ = new NODE(elem, NULL);
            return ;
        }
        NODE *p = Find(elem);
        if( p->elem_ == elem ) {
            p->count_ ++;
            return ;
        }

        if( p->elem_ > elem ) {
            p->left_ = new NODE(elem, p);
        }
        if( p->elem_ < elem ) {
            p->right_ = new NODE(elem, p);
        }
        while( p ) {
            p->UpdateHeight();
            if( -2 == p->Balance() || p->Balance() == 2 )
                break;
            p = p->parent_;
        }

        // 旋转
        if( p ) {
            if( p->Balance() == -2 ) {
                if( p->left_->Balance() == -1 ) {
                    RotateRight(p);
                }
                else {
                    RotateLeft(p->left_);
                    RotateRight(p);
                }
            }
            else {
                if( p->right_->Balance() == 1 ) {
                    RotateLeft(p);
                }
                else {
                    RotateRight(p->right_);
                    RotateLeft(p);
                }
            }
        }
    }
    
    bool Delete(int elem) {
        NODE *p = Find(elem);
        if( !p || p->elem_ != elem )
            return false;
        if( p->count_ > 1 ) {
            p->count_ --;
            return true;
        }

    }

    int Count(int elem) {
        NODE *p = Find(elem);
        if( p )
            return p->count_;
        return 0;
    }
    
    int FindMinElem() {
        if( ! root_ )
            return -1;
        NODE *p = root_;
        while( p->left_ )
            p = p->left_;
        return p->elem_;
    }

    int FindFrontElem(int elem) {
        NODE *p = Find(elem);
        if( p->elem_ < elem )
            return p->elem_;
        else {
            while( p->parent_ && p->parent_->elem_ > elem )
                p = p->parent_;
            if( ! p->parent_ )
                return -1;
            p = p->parent_;
            if( ! p->left_ )
                return p->elem_;
            do {
                p = p->left_;
            } while( ! p->right_ );
            do {
                p = p->right_;
            }while( p->parent_);
            return p->elem_;
        }
    }
private:
    void RotateRight(NODE *p) {
        NODE *t = p->left_;
        p->left_ = t->right_;
        t->right_ = p;
        UpdateRelation(p, t);
    }
    void RotateLeft(NODE *p) {
        NODE *t = p->right_;
        p->right_ = t->left_;
        t->left_ = p;
        UpdateRelation(p, t);
    }
    void UpdateRelation(NODE *p, NODE *t) {
        if( p->parent_ ) {
            if( p == p->parent_->left_ ) {
                p->parent_->left_ = t;
                t->parent_ = p->parent_;
            }
            else {
                p->parent_->right_ = t;
                t->parent_ = p->parent_;
            }
        }
        else {
            root_ = t;
            t->parent_ = NULL;
        }
        p->parent_ = t;
        p->UpdateHeight();
        t->UpdateHeight();
    }
    NODE *Find(int elem) {
        if( ! root_ )
            return NULL;
        NODE *p = root_;
        while( p->elem_ != elem ) {
            if( p->elem_ > elem && p->left_ )
                p = p->left_;
            else if( p->elem_ < elem && p->right_ )
                p = p->right_;
            else
                break;
        }
        return p;
    }
    NODE *FindLast() {

    }
    NODE *FindNext() {

    }
    NODE *root_;
};

int main()
{
    
}