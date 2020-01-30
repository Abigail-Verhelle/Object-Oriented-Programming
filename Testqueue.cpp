#include <iostream>
#include "p2queue2.h"
using namespace std;

int main()
{
    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    cout << pop << endl;
    push(6);
    push(7);
    
    while(q.head != q.tail)
    {
        cout << pop << endl;
    }
    
}

