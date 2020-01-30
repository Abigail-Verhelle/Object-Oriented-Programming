#include <iostream>
#include <cassert>
#include "IntegerQueue.h"
using namespace std;

IntegerQueue::IntegerQueue()
{
    
    queue = new int[10];
    head = 0;
    tail = 0;
    qlength = 10;
    
}
// constuctur for coping over
IntegerQueue::IntegerQueue(const IntegerQueue &other)
{
    head = other.head - other.tail;
    tail = 0;
    qlength = other.qlength;
    queue = new int[qlength];
    
    for (int i = other.tail;i < other.head;i++){
        
        queue[i - other.tail] = other.queue[i];
    }
}
IntegerQueue::~IntegerQueue()
{
    delete [] queue;
    queue = NULL;
    head = 0;
    tail = 0;
    
}
void IntegerQueue:: push(int N)
{
    //if full make the queue bigger
    if (head == qlength)
    {
        int noolength = 0;
        int* noo = new int[qlength*2];
        int noosize = size();
        
        // copy the queue over to the new one
        for (int j = 0; head != tail; j++)
        {
            noo[j] = queue[tail];
            tail++;
        }
        delete [] queue;
        
        //reassigning variables after doubling
        queue = noo;
        head = noosize;
        qlength *= 2;
        tail = 0;
        
    }
   
    //pushing into orignal array
    queue[head] = N;
    head++;
    
}
int IntegerQueue::pop()
{
    return queue[tail++];
}
bool IntegerQueue::empty() const
{
    return (tail == head);
}
int IntegerQueue::size() const
{
    return (head - tail);
}
IntegerQueue& IntegerQueue::operator=(const IntegerQueue &other)
{
    //doesn't match copy over
    if(queue != other.queue)
    {
        delete[] queue;
        
        head = other.head - other.tail;
        tail = 0;
        qlength = other.qlength;
        queue = new int[qlength];
        
        for (int i = other.tail;i < other.head;i++){
            
            queue[i - other.tail] = other.queue[i];
        }
    }
    return *this;
}
//outputting the queue
ostream& operator<< (ostream& os, const IntegerQueue &other)
{
    os << "{";
    if(!other.empty()){
        os << other.queue[other.tail];
        for(int i = (other.tail+1);i < other.head;i++){
            os << "," << other.queue[i];
        }
    }
    os << "}";
    return os;
}
