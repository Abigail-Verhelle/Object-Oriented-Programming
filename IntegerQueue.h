#include <iostream>
class IntegerQueue
{
    
// mine
private:
    
    int *queue;
    int head, tail, qlength;
 
//mine and yours
public:
    
    IntegerQueue();
    IntegerQueue(const IntegerQueue &other);
    ~IntegerQueue();
    void push(int N);
    int pop();
    bool empty()const;
    int size()const;
    IntegerQueue& operator=(const IntegerQueue &other);
    friend std::ostream& operator<<(std::ostream& os, const IntegerQueue &other);
};
