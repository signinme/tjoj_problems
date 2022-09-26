/**
 * @name    p123_data.cpp
 * @brief   p123随机测试数据生成程序
 * @date    2022-04-17
 */
#include <iostream>
#include <fstream>
#include <vector>

class TREE {
public:
    struct NODE {
        int item_, layer_;
        NODE *parent_;
        std::vector<NODE*> children_;
        NODE(int item, int layer, NODE *parent = NULL) :
            item_(item), layer_(layer), parent_(parent) {}
        ~NODE() {}
    };

    TREE(int size) : total_num_nodes_(size), deepest_layer_(0), count_(0) {
        Shuffle(size);
        chart_.resize(size);
        Construct(size - 1, 0, NULL);
    }
    ~TREE() { for( auto node : chart_ ) delete node; }

    int FindAncestor(int item1, int item2) {
        NODE *node1 = chart_[item1 - 1];
        NODE *node2 = chart_[item2 - 1];
        int layer1 = node1->layer_;
        int layer2 = node2->layer_;
        while( layer1 < layer2 ) {
            node2 = node2->parent_;
            layer2 --;
        }
        while( layer1 > layer2 ) {
            node1 = node1->parent_;
            layer1 --;
        }
        while( node1 != node2 ) {
            node1 = node1->parent_;
            node2 = node2->parent_;
        }
        return node1->item_;
    }
    void PrintTree(std::ostream &out) {
        for( auto node : chart_ ) {
            for( auto child : node->children_ )
                out << node->item_ << ' ' << child->item_ << std::endl;
        }
    }
private:
    std::vector<int> name_list_;
    std::vector<NODE*> chart_;

    int total_num_nodes_;
    int deepest_layer_;
    int count_;

    /**
     * @brief 随机洗牌程序
     */
    void Shuffle(int size) {
        name_list_.resize(size);
        for( int i = 0; i < size; i ++ )
            name_list_[i] = i + 1;
        for( int i = size - 1; i > 0; i -- ) {
            int j = rand() % (i + 1);
            int t = name_list_[i];
            name_list_[i] = name_list_[j];
            name_list_[j] = t;
        }
    }
    NODE *Construct(int size, int layer, NODE *parent) {
        deepest_layer_ = std::max(deepest_layer_, layer);
        NODE *node = new NODE(name_list_[count_], layer, parent);
        chart_[name_list_[count_ ++] - 1] = node;
        
        if( size == 0 )
            return node;
        
        int num_child = (rand() % std::min(size, std::max(total_num_nodes_ / 5, 2))) + 1;
        size -= num_child;
        for( int i = 0; i < num_child - 1; i ++ ) {
            int child_size = rand() % (size + 1);
            node->children_.push_back(Construct(child_size, layer + 1, node));
            size -= child_size;
        }
        node->children_.push_back(Construct(size, layer + 1, node));
        return node;
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

        int T, max_n, min_n, max_m, min_m;
        if( index <= test_num * 0.2 ) {
            T = 2;
            max_n = 15;
            min_n = 10;
            max_m = 10;
            min_m = 5;
        }
        else if( index <= test_num * 0.4 ) {
            T = 10;
            max_n = 100;
            min_n = 70;
            max_m = 100;
            min_m = 50;
        }
        else {
            T = 100;
            max_n = 1000;
            min_n = 900;
            max_m = 1000;
            min_m = 500;
        }
        fin << T << std::endl;
        while( T -- ){
            int n = rand() % (max_n - min_n + 1) + min_n;
            int m = rand() % (max_m - min_m + 1) + min_m;
            fin << n << ' ' << m << std::endl;
            TREE t(n);
            t.PrintTree(fin);
            while( m -- ) {
                int item1 = rand() % n + 1;
                int item2 = rand() % n + 1;
                int ancestor = t.FindAncestor(item1, item2);
                fin << item1 << ' ' << item2 << std::endl;
                fout << ancestor << std::endl;
            }
        }
        fin.close();
        fout.close();
    }
}