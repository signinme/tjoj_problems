/**
 * p77 示例程序
 * @author 张校
 * @date 2021-10-25
 * @brief
 */
#include <iostream>
using namespace std;

struct Node {
    Node* next;
    int p, e;
    Node() { next = NULL; }
    Node(int p_, int e_, Node *n_ = NULL) : p(p_), e(e_), next(n_) {}
    ~Node() { if( next != NULL) delete next; }
};

class List {
private:
    Node head;
public:
    List() { head.next = NULL; }
    ~List() { clear(); }
    void clear()
    {
        if( head.next != NULL)
            delete head.next;
        head.next = NULL;
    }
    void push(int p, int e, bool rev = false) // 维护一个有序链表
    {
        if( head.next == NULL ) // 队列为空，直接插入链表头
        {
            head.next = new Node(p, e, NULL);
            return ;
        }
        else
        {
            Node *i = &head;
            while( i->next != NULL && (!rev && i->next->e <= e || rev && i->next->e >= e) )
                i = i->next;
            
            if( i->e == e ) // 多项式中存在指数相同项
                i->p += p;
            else
                i->next = new Node(p, e, i->next);
        }
    }

    void merge(const List &l)
    {
        Node* p1 = &head, *p2 = l.head.next;
        while( p1->next != NULL && p2 != NULL )
        {
            if( p2->e == p1->next->e )
            {
                p1->next->p += p2->p;
                p1 = p1->next;
                p2 = p2->next;
            }
            else if( p2->e > p1->next->e )
                p1 = p1->next;
            else
            {
                p1->next = new Node(p2->p, p2->e, p1->next);
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        if( p1->next == NULL )
        {
            while( p2 != NULL )
            {
                p1->next = new Node(p2->p, p2->e, NULL);
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }

    void revert()
    {
        Node *p = head.next;
        head.next = NULL;
        while( p != NULL )
        {
            Node *t = head.next;
            head.next = p;
            p = p->next;
            head.next->next = t;
        }
    }

    void show()
    {
        for( Node *p = head.next; p != NULL; p = p->next )
            if( p->p != 0 )
                cout << p->p << ' ' << p->e << ' ';
        cout << endl;
    }
    // 这里注意一下，如果class中含有指针，这样传参时一定要用引用，或者直接传地址
    // 因为如果直接传clas，这个参数在函数结束时会调用析构函数，在析构函数中会把原来的内存也销毁了！！！
    // 在这里，因为参数l1和main函数中申明的l1中head.next是一样的！！！
    static void add(const List &l1, const List &l2, List &l3) // 相加，分别加入
    {
       l3.merge(l1);
       l3.merge(l2);
    }

    static void mul(const List &l1, const List &l2, List &l4) // 相乘，双重for循环
    {
        List lt;
        for( Node *i = l1.head.next; i != NULL; i = i->next )
        {
            lt.clear();
            for( Node *j = l2.head.next; j != NULL; j = j->next )
                lt.push(i->p * j->p, i->e + j->e , true); // 系数相乘，指数相加
            lt.revert();
            l4.merge(lt);
        }
    }
};

int main()
{
    int n, m;
    List l1, l2, l3, l4;
    cin >> n; // 输入第一个多项式长度
    while( n -- ) // 输入第一个多项式
    {
        int p, e;
        cin >> p >> e;
        l1.push(p, e);
    }
    cin >> m; // 输入第二个多项式长度
    while( m -- ) // 输入第二个多项式
    {
        int p, e;
        cin >> p >> e;
        l2.push(p, e);
    }
    int ope;
    cin >> ope;
    // 当opo == 0 时，可以直接foreach(i in l1) l2.push(i); l2.show()
    if( ope % 2 == 0 ) { List::add(l1, l2, l3); l3.show(); } // 相加
    if( ope >= 1     ) { List::mul(l1, l2, l4); l4.show(); } // 相乘
    return 0;
}