#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>


namespace JumpList {
class CalculateIndexLevelByRandom {
public:
    /**
     * @brief   随机生成当前节点指针数组长度
     */
    int operator()(int size, int gap, int max_index_layers) {
        int index_level = 1;
        int rand_int = (rand() % size) >> gap;
        while (rand_int > 0 && (rand_int & 1) == 1) {
            index_level += 1;
            rand_int = rand_int >> gap;
        }
        return std::min(index_level, max_index_layers);
    }
};

template<class ValueType, class CalculateIndexLevel = CalculateIndexLevelByRandom>
class JumpList {
private:
    class Node {
    public:
        Node() : indexs_(1, nullptr) {}
        Node(const ValueType &value, int index_level = 1) : value_(value), indexs_(index_level, nullptr) {}
        Node(const ValueType &&value, int index_level = 1) : value_(value), indexs_(index_level, nullptr) {}
        ~Node() {
            if (indexs_[0] != nullptr) {
                delete indexs_[0];
            }
        }

        ValueType value_;
        
        std::vector<Node *> indexs_;
    };
public:
    JumpList() : max_index_layers_(10), size_(0), index_gap_(1) {}
    JumpList(int mil, int ig) : max_index_layers_(mil), size_(0), index_gap_(ig) {}
    ~JumpList() = default;

    int size() {
        return size_;
    }

    int getSearchTimes() {
        return search_times_;
    }

    void insertValue(ValueType &value)  {
        size_ += 1;
        if (size_ == 0) {
            head_.indexs_[0] = new Node(value);
        }
        else {
            std::vector<Node *> heads_list = findLowerBound(value);
            if (heads_list[0]->indexs_[0] != nullptr && heads_list[0]->indexs_[0]->value_ == value) {
                // 待插入数据已存在
                return;
            }
            int index_level = CalculateIndexLevel()(size_, index_gap_, max_index_layers_);
            Node *node = new Node(value, index_level);
            // 更新前序节点指针数组
            for (int i = 0; i < std::min(index_level, (int)heads_list.size()); i ++) {
                node->indexs_[i] = heads_list[i]->indexs_[i];
                heads_list[i]->indexs_[i] = node;
            }
            // 扩展头部指针数组
            for (int i = heads_list.size(); i < index_level; i ++) {
                if (head_.indexs_.size() <= i) {
                    head_.indexs_.push_back(node);
                }
                else {
                    head_.indexs_[i] = node;
                }
            }
        }
    }

    bool findValue(const ValueType &value) {
        if (size_ == 0) {
            return false;
        }
        std::vector<Node *> heads_list = findLowerBound(value);
        if (heads_list[0]->indexs_[0] != nullptr) {
            return heads_list[0]->indexs_[0]->value_ == value;
        }
        return false;
    }

    void deleteValue(ValueType &value) {
        if (size_ == 0) {
            return;
        }
        std::vector<Node *> heads_list(findLowerBound(value));
        if (heads_list[0]->indexs_[0] == nullptr || heads_list[0]->indexs_[0]->value_ != value) {
            // 待删除数据不存在
            return;
        }
        
        size_--;
        for (int i = 1; i < heads_list.size() && heads_list[i]->indexs_[i] != nullptr && heads_list[i]->indexs_[i]->value_ == value; i ++) {
            // 更新前序节点指针数组
            heads_list[i]->indexs_[i] = heads_list[0]->indexs_[0]->indexs_[i];
            heads_list[0]->indexs_[0]->indexs_[i] = nullptr;
        }
        Node *tmp = heads_list[0]->indexs_[0];
        heads_list[0]->indexs_[0] = tmp->indexs_[0];
        tmp->indexs_[0] = nullptr;
        delete tmp;
    }

private:
    /**
     * @brief   查找前序指针数组
    */
    std::vector<Node*> findLowerBound(const ValueType &value) {
        search_times_ = 0;
        std::vector<Node *> heads_list;
        Node *p = &head_;
        int index = head_.indexs_.size() - 1;
        while (index >= 0) {
            while (p->indexs_[index] != nullptr && p->indexs_[index]->value_ < value) {
                search_times_ += 1;
                p = p->indexs_[index];
            }
            heads_list.push_back(p);
            index--;
        }
        if (heads_list.size() > 1) {
            std::reverse(heads_list.begin(), heads_list.end());
        }
        return heads_list;
    }

    Node head_;

    int max_index_layers_;

    int size_;

    int index_gap_;

    int search_times_;
};

}


int main() {
    srand((unsigned)time(NULL));

    JumpList::JumpList<int> gl;
    for (int i = 0; i < 10000; i++) {
        gl.insertValue(i);
        std::cout << gl.getSearchTimes() << ' ';
        gl.findValue(i);
        std::cout << gl.getSearchTimes() << std::endl;
    }
    return 0;
}