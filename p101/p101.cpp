/**
 * 标题：队列中的最大值样例代码
 * 作者：张校
 * 时间：2021-10-7
 */

#include <iostream>
using namespace std;

#define MAX_QUEUE_SIZE 10005

int queue[MAX_QUEUE_SIZE];
int max_queue[MAX_QUEUE_SIZE];

int main()
{
    int size;
    cin >> size;
    int head = 0, tail = 0;
    int m_head = 0, m_tail = 0;
    char ope[10];
    while( true )
    {
        cin >> ope;
        if( ope[0] == 'q' )
            break;
        else if( ope[0] == 'e' )
        {
            int n;
            cin >> n;
            if( head % (size + 1) == (tail + 1) % (size + 1) )
                cout << "Queue is Full" << endl;
            else
            {
                queue[tail] = n;
                tail = (tail + 1) % (size + 1);
                while( m_tail != m_head && max_queue[(m_tail + size) % (size + 1)] < n)
                    m_tail = (m_tail + size) % (size + 1);
                max_queue[m_tail] = n;
                m_tail = (m_tail + 1) % (size + 1);
            }
        }
        else if( ope[0] == 'd' )
        {
            if( head == tail )
                cout << "Queue is Empty" << endl;
            else
            {
                cout << queue[head] << endl;
                
                if( max_queue[m_head] == queue[head] )
                    m_head = (m_head + 1) % (size + 1);
                head = (head + 1) % (size + 1);
            }
        }
        else if( ope[0] == 'm')
        {
            if( head == tail )
                cout << "Queue is Empty" << endl;
            else
            {
                cout << max_queue[m_head] << endl;
            }
        }
    }
    if( head == tail )
        cout << "Queue is Empty" << endl;
    else
    {
        cout << queue[head];
        for( int i = (head + 1) % (size + 1); i != tail; i = (i + 1) % (size + 1))
            cout << ' ' << queue[i];
        cout << endl;
    }
}