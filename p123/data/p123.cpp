/**
 * @name    p123.cpp
 * @brief   p123示例代码
 * @date    2022-04-17
 */
#include <iostream>
#include <map>

class TREE {
public:
    struct NODE {
        int item_, layer_;
        NODE *parent_;
        NODE(int item, NODE *parent = NULL) :
            item_(item), layer_(0), parent_(parent) {}
        ~NODE() {}

        int GetLayer() {
            if( layer_ )
                return layer_;
            if( parent_ == NULL )
                return layer_ = 1;
            return layer_ = parent_->GetLayer() + 1;
        }
    };

    TREE() {}
    ~TREE() { for( auto node : chart_ ) delete node.second; }

    void Insert(int parent, int child) {
        if( chart_.find(parent) == chart_.end() )
            chart_[parent] = new NODE(parent, NULL);
        if( chart_.find(child) == chart_.end() )
            chart_[child] = new NODE(child, chart_[parent]);
        else
            chart_[child]->parent_ = chart_[parent];
    }

    int FindAncestor(int item1, int item2) {
        NODE *node1 = chart_[item1];
        NODE *node2 = chart_[item2];
        int layer1 = node1->GetLayer();
        int layer2 = node2->GetLayer();
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
private:
    std::map<int, NODE*> chart_;
};

int main() {
    int T;
    std::cin >> T;
    while( T -- ) {
        TREE t;
        int n, m;
        std::cin >> n >> m;
        while( -- n ) {
            int parent, child;
            std::cin >> parent >> child;
            t.Insert(parent, child);
        }
        while( m -- ) {
            int item1, item2;
            std::cin >> item1 >> item2;
            std::cout << t.FindAncestor(item1, item2) << std::endl;
        }
    }
    return 0;
}