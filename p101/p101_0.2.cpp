#include <iostream>
#include <sys/time.h>
using namespace std;

#define MAX_QUEUE_SIZE 10005

int queue[MAX_QUEUE_SIZE];

int main()
{
    // struct timeval timeStart, timeEnd, timeSystemStart; 
    // double runTime=0, systemRunTime; 
    // gettimeofday(&timeStart, NULL );

    int size;
    cin >> size;
    int head = 0, tail = 0;
    char ope[10];

    int last_max = false, last_number;
    while( true )
    {
        cin >> ope;
        if( ope[0] == 'q' )
            break;
        else if( ope[0] == 'e' )
        {
            last_max = false;
            int n;
            cin >> n;
            if( head % (size + 1) == (tail + 1) % (size + 1) )
                cout << "Queue is Full" << endl;
            else
            {
                queue[tail] = n;
                tail = (tail + 1) % (size + 1);
            }
        }
        else if( ope[0] == 'd' )
        {
            last_max = false;
            if( head == tail )
                cout << "Queue is Empty" << endl;
            else
            {
                cout << queue[head] << endl;
                head = (head + 1) % (size + 1);
            }
        }
        else if( ope[0] == 'm')
        {   
            if( head == tail )
                cout << "Queue is Empty" << endl;
            else if(last_max == true)
            {
                 cout << last_number << endl;
            }
            else
            {
                int max_num = queue[head];
                for( int i = head; i != tail; i = (i + 1) % (size + 1))
                {
                    if( queue[i] > max_num )
                        max_num = queue[i];
                }
                cout << max_num << endl;
                last_number = max_num;
            }
            
            last_max = true;
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

    // gettimeofday( &timeEnd, NULL ); 
    // runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;
    // printf("runTime is %lf s\n", runTime);         

}