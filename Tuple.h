#include <iostream>
#include <cmath>
#include <vector>
template <class T>
class TupleData {
public:
    
    TupleData(int n) {DatStuff =  std::vector<T>(n); uses = 0;}
    TupleData(const T *p,int n){DatStuff.assign(p,p+n);uses = 0;}
    TupleData(const TupleData& other) {DatStuff.assign(other.DatStuff.begin(),other.DatStuff.end()); uses = 0;}
    ~TupleData()
    {
        decrementUse();
        if(uses == 0)
        {
            delete this;
        }
    }
    // size 🐞
    int size() const { return DatStuff.size(); }
    
    //Setters
    void useCount(int u) {uses = u;}
    
    //Getters
    int useCount() const {return uses;}
    
    void incrementUse() { uses++; }
    void decrementUse()
    {
        uses--;
        if(uses==0)
            delete this;
    }
    
    T& operator[](int i);
    const T& operator[](int i) const;
    bool operator==(const TupleData<T>& other) const;
    bool operator!=(const TupleData<T>& other) const;
    
private:
    int cardinality;
    int uses;
    std::vector<T> DatStuff;
    static T a;
};

template<class T>
class Tuple {
public:
    Tuple(int n):data(new TupleData<T>(n)) { data->incrementUse(); }
    Tuple(const T *p, int n):data(new TupleData<T>(p,n)) { data->incrementUse(); }
    Tuple(const Tuple& other):data(other.data) { data->incrementUse(); }
    ~Tuple() { data->decrementUse(); }
    
    int size() const { return data->size(); }
    T magnitude() const { return sqrt((*this) * (*this)); }
    
    const Tuple<T>& operator=(const Tuple<T>& other);
    bool operator==(const Tuple<T>& other) const;
    bool operator!=(const Tuple<T>& other) const;
    T& operator[](int i);
    const T& operator[](int i) const;
    
#ifdef DEBUG
    TupleData<T>& implementation() const { return *data; }
#endif
    
private:
    TupleData<T> *data;
    static T a;
};

// !=
template <class T>
bool TupleData<T>::operator!=(const TupleData<T>& other) const
{
    return !(*this == other);
}
//!=
template <class T>
bool Tuple<T>::operator!=(const Tuple<T>& other) const
{
    return !(*this == other);
}
// =
template <class T>
const Tuple<T>& Tuple<T>::operator=(const Tuple<T>& other)
{
    data -> decrementUse();
    data = other.data;
    other.data -> incrementUse();
    return *this;
}
// ==
template <class T>
bool Tuple<T>::operator==(const Tuple& other) const
{
    if (this->size() != other.size())
    {
        return false;
    }
    for (int p = 0; p < this->size();p++)
    {
        if ((*data)[p] != (*other.data)[p])
        {
            return false;
        }
    }
    return true;
}
// [1]
template <class T>
T& TupleData<T>::operator[](int i)
{
    return DatStuff[i];
}
//[2]
template <class T>
const T& TupleData<T>::operator[](int u) const
{
    
    if ( u < 0 || this->size())
    {
        a = 0;
        return a;
    }
    return DatStuff[u];
}
// [3]
template <class T>
T& Tuple<T>::operator[](int t)
{
    //outside of the bounds
    if(t < 0 || this->size() <= t)
    {
        a = 0;
        return a;
    }
    if (this->data->useCount() > 1)
    {
        TupleData<T> * noo = new TupleData<T>(*data);
        data->decrementUse();
        data = noo;
        data->incrementUse();
    }
    return (*data)[t];
}
//[4]
template <class T>
const T& Tuple<T>::operator[](int p)const
{
    if ( p >= data->size())
    {
        a = 0;
        return a;
    }
    return (*data)[p];
}
// +
template<class T> Tuple<T>
operator+(const Tuple<T>& a, const Tuple<T>& b)
{
    int noosize = (a.size() > b.size()) ? a.size() : b.size();
    Tuple<T> nooTuple(noosize);
    for (int p = 0; p < noosize; p++)
    {
        nooTuple[p] = a[p] + b[p];
    }
    if (a.size() > b.size())
    {
        for (int p = b.size(); p < a.size(); p++)
        {
            nooTuple[p] = a[p];
        }
    }
    else
    {
        for (int p = a.size();p < b.size(); p++)
        {
            nooTuple[p] = b[p];
        }
    }
    return nooTuple;
}
// +=
template<class T>
const Tuple<T> operator+=( Tuple<T>& a, const Tuple<T>& b)
{
    return a = (a+b);
}
// TupleA * TupleB
template<class T>
T operator*(const Tuple<T>& a, const Tuple<T>& b)
{
    T product = 0;
    for(int p = 0; p < ((a.size() < b.size()) ? a.size(): b.size()); p++)
    {
        product += (a[p] * b[p]);
    }
    return product;
}
// Tuple A * b
template<class T>
Tuple<T> operator*(const Tuple<T>& a, const T& b)
{
    Tuple<T> noothing(a.size());
    for(int p = 0; p < a.size();p++)
    {
        noothing[p] = a[p] * b;
    }
    return noothing;
}
// TupleB * a
template<class T>
Tuple<T> operator*(const T& a, const Tuple<T>& b)
{
    return b * a;
}
//*=
template <class T>
const Tuple<T>& operator*=(Tuple<T>& a, const T& b)
{
    return a = (a * b);
    
}


template <class T>
T Tuple<T>::a = 0;

template <class T>
T TupleData<T>::a = 0;

