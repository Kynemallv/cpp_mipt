#include <iostream>
#include <Tracer_lib/tracer.h>

constexpr bool kDebug{false};

template <typename T>
class allocator
{
public:
    T *allocate(int n);
    void deallocate(T *p) { free(p); }

    void construct(T *p, const T &v) { new (p) T{v}; }
    void destroy(T *p) { p->~T(); }
};

template <typename T>
T *allocator<T>::allocate(int n)
{
    T *p = (T *)malloc(n * sizeof(T));
    if (!p)
        throw std::bad_alloc();
    
    return p;
}

template <typename T, typename A = allocator<T>>
class Vector
{
    A alloc;
    int sz;
    T *elem;
    int space;

public:
    Vector() : sz{0}, elem{nullptr}, space { 0 } { TRACE_FUNC; };  // default constructor

    explicit Vector(int s);                                        // arg constructor

    Vector(std::initializer_list<T> l);                            // args constructor

    Vector(const Vector &);                                        // copy constructor
    Vector &operator=(const Vector &);                             // copy =

    Vector &operator=(Vector &&);                                  // move =
    Vector(const Vector &&);                                       // move constructor

    ~Vector();                                                     // destructor

    T &at(int);
    const T &at(int) const;

    T &operator[](int n) { return elem[n]; };
    const T &operator[](int n) const { return elem[n]; };

    int size() const { return sz; };
    int capacity() const { return space; };

    void resize(int newsize, T val = T());
    void push_back(const T &d);
    void reserve(int newalloc);
private:
    void free_resources();
}; 

template <typename T, typename A>
Vector<T, A>::Vector(int s) 
{
    if (kDebug)
        TRACE_FUNC;
    
    if (s < 0)
        throw std::logic_error("s must be not negative");

    try
    {
        sz = s;
        elem = alloc.allocate(s);
        space = s;

        for (int i = 0; i < sz; ++i)
            alloc.construct(&elem[i], T());
    }
    catch(...)
    {
        this->free_resources();
        throw;
    }
}; 

template <typename T, typename A>
Vector<T, A>::Vector(const Vector<T, A> &arg)
    : sz{arg.size()}, elem{alloc.allocate(arg.size())}, space{arg.size()}
{
    if (kDebug)
        TRACE_FUNC;
    
    try
    {
        for (int i = 0; i < sz; ++i)
            alloc.construct(&elem[i], arg.elem[i]);
    }
    catch(...)
    {
       this->free_resources;
       throw; 
    }
    
}

template <typename T, typename A>
Vector<T, A>::Vector(std::initializer_list<T> l)
{
    if (kDebug)
        TRACE_FUNC;

    try
    {
        sz = l.size();
        elem = alloc.allocate(l.size());
        space = l.size();

        int i{0};
        for (auto el : l)
        {
            alloc.construct(&elem[i], el);
            ++i;
        }
    }
    catch(...)
    {
        this->free_resources();
        throw;
    }
};

template <typename T, typename A>
Vector<T, A>::Vector(const Vector<T, A> &&a)
    : sz{a.sz}, elem{a.elem}, space{a.sz}
{
    TRACE_FUNC;

    a.sz = 0;
    a.space = 0;
    a.elem = nullptr;
}

template <typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(Vector &&a)
{ 
    this->free_resources();

    elem = a.elem;
    sz = a.sz;
    space = a.space;

    a.elem = nullptr;
    a.sz = 0;
    a.space = 0;

    return *this;
}

template <typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(const Vector &a)
{
    if (this == &a)
        return *this;

    if (a.sz <= space)
    {
        for (int i = 0; i < a.sz; ++i)
            elem[i] = a.elem[i];
        sz = a.sz;
        return *this;
    }

    T *p = alloc.allocate(a.sz);
    for (int i = 0; i < a.sz; ++i)
        alloc.construct(&p[i], a.elem[i]);

    this->free_resources();
    elem = p;
    sz = a.sz;
    space = a.sz;
    return *this;
}

template <typename T>
bool is_vector(T *t) { return false; }

template <typename T, typename A>
bool is_vector(Vector<T, A> *v) { return true; }

template <typename T, typename A>
void Vector<T, A>::free_resources()
{
    if(is_vector(elem))
    {
        for (int i = 0; i < sz; ++i)
            alloc.destroy(&elem[i]);          
    }

    if (elem)
        alloc.deallocate(elem);
}

template <typename T, typename A>
Vector<T, A>::~Vector()
{
    if (kDebug)
        TRACE_FUNC;

    this->free_resources();
}

template <typename T, typename A>
T &Vector<T, A>::at(int n)
{
    if (n <= 0 || sz <= n)
        throw std::out_of_range("");
    return elem[n];
}

template <typename T, typename A>
const T &Vector<T, A>::at(int n) const
{
    if (n <= 0 || sz <= n)
        throw std::out_of_range("");
    return elem[n];
}

template <typename T, typename A>
void Vector<T, A>::reserve(int newalloc)
{
    if (newalloc < 0)
        throw std::logic_error("newalloc must be not negative");
    
    if (newalloc <= space)
        return;

    T *p = alloc.allocate(newalloc);
    for (int i = 0; i < sz; ++i)
        alloc.construct(&p[i], elem[i]);

    this->free_resources();
    elem = p;
    space = newalloc;
}

template <typename T, typename A>
void Vector<T, A>::push_back(const T &val)
{
    if (space == 0)
        reserve(sizeof(T));
    else if (sz == space)
        reserve(2 * space);

    alloc.construct(&elem[sz], val);
    ++sz;
}

template <typename T, typename A>
void Vector<T, A>::resize(int newsize, T val)
{
    if (newsize < 0)
        throw std::logic_error("newsize must be not negative");

    reserve(newsize);
    for (int i = sz; i < newsize; ++i)
        alloc.construct(&elem[i], val);
    for (int i = newsize; i < sz; ++i)
        alloc.destroy(&elem[i]);
    sz = newsize;
}