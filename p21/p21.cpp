#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
    stack<char> s;
    string input, output;
    cin >> input;
    while( cin >> output )
    {
        while( s.size() > 0 ) s.pop();
        int i = 0, j = 0;
        while( j < output.length() )
        {
            if( s.size() > 0 && s.top() == output[j] )
            {
                s.pop();
                j ++;
            }
            else if( i < input.length() )
                s.push(input[i ++]);
            else break;
        }
        cout << ( j == output.length() ? "yes" : "no" ) << endl;
    }
    return true;
}