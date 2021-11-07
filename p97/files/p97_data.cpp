/**
 * p97 随机测试数据生成程序
 * @author 张校
 * @date 2021-10-17
 * @brief
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
using namespace std;

#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))

class FAMILY_TREE { // 保存一堆颗家族树
public:
    static const int MAX_CHILDREN_NUM = 30; // 研究表明，在一夫一妻的情况下，一个个体至多只能有30个后代
    static const int MAX_MEMBER_NUM = 10000; // 最大成员数（最多生成多少个名字）
    static vector<string> names; // 随机名字列表
    static vector<string> operations; // 关系列表

    struct MEMBER {
        static const char separator = ' ';
        int layer; // 当前成员辈分
        string name; // 当前成员名字
        MEMBER *parent; // 当前成员长辈
        vector<MEMBER *> kids_list; // 当前成员孩子列表
        MEMBER(const string &n_ = "root", MEMBER *p_ = NULL, int l_ = 0) : name(n_), parent(p_), layer(l_) {}
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
        void show(ostream &f) {
            for( int i = 0; i < layer; i ++ )
                f << separator;
            if( name != "root")
                f << name << endl;
            for( auto i : kids_list )
                i->show(f);
        }
        /**
         * gen_member(int n, int &id)
         * @brief 生成一个成员的所有子成员
         * @param int n 剩余成员个数
         * @param int &id 现成员id
         */
        int gen_member(int n, int &id, FAMILY_TREE &ft)
        {
            id ++;
            ft.name_map[name] = this;
            if( n == 0 )
                return layer;
            int deepth = 0;
            int kids = rand() % int(min(n, MAX_CHILDREN_NUM * max(0.1, min(1.0, n / 3000)))) + 1;
            int last = n - kids;
            while( kids )
            {
                int tmp = last;
                if( -- kids != 0 )
                    tmp = rand() % (last + 1);
                last -= tmp;
                kids_list.push_back(new MEMBER(names[id], this, layer + 1));
                int t = kids_list.back()->gen_member(tmp, id, ft);
                deepth = max(deepth, t);
            }
            return deepth + 1;
        }
    };

    /**
     * MEMBER *insert(MEMBER *p, string name)
     * @brief 插入一个成员
     * @param MEMBER *p   父节点指针
     * @param string name 新成员名字
     * @return 新成员指针
     */
    MEMBER *insert(MEMBER *p, const string &name) { return (name_map[name] = p->insert(name)); }

    /**
     * void walk(int up_lenth, int down_lenth, const string &name1, string &name2)
     * @brief 在家族树起点开始随机行走以生成另一随机点
     * @param int up_lenth 向上行走步数
     * @param int down_lenth 向下行走步数
     * @param string &name1 起点
     * @param string &name2 终点
     */
    void walk(int up_lenth, int down_lenth, const string &name1, string &name2)
    {
        MEMBER *p = name_map[name1];
        while( up_lenth -- && p->parent != &root )
            p = p->parent;
        while( down_lenth -- && ! p->kids_list.empty())
            p = p->kids_list[rand() % (p->kids_list.size())];
        name2 = p->name;
    }

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
        for( int i = 0; i < name_map[n1]->layer - name_map[n2]->layer; i ++ ) // n1向上一定辈分后是否是n2
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
    void show_family_tree(ostream &f) { root.show(f); }
    void show_name_map() { for(auto i : name_map) cout << i.first << ' ' << i.second << endl; }
    
    /**
     * gen_family_tree()
     * @brief 生成一颗家族树
     */
    int gen_family_tree(int n)
    {
        clear();
        n = min(n, FAMILY_TREE::MAX_MEMBER_NUM);
        int id = 0;
        root.kids_list.push_back(new MEMBER(names[id], &root, id));
        return root.kids_list.back()->gen_member(n - 1, id, *this);
    }

    /**
     * write_name_list()
     * @brief 生成随机名字列表
     */
    static void write_name_list()
    {
        for( int i = 1; i <= FAMILY_TREE::MAX_MEMBER_NUM; i ++ )
        {
            string name;
            int n = i;
            while( n )
            {
                if( n % 2 == 0 )
                    name += char('A' + (n % 26));
                else
                    name += char('a' + (n % 26));
                name += 'A' + (rand() % 2) * 32 + (rand() % 26);
                name += 'A' + (rand() % 2) * 32 + (rand() % 26);
                n /= 26;
            }
            for( int j = name.length(); j < 9; j ++ )
                name += '_';
            FAMILY_TREE::names.push_back(name);
        }
    }
    
    FAMILY_TREE() {}
    ~FAMILY_TREE() {} // 因为root不是指针，在FAMILY TREE析构时root会自动析构

    void clear()
    {
        name_map.clear();
        root.clear();
    }

private:
    MEMBER root; // 根节点（注意，实际上，这个家族树是可以保存多个家族的，但根据题目要求，只有一个）
    map<string, MEMBER*> name_map; // 名字列表，根据名字获取成员指针
};
vector<string> FAMILY_TREE::names;
vector<string> FAMILY_TREE::operations = {"a child", "the parent", "a sibling", "an ancestor", "a descendant"};
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
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试数据个数
    FAMILY_TREE::write_name_list();
    for( int index = 1; index <= test_num; index ++ )
    {
        string file_input = "input" + to_string(index) + ".txt";
        string file_output = "output" + to_string(index) + ".txt";
        ofstream fin(file_input.c_str()), fout(file_output.c_str());

        int test_set_num;
        if( index <= test_num * 0.2 )
            test_set_num = 1;
        else if( index <= test_num * 0.4 )
            test_set_num = 5;
        else
            test_set_num = 10;

        while( test_set_num -- )
        {
            int n, m;
            if( index <= test_num * 0.2 ){
                n = (rand() % 5) + 15;
                m = (rand() % 5) + 35;
            }
            else if( index <= test_num * 0.4 ){
                n = (rand() % 10) + 90;
                m = (rand() % 10) + 190;
            }
            else{
                n = (rand() % 100) + 9901;
                m = (rand() % 100) + 9901;
            }
            fin << n << ' ' << m << endl;
            FAMILY_TREE ft; // 家族树
            int deepth = ft.gen_family_tree(n); // 生成一颗家族树

            ft.show_family_tree(fin);
            for( int i = 0; i < m; i ++)
            {
                int ope = rand() % 5;
                string name1 = FAMILY_TREE::names[rand() % n], name2;
                // 这里因为随机出一个正确的关系几乎不可能，所以尽量人为控制关系成立与否
                // 但本程序的这种控制不是100%正确的，可以想想为什么
                if( rand() % 2 == 0 ) { // 尝试生成一段错误关系
                    ft.walk(rand() % deepth, rand() % deepth, name1, name2);
                }
                else { // 尝试生成一段正确关系
                    switch(ope) {
                        case 0: ft.walk(1, 0, name1, name2); break;
                        case 1: ft.walk(0, 1, name1, name2); break;
                        case 2: ft.walk(rand() % (deepth / 2), rand() % (deepth / 2), name1, name2); break;
                        case 3: ft.walk(0, rand() % deepth, name1, name2); break;
                        case 4: ft.walk(rand() % deepth, 0, name1, name2); break;
                    }
                }
                fin << name1 << " is " << FAMILY_TREE::operations[ope] << " of " << name2 << "." << endl;
                int ans = false;
                if( ft.hava_member(name1) && ft.hava_member(name2) ) // 判断两个成员是否都在成员树中
                {
                    switch(ope) // 判断两个成员关系
                    {
                        case 0 : ans = ft.is_child(     name1, name2); break;
                        case 1 : ans = ft.is_parent(    name1, name2); break;
                        case 2 : ans = ft.is_sibling(   name1, name2); break;
                        case 3 : ans = ft.is_ancestor(  name1, name2); break;
                        case 4 : ans = ft.is_descendant(name1, name2); break;
                        default: break;
                    }
                }
                fout << (ans ? "True" : "False") << endl;
            }
            fout << endl; // 不要忘记打印空行
        }
        fin << "0 0" << endl;
        fin.close();
        fout.close();
    }
    return 0;
}