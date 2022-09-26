#include <iostream>
#include <string>
using namespace std;

class Stack {
public:
    Stack(int size_) : size(size_)
    {
        len = 0;
        stack = new int[size_];
    }
    ~Stack() { delete[] stack; }

    bool push(int n)
    {
        if( len == size )
            return false;
        stack[len ++] = n;
        return true;
    }
    bool pop(int &n)
    {
        if( len == 0 )
            return false;
        n = stack[-- len];
        return true;
    }
    void show(ostream &out)
    {
        if( ! len )
            return ;
        out << stack[len - 1];
        for( int i = len - 2; i >= 0; i -- )
            out << ' ' << stack[i];
        out << endl;
    }
private:
    int *stack, len, size;
};

int main()
{
    int n;
    cin >> n;
    Stack s(n);
    while( true )
    {
        string ope;
        cin >> ope;
        if( ope == "quit" )
            break;
        if( ope == "push" )
        {
            cin >> n;
            if( ! s.push(n) )
                cout << "Stack is Full" << endl;
        }
        if( ope == "pop" )
        {
            if( ! s.pop(n) )
                cout << "Stack is Empty" << endl;
            else
                cout << n << endl;
        }
    }
    s.show(cout);
    return 0;
}
