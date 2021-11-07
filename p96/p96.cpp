/*
 * 样例代码
 * 2021.9.28 张校
 */
#include <iostream>
#include <string>
using namespace std;
#define MAX_STRING_LENGTH 200

string str; // 输入字符串
char stack[MAX_STRING_LENGTH]; // 栈

void print_stack(const char *p)
{
    cout << "stack : " ;
    for( char *i = stack; i != p; i ++ )
        cout << *i;
    cout << endl;
}

int check_level(const char c) // 计算符号优先级
{
    switch( c )
    {
    case '!':
        return 2;
    case '&':
        return 1;
    case '|' : 
        return 0;
    default :
        return -1;
    }
    return -1;
}

int calculate_expression_by_level(char *&p, int level) // 计算栈中优先级高于level的所有式子
{
    bool base = *(-- p) == 'V';
    int now_level = 3; // 当前优先级
    while( p > stack )
    {
        if( *(p - 1) == '(')
        {
            if( level != -1 ) // 判断是否因为遇到')'而调用此函数
                break;
            if( p - 1 == stack ) // 判断栈是否触底
                now_level = 0;
            else
                now_level = check_level(*(p - 2)); // 需要返回括号前的优先级
            p --;
            break;
        }
        else if( *(p - 1) == '!' )
        {
            now_level = 2;
            base = base ^ true;
            p --;
        }
        else if( *(p - 1) == 'V' or *(p - 1) == 'F' )
        {
            if( now_level == 0 )
                base = base | ( *(-- p) == 'V' );
            else
                base = base & ( *(-- p) == 'V' );
        }
        else if( *(p - 1) == '&' )
        {
            now_level = 1;
            p --;
        }
        else
        {
            now_level = 0;
            if( level >= 1 )
                break;
            p --;
        }
    }
    *(p ++) = base ? 'V' : 'F';
    return now_level;
}

int main()
{
    int n = 0;
    // cin >> str; // 计算单个表达式
    while( getline(cin, str) )
    {
        int level = 0; // 当前运算
        char *p = stack; // 栈指针
        for( char *i = (char*)str.c_str(); *i != 0; i ++ )
        {
            switch( *i ) {
            case 'V' : case 'F' :
                *(p ++) = *i; // 符号入栈
                break;
            case '|' :
                if( level == 0 )
                {
                    *(p ++) = *i;
                }
                else
                {
                    calculate_expression_by_level(p, 0); // 计算栈中优先级高于|的式子
                    *(p ++) = *i;
                    level = 0;
                }
                break;
            case '&' :
                if( level <= 1 )
                {
                    *(p ++) = *i;
                    level = 1;
                }
                else
                {
                    calculate_expression_by_level(p, 1); // 计算栈中优先级高于&的式子
                    *(p ++) = *i;
                    level = 1;
                }
                break;
            case '!' :
                *(p ++) = *i;
                level = 2;
                break;
            case '(' :
                *(p ++) = *i;
                level = 0; // 计算优先级回到|
                break;
            case ')' :
                level = calculate_expression_by_level(p, -1); // 计算栈顶到'('之间的式子
                break;
            default :
                break;
            }
            // 打印分析过程
            // cout << *i << ' ';
            // print_stack(p);
        }
        calculate_expression_by_level(p, 0); // 计算栈中剩余式子
        cout << "Expression " << ++ n << ": " << *(-- p) << endl; 
    }
    
    return 0;
}
