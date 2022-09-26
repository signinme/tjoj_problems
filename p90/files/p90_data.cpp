/**
 * @name    p90_data.cpp
 * @brief   p90 随机测试数据生成程序
 * @author  张校
 * @date    2021-12-11
 */

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

/**
 * @brief 平衡二叉排序树
 */
class SORTTREE {
public:
    static const int MAX_ELEM = 100000;
    static const int RANDOM_GAP = 10; // 尽量保证 MAX_ELEM / RANDOM_GAP > n
    struct NODE {
        NODE *left_, *right_, *parent_;
        int elem_, count_, height_;
        NODE(int elem, NODE *parent) : elem_(elem), parent_(parent) {
            left_ = NULL;
            right_ = NULL;
            count_ = 1;
            height_ = 1;
        }
        ~NODE() {
            if( left_ )
                delete left_;
            if( right_ )
                delete right_;
        }
        /**
         * @brief 计算平衡度
         */
        int Balance() {
            return - (left_ ? left_->height_ : 0) + (right_ ? right_->height_ : 0);
        }
        /**
         * @brief 更新节点高度
         */
        void UpdateHeight() {
            height_ = std::max((left_ ? left_->height_ : 0), (right_ ? right_->height_ : 0)) + 1;
        }
        /**
         * @name    bool Find(int elem, NODE *&last, NODE *&thiss, NODE *&next, bool &found)
         * @brief   查找一个元素的对应前驱、对应节点、对应后续节点
         * @param   elem 待查找的元素
         * @param   last 前驱，若没有则为NULL，需要初始化为NULL
         * @param   thiss 对应节点，若没有则为NULL
         * @param   next 后继，若没有则为NULL，需要初始化为NULL
         * @param   found 是否已经找到，true表示已经找到，接下来递归找到后继节点就退出
         * @return  是否找到后继，查找结束
         */
        bool Find(int elem, NODE *&last, NODE *&thiss, NODE *&next, bool &found) {
            if( left_ )
                if( left_->Find(elem, last, thiss, next, found) )
                    return true;
            if( found ) { // 已经找到，该节点即为后继节点，所有节点都找到，遍历退出
                next = this;
                return true;
            }
            if( elem_ > elem ) { // 没有对应节点，找到前驱和后继，遍历退出
                thiss = NULL;
                next = this;
                return true;
            }
            if( elem_ == elem ) { // 找到对应节点，需要遍历右子树找后继
                thiss = this;
                found = true;
            }
            else
                last = this; // 没有找到对应节点，当前节点值小于查找元素，暂时设为前驱
            if( right_ )
                return right_->Find(elem, last, thiss, next, found);
            return false; // 查找还未结束
        }
    };

    SORTTREE() { root_ = NULL; }
    ~SORTTREE() { delete root_; }
    /**
     * @brief 插入一个元素
     */
    void Insert(int elem) {
        if( ! root_ ) {
            root_ = new NODE(elem, NULL);
            return ;
        }
        NODE *l = NULL, *p = NULL, *n = NULL;
        bool found = false;
        root_->Find(elem, l, p, n, found);
        
        if( p ) {
            p->count_ ++;
            return ;
        }
        // 前驱的右孩子和后继的左孩子之中一定有一个为空，将新节点插入
        if( l && !l->right_) {
            p = (l->right_ = new NODE(elem, l));
        }
        else {
            p = (n->left_ = new NODE(elem, n));
        }
        KeepBalance(p);
    }
    /**
     * @brief 删除一个元素
     */
    bool Delete(int elem) {
        if( ! root_ )
            return false;
        NODE *l = NULL, *p = NULL, *n = NULL;
        bool found = false;
        root_->Find(elem, l, p, n, found);
        if( !p ) // 没找到
            return false;
        if( p->count_ > 1 ) { // 待删除元素不止一个，计数减一即可
            p->count_ --;
            return true;
        }
        // 待删除元素只有一个，需要删除节点
        if( !p->left_ && !p->right_ ) { // 待删除节点为叶子节点
            if( ! p->parent_ ) {
                root_ = NULL;
            }
            else {
                ChangeParent(p, NULL);
                KeepBalance(p->parent_);
            }
        }
        else if( !p->left_ ) { // 没有左子树，无法用前驱代替自己，用右子树代替自己
                               // 如果没有右子树，也可以直接用左子树代替自己
            ChangeParent(p, p->right_);
            KeepBalance(p->parent_);
        }
        else { // 有左子树，则前驱一定在左子树中，用前驱代替自己
            if( p->left_ == l ) { // 前驱就是左孩子
                l->right_ = p->right_;
                if( p->right_ )
                    p->right_->parent_ = l;
                ChangeParent(p, l);
                KeepBalance(l);
            }
            else { // 找到前驱，用前驱代替自己，处理亲子关系
                NODE *t = l->parent_;
                t->right_ = l->left_;
                if( l->left_ )
                    l->left_->parent_ = t;

                l->left_ = p->left_;
                p->left_->parent_ = l;
                l->right_ = p->right_;
                if( p->right_ )
                    p->right_->parent_ = l;

                ChangeParent(p, l);
                KeepBalance(t);
            }
        }
        p->left_ = p->right_ = NULL;
        delete p;
        return true;
    }
    /**
     * @brief 元素计数
     */
    int Count(int elem) {
        if( ! root_ )
            return 0;
        NODE *l = NULL, *p = NULL, *n = NULL;
        bool found = false;
        root_->Find(elem, l, p, n, found);
        if( p )
            return p->count_;
        return 0;
    }
    /**
     * @brief 查找最小元素
     */
    int FindMinElem() {
        if( ! root_ )
            return -1;
        NODE *p = root_;
        while( p->left_ )
            p = p->left_;
        return p->elem_;
    }
    /**
     * @brief 查找前驱元素
     */
    int FindFrontElem(int elem) {
        if( ! root_ )
            return -1;
        NODE *l = NULL, *p = NULL, *n = NULL;
        bool found = false;
        
        root_->Find(elem, l, p, n, found);
        if( l )
            return l->elem_;
        return -1;
    }
private:
    /**
     * @brief 保持树的平衡
     * @param p 可能失衡的最低节点
     */
    void KeepBalance(NODE *p) {
        while( p ) {
            p->UpdateHeight();
            if( -2 >= p->Balance() || p->Balance() >= 2 ) {
                // 旋转
                if( p->Balance() < 0 ) {
                    if( p->left_->Balance() <= 0 ) {
                        RotateRight(p);
                    }
                    else {
                        RotateLeft(p->left_);
                        RotateRight(p);
                    }
                }
                else {
                    if( p->right_->Balance() >= 0 ) {
                        RotateLeft(p);
                    }
                    else {
                        RotateRight(p->right_);
                        RotateLeft(p);

                    }
                }
            }
            p = p->parent_;
        }
    }
    /**
     * @brief 右旋转
     */
    void RotateRight(NODE *p) {
        NODE *t = p->left_;
        p->left_ = t->right_;
        if( t->right_ )
            t->right_->parent_ = p;
        t->right_ = p;
        UpdateRelation(p, t);
    }
    /**
     * @brief 左旋转
     */
    void RotateLeft(NODE *p) {
        NODE *t = p->right_;
        p->right_ = t->left_;
        if( t->left_ )
            t->left_->parent_ = p;
        t->left_ = p;
        UpdateRelation(p, t);
    }
    /**
     * @brief 更新旋转后节点关系
     */
    void UpdateRelation(NODE *p, NODE *t) {
        ChangeParent(p, t);
        p->parent_ = t;
        p->UpdateHeight();
        t->UpdateHeight();
    }
    /**
     * @brief 用将p的家族关系赋予t
     */
    void ChangeParent(NODE *p, NODE *t) {
        if( t )
            t->parent_ = p->parent_;
        if( p->parent_ ) {
            if( p == p->parent_->left_ ) 
                p->parent_->left_ = t;
            else 
                p->parent_->right_ = t;
        }
        else
            root_ = t;
    }
    NODE *root_;
};

int RandomElem(std::map<int, int> &M) {
    if( ! M.size() )
        return rand() % SORTTREE::MAX_ELEM + 1;
    std::map<int, int>::iterator it = M.begin();
    std::advance(it, rand() % M.size());
    return (*it).first;
}

int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n;
        if( index <= test_num * 0.2 ) {
            n = rand() % 6 + 15;
        } else if( index <= test_num * 0.4 ) {
            n = rand() % 11 + 90;
        } else if( index <= test_num * 0.6 ) {
            n = rand() % 51 + 500;
        } else {
            n = rand() % 101 + 900;
        }
        fin << n << std::endl;

        SORTTREE &T = *(new SORTTREE);
        std::map<int, int> M;

        int last_insert;
        for( int i = 0; i < n; i ++) {
            int ope, elem = 0, last = 0;
            // 接下来生成随机操作
            if( index % 2 == 0 ) { // 一般的数据会考察树的性能，即输入数据是有序的
                if( i == 0 ) {
                    ope = 1;
                    if( index % 4 == 0 ) 
                        elem = SORTTREE::MAX_ELEM - rand() % SORTTREE::RANDOM_GAP;
                    else
                        elem = rand() % SORTTREE::RANDOM_GAP;
                    last_insert = elem;
                }
                else if( i <= 0.7 * n ) { // 前70%操作中绝大部分为插入，且插入数据基本有序
                    int select = rand() % 20;
                    if( select < 16 ) {
                        ope = 1;
                        if( index % 4 == 0 ) { 
                            elem = std::max(1, last_insert - (rand() % (12 * SORTTREE::RANDOM_GAP) - SORTTREE::RANDOM_GAP));
                            last_insert = std::min(last_insert, elem);
                        }
                        else {
                            elem = last_insert + (rand() % (12 * SORTTREE::RANDOM_GAP) - SORTTREE::RANDOM_GAP);
                            last_insert = std::max(last_insert, elem);
                        }
                    }
                    else if( select == 16 ) {
                        ope = 2;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                    else if( select == 17 ) {
                        ope = 3;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                    else if( select == 18 ) {
                        ope = 4;
                    }
                    else {
                        ope = 5;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                }
                else { // 后一半数据中查找居多，且基本位于树底端
                    int select = rand() % 20;
                    if( select < 2 ) {
                        ope = 1;
                        if( rand() % 3 != 0 ) {
                            if( index % 4 == 0 ) { 
                                elem = last_insert + (rand() % (12 * SORTTREE::RANDOM_GAP) - SORTTREE::RANDOM_GAP);
                                last_insert = std::max(last_insert, elem);
                            }
                            else {
                                elem = last_insert - (rand() % (12 * SORTTREE::RANDOM_GAP) - SORTTREE::RANDOM_GAP);
                                last_insert = std::min(last_insert, elem);
                            }
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if( select < 4 ) {
                        ope = 2;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                    else if( select < 14 ) {
                        ope = 3;
                        if( index % 4 == 0 ) {
                            elem = rand() % int(SORTTREE::MAX_ELEM * 0.2);
                        }
                        else {
                            elem = SORTTREE::MAX_ELEM - rand() % int(SORTTREE::MAX_ELEM * 0.2);
                        }
                    }
                    else if( select == 14 ) {
                        ope = 4;
                    }
                    else {
                        ope = 5;
                        elem = rand() % SORTTREE::MAX_ELEM;
                    }
                }
            }
            else {
                if( i <= n * 0.1 || i > n * 0.3 && i <= n * 0.5 ) {
                    int select = rand() % 20;
                    if( select < 16 ) {
                        ope = 1;
                        if( rand() % 3 < 2 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if( select == 16 ) {
                        ope = 2;
                        if( rand() % 4 < 1 ) {
                            elem = RandomElem(M);
                        }
                        else {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                    else if( select == 17 ) {
                        ope = 3;
                        if( rand() % 4 < 1 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if( select == 18 ) {
                        ope = 4;
                    }
                    else if( select == 19 ) {
                        ope = 5;
                        elem = T.FindMinElem();
                        if( rand() % 5 != 0 || elem == -1 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                }
                else if( i <= n * 0.3 ) {
                    int select = rand() % 20;
                    if( select < 16 ) {
                        ope = 2;
                        if( rand() % 7 < 1 ) {
                            elem = RandomElem(M);
                        }
                        else {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                    else if( select == 16 ) {
                        ope = 1;
                        if( rand() % 3 < 2 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if( select == 17 ) {
                        ope = 3;
                        if( rand() % 4 < 1 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if( select == 18 ) {
                        ope = 4;
                    }
                    else if( select == 19 ) {
                        ope = 5;
                        elem = T.FindMinElem();
                        if( rand() % 5 != 0 || elem == -1 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                }
                else {
                    int select = rand() % 10;
                    if( select < 3 ) {
                        ope = 1;
                        if( rand() % 3 < 2 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if( select < 5 ) {
                        ope = 2;
                        if( rand() % 4 < 1 ) {
                            elem = RandomElem(M);
                        }
                        else {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                    else if( select == 6 ) {
                        ope = 3;
                        if( rand() % 4 < 1 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                        else {
                            elem = RandomElem(M);
                        }
                    }
                    else if( select == 7 ) {
                        ope = 4;
                    }
                    else {
                        ope = 5;
                        elem = T.FindMinElem();
                        if( rand() % 5 != 0 || elem == -1 ) {
                            elem = rand() % SORTTREE::MAX_ELEM;
                        }
                    }
                }
            }
            fin << ope;
            if( ope != 4 )
                fin << ' ' << elem;
            fin << std::endl;

            switch( ope ) {
            case 1:
                T.Insert(elem);
                if( M.find(elem) != M.end() )
                    M[elem] ++;
                else
                    M[elem] = 1;
                break;
            case 2:
                if( ! T.Delete(elem) )
                    fout << "None" << std::endl;
                if( M.find(elem) != M.end() ) {
                    if( M[elem] > 0 )
                        M[elem] --;
                    else
                        M.erase(elem);
                }
                break;
            case 3:
                fout << T.Count(elem) << std::endl;
                break;
            case 4:
                fout << T.FindMinElem() << std::endl;
                break;
            case 5:
                last = T.FindFrontElem(elem);
                if( last == -1 )
                    fout << "None" << std::endl;
                else
                    fout << last << std::endl;
                break;
            default:
                break;
            }
        }
        delete &T;
        fin.close();
        fout.close();
    }
    return 0;
}