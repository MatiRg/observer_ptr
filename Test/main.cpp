#include <iostream>
#include <unordered_map>
#include "../Include/observer_ptr.hpp"

struct Base
{
    virtual ~Base() {}
};

struct Derrivied: public Base
{
};

struct Other
{
};

int main()
{
    int a = 7, b = 3;
    observer_ptr<int> o1 = make_observer(&a);
    observer_ptr<int> o2 = make_observer(&b);
    //
    if( o1 == o2 )
    {
    }
    if( !o1 )
    {
    }
    if( o2 )
    {
    }
    int* old{o1};
    //int* old2 = o2; Bad
    int c = *o2;
    observer_ptr<int> o3{&c};
    o1 = nullptr;
    o1 = &b;
    //
    swap(o1, o2);
    //
    Base aa;
    Derrivied bb;
    Other cc;
    observer_ptr<Base> x1{&aa};
    observer_ptr<Base> x2{&bb};
    //observer_ptr<Base> x3{&cc}; Bad
    x1 = &bb;
    //
    std::unordered_map<int, observer_ptr<Base>> SomeMap;

    return 0;
}
