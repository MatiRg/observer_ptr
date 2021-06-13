// Mateusz Rugor
// MIT License
#pragma once
#include <cstddef>
#include <utility>
#include <type_traits>

template<class T>
class observer_ptr final
{
public:
    using element_type = T;
public:
    observer_ptr() {}

    observer_ptr(std::nullptr_t) {}

    explicit observer_ptr(element_type* p): ptr(p) {}

    template<class T2, std::enable_if_t<std::is_convertible<T2*, element_type*>::value, bool> = true>
    observer_ptr(observer_ptr<T2> other): ptr(other.ptr) {}

    observer_ptr(const observer_ptr<element_type>& other): ptr(other.ptr) {}

    observer_ptr(observer_ptr<element_type>&& other): ptr(std::move(other.ptr)) {}

    ~observer_ptr() = default;

    observer_ptr<element_type>& operator=(std::nullptr_t)
    {
        reset();
        return *this;
    }

    observer_ptr<element_type>& operator=(element_type* p)
    {
        reset(p);
        return *this;
    }

    // Pass by Value!
    observer_ptr<element_type>& operator=(observer_ptr<element_type> other)
    {
        // copy-and-swap idiom
        swap(*this, other);
        return *this;
    }

    observer_ptr<element_type>& operator=(observer_ptr<element_type>&& other)
    {
         ptr = std::move(other.ptr);
         return *this;
    }

    element_type* release()
    {
        element_type* tmp = ptr;
        reset();
        return tmp;
    }

    void reset(element_type* p = nullptr)
    {
        ptr = p;
    }

    element_type* get() const
    {
        return ptr;
    }

    explicit operator bool() const
    {
        return ptr != nullptr;
    }

    element_type& operator*() const
    {
        return *ptr;
    }

    element_type* operator->() const
    {
        return ptr;
    }

    explicit operator element_type*() const
    {
        return ptr;
    }

    bool operator!() const
    {
        return !ptr;
    }

    void swap(observer_ptr<element_type>& other)
    {
        swap(*this, other);
    }

    friend void swap(observer_ptr<element_type>& first, observer_ptr<element_type>& second)
    {
        // For ADL
        using std::swap;
        swap(first.ptr, second.ptr);
    }

    friend bool operator==(const observer_ptr<element_type>& lhs, const observer_ptr<element_type>& rhs)
    {
        return lhs.ptr == rhs.ptr;
    }

    friend bool operator!=(const observer_ptr<element_type>& lhs, const observer_ptr<element_type>& rhs)
    {
        return lhs.ptr != rhs.ptr;
    }

    friend bool operator<(const observer_ptr<element_type>& lhs, const observer_ptr<element_type>& rhs)
    {
        return lhs.ptr < rhs.ptr;
    }

    friend bool operator>(const observer_ptr<element_type>& lhs, const observer_ptr<element_type>& rhs)
    {
        return lhs.ptr > rhs.ptr;
    }

    friend bool operator<=(const observer_ptr<element_type>& lhs, const observer_ptr<element_type>& rhs)
    {
        return lhs.ptr <= rhs.ptr;
    }

    friend bool operator>=(const observer_ptr<element_type>& lhs, const observer_ptr<element_type>& rhs)
    {
        return lhs.ptr >= rhs.ptr;
    }
private:
    element_type* ptr{};
};

template<class T>
observer_ptr<T> make_observer(T* p)
{
    return observer_ptr<T>{p};
}

namespace std
{
    template<class T>
    struct hash<observer_ptr<T>>
    {
        size_t operator()(const observer_ptr<T>& p) const
        {
            return hash<T*>()(p.get());
        }
    };
}

