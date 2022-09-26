#include <iostream>
#include <fstream>
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
        /**
         * @brief   打印树
         */
        void PrintNode(std::ostream &out, int order) {
            if( order == 0 ) out << item_;
            if( left_ ) left_->PrintNode(out, order);
            if( order == 1 ) out << item_;
            if( right_ ) right_->PrintNode(out, order);
            if( order == 2 ) out << item_;
        }
        /**
         * @brief   仅交换一个节点的左右子树以保证原树先序和交换后树中序无法构建二叉树
         */
        bool MakeError() {
            bool e1 = false, e2 = false, e3 = false;
            if( left_ && right_ && rand() % 10 <= 2 ) {
                NODE *t = left_;
                left_ = right_;
                right_ = t;
                return true;
            }
            if( left_ && left_->MakeError() )
                return true;
            if( right_ && right_->MakeError() )
                return true;
            return false;
        }
    };

    TREE(int length) {
        Shuffle();
        count_ = 0;
        root_ = Construct(length);
    }
    ~TREE() {
        if( root_ )
            delete root_;
    }
    void PrintTree(std::ostream &out, int order) {
        if( ! root_ )
            return ;
        root_->PrintNode(out, order);
    }
    bool MakeError() {
        if( root_ )
            return root_->MakeError();
        else
            return false;
    }
private:
    NODE *root_;
    int count_;
    std::string name_list_;
    /**
     * @brief 随机洗牌
     */
    void Shuffle() {
        name_list_ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        for( int i = 60; i > 0; i -- ) {
            int j = rand() % (i + 1);
            char temp = name_list_[i];
            name_list_[i] = name_list_[j];
            name_list_[j] = temp;
        }
    }
    NODE *Construct(int length) {
        if( length == 0 )
            return NULL;
        if( length == 1 )
            return new NODE(name_list_[count_ ++], NULL, NULL);
        int l = rand() % length;
            return new NODE(name_list_[count_ ++], Construct(l), Construct(length - l - 1));
    }
};

int main() {
    srand((unsigned) time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file);
        std::ofstream fout(output_file);

        int num, max_length, min_length;
        if( index <= test_num * 0.2 ) {
            num = 5;
            max_length = 10;
            min_length = 3;
        }
        else if( index <= test_num * 0.4 ) {
            num = 10;
            max_length = 20;
            min_length = 10;
        }
        else {
            num = 1000;
            max_length = 61;
            min_length = 55;
        }

        while( num -- ) {
            TREE t(rand() % (max_length - min_length + 1) + min_length);
            t.PrintTree(fin, 0); fin << ' ';
            if( rand() % 10 <= 2 && t.MakeError() ) {
                t.PrintTree(fin, 1); fin << std::endl;
                fout << "Error" << std::endl;
            }
            else {
                t.PrintTree(fin, 1); fin << std::endl;
                t.PrintTree(fout, 2); fout << std::endl;
            }
        }
        fin.close();
        fout.close();
    }
}