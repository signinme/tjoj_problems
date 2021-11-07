/**
 * p97 样例程序
 * @author 张校
 * @date 2021-10-17
 * @brief
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
using namespace std;

class FAMILY_TREE { // 保存一堆颗家族树
public:
    static const int MAX_CHILDREN_NUM = 70; // 研究表明，在一夫一妻的情况下，一个个体至多只能有70个后代
    
    struct MEMBER {
        static const char separator = ' ';
        int layer; // 当前成员辈分
        string name; // 当前成员名字
        MEMBER *parent; // 当前成员长辈
        vector<MEMBER *> kids_list; // 当前成员孩子列表
        MEMBER(const string &n_ = string("root"), MEMBER *p_ = NULL, int l_ = 0) : name(n_), parent(p_), layer(l_) {}
        ~MEMBER() { clear(); }
        /**
         * void clear()
         * @brief 删除所有孩子
         */
        void clear() { for( auto i : kids_list ) delete i; }

        /**
         * MEMBER *insert(string &n_)
         * @brief 插入一个新成员
         * @param string &n_ 新成员名字
         * @return 新成员指针
         */
        MEMBER *insert(const string &n_) {
            kids_list.push_back(new MEMBER(n_, this, layer + 1));
            return kids_list.back();
        }

        /**
         * void show()
         * @brief 打印当前节点和其所有孩子
         */
        void show() {
            for( int i = 0; i < layer; i ++ )
                cout << separator;
            cout << name << endl;
            for( auto i : kids_list )
                i->show();
        }
    };

    /**
     * @brief 获取root节点指针
     */
    MEMBER *get_root() { return &root; }
    /**
     * MEMBER *insert(MEMBER *p, string name)
     * @brief 插入一个成员
     * @param MEMBER *p   父节点指针
     * @param string name 新成员名字
     * @return 新成员指针
     */
    MEMBER *insert(MEMBER *p, const string &name) { return (name_map[name] = p->insert(name)); }

    /**
     * 5个判断函数
     * @brief 判断两个成员的关系
     * @param string n1 第一个成员名字
     * @param string n2 第二个成员名字
     * @return 关系是否成立
     */
    bool is_child(const string &n1, const string &n2)   { return name_map[n1]->parent == name_map[n2]; }
    bool is_parent(const string &n1, const string &n2)  { return is_child(n2, n1); }
    bool is_sibling(const string &n1, const string &n2) { return name_map[n1]->parent == name_map[n2]->parent; }
    bool is_descendant(const string &n1, const string &n2)
    {
        MEMBER *p = name_map[n1];
        for( int i = 0; i < name_map[n1]->layer - name_map[n2]->layer; i ++ )
            p = p->parent;
        return p == name_map[n2];
    }
    bool is_ancestor(const string &n1, const string &n2) { return is_descendant(n2, n1); }
    /**
     * bool hava_member(string name)
     * @brief 判断名字是否存在于家族树
     * @param string name 名字
     * @return 是否存在
     */
    bool hava_member(const string &name) { return name_map.find(name) != name_map.end(); }

    /**
     * 2个show展示函数
     * @brief 打印所有家族树或名字表
     */
    void show_family_tree() { root.show(); }
    void show_name_map() { for(auto i : name_map) cout << i.first << ' ' << i.second << endl; }
    
    FAMILY_TREE() {}
    ~FAMILY_TREE() {}

private:
    MEMBER root; // 根节点（注意，实际上，这个家族树是可以保存多个家族的，但根据题目要求，只有一个）
    map<string, MEMBER*> name_map; // 名字列表，根据名字获取成员指针
};

/**
 * inline int trim(string &s)
 * @brief 去除首空格和尾部分割符
 * @param string &s 操作的字符串
 * @return 字符串前分隔符个数
 */
inline int trim(string &s)
{
    int n = s.find_first_not_of(" \t");
    s.erase(0, n);
    s.erase(s.find_last_not_of(" .\r\n\t") + 1);
    return n;
}

int main()
{
    int n, m; string name;
    while( true )
    {
        cin >> n >> m;
        if( n == 0 && m == 0 )
            break;
        while( getchar() != '\n'); // 读取掉前两个数后的换行
        FAMILY_TREE ft; // 家族树
        FAMILY_TREE::MEMBER *pointer = ft.get_root(); // 初始父节点
        int layer = 0; // 计算辈分
        stack<FAMILY_TREE::MEMBER *> st;
        /**
         * 输入家族树
         * @brief 每输入一个新成员，就将其父节点压入栈中，然后尝试读取其孩子
         *        如果发现输入不是当前节点的子节点，则弹出对应个数的父节点
         */
        while( n -- )
        {
            int i = 0;
            getline(cin, name);
            i = trim(name); // 计算当前成员辈分，获取名字
            while( i < layer ) // 获取其父母成员
            {
                layer --;
                pointer = st.top();
                st.pop();
            }
            st.push(pointer); // 将其父母成员压入栈中，准备读取其字节点
            pointer = ft.insert(pointer, name); // 将其加入家族树，获取其节点指针作为下一轮读取的父节点
            layer ++;
        }

        string name1, name2, ope, t;
        while( m -- )
        {
            cin >> name1 >> t >> t >> ope >> t >> name2; // 读取两个名字和需要判断的关系
            trim(name2); // 删掉第二个名字后面的'.'和换行符等
            bool ans = false;
            if( ft.hava_member(name1) && ft.hava_member(name2) ) // 判断两个成员是否都在成员树中
            {
                switch(ope[0]) // 判断两个成员关系
                {
                case 'c' : ans = ft.is_child(     name1, name2); break;
                case 'p' : ans = ft.is_parent(    name1, name2); break;
                case 's' : ans = ft.is_sibling(   name1, name2); break;
                case 'a' : ans = ft.is_ancestor(  name1, name2); break;
                case 'd' : ans = ft.is_descendant(name1, name2); break;
                default: break;
                }
            }
            cout << (ans ? "True" : "False") << endl;
        }
        cout << endl; // 不要忘记打印空行
    }
    return 0;
}