#include <iostream>
#include <cassert>
#include "Tuple.h"
int main()
{
    int data[] = {2,3,5,7,11,13,17,19,23};
    Tuple<int> a(data,9);
    Tuple<int> b = a*3;
    for (int i=0; i<9; i++) {
    }
    Tuple<int> c(data,9);
    c *= 3;
    assert(c == b);}

