/**
 * @file    p129.cpp
 * @name    p129样例程序
 * @date    20221014
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>

class ExpressionTree {
public:
    struct Node {
        char word;
        int height;
        Node *left, *right;
        Node(char w, Node *l = nullptr, Node *r = nullptr ) : word(w), left(l), right(r) {
            if( left != nullptr )
                height = std::max(left->height, right->height) + 1;
            else
                height = 1;
        }
        ~Node() {
            if( left != nullptr )
                delete left;
            if( right != nullptr )
                delete right;
        }

        int calculateExpression(std::map<char, int> &chart) {
            switch(word) {
            case '+': return left->calculateExpression(chart) + right->calculateExpression(chart);
            case '-': return left->calculateExpression(chart) - right->calculateExpression(chart);
            case '*': return left->calculateExpression(chart) * right->calculateExpression(chart);
            case '/': return left->calculateExpression(chart) / right->calculateExpression(chart);
            default : return chart[word];
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

    ExpressionTree(std::string &str) {
        int index = 0;
        root = buildTree(str, index);
    }

    int calculateExpression(std::map<char, int> &chart) {
        return root->calculateExpression(chart);
    }

    void displayExpression(std::ostream &out) {
        root->displayExpression(out);
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

private:
    Node* root;
    Node *buildTree(std::string &str, int &index) {
        std::vector<Node *> st(3); // 栈里最多三个变量
        int pointer = 0;
        char idel_ope, ope; // 栈里最多两个符号
        while( index < str.length() ) {
            if( str[index] >= 'a' && str[index] <= 'z' ) {
                st[pointer ++] = new Node(str[index ++]);
            }
            else {
                if( pointer == 3 ) { // 栈里有三个变量时合并
                    st[1] = new Node(ope, st[1], st[2]);
                    pointer = 2;
                    ope = idel_ope;
                }
                    
                if( str[index] == '+' || str[index] == '-' || str[index] == '*' || str[index] == '/' ) {
                    if( pointer == 2 ) {
                        if( str[index] == '+' || str[index] == '-' || ope == '*' || ope == '/' ) {
                            st[0] = new Node(ope, st[0], st[1]);
                            pointer = 1;
                        }
                        else {
                            idel_ope = ope;
                        }
                    }
                    ope = str[index ++];
                }
                else if( str[index] == '(' ) {
                    st[pointer ++] = buildTree(str, ++ index);
                }
                else if( str[index] == ')' ) {
                    index ++;
                    if( pointer == 2 ) {
                        return new Node(ope, st[0], st[1]);
                    }
                    else if( pointer == 1 ) {
                        return st[0];
                    }
                    else { // build error
                        return nullptr;
                    }
                }
                else {
                    index ++;
                }
            }
            
        }
        std::cerr << "build error" << std::endl;
        return nullptr;
    }
};

int main() {
    std::string expression;
    std::cin >> expression;
    expression += ')';
    ExpressionTree ept(expression);

    int m;
    std::cin>> m;
    std::map<char, int> chart;
    while( m -- ) {
        char c;
        int value;
        std::cin >> c >> value;
        chart[c] = value;
    }

    ept.displayExpression(std::cout);
    std::cout << std::endl;
    ept.displayTree(std::cout);

    std::cout << ept.calculateExpression(chart) << std::endl;
    return 0;
}