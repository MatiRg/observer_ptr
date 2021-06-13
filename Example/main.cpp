/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
*/
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
