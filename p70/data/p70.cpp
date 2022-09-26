/**
 * p70 样例代码
 * @author 张校
 * @date 2021-10-17
 * @brief 里面有一些中文输入输出的问题似乎没有解决
 */

#include <iostream>
#include <cstring>
using namespace std;
 
#define MAX_LIST_LENGTH 20000
#define MAX_NAME_LENGTH 10
 
class LIST {
public:
    struct STUDENT {
        char no[MAX_NAME_LENGTH], name[MAX_NAME_LENGTH];
        STUDENT() {
            no[0]   = '\0';
            name[0] = '\0';
        }
        STUDENT(const STUDENT &item) {
            strcpy(no  , item.no  );
            strcpy(name, item.name);
        }
        STUDENT operator=(const STUDENT &item) {
            strcpy(no  , item.no  );
            strcpy(name, item.name);
            return *(this);
        }
        bool operator==(const STUDENT &item) {
            return (!strcmp(no, item.no) || !item.no[0]) && (!strcmp(name, item.name) || !item.name[0]);
        }
    };
    
    LIST() {
        len = 0;
        memset(list, 0, sizeof(list));
    }
 
    void clear()
    {
        while( len ) delete list[-- len];
        len = 0;
    }
 
    int insert(int index, const STUDENT &stu)
    {
        if( index > len + 1 || index < 1 )
            return -1;
        len ++;
        for( int i = len - 1; i >= index; i -- )
            list[i] = list[i - 1];
        list[index - 1] = new STUDENT(stu);
        return 0;
    }
 
    int remove(int index, STUDENT &stu)
    {
        if( index > len || index < 1 )
            return -1;
        stu = *(list[index - 1]);
        delete list[index - 1];
        for( int i = index - 1; i < len - 1; i ++ )
            list[i] = list[i + 1];
        len --;
        return 0;
    }
 
    int check(STUDENT &stu)
    {
        for( int i = 0; i < len; i ++ )
            if( *list[i] == stu )
            {
                stu = *list[i];
                return i + 1;
            }
        return -1;
    }
 
    int length() { return len; }
private:
    int len;
    STUDENT *list[MAX_LIST_LENGTH] = {0};
};
 
int main()
{
    LIST list;
    int n;
    char ope[10];
    cin >> n;
    for( int i = 0; i < n; i ++ )
    {
        LIST::STUDENT stu;
        cin >> stu.no >> stu.name;
        list.insert(i + 1, stu);
    }
    while( true )
    {
        cin >> ope;
        if( ope[0] == 'e' )
            break;
        LIST::STUDENT stu;
        int index;
        if( ope[0] == 'i' )
        {
            cin >> index >> stu.no >> stu.name;
            cout << list.insert(index, stu) << endl;
        }
        else if( ope[0] == 'r' )
        {
            cin >> index;
            cout << list.remove(index, stu) << endl;
        }
        else if( ope[0] == 'c' )
        {
            cin >> ope;
            if( ope[1] == 'a' )
                cin >> stu.name;
            else
                cin >> stu.no;
            if( (index = list.check(stu)) != -1 )
                cout << index << ' ' << stu.no << ' ' << stu.name << endl;
            else
                cout << -1 << endl;
        }
    }
 
    cout << list.length() << endl;
    return 0;
}