/**
 * @file    p129_data.cpp
 * @name    p129随机测试数据生成程序
 * @date    20221014
 * @note    因为生成weights时没有做限制，程序运行有可能报错（over flow）低概率，多运行几次就好
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class ExpressionTree {
public:
    struct Node {
        char word;
        int height, weight;
        Node *left, *right;
        Node() : left(nullptr), right(nullptr) {}
        ~Node() {
            if( left != nullptr )
                delete left;
            if( right != nullptr )
                delete right;
        }

        void buildTree(int &index, int last_num) {
            if( last_num == 0 ) {
                word = 'a' + index ++;
                height = 1;
            }
            else {
                last_num --;
                switch(rand() % 10) {
                case 0:case 1:case 2:case 3:
                    word = '+';
                    break;
                case 4:case 5:case 6:
                    word = '-';
                    break;
                case 7:case 8:
                    word = '*';
                    break;
                case 9:
                default:
                    word = '/';
                    break;
                }
                int left_last_num = rand() % (last_num + 1);
                left = new Node();
                left->buildTree(index, left_last_num);
                right = new Node();
                right->buildTree(index, last_num - left_last_num);
                height = std::max(left->height, right->height) + 1;
            }
        }

        int generateWeight(int max_num) {
            if( left == nullptr )
                return weight = rand() % max_num + 1;
            switch(word) {
            case '+': return weight = left->generateWeight(max_num) + right->generateWeight(max_num);
            case '-': return weight = left->generateWeight(max_num) - right->generateWeight(max_num);
            case '*': return weight = left->generateWeight(max_num) * right->generateWeight(max_num);
            case '/':
                left->generateWeight(max_num);
                while( right->weight <= 0 )
                    right->generateWeight(left->weight);
                return weight = left->weight / right->weight;
            }
            return 1;
        }

        void displayExpressionOrigin(std::ostream &out, int parent_ope_level) {
            if( left == nullptr ) {
                out << word;
            }
            else {
                int this_ope_level = (word == '+' || word == '-' ? 1 : 2);
                if( this_ope_level <= parent_ope_level )
                    out << '(';
                left->displayExpressionOrigin(out, this_ope_level - 1);
                out << word;
                right->displayExpressionOrigin(out, this_ope_level);
                if( this_ope_level <= parent_ope_level )
                    out << ')';
            }
        }

        void displayExpression(std::ostream &out) {
            if( left == nullptr ) {
                out << word;
            }
            else {
                left->displayExpression(out);
                right->displayExpression(out);
                out << word;
            }
        }
        void displayWeights(std::ostream &out) {
            if( left == nullptr ) {
                out << word << ' ' << weight << std::endl;
            }
            else {
                left->displayWeights(out);
                right->displayWeights(out);
            }
        }
        /**
         * @brief   直接算出每个点的横坐标
         *          父节点和子节点横坐标只差为2^(height-2)
        */
        void getPrintQueue(std::vector<std::vector<std::pair<int, Node*>>> &print_que, int location, int height) {
            print_que[height - 1].push_back(std::make_pair(location, this));
            if( left != nullptr ) {
                left->getPrintQueue(print_que, location - (1 << (height - 2)), height - 1);
                right->getPrintQueue(print_que, location + (1 << (height - 2)), height - 1);
            }
        }
    };

    ExpressionTree(int n) {
        int index = 0, last_num = n - 1;
        root = new Node();
        root->buildTree(index, last_num);
    }

    int generateWeight(int max_num) {
        return root->generateWeight(max_num);
    }

    void displayExpressionOrigin(std::ostream &out) {
        root->displayExpressionOrigin(out, 0);
        out << std::endl;
    }
    void displayExpression(std::ostream &out) {
        root->displayExpression(out);
        out << std::endl;
    }

    void displayTree(std::ostream &out) {
        int height = root->height;
        std::vector<std::vector<std::pair<int, Node*>>> print_que(height);
        root->getPrintQueue(print_que, (1 << (height - 1)) - 1, height);
        for( int i = height - 1; i >= 0; i -- ) {
            for( int j = 0, k = 0; j < print_que[i].size(); j ++ ) {
                out << std::string(print_que[i][j].first - k, ' ');
                out << print_que[i][j].second->word;
                k = print_que[i][j].first + 1;
            }
            out << std::endl;
            if( i > 0 ) {
                for( int j = 0, k = 0; j < print_que[i].size(); j ++ ) {
                    out << std::string(print_que[i][j].first - k - 1, ' ');
                    if( print_que[i][j].second->left != nullptr )
                        out << "/ \\";
                    else
                        out << ' ' << ' ' << ' ';
                    k = print_que[i][j].first + 2;
                }
                out << std::endl;
            }
        }
    }

    void displayWeights(std::ostream &out) {
        root->displayWeights(out);
    }
private:
    Node* root;
};

int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for( int index = 1; index <= test_num; index ++ ) {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n, m;
        if( index <= test_num * 0.2 ) {
            n = 3;
            m = 5;
        }
        else if( index <= test_num * 0.4 ) {
            n = 5;
            m = 10;
        }
        else {
            n = 10;
            m = 100;
        }
        ExpressionTree ept(n);
        

        ept.displayExpression(fout);
        ept.displayTree(fout);
        fout << ept.generateWeight(m) << std::endl;

        ept.displayExpressionOrigin(fin);
        fin << n << std::endl;
        ept.displayWeights(fin);

        fin.close();
        fout.close();
    }
}